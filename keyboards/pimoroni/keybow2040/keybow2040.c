// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
    /* driver, r, g, b */
    { 0, C8_9,  C6_9,  C7_9  }, // LEDB12 0,0
    { 0, C9_9,  C3_9,  C5_9  }, // LEDB11 1,0
    { 0, C8_1,  C6_1,  C7_1  }, // LEDA12 2,0
    { 0, C9_1,  C3_1,  C5_1  }, // LEDA11 3,0
    { 0, C8_10, C6_10, C7_10 }, // LEDB22 0,1
    { 0, C9_10, C3_10, C5_10 }, // LEDB21 1,1
    { 0, C8_2,  C6_2,  C7_2  }, // LEDA22 2,1
    { 0, C9_2,  C3_2,  C5_2  }, // LEDA21 3,1
    { 0, C8_11, C6_11, C7_11 }, // LEDB32 0,2
    { 0, C9_11, C2_10, C5_11 }, // LEDB31 1,2
    { 0, C8_3,  C6_3,  C7_3  }, // LEDA32 2,2
    { 0, C9_3,  C2_2,  C5_3  }, // LEDA31 3,2
    { 0, C8_12, C6_12, C7_12 }, // LEDB42 0,3
    { 0, C9_12, C2_11, C5_12 }, // LEDB41 1,3
    { 0, C8_4,  C6_4,  C7_4  }, // LEDA42 2,3
    { 0, C9_4,  C2_3,  C5_4  }, // LEDA41 3,3
};
#endif
