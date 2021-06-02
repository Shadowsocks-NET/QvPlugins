#include "SimplePlugin.hpp"

#include "core/Kernel.hpp"
#include "core/Serializer.hpp"
#include "ui/UIInterface.hpp"

#include <QDateTime>
#include <QLabel>
#include <QMetaEnum>

bool NaiveProxyPlugin::InitializePlugin()
{
    emit PluginLog("Initializing NaiveProxy plugin.");
    m_OutboundHandler = std::make_unique<NaiveProxyOutboundHandler>();
    m_KernelInterface = std::make_shared<NaiveKernelInterface>();
    m_GUIInterface = new NaiveUIInterface();
    return true;
}
