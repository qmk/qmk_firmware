// Copyright 2019 Yiancar
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#if defined(RGB_MATRIX_ENABLE)
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, SW2_CS1,   SW1_CS1,   SW3_CS1}, //LA1 - esc
    {0, SW2_CS2,   SW1_CS2,   SW3_CS2}, //LA5 - 1
    {0, SW2_CS3,   SW1_CS3,   SW3_CS3}, //LA9 - 2
    {0, SW2_CS4,   SW1_CS4,   SW3_CS4}, //LA13 - 3
    {0, SW2_CS5,   SW1_CS5,   SW3_CS5}, //LA17 - 4
    {0, SW2_CS6,   SW1_CS6,   SW3_CS6}, //LA21 - 5
    {0, SW2_CS7,   SW1_CS7,   SW3_CS7}, //LA25 - 6
    {0, SW2_CS8,   SW1_CS8,   SW3_CS8}, //LA29 - 7
    {0, SW2_CS9,   SW1_CS9,   SW3_CS9}, //LA33 - 8
    {0, SW2_CS10,  SW1_CS10,  SW3_CS10}, //LA37 - 9
    {0, SW2_CS11,  SW1_CS11,  SW3_CS11}, //LA41 - 0
    {0, SW2_CS12,  SW1_CS12,  SW3_CS12}, //LA45 - -
    {0, SW2_CS13,  SW1_CS13,  SW3_CS13}, //LA49 - =
    {0, SW2_CS14,  SW1_CS14,  SW3_CS14}, //LA53 - bspace
    {1, SW2_CS1,   SW1_CS1,   SW3_CS1}, //LB1 - home
    {0, SW5_CS1,   SW4_CS1,   SW6_CS1}, //LA2 - tab
    {0, SW5_CS2,   SW4_CS2,   SW6_CS2}, //LA6 - q
    {0, SW5_CS3,   SW4_CS3,   SW6_CS3}, //LA10 - w
    {0, SW5_CS4,   SW4_CS4,   SW6_CS4}, //LA14 - e
    {0, SW5_CS5,   SW4_CS5,   SW6_CS5}, //LA18 - r
    {0, SW5_CS6,   SW4_CS6,   SW6_CS6}, //LA22 - t
    {0, SW5_CS7,   SW4_CS7,   SW6_CS7}, //LA26 - y
    {0, SW5_CS8,   SW4_CS8,   SW6_CS8}, //LA30 - u
    {0, SW5_CS9,   SW4_CS9,   SW6_CS9}, //LA34 - i
    {0, SW5_CS10,  SW4_CS10,  SW6_CS10}, //LA38 - o
    {0, SW5_CS11,  SW4_CS11,  SW6_CS11}, //LA42 - p
    {0, SW5_CS12,  SW4_CS12,  SW6_CS12}, //LA46 - [
    {0, SW5_CS13,  SW4_CS13,  SW6_CS13}, //LA50 - ]
    {0, SW5_CS14,  SW4_CS14,  SW6_CS14}, //LA54 - |
    {1, SW5_CS1,   SW4_CS1,   SW6_CS1}, //LB2 - pgup
    {0, SW8_CS1,   SW7_CS1,   SW9_CS1}, //LA3 - caps
    {0, SW8_CS2,   SW7_CS2,   SW9_CS2}, //LA7 - a
    {0, SW8_CS3,   SW7_CS3,   SW9_CS3}, //LA11 - s
    {0, SW8_CS4,   SW7_CS4,   SW9_CS4}, //LA15 - d
    {0, SW8_CS5,   SW7_CS5,   SW9_CS5}, //LA19 - f
    {0, SW8_CS6,   SW7_CS6,   SW9_CS6}, //LA23 - g
    {0, SW8_CS7,   SW7_CS7,   SW9_CS7}, //LA27 - h
    {0, SW8_CS8,   SW7_CS8,   SW9_CS8}, //LA31 - j
    {0, SW8_CS9,   SW7_CS9,   SW9_CS9}, //LA35 - k
    {0, SW8_CS10,  SW7_CS10,  SW9_CS10}, //LA39 - l
    {0, SW8_CS11,  SW7_CS11,  SW9_CS11}, //LA43 - ;
    {0, SW8_CS12,  SW7_CS12,  SW9_CS12}, //LA47 - '
    {0, SW8_CS14,  SW7_CS14,  SW9_CS14}, //LA55 - ent
    {1, SW2_CS2,   SW1_CS2,   SW3_CS2}, //LB5 - pgdn
    {0, SW11_CS1,   SW10_CS1,   SW12_CS1}, //LA4 - lshft
    {0, SW11_CS2,   SW10_CS2,   SW12_CS2}, //LA8 - z
    {0, SW11_CS3,   SW10_CS3,   SW12_CS3}, //LA12 - x
    {0, SW11_CS4,   SW10_CS4,   SW12_CS4}, //LA16 - c
    {0, SW11_CS5,   SW10_CS5,   SW12_CS5}, //LA20 - v
    {0, SW11_CS6,   SW10_CS6,   SW12_CS6}, //LA24 - b
    {0, SW11_CS7,   SW10_CS7,   SW12_CS7}, //LA28 - n
    {0, SW11_CS8,   SW10_CS8,   SW12_CS8}, //LA32 - m
    {0, SW11_CS9,   SW10_CS9,   SW12_CS9}, //LA36 - <
    {0, SW11_CS10,  SW10_CS10,  SW12_CS10}, //LA40 - >
    {0, SW11_CS11,  SW10_CS11,  SW12_CS11}, //LA44 - ?
    {0, SW8_CS13,  SW7_CS13,  SW9_CS13}, //LA51 - rshift
    {0, SW11_CS13,  SW10_CS13,  SW12_CS13}, //LA52 - up
    {1, SW8_CS1,   SW7_CS1,   SW9_CS1}, //LB3 - end
    {0, SW2_CS15,  SW1_CS15,  SW3_CS15}, //LA57 - lctrl
    {0, SW5_CS15,  SW4_CS15,  SW6_CS15}, //LA58 - lgui
    {0, SW8_CS15,  SW7_CS15,  SW9_CS15}, //LA59 - lalt
    {0, SW11_CS15,  SW10_CS15,  SW12_CS15}, //LA60 space
    {0, SW11_CS12,  SW10_CS12,  SW12_CS12}, //LA48 - ralt
    {0, SW5_CS16,  SW4_CS16,  SW6_CS16}, //LA62 - fn
    {0, SW8_CS16,  SW7_CS16,  SW9_CS16}, //LA63 - rctrl
    {0, SW11_CS16,  SW10_CS16,  SW12_CS16}, //LA64 - left
    {0, SW11_CS14,  SW10_CS14,  SW12_CS14}, //LA56 - down
    {1, SW11_CS1,   SW10_CS1,   SW12_CS1}, //LB4 - right

    // Mapped with "dead" locations so each indicator is logically separate
    {1, SW2_CS3,   SW7_CS2,   SW3_CS3}, //LB7 - top indi
    {1, SW5_CS2,   SW10_CS2,  SW6_CS2}, //LB6 - mid indi
    {1, SW11_CS2,  SW4_CS2,   SW12_CS2}, //LB6 - bot indi
};
#endif

/* Indicator LEDS are part of the LED driver
 * Top LED is blue only. LED driver 2 RGB 7 Green channel
 * Middle LED is blue and red. LED driver 2 RGB 6 Red and Blue channel
 * Bottom LED is red only LED driver 2 RGB 6 Green channel.
 */
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(68, RGB_WHITE); //0, 0xFF, 0);
    } else {
        rgb_matrix_set_color(68, RGB_OFF);
    }

    layer_state_t state = layer_state|default_layer_state;
    if (state & (1UL << 1)) {
        rgb_matrix_set_color(69, RGB_WHITE); // 0xFF, 0, 0xFF);
    } else {
        rgb_matrix_set_color(69, RGB_OFF);
    }

    if (state & (1UL << 2)) {
        rgb_matrix_set_color(70, RGB_WHITE); //0, 0xFF, 0);
    } else {
        rgb_matrix_set_color(70, RGB_OFF);
    }

    return true;
}
