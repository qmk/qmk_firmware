#pragma once

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // Turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_LED_PROCESS_LIMIT 4
#    define RGB_MATRIX_LED_FLUSH_LIMIT 26

#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_ALL
#    define DRIVER_ADDR_1 0b1010000
#    define DRIVER_COUNT 1
#    define RGB_MATRIX_LED_COUNT 62
#endif
