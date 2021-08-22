#include "BuiltinLatencyTesterPlugin.hpp"

#include "latency/ICMPLatencyTester.hpp"
#include "latency/TCPLatencyTester.hpp"
#include "uvw.hpp"

class LatencyHandler : public ILatencyHandler
{
  public:
    LatencyHandler() = default;
    const LatencyTestEngineId TCPEngineId{ "qv2ray_tcp" };
    const LatencyTestEngineId ICMPEngineId{ "qv2ray_icmp" };
    virtual QList<LatencyTestEngineInfo> PluginLatencyTestEngines() const
    {
        return {
            LatencyTestEngineInfo{ TCPEngineId, true, "TCP Connect Latency", "", [] { return std::make_shared<TCPTestEngine>(); } },
            //            LatencyTestEngineInfo{ ICMPEngineId, true, "ICMP Ping Latency", "", [] { return std::make_unique<ICMPTestEngine>(); } },
        };
    };
    Q_DISABLE_COPY(LatencyHandler)
};

const QvPluginMetadata BuiltinLatencyTesterPlugin::GetMetadata() const
{
    return {
        "TCPing Test Engine",
        "Qv2rayBase Development Team",
        PluginId{ "BuiltinLatencyTester" },
        "This plugin provides latency test engine.",
        QUrl{},
        { COMPONENT_LATENCY_TEST_ENGINE },
    };
}

bool BuiltinLatencyTesterPlugin::InitializePlugin()
{
    m_LatencyTestHandler = std::make_shared<LatencyHandler>();
    return true;
}

void BuiltinLatencyTesterPlugin::SettingsUpdated()
{
}
