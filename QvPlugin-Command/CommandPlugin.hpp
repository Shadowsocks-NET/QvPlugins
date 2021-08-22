#pragma once

#include "QvPlugin/PluginInterface.hpp"
#include "core/CommandConfig.hpp"
#include "core/EventHandler.hpp"

#include <QObject>
#include <QtPlugin>

using namespace Qv2rayPlugin;

class CommandPlugin
    : public QObject
    , public Qv2rayInterface<CommandPlugin>
{
    Q_OBJECT
    QV2RAY_PLUGIN(CommandPlugin)

  public:
    //
    // Basic metainfo of this plugin
    const QvPluginMetadata GetMetadata() const override
    {
        return QvPluginMetadata{ "Qv2ray Command Plugin",                             //
                                 "Qv2ray Workgroup",                                  //
                                 PluginId{ "qvplugin_command" },                      //
                                 "Run any command when an event from Qv2ray occurs.", //
                                 QUrl{},                                              //
                                 {
                                     COMPONENT_EVENT_HANDLER, //
                                     COMPONENT_GUI            //
                                 } };
    }
    bool InitializePlugin() override;
    void SettingsUpdated() override{};
};
