target_compile_definitions(qmk PUBLIC
    PROTOCOL_CHIBIOS
    FIXED_CONTROL_ENDPOINT_SIZE=64
    FIXED_NUM_CONFIGURATIONS=1
)

target_sources(qmk PUBLIC
    usb_main.c
    chibios.c
    ../usb_descriptor.c
    usb_driver.c
    usb_util.c
)

find_package(Chibios REQUIRED)

target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lufa_utils)

# if no printf
target_sources(qmk PUBLIC ${CMAKE_SOURCE_DIR}/lib/printf/src/printf/printf.c)
target_include_directories(qmk PUBLIC ${CMAKE_SOURCE_DIR}/lib/printf/src/printf)