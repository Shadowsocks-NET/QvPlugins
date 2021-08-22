#pragma once
#include "QvPlugin/Handlers/KernelHandler.hpp"

#include <QProcess>

class QvTrojanGoPluginKernel : public Qv2rayPlugin::Kernel::PluginKernel
{
    Q_OBJECT

  public:
    QvTrojanGoPluginKernel();
    void SetConnectionSettings(const QMap<Qv2rayPlugin::Kernel::KernelOptionFlags, QVariant> &settings, const IOConnectionSettings &connectionInfo) override;
    void Start() override;
    bool Stop() override;
    virtual bool PrepareConfigurations() override;
    virtual KernelId GetKernelId() const override
    {
        return KernelId{ "trojan-go-kernel" };
    }

  signals:
    void OnCrashed(const QString &);
    void OnLog(const QString &);
    void OnStatsAvailable(StatisticsObject);

  private slots:
    void OnProcessOutputReadyRead(int);
    void OnProcessClosed();

  private:
    QString url;
    QString listenAddress;
    QProcess process;
    bool mux;
    int listenPort;
    bool isStarted;
};

class TrojanGoPluginKernelInterface : public Qv2rayPlugin::Kernel::IKernelHandler
{
  public:
    virtual QList<Qv2rayPlugin::Kernel::KernelFactory> PluginKernels() const override
    {
        Qv2rayPlugin::Kernel::KernelFactory trojan_go;
        trojan_go.Create = []() { return std::make_unique<QvTrojanGoPluginKernel>(); };
        trojan_go.Id = KernelId{ "trojan-go-kernel" };
        trojan_go.Name = "Trojan-Go";
        trojan_go.SupportedProtocols = { "trojan", "trojan-go" };
        return QList<Qv2rayPlugin::Kernel::KernelFactory>{} << trojan_go;
    }
};
