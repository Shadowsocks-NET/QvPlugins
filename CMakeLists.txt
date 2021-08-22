project(QvPluginCollections)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_PROJECT_VERSION 1)
set(CMAKE_PROJECT_VERSION_MAJOR 0)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

option(ALL_PLUGINS ON)
option(USE_SYSTEM_PLUGIN_INTERFACE OFF)

if(USE_SYSTEM_PLUGIN_INTERFACE)
    find_package(QvPluginInterface REQUIRED)
else()
    add_subdirectory(plugin-interface)
endif()

macro(plugin_collection name)
    option("HAS_PLUGIN_${name}" ${ALL_PLUGINS})
    if(${HAS_PLUGIN_${name}} OR ALL_PLUGINS)
        add_subdirectory(QvPlugin-${name})
        message("|| State || QvPlugin-${name}: ON")
    else()
        message("|| State || QvPlugin-${name}: OFF")
    endif()
endmacro()

#plugin_collection(Command)
plugin_collection(Trojan-Go)
#plugin_collection(NaiveProxy)
plugin_collection(LatencyTest)
