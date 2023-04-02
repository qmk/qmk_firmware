option(BACKLIGHT_ENABLE "" TRUE)
set(BACKLIGHT_DRIVER "pwm" CACHE STRING "Backlight driver")
set_property(CACHE BACKLIGHT_DRIVER PROPERTY STRINGS pwm timer software custom)

if(${BACKLIGHT_ENABLE})
    add_library(backlight
      quantum/backlight/backlight.c 
      quantum/process_keycode/process_backlight.c
    )
    string(JSON BACKLIGHT_PIN GET ${QMK_KEYBOARD_INFO_JSON_STRING} backlight pin)
    add_compile_definitions(
        BACKLIGHT_ENABLE
        BACKLIGHT_PIN=${BACKLIGHT_PIN}
    )
    if(${BACKLIGHT_DRIVER} STREQUAL "custom")
        add_compile_definitions(BACKLIGHT_CUSTOM_DRIVER)
    else()
        target_sources(backlight PRIVATE quantum/backlight/backlight_driver_common.c)
        if(${BACKLIGHT_DRIVER} STREQUAL "pwm")
            target_sources(backlight PRIVATE quantum/backlight/backlight_${CMAKE_SYSTEM_PROCESSOR}.c)
        else()
            target_sources(backlight PRIVATE quantum/backlight/backlight_${BACKLIGHT_DRIVER}.c)
        endif()
    endif()
    target_include_directories(backlight PUBLIC quantum/backlight)
    target_include_directories(quantum PUBLIC quantum/backlight)
    target_link_libraries(backlight PUBLIC quantum)
endif()
