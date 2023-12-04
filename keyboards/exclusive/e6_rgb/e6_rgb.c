#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
void matrix_init_kb(void) {
  setPinOutput(D5);
  writePinHigh(D5);
  matrix_init_user();
}

const is31fl3733_led_t PROGMEM g_is31fl3733_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
//cs1
    {0, K_1,    J_1,    L_1},
    {0, H_1,    G_1,    I_1},
    {0, E_1,    D_1,    F_1},
    {0, B_1,    A_1,    C_1},

//cs2
    {0, K_2,    J_2,    L_2},
    {0, H_2,    G_2,    I_2},
    {0, E_2,    D_2,    F_2},
    {0, B_2,    A_2,    C_2},
//cs3
    {0, K_3,    J_3,    L_3},
    {0, H_3,    G_3,    I_3},
    {0, E_3,    D_3,    F_3},
    {0, B_3,    A_3,    C_3},
//cs4
    {0, K_4,    J_4,    L_4},
    {0, H_4,    G_4,    I_4},
    {0, E_4,    D_4,    F_4},
    {0, B_4,    A_4,    C_4},
//cs5
    {0, K_5,    J_5,    L_5},
    {0, H_5,    G_5,    I_5},
    {0, E_5,    D_5,    F_5},
    {0, B_5,    A_5,    C_5},
//cs6
    {0, K_6,    J_6,    L_6},
    {0, H_6,    G_6,    I_6},
    {0, E_6,    D_6,    F_6},
    {0, B_6,    A_6,    C_6},
//cs7
    {0, K_7,    J_7,    L_7},
    {0, H_7,    G_7,    I_7},
    {0, E_7,    D_7,    F_7},
    {0, B_7,    A_7,    C_7},
//cs8
    {0, K_8,    J_8,    L_8},
    {0, H_8,    G_8,    I_8},
    {0, E_8,    D_8,    F_8},
    {0, B_8,    A_8,    C_8},
//cs9
    {0, K_9,    J_9,    L_9},
    {0, H_9,    G_9,    I_9},
    {0, E_9,    D_9,    F_9},
    {0, B_9,    A_9,    C_9},
//cs10
    {0, K_10,   J_10,   L_10},
    {0, H_10,   G_10,   I_10},
    {0, E_10,   D_10,   F_10},
    {0, B_10,   A_10,   C_10},
//cs11
    {0, K_11,   J_11,   L_11},
    {0, H_11,   G_11,   I_11},
    {0, E_11,   D_11,   F_11},
    {0, B_11,   A_11,   C_11},
//cs12
    {0, K_12,   J_12,   L_12},
    {0, H_12,   G_12,   I_12},
    {0, E_12,   D_12,   F_12},
    {0, B_12,   A_12,   C_12},
//cs13
    {0, K_13,   J_13,   L_13},
    {0, H_13,   G_13,   I_13},
    {0, E_13,   D_13,   F_13},
    {0, B_13,   A_13,   C_13},
//cs14
    {0, K_14,   J_14,   L_14},
    {0, H_14,   G_14,   I_14},
    {0, E_14,   D_14,   F_14},
    {0, B_14,   A_14,   C_14},
//cs15
    {0, K_15,   J_15,   L_15},

    {0, E_15,   D_15,   F_15},
    {0, B_15,   A_15,   C_15},
//cs16
    {0, K_16,   J_16,   L_16},
    {0, H_16,   G_16,   I_16},
    {0, E_16,   D_16,   F_16},
    {0, B_16,   A_16,   C_16},
};

led_config_t g_led_config = { {
    {   0,   1,   4,   5,  12,  13,  36,  20,  21,  24,  25,  16,  17,  28 },
    {   2,   6,   7,  14,  15,  37,  38,  22,  23,  26,  27,  18,  19,  30 },
    {   3,   8,   9,  32,  33,  39,  40,  44,  45,  48,  49,  52,  31, NO_LED },
    {  59,  10,  11,  34,  35,  41,  42,  46,  47,  50,  53,  54,  56, NO_LED },
    {  60,  61,  62, NO_LED, NO_LED,  43,  51,  55,  58,  57, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
//cs1
    {   0,   0 }, {  17,   0 }, {   0,  16 }, {   0,  32 },
//cs2
    {  34,   0 }, {  51,   0 }, {  17,  16 }, {  34,  16 },
//cs3
    {  17,  32 }, {  34,  32 }, {  17,  48 }, {  34,  48 },
//cs4
    {  68,   0 }, {  85,   0 }, {  51,  16 }, {  68,  16 },
//cs5
    { 187,   0 }, { 204,   0 }, { 187,  16 }, { 204,  16 },
//cs6
    { 119,   0 }, { 136,   0 }, { 119,  16 }, { 136,  16 },
//cs7
    { 153,   0 }, { 170,   0 }, { 153,  16 }, { 170,  16 },
//cs8
    { 221,   0 }, { 221,   0 }, { 221,  32 }, { 221,  16 },
//cs9
    {  51,  32 }, {  68,  32 }, {  51,  48 }, {  68,  48 },
//cs10
    { 102,   0 }, {  85,  16 }, { 102,  16 }, {  85,  32 },
//cs11
    { 102,  32 }, {  85,  48 }, { 102,  48 }, { 102,  64 },
//cs12
    { 119,  32 }, { 136,  32 }, { 119,  48 }, { 136,  48 },
//cs13
    { 153,  32 }, { 170,  32 }, { 153,  48 }, { 136,  48 },
//cs14
    { 187,  32 }, { 170,  48 }, { 187,  48 }, { 153,  48 },
//cs15
    { 221,  48 }, { 221,  64 }, { 204,  64 },
//cs16
    {   0,  48 }, {   0,  64 }, {  17,  64 }, {  34,  64 }
}, {
//cs1
    1, 4, 1, 1,
//cs2
    4, 4, 4, 4,
//cs3
    4, 4, 4, 4,
//cs4
    4, 4, 4, 4,
//cs5
    4, 4, 4, 4,
//cs6
    4, 4, 4, 4,
//cs7
    4, 4, 4, 4,
//cs8
    4, 4, 1, 1,
//cs9
    4, 4, 4, 4,
//cs10
    4, 4, 4, 4,
//cs11
    4, 4, 4, 4,
//cs12
    4, 4, 4, 4,
//cs13
    4, 4, 4, 1,
//cs14
    4, 4, 1, 1,
//cs15
    1, 1, 1,
//cs16
    1, 1, 1, 1
} };

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
#if defined(RGBLIGHT_ENABLE) && defined(RGB_MATRIX_ENABLE)
            case KC_F13: // toggle rgb matrix
                rgb_matrix_toggle();
                return false;
            case KC_F14:
                rgb_matrix_step();
                return false;
            case KC_F15:
                rgb_matrix_increase_hue();
                return false;
            case KC_F16:
                rgb_matrix_increase_sat();
                return false;
            case KC_F17:
                rgb_matrix_increase_val();
                return false;
#endif
            default:
                break;
        }
    }
  return true;
}
