#include "Serializer.hpp"

#include <QUrlQuery>

std::optional<QString> NaiveProxyOutboundHandler::Serialize(const PluginOutboundDescriptor &info) const
{
    if (info.Protocol != "naive")
        return std::nullopt;

    QUrl url;
    const auto object = info.Outbound;
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
    url.setFragment(info.ConnectionName);

    return url.toString();
}

std::optional<PluginOutboundDescriptor> NaiveProxyOutboundHandler::Deserialize(const QString &link) const
{
    PluginOutboundDescriptor info;
    QUrl url(link);
    if (!url.isValid())
        return std::nullopt;

    const auto name = url.fragment();
    info.ConnectionName = name.isEmpty() ? QString("[%1]-%2:%3").arg(url.scheme()).arg(url.host()).arg(url.port()) : name;

    const QStringList trueList = { "1", "true", "yes", "y", "on" };
    const auto usePadding = trueList.contains(QUrlQuery{ url }.queryItemValue("padding").toLower());

    info.Outbound = QJsonObject{ { "protocol", url.scheme() },   //
                                 { "host", url.host() },         //
                                 { "port", url.port(443) },      //
                                 { "username", url.userName() }, //
                                 { "password", url.password() }, //
                                 { "padding", usePadding } };
    info.Protocol = "naive";
    return info;
}

bool NaiveProxyOutboundHandler::SetOutboundInfo(const QString &protocol, QJsonObject &outbound, const PluginIOBoundData &info) const
{
    if (protocol != "naive")
        return false;
    if (info.contains(IOBOUND::ADDRESS))
        outbound["host"] = info[IOBOUND::ADDRESS].toString();
    if (info.contains(IOBOUND::PORT))
        outbound["port"] = info[IOBOUND::PORT].toInt();
    if (info.contains(IOBOUND::SNI))
        outbound["sni"] = info[IOBOUND::SNI].toString();
    return true;
}

std::optional<PluginIOBoundData> NaiveProxyOutboundHandler::GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const
{
    return PluginIOBoundData{ { IOBOUND::PROTOCOL, protocol },
                              { IOBOUND::ADDRESS, outbound["host"].toString() },
                              { IOBOUND::PORT, outbound["port"].toInt() },
                              { IOBOUND::SNI, outbound["sni"].toString() } };
}
