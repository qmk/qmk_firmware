#include "disco9.h"

#ifdef RGB_MATRIX_ENABLE

#define LED_POS(col, row) { col * (224 / 2), row * (64 / 2) }

led_config_t g_led_config = {
    /* key matrix to led matrix */
    {
        { 2, 1, 0 },
        { 3, 4, 5 },
        { 8, 7, 6 },
    },
    /* led index to physical position */
    {
        /* reversemounts */
        LED_POS(2, 0), LED_POS(1, 0), LED_POS(0, 0),
        LED_POS(0, 1), LED_POS(1, 1), LED_POS(2, 1),
        LED_POS(2, 2), LED_POS(1, 2), LED_POS(0, 2),
        /* smds */
        LED_POS(0.5, 2), LED_POS(1.5, 2),
        LED_POS(2, 1.5), LED_POS(1, 1.5), LED_POS(0, 1.5),
        LED_POS(0.5, 1), LED_POS(1.5, 1),
        LED_POS(2, 0.5), LED_POS(1, 0.5), LED_POS(0, 0.5),
        LED_POS(0.5, 0), LED_POS(1.5, 0)
    },
    /* led types */
    {
        4, 4, 4,
        4, 4, 4,
        4, 4, 4,
        4, 4,
        4, 4, 4,
        4, 4,
        4, 4, 4,
        4, 4
    }
};

#endif
