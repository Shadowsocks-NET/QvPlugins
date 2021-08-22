#pragma once

#include "QvPlugin/PluginInterface.hpp"

#include <QObject>
#include <QtPlugin>

using namespace Qv2rayPlugin;

class NaiveProxyPlugin
    : public QObject
    , public Qv2rayInterface<NaiveProxyPlugin>
{
    Q_OBJECT
    QV2RAY_PLUGIN(NaiveProxyPlugin)

  public:
    //
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{
            "NaiveProxy Plugin",
            "Qv2ray Workgroup",
            PluginId{ "qvplugin_naiveproxy" },
            "NaiveProxy Plugin.",
            QUrl{},
            {
                COMPONENT_GUI,
                COMPONENT_KERNEL,
                COMPONENT_OUTBOUND_HANDLER,
            },
        };
    }
    bool InitializePlugin() override;
    void SettingsUpdated() override{};
};
