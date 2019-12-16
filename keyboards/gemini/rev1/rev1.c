#include "gemini.h"
#include "split_util.h"         /* isLeftHand */

#define LED_POS(col, row) { col * (224 / 11), row * (64 / 3) }

led_config_t g_led_config = {
    /* key matrix to led matrix */
    {
        { 0,      1,      2,      3,      4,  5  },
        { 6,      7,      8,      9,      10, 11 },
        { 12,     13,     14,     15,     16, 17 },
        { NO_LED, NO_LED, NO_LED, NO_LED, 18, 19 },
        /* 20, 21, 22, 23, 24, 25 are underglows */
        { 26,     27,     28,     29,     30, 31 },
        { 32,     33,     34,     35,     36, 37 },
        { 38,     39,     40,     41,     42, 43 },
        { NO_LED, NO_LED, NO_LED, NO_LED, 44, 45 },
        /* 46, 47, 48, 49, 50, 51 are underglows */
    },
    /* led index to physical position */
    {
        /* backlights */
        LED_POS(0, 0), LED_POS(1, 0), LED_POS(2, 0), LED_POS(3, 0), LED_POS(4, 0), LED_POS(5, 0),
        LED_POS(0, 1), LED_POS(1, 1), LED_POS(2, 1), LED_POS(3, 1), LED_POS(4, 1), LED_POS(5, 1),
        LED_POS(0, 2), LED_POS(1, 2), LED_POS(2, 2), LED_POS(3, 2), LED_POS(4, 2), LED_POS(5, 2),
        LED_POS(4, 3), LED_POS(5, 3),
        /* underglows */
        LED_POS(0.5, 0.5), LED_POS(2.5, 0.5), LED_POS(4.5, 0.5),
        LED_POS(0.5, 2.0), LED_POS(2.5, 2.0), LED_POS(4.5, 2.0),
        /* backlights */
        LED_POS(11, 0), LED_POS(10, 0), LED_POS(9, 0), LED_POS(8, 0), LED_POS(7, 0), LED_POS(6, 0),
        LED_POS(11, 1), LED_POS(10, 1), LED_POS(9, 1), LED_POS(8, 1), LED_POS(7, 1), LED_POS(6, 1),
        LED_POS(11, 2), LED_POS(10, 2), LED_POS(9, 2), LED_POS(8, 2), LED_POS(7, 2), LED_POS(6, 2),
        LED_POS(7, 3), LED_POS(6, 3),
        /* underglows */
        LED_POS(10.5, 0.5), LED_POS(8.5, 0.5), LED_POS(6.5, 0.5),
        LED_POS(10.5, 2.0), LED_POS(8.5, 2.0), LED_POS(6.5, 2.0),
    },
    /* led types */
    {
        /* backlights */
        1, 4, 4, 4, 4, 4,
        1, 4, 4, 4, 4, 4,
        1, 4, 4, 4, 4, 4,
        1, 1,
        /* underglows */
        2, 2, 2,
        2, 2, 2,
        /* backlights */
        1, 4, 4, 4, 4, 4,
        1, 4, 4, 4, 4, 4,
        1, 4, 4, 4, 4, 4,
        1, 1,
        /* underglows */
        2, 2, 2,
        2, 2, 2,
    }
};

void keyboard_post_init_kb (void) {
    if (!isLeftHand) {
        rgb_matrix_disable_noeeprom();
    }
    keyboard_post_init_user();
}
