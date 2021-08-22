#include "Kernel.hpp"

#include "QvPlugin/PluginInterface.hpp"
#include "SimplePlugin.hpp"

#include <QFile>

NaiveProxyKernel::NaiveProxyKernel() : PluginKernel()
{
    process.setProcessChannelMode(QProcess::MergedChannels);
    connect(&process, &QProcess::readyRead, [this]() { emit this->OnLog(process.readAll()); });
    connect(&process, &QProcess::stateChanged, [this]() {
        if (this->isStarted && process.state() == QProcess::ProcessState::NotRunning)
        {
            this->isStarted = false;
            Stop();
            emit OnCrashed(tr("NaiveProxy kernel crashed with code %1").arg(process.exitCode()));
        }
    });
}

void NaiveProxyKernel::Start()
{
    const auto executablePath = NaiveProxyPlugin::PluginInstance->GetSettings()["kernelPath"].toString();
    if (!QFile::exists(executablePath))
    {
        NaiveProxyPlugin::ShowMessageBox(tr("Naive!"), tr("We cannot find your NaiveProxy kernel. Please configure it in the plugin settings."));
        return;
    }

    QStringList arguments{ "--log" };

    // proxy
    {
        QUrl url;
        url.setScheme(protocol.replace("naive+", ""));
        if (!username.isEmpty() || !password.isEmpty())
        {
            url.setUserName(username);
            url.setPassword(password);
        }
        if (!sni.isEmpty())
        {
            // ### Hack : SNI is used for proxychains
            url.setHost(sni);
            arguments << QString("--host-resolver-rules=MAP %1 127.0.0.1").arg(sni);
        }
        else
        {
            url.setHost(host);
        }
        url.setPort(port);
        arguments << QString("--proxy=%1").arg(url.url());
    }

    if (this->padding)
    {
        arguments << "--padding";
    }

    // listen socks
    if (this->socksPort)
    {
        arguments << QString("--listen=socks://%1:%2").arg(listenIp).arg(socksPort);
    }

    // listen http
    if (this->httpPort)
    {
        httpProxy.httpListen(QHostAddress(listenIp), httpPort, socksPort);
    }

    // launch
    this->process.start(executablePath, arguments);
    isStarted = true;
    return;
}

void NaiveProxyKernel::SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &options, const IOConnectionSettings &settings)
{
    sni.clear();
    this->listenIp = options[KERNEL_LISTEN_ADDRESS].toString();
    this->socksPort = options[KERNEL_SOCKS_ENABLED].toBool() ? options[KERNEL_SOCKS_PORT].toInt() : 0;
    this->httpPort = options[KERNEL_HTTP_ENABLED].toBool() ? options[KERNEL_HTTP_PORT].toInt() : 0;
    this->host = settings.address;
    this->port = settings.port.from;
    this->username = settings.protocolSettings["username"].toString();
    this->password = settings.protocolSettings["password"].toString();
    this->protocol = settings.protocolSettings["protocol"].toString();
    this->padding = settings.protocolSettings["padding"].toBool();
    //
    // Special SNI option
    if (settings.protocolSettings.contains("sni"))
        sni = settings.protocolSettings["sni"].toString();
    //

    if (this->protocol != "https" && this->protocol != "quic")
    {
        emit OnLog("warning: outbound protocol falled back to https");
        this->protocol = "https";
    }

    if (this->port <= 0 || this->port >= 65536)
    {
        emit OnLog("warning: outbound port falled back to 443");
        this->port = 443;
    }
}

bool NaiveProxyKernel::Stop()
{
    if (this->httpPort)
    {
        httpProxy.close();
    }
    isStarted = false;
    this->process.close();
    this->process.waitForFinished();
    return true;
}

bool NaiveProxyKernel::PrepareConfigurations()
{
    return true;
}
