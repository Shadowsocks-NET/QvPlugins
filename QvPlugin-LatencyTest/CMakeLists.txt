set(CMAKE_AUTOMOC ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if(NOT TARGET Qv2ray::libuvw)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/libuvw.cmake)
endif()

qv2ray_add_plugin(QvPlugin-LatencyTest
    CLASS_NAME "BuiltinLatencyTesterPlugin")

target_sources(QvPlugin-LatencyTest PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/BuiltinLatencyTesterPlugin.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BuiltinLatencyTesterPlugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/latency/DNSBase.hpp
    ${CMAKE_CURRENT_LIST_DIR}/latency/TCPLatencyTester.hpp
    ${CMAKE_CURRENT_LIST_DIR}/latency/TCPLatencyTester.cpp
    ${CMAKE_CURRENT_LIST_DIR}/latency/ICMPLatencyTester.hpp
    ${CMAKE_CURRENT_LIST_DIR}/latency/ICMPLatencyTester.cpp)

target_link_libraries(QvPlugin-LatencyTest
    PRIVATE
    Qv2ray::libuvw)

if(WIN32)
    target_link_libraries(QvPlugin-LatencyTest PRIVATE Iphlpapi)
endif()
