add_library(pico_latching_switch INTERFACE)

target_sources(pico_latching_switch INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/source/latching_switch.cpp
        )

target_include_directories(pico_latching_switch INTERFACE ${CMAKE_CURRENT_LIST_DIR}/api)
target_link_libraries(pico_latching_switch INTERFACE pico_interfaces pico_stdlib hardware_gpio)