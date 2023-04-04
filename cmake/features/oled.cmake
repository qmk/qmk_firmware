option(OLED_ENABLE "" TRUE)
if(${OLED_ENABLE})
    add_library(oled
      drivers/oled/ssd1306_sh1106.c 
      platforms/${QMK_PLATFORM}/drivers/i2c_master.c)
    add_compile_definitions(OLED_ENABLE)
    target_include_directories(oled PUBLIC drivers)
    target_include_directories(quantum PUBLIC drivers/oled)
    target_include_directories(oled PUBLIC drivers/oled)
    target_include_directories(oled PUBLIC platforms/${QMK_PLATFORM}/drivers)
    target_link_libraries(oled PUBLIC quantum)
    target_link_libraries(oled PUBLIC platform_avr)
endif()
