#include "Serializer.hpp"

#include <QUrlQuery>

std::optional<QString> NaiveProxyOutboundHandler::Serialize(const QString &name, const IOConnectionSettings &outbound) const
{
    if (outbound.protocol != "naive")
        return std::nullopt;

    QUrl url;
    const auto object = outbound.protocolSettings;
    if (const auto protocol = object["protocol"].toString(); protocol != "https" && protocol != "quic")
        url.setScheme("naive+https");
    else
        url.setScheme("naive+" + protocol);

    if (const auto username = object["username"].toString(); !username.isEmpty())
        url.setUserName(username);
    if (const auto password = object["password"].toString(); !password.isEmpty())
        url.setPassword(password);

    url.setHost(object["host"].toString());

    if (const auto port = object["port"].toInt(443); port <= 0 || port >= 65536)
        url.setPort(443);
    else
        url.setPort(port);

    QUrlQuery query;
    query.setQueryItems({ { "padding", object["padding"].toBool() ? "true" : "false" } });
    url.setQuery(query);
    url.setFragment(name);

    return url.toString();
}

std::optional<std::pair<QString, IOConnectionSettings>> NaiveProxyOutboundHandler::Deserialize(const QString &link) const
{
    IOConnectionSettings info;
    QUrl url(link);
    if (!url.isValid())
        return std::nullopt;

    const auto name = url.fragment();
    const auto newName = name.isEmpty() ? QString("[%1]-%2:%3").arg(url.scheme()).arg(url.host()).arg(url.port()) : name;

    const QStringList trueList = { "1", "true", "yes", "y", "on" };
    const auto usePadding = trueList.contains(QUrlQuery{ url }.queryItemValue("padding").toLower());

    info.protocolSettings = IOProtocolSettings{ QJsonObject{ { "protocol", url.scheme() },   //
                                                             { "host", url.host() },         //
                                                             { "port", url.port(443) },      //
                                                             { "username", url.userName() }, //
                                                             { "password", url.password() }, //
                                                             { "padding", usePadding } } };
    info.protocol = "naive";
    return std::make_pair(newName, info);
}

bool NaiveProxyOutboundHandler::SetOutboundInfo(IOConnectionSettings &outbound, const PluginIOBoundData &info) const
{
    if (outbound.protocol != "naive")
        return false;
    if (info.contains(IOBOUND_DATA_TYPE::IO_SNI))
        outbound.protocolSettings["sni"] = info[IOBOUND_DATA_TYPE::IO_SNI].toString();
    return true;
}

std::optional<PluginIOBoundData> NaiveProxyOutboundHandler::GetOutboundInfo(const IOConnectionSettings &outbound) const
{
    return PluginIOBoundData{ { IOBOUND_DATA_TYPE::IO_SNI, outbound.protocolSettings["sni"].toString() } };
}
