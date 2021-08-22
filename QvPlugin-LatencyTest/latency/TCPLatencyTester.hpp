#pragma once

#include "DNSBase.hpp"

class TCPTestEngine : public CommonDNSBasedAsyncLatencyTestEngine<TCPTestEngine>
{
    Q_OBJECT
  public:
    virtual ~TCPTestEngine() = default;
    TCPTestEngine();
    using CommonDNSBasedAsyncLatencyTestEngine<TCPTestEngine>::CommonDNSBasedAsyncLatencyTestEngine;

  signals:
    void OnLatencyTestFinishedSignal(const ConnectionId &, const Qv2rayPlugin::Latency::LatencyTestResponse &) override;

  protected:
    virtual void Prepare() override;
    virtual void StartTestAsync() override;

  private:
    void CheckAndReturn();
};
