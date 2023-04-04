add_compile_definitions(
    PROTOCOL_CHIBIOS
    FIXED_CONTROL_ENDPOINT_SIZE=64
    FIXED_NUM_CONFIGURATIONS=1
)

add_library(tmk_core_protocol_chibios
    usb_main.c
    chibios.c
    ../usb_descriptor.c
    usb_driver.c
    usb_util.c
)

# find_package(lufa REQUIRED)

target_include_directories(tmk_core_protocol_chibios PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tmk_core_protocol_chibios PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lufa_utils)

# target_link_libraries(tmk_core_protocol_chibios PUBLIC lufa)
target_link_libraries(tmk_core_protocol_chibios PUBLIC quantum)