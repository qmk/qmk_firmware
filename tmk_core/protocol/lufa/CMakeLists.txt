set(ARCH AVR8)
set(USE_STATIC_OPTIONS "(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)")

add_compile_definitions(
    PROTOCOL_LUFA
    ARCH=ARCH_${ARCH}
    BOARD=BOARD_NONE

    USB_DEVICE_ONLY
    USE_FLASH_DESCRIPTORS
    USE_STATIC_OPTIONS=${USE_STATIC_OPTIONS}
    FIXED_CONTROL_ENDPOINT_SIZE=8
    FIXED_NUM_CONFIGURATIONS=1
)

add_library(tmk_core_protocol_lufa 
    lufa.c
    ../usb_descriptor.c
    usb_util.c 
)

find_package(lufa REQUIRED)

target_include_directories(tmk_core_protocol_lufa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tmk_core_protocol_lufa PUBLIC lufa)
target_link_libraries(tmk_core_protocol_lufa PUBLIC quantum)