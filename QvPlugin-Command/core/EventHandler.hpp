#pragma once

#include "QvPlugin/Handlers/EventHandler.hpp"

using namespace Qv2rayPlugin::Event;

class SimpleEventHandler : public Qv2rayPlugin::Event::IEventHandler
{
  public:
    SimpleEventHandler() = default;
    void ProcessEvent(const Connectivity::EventObject &o) override;
    void ProcessEvent(const ConnectionEntry::EventObject &) override;
};
