project(QvPluginCollections)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_PROJECT_VERSION 1)
set(CMAKE_PROJECT_VERSION_MAJOR 0)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 0)

option(ALL_PLUGINS OFF)

macro(plugin_collection name)
    option("HAS_PLUGIN_${name}" OFF)
    if(${HAS_PLUGIN_${name}} OR ALL_PLUGINS)
        add_subdirectory(QvPlugin-${name})
        message("|| State || QvPlugin-${name}: ON")
    else()
        message("|| State || QvPlugin-${name}: OFF")
    endif()
endmacro()

plugin_collection(Command)
plugin_collection(Trojan-Go)
plugin_collection(NaiveProxy)
