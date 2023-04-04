# add_compile_options(
#     -mmcu=${QMK_MCU}
# )
# add_link_options(
#     -mmcu=${QMK_MCU}
# )
target_sources(qmk PUBLIC 
    hardware_id.c
    platform.c
    suspend.c
    timer.c
    printf.c
    bootloaders/bootloadhid.c
    xprintf.S
)
target_include_directories(qmk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# target_link_libraries(platforms_avr ${QMK_TARGET})
# target_link_libraries(platforms_avr quantum)