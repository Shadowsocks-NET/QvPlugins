#pragma once
#include "QvPlugin/Handlers/OutboundHandler.hpp"

#include <QObject>

class NaiveProxyOutboundHandler : public Qv2rayPlugin::Outbound::IOutboundProcessor
{
  public:
    explicit NaiveProxyOutboundHandler() : Qv2rayPlugin::Outbound::IOutboundProcessor(){};

    virtual std::optional<QString> Serialize(const QString &name, const IOConnectionSettings &outbound) const override;
    virtual std::optional<std::pair<QString, IOConnectionSettings>> Deserialize(const QString &link) const override;

    virtual std::optional<PluginIOBoundData> GetOutboundInfo(const IOConnectionSettings &outbound) const override;
    virtual bool SetOutboundInfo(IOConnectionSettings &outbound, const PluginIOBoundData &info) const override;

    QList<QString> SupportedProtocols() const override
    {
        return { "naive" };
    }
    QList<QString> SupportedLinkPrefixes() const override
    {
        return { "naive+https://", "naive+quic://" };
    }
};
