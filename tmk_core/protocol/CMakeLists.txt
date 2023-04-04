target_sources(qmk PUBLIC
    host.c
    report.c
    usb_device_state.c
    usb_util.c
)
# target_compile_definitions(
    # MOUSE_ENABLED
    # EXTRAKEY_ENABLE
    # NKRO_ENABLE
# )
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(tmk_core_protocol ${QMK_TARGET})
# target_link_libraries(tmk_core_protocol quantum)
# target_link_libraries(tmk_core_protocol tmk_core_protocol_${QMK_PROTOCOL})
# target_link_libraries(tmk_core_protocol platforms_${QMK_PLATFORM})

add_subdirectory(${QMK_PROTOCOL})