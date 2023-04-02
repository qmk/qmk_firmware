add_library(tmk_core_protocol
    host.c
    report.c
    usb_device_state.c
    usb_util.c
)
add_compile_definitions(
    # MOUSE_ENABLED
    # EXTRAKEY_ENABLE
    # NKRO_ENABLE
)
target_include_directories(tmk_core_protocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tmk_core_protocol PUBLIC quantum)

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "avr")
    add_subdirectory(lufa)
endif()