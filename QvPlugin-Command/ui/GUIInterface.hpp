#pragma once

#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "ui/CommandPluginSettings.hpp"

using namespace Qv2rayPlugin;

class CommandGUIInterface : public Qv2rayPlugin::Gui::Qv2rayGUIInterface
{
  public:
    QIcon Icon() const override
    {
        return QIcon(":/assets/qv2ray.png");
    }

    QList<Qv2rayPlugin::PLUGIN_GUI_COMPONENT_TYPE> GetComponents() const override
    {
        return { GUI_COMPONENT_SETTINGS };
    }

    std::unique_ptr<Qv2rayPlugin::Gui::PluginSettingsWidget> GetSettingsWidget() const override
    {
        return std::make_unique<CommandPluginSettings>();
    }

    PluginEditorDescriptor GetInboundEditors() const override
    {
        return {};
    }

    PluginEditorDescriptor GetOutboundEditors() const override
    {
        return {};
    }

    std::unique_ptr<Qv2rayPlugin::Gui::PluginMainWindowWidget> GetMainWindowWidget() const override
    {
        return nullptr;
    }
};
