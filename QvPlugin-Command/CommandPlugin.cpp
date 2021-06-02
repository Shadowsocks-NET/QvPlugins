#include "CommandPlugin.hpp"

#include "ui/CommandPluginSettings.hpp"
#include "ui/GUIInterface.hpp"

bool CommandPlugin::InitializePlugin()
{
    m_EventHandler = std::make_shared<SimpleEventHandler>();
    m_GUIInterface = new CommandGUIInterface();
    return true;
}
