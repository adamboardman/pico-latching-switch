cmake_minimum_required(VERSION 3.12)

add_definitions(-DMOCK_PICO_PI)

project(tests)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 REQUIRED)

include_directories(../)

add_executable(
        tests
        test_latching_switch.cpp
        latching_switch_mocks.cpp
        pico_pi_mocks.cpp
        ../latching_switch.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)