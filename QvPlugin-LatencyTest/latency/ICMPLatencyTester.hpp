#pragma once

#include "DNSBase.hpp"

class ICMPTestEngine : public CommonDNSBasedAsyncLatencyTestEngine<ICMPTestEngine>
{
    Q_OBJECT
  public:
    virtual ~ICMPTestEngine();
    using CommonDNSBasedAsyncLatencyTestEngine<ICMPTestEngine>::CommonDNSBasedAsyncLatencyTestEngine;

  protected:
    virtual void Prepare() override;
    virtual void StartTestAsync() override;

  signals:
    void OnLatencyTestFinishedSignal(const ConnectionId &, const Qv2rayPlugin::Latency::LatencyTestResponse &) override;

  private:
    bool checkAndFinalize();

#ifdef Q_OS_UNIX
    // unix
    void deinit();
    // number incremented with every echo request packet send
    unsigned short seq = 1;
    // socket
    int socketId = -1;
    std::shared_ptr<uvw::TimerHandle> timeoutTimer;
    std::shared_ptr<uvw::PollHandle> pollHandle;
    std::vector<timeval> startTimevals;
#elif defined(Q_OS_WIN)
  private:
    void pingImpl();

  private:
    uint64_t timeout = 3000;
    std::shared_ptr<uvw::TimerHandle> waitHandleTimer;
#endif
};
