#pragma once

#define IGNORE_MOD_TAP_INTERRUPT

#define TAP_CODE_DELAY 5
#define TAPPING_TERM 180

#ifdef COMBO_ENABLE
#    define COMBO_COUNT 11
#    define COMBO_TERM 100
#endif

#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 	           200 // Delay between pressing a movement key and cursor movement
#    define MOUSEKEY_INTERVAL          16  // Time between cursor movements
#    define MOUSEKEY_MAX_SPEED         8   // Maximum cursor speed at which acceleration stops
#    define MOUSEKEY_TIME_TO_MAX       10  // Time until maximum cursor speed is reached
#    define MOUSEKEY_WHEEL_DELAY       200 // Delay between pressing a wheel key and wheel movement
#    define MOUSEKEY_WHEEL_INTERVAL    150 // Time between wheel movements
#    define MOUSEKEY_WHEEL_MAX_SPEED   8   // Maximum number of scroll steps per scroll action
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 40  // Time until maximum scroll speed is reached
#endif

#ifdef OLED_DRIVER_ENABLE
#    define OLED_TIMEOUT 0  // Disable built-in timeout
#    define OLED_CUSTOM_TIMEOUT 10000
#endif
