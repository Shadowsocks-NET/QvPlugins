#pragma once
#include "QvPlugin/Handlers/LatencyTestHandler.hpp"
#include "uvw.hpp"

#define coco_enter(c)                                                                                                                                                    \
    switch (details::coroutine_ref _coro_value = c)                                                                                                                      \
    case -1:                                                                                                                                                             \
        if (_coro_value)                                                                                                                                                 \
        {                                                                                                                                                                \
            goto terminate_coroutine;                                                                                                                                    \
        terminate_coroutine:                                                                                                                                             \
            _coro_value = -1;                                                                                                                                            \
            goto bail_out_of_coroutine;                                                                                                                                  \
        bail_out_of_coroutine:                                                                                                                                           \
            break;                                                                                                                                                       \
        }                                                                                                                                                                \
        else                                                                                                                                                             \
        case 0:

#define __co_yield_impl(n)                                                                                                                                               \
    for (_coro_value = (n);;)                                                                                                                                            \
        if (_coro_value == 0)                                                                                                                                            \
        {                                                                                                                                                                \
            case (n):; break;                                                                                                                                            \
        }                                                                                                                                                                \
        else                                                                                                                                                             \
            switch (_coro_value ? 0 : 1)                                                                                                                                 \
                for (;;)                                                                                                                                                 \
                case -1:                                                                                                                                                 \
                    if (_coro_value)                                                                                                                                     \
                        goto terminate_coroutine;                                                                                                                        \
                    else                                                                                                                                                 \
                        for (;;)                                                                                                                                         \
                        case 1:                                                                                                                                          \
                            if (_coro_value)                                                                                                                             \
                                goto bail_out_of_coroutine;                                                                                                              \
                            else                                                                                                                                         \
                            case 0:

#define coco_yield __co_yield_impl(__LINE__)
#define coro(f) [this, ptr = (std::enable_shared_from_this<T>::shared_from_this())](auto &&e, auto &&h) { f(std::forward<decltype(e)>(e), std::forward<decltype(h)>(h)); }

namespace details
{
    struct coroutine_ref;
    struct coroutine
    {
        // clang-format off
        coroutine() : line_(0){};
        bool await_ready() const { return line_ == -1; }
        // clang-format on

      private:
        friend struct coroutine_ref;
        int line_;
    };

    struct coroutine_ref
    {
        // clang-format off
        coroutine_ref(coroutine &c) : line_(c.line_), modified_(false) { };
        ~coroutine_ref() { if (!modified_) line_ = -1; }
        operator int() const { return line_; }
        int &operator=(int v) { modified_ = true; return line_ = v; }
        // clang-format on

      private:
        void operator=(coroutine_ref const &);
        int &line_;
        bool modified_;
    };

} // namespace details

template<typename T>
class CommonDNSBasedAsyncLatencyTestEngine
    : public details::coroutine
    , public std::enable_shared_from_this<T>
    , public Qv2rayPlugin::Latency::LatencyTestEngine
{
  public:
    static constexpr int TOTAL_TEST_COUNT = 3;
    CommonDNSBasedAsyncLatencyTestEngine() = default;
    virtual ~CommonDNSBasedAsyncLatencyTestEngine() = default;

  protected:
    int isAddr(const QString &address, int port)
    {
        auto host = address.toStdString();
        if (uv_ip4_addr(host.data(), port, reinterpret_cast<sockaddr_in *>(&storage)) == 0)
        {
            return AF_INET;
        }
        if (uv_ip6_addr(host.data(), port, reinterpret_cast<sockaddr_in6 *>(&storage)) == 0)
        {
            return AF_INET6;
        }
        return -1;
    }

  protected:
    virtual void Prepare() = 0;
    virtual void StartTestAsync() = 0;

  public:
    virtual void TestLatencyAsync(std::shared_ptr<uvw::Loop> loop, const Qv2rayPlugin::Latency::LatencyTestRequest &req) override
    {
        this->loop = loop;
        request = req;
        Prepare();
        if (errored)
            emit OnLatencyTestFinishedSignal(req.id, response);

        response = Qv2rayPlugin::Latency::LatencyTestResponse();
        response.total = TOTAL_TEST_COUNT;
        response.avg = 0;
        response.worst = 0;
        response.best = 0;

        if ((af = isAddr(req.host, req.port)), af == -1)
        {
            // If the requested address is not a valid IP.
            getAddrHandle = loop->resource<uvw::GetAddrInfoReq>();
            sprintf(digitBuffer, "%d", req.port);
            LookupDNS(0, 0);
        }
        else
        {
            StartTestAsync();
        }
    }

    template<typename E, typename H>
    void LookupDNS(E &&e, H &&h)
    {
        coco_enter(*this)
        {
            if (getAddrHandle)
            {
                getAddrHandle->once<uvw::ErrorEvent>(coro(LookupDNS));
                getAddrHandle->once<uvw::AddrInfoEvent>(coro(LookupDNS));
                coco_yield return getAddrHandle->addrInfo(request.host.toStdString(), digitBuffer);
                coco_yield if constexpr (std::is_same_v<uvw::AddrInfoEvent, std::remove_reference_t<E>>)
                {
                    if (GetAddrInfoCallback(e) != 0)
                    {
                        response.error = QObject::tr("DNS not resolved");
                        response.avg = LATENCY_TEST_VALUE_ERROR;
                        h.clear();
                        errored = true;
                        return;
                    }
                }
                else // should be else?
                {
                    if constexpr (std::is_same_v<uvw::ErrorEvent, std::remove_reference_t<E>>)
                    {
                        response.error = QObject::tr("DNS not resolved");
                        response.avg = LATENCY_TEST_VALUE_ERROR;
                        h.clear();
                        errored = true;
                        return;
                    }
                }
            }
        }

        StartTestAsync();

        if (getAddrHandle)
            getAddrHandle->clear();
    }

    int GetAddrInfoCallback(uvw::AddrInfoEvent &e)
    {
        struct addrinfo *rp = nullptr;
        for (rp = e.data.get(); rp != nullptr; rp = rp->ai_next)
        {
            if (rp->ai_family == AF_INET)
            {
                if (rp->ai_family == AF_INET)
                {
                    af = AF_INET;
                    memcpy(&storage, rp->ai_addr, sizeof(struct sockaddr_in));
                }
                else if (rp->ai_family == AF_INET6)
                {
                    af = AF_INET6;
                    memcpy(&storage, rp->ai_addr, sizeof(struct sockaddr_in6));
                }
                break;
            }
        }
        if (rp == nullptr)
        {
            // fallback: if we can't find prefered AF, then we choose alternative.
            for (rp = e.data.get(); rp != nullptr; rp = rp->ai_next)
            {
                if (rp->ai_family == AF_INET)
                {
                    af = AF_INET;
                    memcpy(&storage, rp->ai_addr, sizeof(struct sockaddr_in));
                }
                else if (rp->ai_family == AF_INET6)
                {
                    af = AF_INET6;
                    memcpy(&storage, rp->ai_addr, sizeof(struct sockaddr_in6));
                }
                break;
            }
        }
        if (rp)
            return 0;
        return -1;
    }

  protected:
    bool errored = false;
    int af = AF_INET;

    std::shared_ptr<uvw::Loop> loop;
    Qv2rayPlugin::Latency::LatencyTestResponse response;
    Qv2rayPlugin::Latency::LatencyTestRequest request;
    sockaddr_storage storage;
    char digitBuffer[20] = { 0 };
    std::shared_ptr<uvw::GetAddrInfoReq> getAddrHandle;
};
