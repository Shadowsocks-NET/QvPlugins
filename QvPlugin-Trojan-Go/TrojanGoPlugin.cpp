#include "TrojanGoPlugin.hpp"

#include "ui/GUIInterface.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>

bool QvTrojanGoPlugin::InitializePlugin()
{
    m_OutboundHandler = std::make_shared<TrojanGoSerializer>();
    m_KernelInterface = std::make_unique<TrojanGoPluginKernelInterface>();
    m_GUIInterface = new TrojanGoGUIInterface();
    return true;
}
