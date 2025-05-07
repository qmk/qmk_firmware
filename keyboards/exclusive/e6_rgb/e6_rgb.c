#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
//cs1
    {0, SW11_CS1,    SW10_CS1,    SW12_CS1},
    {0, SW8_CS1,    SW7_CS1,    SW9_CS1},
    {0, SW5_CS1,    SW4_CS1,    SW6_CS1},
    {0, SW2_CS1,    SW1_CS1,    SW3_CS1},

//cs2
    {0, SW11_CS2,    SW10_CS2,    SW12_CS2},
    {0, SW8_CS2,    SW7_CS2,    SW9_CS2},
    {0, SW5_CS2,    SW4_CS2,    SW6_CS2},
    {0, SW2_CS2,    SW1_CS2,    SW3_CS2},
//cs3
    {0, SW11_CS3,    SW10_CS3,    SW12_CS3},
    {0, SW8_CS3,    SW7_CS3,    SW9_CS3},
    {0, SW5_CS3,    SW4_CS3,    SW6_CS3},
    {0, SW2_CS3,    SW1_CS3,    SW3_CS3},
//cs4
    {0, SW11_CS4,    SW10_CS4,    SW12_CS4},
    {0, SW8_CS4,    SW7_CS4,    SW9_CS4},
    {0, SW5_CS4,    SW4_CS4,    SW6_CS4},
    {0, SW2_CS4,    SW1_CS4,    SW3_CS4},
//cs5
    {0, SW11_CS5,    SW10_CS5,    SW12_CS5},
    {0, SW8_CS5,    SW7_CS5,    SW9_CS5},
    {0, SW5_CS5,    SW4_CS5,    SW6_CS5},
    {0, SW2_CS5,    SW1_CS5,    SW3_CS5},
//cs6
    {0, SW11_CS6,    SW10_CS6,    SW12_CS6},
    {0, SW8_CS6,    SW7_CS6,    SW9_CS6},
    {0, SW5_CS6,    SW4_CS6,    SW6_CS6},
    {0, SW2_CS6,    SW1_CS6,    SW3_CS6},
//cs7
    {0, SW11_CS7,    SW10_CS7,    SW12_CS7},
    {0, SW8_CS7,    SW7_CS7,    SW9_CS7},
    {0, SW5_CS7,    SW4_CS7,    SW6_CS7},
    {0, SW2_CS7,    SW1_CS7,    SW3_CS7},
//cs8
    {0, SW11_CS8,    SW10_CS8,    SW12_CS8},
    {0, SW8_CS8,    SW7_CS8,    SW9_CS8},
    {0, SW5_CS8,    SW4_CS8,    SW6_CS8},
    {0, SW2_CS8,    SW1_CS8,    SW3_CS8},
//cs9
    {0, SW11_CS9,    SW10_CS9,    SW12_CS9},
    {0, SW8_CS9,    SW7_CS9,    SW9_CS9},
    {0, SW5_CS9,    SW4_CS9,    SW6_CS9},
    {0, SW2_CS9,    SW1_CS9,    SW3_CS9},
//cs10
    {0, SW11_CS10,   SW10_CS10,   SW12_CS10},
    {0, SW8_CS10,   SW7_CS10,   SW9_CS10},
    {0, SW5_CS10,   SW4_CS10,   SW6_CS10},
    {0, SW2_CS10,   SW1_CS10,   SW3_CS10},
//cs11
    {0, SW11_CS11,   SW10_CS11,   SW12_CS11},
    {0, SW8_CS11,   SW7_CS11,   SW9_CS11},
    {0, SW5_CS11,   SW4_CS11,   SW6_CS11},
    {0, SW2_CS11,   SW1_CS11,   SW3_CS11},
//cs12
    {0, SW11_CS12,   SW10_CS12,   SW12_CS12},
    {0, SW8_CS12,   SW7_CS12,   SW9_CS12},
    {0, SW5_CS12,   SW4_CS12,   SW6_CS12},
    {0, SW2_CS12,   SW1_CS12,   SW3_CS12},
//cs13
    {0, SW11_CS13,   SW10_CS13,   SW12_CS13},
    {0, SW8_CS13,   SW7_CS13,   SW9_CS13},
    {0, SW5_CS13,   SW4_CS13,   SW6_CS13},
    {0, SW2_CS13,   SW1_CS13,   SW3_CS13},
//cs14
    {0, SW11_CS14,   SW10_CS14,   SW12_CS14},
    {0, SW8_CS14,   SW7_CS14,   SW9_CS14},
    {0, SW5_CS14,   SW4_CS14,   SW6_CS14},
    {0, SW2_CS14,   SW1_CS14,   SW3_CS14},
//cs15
    {0, SW11_CS15,   SW10_CS15,   SW12_CS15},

    {0, SW5_CS15,   SW4_CS15,   SW6_CS15},
    {0, SW2_CS15,   SW1_CS15,   SW3_CS15},
//cs16
    {0, SW11_CS16,   SW10_CS16,   SW12_CS16},
    {0, SW8_CS16,   SW7_CS16,   SW9_CS16},
    {0, SW5_CS16,   SW4_CS16,   SW6_CS16},
    {0, SW2_CS16,   SW1_CS16,   SW3_CS16},
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
    if (!process_record_user(keycode, record)) {
        return false;
    }

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
