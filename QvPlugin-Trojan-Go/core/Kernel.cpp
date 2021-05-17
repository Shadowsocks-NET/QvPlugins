#include "Kernel.hpp"

#include "TrojanGoPlugin.hpp"

#include <QFile>

QvTrojanGoPluginKernel::QvTrojanGoPluginKernel() : PluginKernel()
{
    connect(&process, &QProcess::channelReadyRead, this, &QvTrojanGoPluginKernel::OnProcessOutputReadyRead);
    connect(&process, &QProcess::stateChanged, this, &QvTrojanGoPluginKernel::OnProcessClosed);
}

bool QvTrojanGoPluginKernel::Start()
{
    const auto executablePath = QvTrojanGoPluginInstance->GetSettings()["kernelPath"].toString();
    if (!QFile::exists(executablePath))
    {
        QvTrojanGoPluginInstance->PluginErrorMessageBox(tr("Stupid Configuration?"),
                                                        tr("We cannot find your Trojan-Go kernel. Please configure it in the plugin settings."));
        return false;
    }

    process.setProgram(executablePath);
    process.setArguments({ "-url", url, "-url-option", QString(mux ? "mux=true;listen=" : "mux=false;listen=") + listenAddress + ":" + QString::number(listenPort) });
    process.start();
    process.waitForStarted();
    isStarted = true;
    return true;
}

void QvTrojanGoPluginKernel::SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &settings, const QJsonObject &connectionInfo)
{
    listenAddress = settings[KERNEL_LISTEN_ADDRESS].toString();
    listenPort = settings[KERNEL_HTTP_ENABLED].toBool() ? settings[KERNEL_HTTP_PORT].toInt() : settings[KERNEL_SOCKS_PORT].toInt();
    url = TrojanGoSerializer().Serialize(PluginOutboundInfo{ "Connection", "trojan-go", connectionInfo, {} }).value();

    TrojanGoShareLinkObject obj;
    obj.loadJson(connectionInfo);
    mux = obj.mux;
}

void QvTrojanGoPluginKernel::OnProcessClosed()
{
    if (isStarted)
    {
        if (process.state() == QProcess::NotRunning)
            emit OnCrashed(tr("Trojan-Go Kernel Crashed."));
    }
}

void QvTrojanGoPluginKernel::OnProcessOutputReadyRead(int)
{
    emit OnKernelLog(process.readAll());
}

bool QvTrojanGoPluginKernel::Stop()
{
    isStarted = false;
    process.close();
    process.waitForFinished();
    return true;
}
