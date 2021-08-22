project(QvPlugin-NaiveProxy)
cmake_minimum_required(VERSION 3.1.0)

qv2ray_add_plugin(QvPlugin-NaiveProxy Widgets
    HTTP_TO_SOCKS
    CLASS_NAME "NaiveProxyPlugin")

target_sources(QvPlugin-NaiveProxy PRIVATE
    SimplePlugin.hpp
    SimplePlugin.cpp
    core/Serializer.cpp
    core/Serializer.hpp
    core/Kernel.cpp
    core/Kernel.hpp
    ui/OutboundEditor.ui
    ui/OutboundEditor.cpp
    ui/OutboundEditor.hpp
    ui/SettingsWidget.cpp
    ui/SettingsWidget.hpp
    ui/SettingsWidget.ui
    ui/UIInterface.hpp
    resx.qrc)
