#pragma once

#include "QvPlugin/Handlers/KernelHandler.hpp"
#include "QvPlugin/Socksify/HttpProxy.hpp"

#include <QProcess>

inline QUuid NAIVE_KERNEL_ID = QUuid{ "39e1043f-7c2f-4287-9030-214bc62f94d8" };

class NaiveProxyKernel : public Qv2rayPlugin::Kernel::PluginKernel
{
    Q_OBJECT
  public:
    explicit NaiveProxyKernel();
    virtual ~NaiveProxyKernel() = default;
    virtual void Start() override;
    virtual bool Stop() override;
    virtual void SetConnectionSettings(const QMap<Qv2rayPlugin::Kernel::KernelOptionFlags, QVariant> &settings, const IOConnectionSettings &connectionInfo) override;
    virtual bool PrepareConfigurations() override;
    virtual KernelId GetKernelId() const override
    {
        return KernelId{ "naiveproxy-kernel" };
    }
  signals:
    void OnCrashed(const QString &);
    void OnLog(const QString &);
    void OnStatsAvailable(StatisticsObject);

  private:
    QString protocol;
    QString host;
    QString username;
    QString password;
    QString listenIp;
    bool padding;
    int port;
    QProcess process;
    QString sni;

  private:
    bool isStarted = false;
    int socksPort = 0;
    int httpPort = 0;
    Qv2rayPlugin::Utils::HttpProxy httpProxy;
};

class NaiveKernelInterface : public Qv2rayPlugin::Kernel::IKernelHandler
{
  public:
    virtual QList<Qv2rayPlugin::Kernel::KernelFactory> PluginKernels() const override
    {
        Qv2rayPlugin::Kernel::KernelFactory naive;
        naive.Create = []() { return std::make_unique<NaiveProxyKernel>(); };
        naive.Id = KernelId{ "naiveproxy-kernel" };
        naive.Name = "NaiveProxy";
        naive.SupportedProtocols = { "naiveproxy" };
        return QList<Qv2rayPlugin::Kernel::KernelFactory>{} << naive;
    }
};
