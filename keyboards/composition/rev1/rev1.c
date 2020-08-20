#include "composition.h"

/* col: 0 - 11, row: 0 - 3 */
#define LED_POS(col, row) { col * (224 / 11), row * (64 / 3) }

led_config_t g_led_config = {
    /* key matrix to led matrix */
    {
        { 0,      2,      4,      6,      8,      10 },
        { 1,      3,      5,      7,      9,      11 },
        { 12,     14,     16,     18,     20,     22 },
        { 13,     15,     17,     19,     21,     23 },
        { 24,     26,     28,     30,     32,     34 },
        { 25,     27,     29,     31,     33,     35 },
        { NO_LED, 36,     38,     40,     NO_LED, NO_LED },
        { NO_LED, NO_LED, 37,     39,     NO_LED, NO_LED }
    },
    /* led index to physical position */
    {
        /* backlights - qwer (0-11) */
        LED_POS(0, 0), LED_POS(1, 0), LED_POS( 2, 0), LED_POS( 3, 0),
        LED_POS(4, 0), LED_POS(5, 0), LED_POS( 6, 0), LED_POS( 7, 0),
        LED_POS(8, 0), LED_POS(9, 0), LED_POS(10, 0), LED_POS(11, 0),
        /* backlights - asdf (12-23) */
        LED_POS(0, 1), LED_POS(1, 1), LED_POS( 2, 1), LED_POS( 3, 1),
        LED_POS(4, 1), LED_POS(5, 1), LED_POS( 6, 1), LED_POS( 7, 1),
        LED_POS(8, 1), LED_POS(9, 1), LED_POS(10, 1), LED_POS(11, 1),
        /* backlights - zxcv (24-35) */
        LED_POS(0, 2), LED_POS(1, 2), LED_POS( 2, 2), LED_POS( 3, 2),
        LED_POS(4, 2), LED_POS(5, 2), LED_POS( 6, 2), LED_POS( 7, 2),
        LED_POS(8, 2), LED_POS(9, 2), LED_POS(10, 2), LED_POS(11, 2),
        /* backlights - thumbs (36-40) */
        LED_POS(3.5, 3), LED_POS(4.5, 3), LED_POS(5.5, 3),
        LED_POS(6.5, 3), LED_POS(7.5, 3),
        /* underglows - bottom (41-43) */
        LED_POS(7, 2.5), LED_POS(5.5, 2.5), LED_POS(4, 2.5),
        /* underglows - lower (44-49) */
        LED_POS(10.5, 1.5), LED_POS(8.5, 1.5), LED_POS(6.5, 1.5),
        LED_POS( 4.5, 1.5), LED_POS(2.5, 1.5), LED_POS(0.5, 1.5),
        /* underglows - upper (50-55) */
        LED_POS(10.5, 0.5), LED_POS(8.5, 0.5), LED_POS(6.5, 0.5),
        LED_POS( 4.5, 0.5), LED_POS(2.5, 0.5), LED_POS(0.5, 0.5)
    },
    /* led types */
    {
        /* backlights */
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 1, 1,
        /* underglows */
        2, 2, 2,
        2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2
    }
};

void keyboard_post_init_kb (void) {
    keyboard_post_init_user();
}
