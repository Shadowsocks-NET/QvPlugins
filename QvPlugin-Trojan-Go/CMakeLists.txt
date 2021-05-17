project(QvPlugin-TrojanGo)
cmake_minimum_required(VERSION 3.1.0)
include(${CMAKE_SOURCE_DIR}/plugin-interface/QvPluginInterface.cmake)

add_library(${PROJECT_NAME} MODULE
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

qv2ray_configure_plugin(${PROJECT_NAME} Widgets)
