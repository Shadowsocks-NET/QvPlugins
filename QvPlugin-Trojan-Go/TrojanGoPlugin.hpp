#pragma once

#include "QvPluginInterface.hpp"
#include "core/Kernel.hpp"
#include "core/Serializer.hpp"

#include <QObject>
#include <QtPlugin>

using namespace Qv2rayPlugin;

class QvTrojanGoPlugin
    : public QObject
    , public Qv2rayInterface
{
    Q_INTERFACES(Qv2rayPlugin::Qv2rayInterface)
    Q_PLUGIN_METADATA(IID Qv2rayInterface_IID)
    Q_OBJECT
  public:
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{ "Trojan-Go Plugin",                                 //
                                 "Qv2ray Workgroup",                                 //
                                 "qvtrojango_plugin",                                //
                                 "Connect to Trojan-GFW/Trojan-Go server in Qv2ray", //
                                 "",                                                 //
                                 {
                                     COMPONENT_GUI,             //
                                     COMPONENT_KERNEL,          //
                                     COMPONENT_OUTBOUND_HANDLER //
                                 } };
    }
    bool InitializePlugin() override;
    void SettingsUpdated() override{};

  signals:
    void PluginLog(QString) const override;
    void PluginErrorMessageBox(QString, QString) const override;
};
