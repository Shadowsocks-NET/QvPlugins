#pragma once

#include "handlers/KernelHandler.hpp"
#include "socks2http/HttpProxy.hpp"

#include <QProcess>

inline QUuid NAIVE_KERNEL_ID = QUuid{ "39e1043f-7c2f-4287-9030-214bc62f94d8" };

class NaiveProxyKernel : public PluginKernel
{
  public:
    explicit NaiveProxyKernel();
    virtual ~NaiveProxyKernel() = default;
    bool Start() override;
    bool Stop() override;
    void SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &options, const QJsonObject &settings) override;
    QUuid KernelId() const override
    {
        return NAIVE_KERNEL_ID;
    }

  private:
    QString protocol;
    QString host;
    QString username;
    QString password;
    QString listenIp;
    bool padding;
    int port;
    QProcess process;
    //
    QString sni;

  private:
    bool isStarted = false;
    int socksPort = 0;
    int httpPort = 0;
    Qv2rayPlugin::Utils::HttpProxy httpProxy;
};

class NaiveKernelInterface : public PluginKernelInterface
{
  public:
  public:
    QList<KernelInfo> GetKernels() const override
    {
        KernelInfo naive;
        naive.Create = []() { return std::make_unique<NaiveProxyKernel>(); };
        naive.Id = NAIVE_KERNEL_ID;
        naive.Name = "Trojan-Go";
        naive.SupportedProtocols = { "trojan", "trojan-go" };
        return QList<KernelInfo>{} << naive;
    }
};
