#pragma once
#include "Common.hpp"
#include "QvPlugin/Handlers/OutboundHandler.hpp"

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QtDebug>
#include <QtGlobal>

using namespace Qv2rayPlugin;

class TrojanGoSerializer : public Qv2rayPlugin::Outbound::IOutboundProcessor
{
  public:
    explicit TrojanGoSerializer() : Qv2rayPlugin::Outbound::IOutboundProcessor(){};
    std::optional<QString> Serialize(const QString &name, const IOConnectionSettings &outbound) const override
    {
        TrojanGoShareLinkObject obj;
        obj.loadJson(outbound.protocolSettings);
        QUrl url;
        QUrlQuery query;
        url.setScheme(outbound.protocol);
        url.setHost(obj.server);
        url.setPort(obj.port);
        url.setUserInfo(obj.password);
        url.setFragment(name);
        url.setPath("/");
        //
        query.addQueryItem("type", TRANSPORT_TYPE_STRING_MAP[obj.type]);
        if (!obj.sni.isEmpty())
            query.addQueryItem("sni", obj.sni);
        if (obj.type == TRANSPORT_WEBSOCKET)
        {
            if (!obj.host.isEmpty())
            {
                query.addQueryItem("host", QUrl::toPercentEncoding(obj.host));
            }
            else
            {
                qWarning() << "empty host is deprecated when websocket is used";
            }
            query.addQueryItem("path", QUrl::toPercentEncoding(obj.path));
            if (!obj.encryption.isEmpty())
                query.addQueryItem("encryption", QUrl::toPercentEncoding(obj.encryption));
            if (!obj.plugin.isEmpty())
                query.addQueryItem("plugin", QUrl::toPercentEncoding(obj.plugin));
        }
        url.setQuery(query);
        return url.toString(QUrl::FullyEncoded);
    }

    std::optional<std::pair<QString, IOConnectionSettings>> Deserialize(const QString &url) const override
    {
        IOConnectionSettings outbound;
        QUrl link{ url };
        QUrlQuery query{ link };
        if (!link.isValid())
            return std::nullopt;

        if (link.scheme() != "trojan-go")
            return std::nullopt;

        const auto extractQueryField = [&query](const QString &key) -> QString { return query.queryItemValue(key, QUrl::FullyDecoded); };

        TrojanGoShareLinkObject info;
        info.password = link.userName(QUrl::FullyDecoded);
        if (info.password.isEmpty())
            return std::nullopt;

        info.server = link.host(QUrl::FullyDecoded);
        if (info.server.isEmpty())
            return std::nullopt;

        info.port = link.port(443);
        if (info.port < 1 || info.port > 65535)
            return std::nullopt;

        {
            bool hasSNI = query.hasQueryItem("sni");
            if (hasSNI)
            {
                info.sni = extractQueryField("sni");
                if (info.sni.isEmpty())
                    return std::nullopt;
            }
            else
                info.sni = info.server;
        }

        {
            const auto hasType = query.hasQueryItem("type");
            if (hasType)
            {
                const auto _type = extractQueryField("type");
                if (!TRANSPORT_TYPE_STRING_MAP.values().contains(_type))
                    return std::nullopt;
                info.type = TRANSPORT_TYPE_STRING_MAP.key(_type);
            }
            else
                info.type = TRANSPORT_ORIGINAL;
        }

        {
            bool hasHost = query.hasQueryItem("host");
            if (!hasHost)
            {
                info.host = info.server;
            }
            else
            {
                info.host = extractQueryField("host");
                if (info.host.isEmpty())
                    return std::nullopt;
            }
        }

        {
            info.path = extractQueryField("path");
            if (info.type == TRANSPORT_WEBSOCKET)
            {
                if (info.path.isEmpty())
                    return std::nullopt;
            }
        }

        bool hasEncryption = query.hasQueryItem("encryption");
        if (hasEncryption)
        {
            info.encryption = extractQueryField("encryption");
            if (info.encryption.isEmpty())
                return std::nullopt;
            if (info.encryption.startsWith("ss;"))
            {
                const auto ssParms = info.encryption.split(";");
                if (ssParms.length() != 2)
                    return std::nullopt;
                else
                {
                    const auto ssParms2 = ssParms[1].split(":");
                    if (!VALID_SHADOWSOCKS_ENCRYPTION_LIST.contains(ssParms2[0]))
                        return std::nullopt;
                }
            }
            else
                return std::nullopt;
        }

        bool hasPlugin = query.hasQueryItem("plugin");
        if (hasPlugin)
        {
            info.plugin = extractQueryField("plugin");
            if (info.plugin.isEmpty())
                return std::nullopt;
        }

        const auto name = link.fragment(QUrl::FullyDecoded);
        outbound.protocol = "trojan-go";
        outbound.protocolSettings = IOProtocolSettings{ info.toJson() };
        return std::make_pair(name, outbound);
    }

    std::optional<PluginIOBoundData> GetOutboundInfo(const IOConnectionSettings &outbound) const override
    {
        if (outbound.protocol == "trojan-go")
            return PluginIOBoundData{ { IOBOUND_DATA_TYPE::IO_SNI, outbound.protocolSettings["sni"] } };
        return {};
    }

    bool SetOutboundInfo(IOConnectionSettings &outbound, const PluginIOBoundData &info) const override
    {
        if (outbound.protocol != "trojan-go")
            return false;
        if (info.contains(IOBOUND_DATA_TYPE::IO_SNI))
            outbound.protocolSettings["sni"] = info[IOBOUND_DATA_TYPE::IO_SNI].toString();
        return true;
    }

    QList<QString> SupportedLinkPrefixes() const override
    {
        return { "trojan-go://" };
    }

    QList<QString> SupportedProtocols() const override
    {
        return { "trojan-go" };
    }
};
