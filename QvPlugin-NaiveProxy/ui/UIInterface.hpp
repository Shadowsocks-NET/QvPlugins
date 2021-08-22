#pragma once

#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "ui/OutboundEditor.hpp"
#include "ui/SettingsWidget.hpp"

using namespace Qv2rayPlugin;

class NaiveUIInterface : public Qv2rayPlugin::Gui::Qv2rayGUIInterface
{
    QIcon Icon() const override
    {
        return QIcon(":/assets/naive.png");
    }
    virtual std::unique_ptr<Qv2rayPlugin::Gui::PluginSettingsWidget> GetSettingsWidget() const override
    {
        return std::make_unique<SettingsWidget>();
    }
    virtual PluginEditorDescriptor GetInboundEditors() const override
    {
        return {};
    }
    virtual PluginEditorDescriptor GetOutboundEditors() const override
    {
        return { make_editor_info<NaiveOutboundEditor>("naive", "NaiveProxy") };
    }
    virtual std::unique_ptr<Qv2rayPlugin::Gui::PluginMainWindowWidget> GetMainWindowWidget() const override
    {
        return nullptr;
    }
    virtual QList<PLUGIN_GUI_COMPONENT_TYPE> GetComponents() const override
    {
        return { GUI_COMPONENT_SETTINGS, GUI_COMPONENT_OUTBOUND_EDITOR };
    }
};
