#include "TCPLatencyTester.hpp"

constexpr int TCP_CONNECTION_TIMEOUT_SECS = 5;

int getSocket(int af, int socktype, int proto)
{
    uv_os_sock_t fd;
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
    if ((fd = socket(af, socktype, proto)) == INVALID_SOCKET)
    {
        return 0;
    }
    // Set TCP connection timeout per-socket level.
    // See [https://github.com/libuv/help/issues/54] for details.
#if defined(_WIN32) && !defined(__SYMBIAN32__)
#ifndef TCP_MAXRT
#define TCP_MAXRT 5
#endif
    setsockopt(fd, IPPROTO_TCP, TCP_MAXRT, (char *) &TCP_CONNECTION_TIMEOUT_SECS, sizeof(TCP_CONNECTION_TIMEOUT_SECS));
#elif defined(__APPLE__)
    // (billhoo) MacOS uses TCP_CONNECTIONTIMEOUT to do so.
    setsockopt(fd, IPPROTO_TCP, TCP_CONNECTIONTIMEOUT, (char *) &TCP_CONNECTION_TIMEOUT_SECS, sizeof(TCP_CONNECTION_TIMEOUT_SECS));
#else // Linux like systems
    uint32_t conn_timeout_ms = TCP_CONNECTION_TIMEOUT_SECS * 1000;
    setsockopt(fd, IPPROTO_TCP, TCP_USER_TIMEOUT, (char *) &conn_timeout_ms, sizeof(conn_timeout_ms));
#endif
    return (int) fd;
}

TCPTestEngine::TCPTestEngine()
{
}

void TCPTestEngine::Prepare()
{
}

void TCPTestEngine::StartTestAsync()
{
    for (auto i = 0; i < response.total; i++)
    {
        auto tcpClient = loop->resource<uvw::TCPHandle>();
        tcpClient->open(getSocket(af, SOCK_STREAM, IPPROTO_TCP));
        tcpClient->once<uvw::ErrorEvent>(
            [ptr = shared_from_this()](const uvw::ErrorEvent e, uvw::TCPHandle &h)
            {
                ptr->response.failed++;
                ptr->response.error = e.what();
                h.clear();
                h.close();
                ptr->CheckAndReturn();
            });
        tcpClient->once<uvw::ConnectEvent>(
            [thisptr = shared_from_this(), start = system_clock::now()](auto &, auto &h)
            {
                system_clock::time_point end = system_clock::now();
                auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                long ms = milliseconds.count();
                thisptr->response.succeeded++;
                thisptr->response.avg += ms;
#undef max
#undef min
                thisptr->response.worst = std::max(thisptr->response.worst, ms);
                thisptr->response.best = std::min(thisptr->response.best, ms);
                h.clear();
                h.close();
                thisptr->CheckAndReturn();
            });
        tcpClient->connect(reinterpret_cast<const sockaddr &>(storage));
    }
}

void TCPTestEngine::CheckAndReturn()
{
    if (response.failed + response.succeeded != response.total)
        return;

    if (response.failed == response.total)
        response.avg = LATENCY_TEST_VALUE_ERROR;
    else
        response.error.clear(), response.avg = response.avg / response.succeeded;

    emit OnLatencyTestFinishedSignal(request.id, response);
}
