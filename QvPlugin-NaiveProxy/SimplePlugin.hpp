#pragma once

#include "QvPluginInterface.hpp"

#include <QObject>
#include <QtPlugin>

using namespace Qv2rayPlugin;

class NaiveProxyPlugin
    : public QObject
    , public Qv2rayInterface
{
    Q_INTERFACES(Qv2rayPlugin::Qv2rayInterface)
    Q_PLUGIN_METADATA(IID Qv2rayInterface_IID)
    Q_OBJECT
  public:
    //
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{ "NaiveProxy Plugin",   //
                                 "Qv2ray Workgroup",    //
                                 "qvplugin_naiveproxy", //
                                 "NaiveProxy Plugin.",  //
                                 "",                    //
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
