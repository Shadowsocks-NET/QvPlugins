#include "Kernel.hpp"

#include "TrojanGoPlugin.hpp"

#include <QFile>

QvTrojanGoPluginKernel::QvTrojanGoPluginKernel() : PluginKernel()
{
    connect(&process, &QProcess::channelReadyRead, this, &QvTrojanGoPluginKernel::OnProcessOutputReadyRead);
    connect(&process, &QProcess::stateChanged, this, &QvTrojanGoPluginKernel::OnProcessClosed);
}

void QvTrojanGoPluginKernel::Start()
{
    const auto executablePath = QvTrojanGoPlugin::PluginInstance->GetSettings()["kernelPath"].toString();
    if (!QFile::exists(executablePath))
    {
        QvTrojanGoPlugin::ShowMessageBox(tr("Stupid Configuration?"), tr("We cannot find your Trojan-Go kernel. Please configure it in the plugin settings."));
        return;
    }

    process.setProgram(executablePath);
    process.setArguments({ "-url", url, "-url-option", QString(mux ? "mux=true;listen=" : "mux=false;listen=") + listenAddress + ":" + QString::number(listenPort) });
    process.start();
    process.waitForStarted();
    isStarted = true;
    return;
}

void QvTrojanGoPluginKernel::SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &settings, const IOConnectionSettings &connectionInfo)
{
    listenAddress = settings[KERNEL_LISTEN_ADDRESS].toString();
    listenPort = settings[KERNEL_HTTP_ENABLED].toBool() ? settings[KERNEL_HTTP_PORT].toInt() : settings[KERNEL_SOCKS_PORT].toInt();
    url = TrojanGoSerializer().Serialize("", connectionInfo).value();

    TrojanGoShareLinkObject obj;
    obj.loadJson(connectionInfo.protocolSettings);
    obj.server = connectionInfo.address;
    obj.port = connectionInfo.port.from;
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
    emit OnLog(process.readAll());
}

bool QvTrojanGoPluginKernel::Stop()
{
    isStarted = false;
    process.close();
    process.waitForFinished();
    return true;
}

bool QvTrojanGoPluginKernel::PrepareConfigurations()
{
    return true;
}
