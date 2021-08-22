project(QvPlugin-Command)
cmake_minimum_required(VERSION 3.1.0)

qv2ray_add_plugin(QvPlugin-Command Widgets
    CLASS_NAME "CommandPlugin")

target_sources(QvPlugin-Command PRIVATE
    CommandPlugin.hpp
    CommandPlugin.cpp
    core/EventHandler.cpp
    core/EventHandler.hpp
    core/CommandConfig.hpp
    ui/GUIInterface.hpp
    ui/CommandPluginSettings.cpp
    ui/CommandPluginSettings.hpp
    ui/CommandPluginSettings.ui
    resx.qrc
    )
