#pragma once

#include "QvPlugin/PluginInterface.hpp"
#include "core/Kernel.hpp"
#include "core/Serializer.hpp"

#include <QObject>
#include <QtPlugin>

using namespace Qv2rayPlugin;

class QvTrojanGoPlugin
    : public QObject
    , public Qv2rayInterface<QvTrojanGoPlugin>
{
    Q_OBJECT
    QV2RAY_PLUGIN(QvTrojanGoPlugin)

  public:
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{
            "Trojan-Go Plugin",
            "Qv2ray Workgroup",
            PluginId{ "qvtrojango_plugin" },
            "Connect to Trojan-GFW/Trojan-Go server in Qv2ray",
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
