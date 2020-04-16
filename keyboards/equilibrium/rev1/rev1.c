#include "equilibrium.h"

/* (col + span / 2): 0 - 11.5, row: 0 - 3 */
#define LED_POS(col, row, span) { (col + span / 2) * (224 / 11.5), row * (64 / 3) }

led_config_t g_led_config = {
    /* key matrix to led matrix */
    {
        { 0,      2,      4,      6,      8,      10 },
        { 1,      3,      5,      7,      9,      11 },
        { 12,     14,     16,     18,     20,     22 },
        { 13,     15,     17,     19,     21,     23 },
        { 24,     26,     28,     30,     32,     34 },
        { 25,     27,     29,     31,     33,     NO_LED },
        { NO_LED, 35,     37,     39,     NO_LED, NO_LED },
        { NO_LED, NO_LED, 36,     38,     40,     NO_LED }
    },
    /* led index to physical position */
    {
        /* backlights - qwer (0-11) */
        LED_POS(0, 0, 0), LED_POS(1, 0, 0), LED_POS( 2, 0, 0), LED_POS( 3, 0, 0),
        LED_POS(4, 0, 0), LED_POS(5, 0, 0), LED_POS( 6, 0, 0), LED_POS( 7, 0, 0),
        LED_POS(8, 0, 0), LED_POS(9, 0, 0), LED_POS(10, 0, 0), LED_POS(11, 0, 0.5),
        /* backlights - asdf (12-23) */
        LED_POS(0, 1, 0.25), LED_POS(1.25, 1, 0), LED_POS(2.25,  1, 0), LED_POS(3.25,  1, 0),
        LED_POS(4.25, 1, 0), LED_POS(5.25, 1, 0), LED_POS(6.25,  1, 0), LED_POS(7.25,  1, 0),
        LED_POS(8.25, 1, 0), LED_POS(9.25, 1, 0), LED_POS(10.25, 1, 0), LED_POS(11.25, 1, 0.25),
        /* backlights - zxcv (24-34) */
        LED_POS(0.25, 2, 0.5), LED_POS(1.75, 2, 0), LED_POS(2.75, 2, 0), LED_POS(3.75, 2, 0),
        LED_POS(4.75, 2, 0),   LED_POS(5.75, 2, 0), LED_POS(6.75, 2, 0), LED_POS(7.75, 2, 0),
        LED_POS(8.75, 2, 0),   LED_POS(9.75, 2, 0), LED_POS(10.75, 2, 0.5),
        /* backlights - thumbs (35-40) */
        LED_POS(2.25, 3, 0.25), LED_POS(3.5, 3, 0), LED_POS(4.5, 3, 0.75),
        LED_POS(6.25, 3, 0.75), LED_POS(8,   3, 0), LED_POS(9,   3, 0.25),
        /* underglows - bottom (41-45) */
        LED_POS(8.5, 2.5, 0), LED_POS(7.5, 2.5, 0), LED_POS(5.75, 2.5, 0),
        LED_POS(4, 2.5, 0), LED_POS(3, 2.5, 0),
        /* underglows - lower (46-55) */
        LED_POS(10.75, 1.5, 0), LED_POS(9.75, 1.5, 0), LED_POS(8.75, 1.5, 0),
        LED_POS(7.75,  1.5, 0), LED_POS(6.75, 1.5, 0), LED_POS(5.75, 1.5, 0),
        LED_POS(4.75,  1.5, 0), LED_POS(3.75, 1.5, 0), LED_POS(2.75, 1.5, 0),
        LED_POS(1.75,  1.5, 0),
        /* underglows - upper (56-66) */
        LED_POS(11, 0.5, 0), LED_POS(10, 0.5, 0), LED_POS(9, 0.5, 0),
        LED_POS(8,  0.5, 0), LED_POS(7,  0.5, 0), LED_POS(6, 0.5, 0),
        LED_POS(5,  0.5, 0), LED_POS(4,  0.5, 0), LED_POS(3, 0.5, 0),
        LED_POS(2,  0.5, 0), LED_POS(1,  0.5, 0)
    },
    /* led types */
    {
        /* backlights */
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 1, 1, 1,
        /* underglows */
        2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    }
};

void keyboard_post_init_kb (void) {
    keyboard_post_init_user();
}
