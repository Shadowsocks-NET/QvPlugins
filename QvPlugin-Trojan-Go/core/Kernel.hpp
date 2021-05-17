#pragma once
#include "handlers/KernelHandler.hpp"

#include <QProcess>

inline QUuid NAIVE_KERNEL_ID = QUuid{ "39e1043f-7c2f-4287-9030-214bc62f94d8" };

class QvTrojanGoPluginKernel : public PluginKernel
{
    Q_OBJECT
  public:
    explicit QvTrojanGoPluginKernel();
    /// Kernel related operations
    void SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &settings, const QJsonObject &connectionInfo) override;
    bool Start() override;
    bool Stop() override;
    QUuid KernelId() const override
    {
        return NAIVE_KERNEL_ID;
    }

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

class TrojanGoPluginKernelInterface : public PluginKernelInterface
{
  public:
    QList<KernelInfo> GetKernels() const override
    {
        KernelInfo trojan_go;
        trojan_go.Create = []() { return std::make_unique<QvTrojanGoPluginKernel>(); };
        trojan_go.Id = NAIVE_KERNEL_ID;
        trojan_go.Name = "Trojan-Go";
        trojan_go.SupportedProtocols = { "trojan", "trojan-go" };
        return QList<KernelInfo>{} << trojan_go;
    }
};
