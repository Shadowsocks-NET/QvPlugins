#pragma once

#include "gui/QvGUIPluginInterface.hpp"
#include "ui/OutboundEditor.hpp"
#include "ui/SettingsWidget.hpp"

using namespace Qv2rayPlugin;

class NaiveUIInterface : public Qv2rayPlugin::Qv2rayGUIInterface
{
    QIcon Icon() const override
    {
        return QIcon(":/assets/naive.png");
    }
    virtual std::unique_ptr<PluginSettingsWidget> createSettingsWidgets() const override
    {
        return std::make_unique<SettingsWidget>();
    }
    virtual QList<typed_plugin_editor> createInboundEditors() const override
    {
        return {};
    }
    virtual QList<typed_plugin_editor> createOutboundEditors() const override
    {
        return { make_editor_info<OutboundEditor>("naive", "NaiveProxy") };
    }
    virtual std::unique_ptr<PluginMainWindowWidget> createMainWindowWidget() const override
    {
        return nullptr;
    }
    virtual QList<QV2RAY_PLUGIN_GUI_COMPONENT_TYPE> GetComponents() const override
    {
        return { GUI_COMPONENT_SETTINGS, GUI_COMPONENT_OUTBOUND_EDITOR };
    }
};
