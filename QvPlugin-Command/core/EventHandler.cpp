#include "EventHandler.hpp"

#include "CommandPlugin.hpp"

#include <QProcess>

using QRegExp = QRegularExpression;

using namespace Qv2rayPlugin;

void SimpleEventHandler::ProcessEvent(const Connectivity::EventObject &pluginEvent)
{
    ///
    /// Variables:
    /// $$DISPLAYNAME
    /// $$INBOUND_inboundProtocol
    ///  --> port for that protocol, (e.g. $INBOUND_http as HTTP port)
    ///
    CommandPluginConfig settings;
    settings.loadJson(CommandPlugin::PluginInstance->GetSettings());

    QStringList actions;
    switch (pluginEvent.Type)
    {
        case Connectivity::Connected:
        {
            actions << settings.afterConnection.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
            break;
        }
        case Connectivity::Connecting:
        {
            actions << settings.beforeConnection.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
            break;
        }
        case Connectivity::Disconnected:
        {
            actions << settings.afterDisConnection.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
            break;
        }
        case Connectivity::Disconnecting:
        {
            actions << settings.beforeDisConnection.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
            break;
        }
    }
    for (const auto &action : actions)
    {
        CommandPlugin::ShowMessageBox("TODO", "TODO");
        //        auto _command = action;
        //        _command.replace("$$DISPLAYNAME", pluginEvent.name);
        //        for (const auto &protocol : pluginEvent.InboundPorts.keys())
        //        {
        //            _command.replace("$$INBOUND_" + protocol, QString::number(pluginEvent.InboundPorts[protocol]));
        //        }
        //        bool detached = _command.contains("$$CALL");
        //        _command.replace("$$CALL", "");
        //        if (detached)
        //        {
        //            auto returnvalue = QProcess::execute(_command);
        //            if (returnvalue != 0)
        //            {
        //                CommandPlugin::Log("Failed to execute command : \"" + action + "\"");
        //            }
        //        }
        //        else
        //        {
        //            QProcess::startDetached(_command);
        //        }
    }
}

// void SimpleEventHandler::ProcessEvent(const SystemProxy::EventObject &pluginEvent)
//{
//    ///
//    /// Variables:
//    /// $$HTTP: HTTP port (could be 0)
//    /// $$SOCKS: SOCKS port (could be 0)
//    ///
//    CommandPluginConfig settings;
//    settings.loadJson(CommandPlugin::PluginInstance->GetSettings());
//    QStringList actions;
//    switch (pluginEvent.State)
//    {
//        case SystemProxy::SetProxy:
//        {
//            actions << settings.setSystemProxy.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
//            break;
//        }
//        case SystemProxy::ClearProxy:
//        {
//            actions << settings.clearSystemProxy.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
//            break;
//        }
//    }

//    for (const auto &action : actions)
//    {
//        auto _command = action;
//        _command.replace("$$HTTP", QString::number(pluginEvent.PortSettings[SystemProxy::SystemProxy_HTTP]));
//        _command.replace("$$SOCKS", QString::number(pluginEvent.PortSettings[SystemProxy::SystemProxy_SOCKS]));
//        bool detached = _command.contains("$$CALL");
//        _command.replace("$$CALL", "");
//        if (detached)
//        {
//            auto returnvalue = QProcess::execute(_command);
//            if (returnvalue != 0)
//            {
//                CommandPlugin::PluginInstance->PluginLog("Failed to execute command : \"" + action + "\"");
//            }
//        }
//        else
//        {
//            QProcess::startDetached(_command);
//        }
//    }
//}

void SimpleEventHandler::ProcessEvent(const ConnectionEntry::EventObject &pluginEvent)
{
    ///
    /// Variables:
    /// $$DISPLAYNAME
    /// $$ORIGINAL_NAME
    ///

    CommandPluginConfig settings;
    settings.loadJson(CommandPlugin::PluginInstance->GetSettings());

    QStringList actions;
    switch (pluginEvent.Type)
    {
        case ConnectionEntry::Created:
        {
            actions << settings.connectionCreated.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
            break;
        }
        case ConnectionEntry::FullyRemoved:
        case ConnectionEntry::RemovedFromGroup:
        {
            actions << settings.connectionDeleted.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
            break;
        }
        case ConnectionEntry::Renamed:
        {
            actions << settings.connectionRenamed.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
            break;
        }
        case ConnectionEntry::Edited:
        {
            actions << settings.connectionUpdated.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
            break;
        }
        case ConnectionEntry::LinkedWithGroup:
        {
            break;
        }
    }
    for (const auto &action : actions)
    {
        CommandPlugin::ShowMessageBox("TODO", "TODO");
        //        auto _command = action;
        //        _command.replace("$$DISPLAYNAME", "TODO");
        //        _command.replace("$$ORIGINAL_NAME", pluginEvent.OriginalName);
        //        bool detached = _command.contains("$$CALL");
        //        _command.replace("$$CALL", "");
        //        if (detached)
        //        {
        //            auto returnvalue = QProcess::execute(_command);
        //            if (returnvalue != 0)
        //            {
        //                CommandPlugin::PluginInstance->PluginLog("Failed to execute command : \"" + action + "\"");
        //            }
        //        }
        //        else
        //        {
        //            QProcess::startDetached(_command);
        //        }
    }
}
