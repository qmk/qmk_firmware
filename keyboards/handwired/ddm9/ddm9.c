#include "ddm9.h"

#ifdef RGB_MATRIX_ENABLE

#define LED_POS(col, row) { col * (224 / 2), row * (64 / 2) }

led_config_t g_led_config = {
    /* key matrix to led matrix */
    {
        { 0, 3, 6, 1, 4, 7, 2, 5, 8 }
    },
    /* led index to physical position */
    {
        LED_POS(0, 0), LED_POS(1, 0), LED_POS(1, 0),
        LED_POS(0, 1), LED_POS(1, 1), LED_POS(2, 1),
        LED_POS(0, 2), LED_POS(1, 2), LED_POS(1, 2)
    },
    /* led types */
    {
        4, 4, 4,
        4, 4, 4,
        4, 4, 4
    }
};

#endif
