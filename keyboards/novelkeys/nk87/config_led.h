#pragma once



#ifdef RGB_MATRIX_ENABLE
    #define DRIVER_ADDR_1 0x50
    #define DRIVER_ADDR_2 0x52
    #define DRIVER_COUNT 2

    #define DRIVER_1_LED_TOTAL 63
    #define DRIVER_2_LED_TOTAL 26
    #define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

#endif