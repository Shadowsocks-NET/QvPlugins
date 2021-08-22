project(QvPlugin-TrojanGo)
cmake_minimum_required(VERSION 3.1.0)

qv2ray_add_plugin(QvPlugin-TrojanGo Widgets
    CLASS_NAME "QvTrojanGoPlugin")

target_sources(QvPlugin-TrojanGo PRIVATE
    TrojanGoPlugin.hpp
    TrojanGoPlugin.cpp
    core/Common.hpp
    core/Serializer.cpp
    core/Serializer.hpp
    core/Kernel.cpp
    core/Kernel.hpp
    widgets/TrojanGoSettingsWidget.cpp
    widgets/TrojanGoSettingsWidget.hpp
    widgets/TrojanGoSettingsWidget.ui
    widgets/TrojanGoOutboundWidget.cpp
    widgets/TrojanGoOutboundWidget.hpp
    widgets/TrojanGoOutboundWidget.ui
    ui/GUIInterface.hpp
    resx.qrc)
