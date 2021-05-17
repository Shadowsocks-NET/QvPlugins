#pragma once
#include "handlers/OutboundHandler.hpp"

#include <QObject>

class NaiveProxyOutboundHandler : public PluginOutboundHandler
{
  public:
    explicit NaiveProxyOutboundHandler() : PluginOutboundHandler(){};

    std::optional<QString> Serialize(const PluginOutboundInfo &outbound) const override;
    std::optional<PluginOutboundInfo> Deserialize(const QString &link) const override;

    std::optional<PluginOutboundData> GetOutboundInfo(const QString &protocol, const QJsonObject &outbound) const override;
    bool SetOutboundInfo(const QString &protocol, QJsonObject &outbound, const PluginOutboundData &info) const override;

    QList<QString> SupportedProtocols() const override
    {
        return { "naive" };
    }
    QList<QString> SupportedLinkPrefixes() const override
    {
        return { "naive+https://", "naive+quic://" };
    }
};
