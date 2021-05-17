#pragma once
#include "handlers/EventHandler.hpp"

class SimpleEventHandler : public Qv2rayPlugin::handlers::event::PluginEventHandler
{
  public:
    SimpleEventHandler() = default;
    void ProcessEvent(const SystemProxy::EventObject &o) override;
    void ProcessEvent(const Connectivity::EventObject &o) override;
    void ProcessEvent(const ConnectionEntry::EventObject &) override;
};
