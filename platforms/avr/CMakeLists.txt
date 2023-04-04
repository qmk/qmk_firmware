add_compile_options(
    -mmcu=${QMK_MCU}
)
add_link_options(
    -mmcu=${QMK_MCU}
)
add_library(platforms_avr 
    hardware_id.c
    platform.c
    suspend.c
    timer.c
    printf.c
    bootloaders/bootloadhid.c
)
target_include_directories(platforms_avr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(platforms_avr PUBLIC platforms quantum)