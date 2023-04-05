set(ARCH AVR8)
set(USE_STATIC_OPTIONS "(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)")

target_compile_definitions(qmk PUBLIC
    PROTOCOL_LUFA
    ARCH=ARCH_${ARCH}
    BOARD=BOARD_NONE

    USB_DEVICE_ONLY
    USE_FLASH_DESCRIPTORS
    USE_STATIC_OPTIONS=${USE_STATIC_OPTIONS}
    FIXED_CONTROL_ENDPOINT_SIZE=8
    FIXED_NUM_CONFIGURATIONS=1
)

target_sources(qmk PUBLIC 
    lufa.c
    ../usb_descriptor.c
    usb_util.c 
)

find_package(Lufa REQUIRED)
# target_compile_definitions(lufa PUBLIC ${COMPILE_DEFINITIONS})

target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(qmk lufa)

# target_link_libraries(tmk_core_protocol_lufa ${QMK_TARGET})
# target_link_libraries(tmk_core_protocol_lufa quantum)
# target_link_libraries(tmk_core_protocol_lufa tmk_core_protocol)
# target_link_libraries(tmk_core_protocol_lufa lufa)
# target_link_libraries(tmk_core_protocol_lufa platforms)
# target_link_libraries(tmk_core_protocol_lufa platforms_${QMK_PLATFORM})