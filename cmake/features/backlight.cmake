option(BACKLIGHT_ENABLE "" TRUE)
set(BACKLIGHT_DRIVER "pwm" CACHE STRING "Backlight driver")
set_property(CACHE BACKLIGHT_DRIVER PROPERTY STRINGS pwm timer software custom)

string(JSON BACKLIGHT_PIN ERROR_VARIABLE NO_BACKLIGHT_PIN GET ${QMK_KEYBOARD_INFO_JSON_STRING} backlight pin)
if(${BACKLIGHT_ENABLE} AND NOT ${NO_BACKLIGHT_PIN} STREQUAL "backlight-NOTFOUND")
    add_library(backlight
      quantum/backlight/backlight.c 
      quantum/process_keycode/process_backlight.c
    )
    add_compile_definitions(
        BACKLIGHT_ENABLE
        BACKLIGHT_PIN=${BACKLIGHT_PIN}
    )
    if(${BACKLIGHT_DRIVER} STREQUAL "custom")
        add_compile_definitions(BACKLIGHT_CUSTOM_DRIVER)
    else()
        target_sources(backlight PRIVATE quantum/backlight/backlight_driver_common.c)
        if(${BACKLIGHT_DRIVER} STREQUAL "pwm")
            target_sources(backlight PRIVATE quantum/backlight/backlight_${QMK_PLATFORM}.c)
        else()
            target_sources(backlight PRIVATE quantum/backlight/backlight_${BACKLIGHT_DRIVER}.c)
        endif()
    endif()
    target_include_directories(backlight PUBLIC quantum/backlight)
    target_include_directories(quantum PUBLIC quantum/backlight)
    target_link_libraries(backlight PUBLIC quantum)
endif()
