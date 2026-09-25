// Copyright 2026 AeroModes
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Driver
 *   |  R        G        B */
    {0, SW2_CS1, SW1_CS1, SW3_CS1},       // KC_ESC
    {0, SW2_CS2, SW1_CS2, SW3_CS2},       // KC_F1
    {0, SW2_CS3, SW1_CS3, SW3_CS3},       // KC_F2
    {0, SW2_CS4, SW1_CS4, SW3_CS4},       // KC_F3
    {0, SW2_CS5, SW1_CS5, SW3_CS5},       // KC_F4
    {0, SW2_CS6, SW1_CS6, SW3_CS6},       // KC_F5
    {0, SW2_CS7, SW1_CS7, SW3_CS7},       // KC_F6
    {0, SW2_CS8, SW1_CS8, SW3_CS8},       // KC_F7
    {0, SW2_CS9, SW1_CS9, SW3_CS9},       // KC_F8
    {0, SW2_CS10, SW1_CS10, SW3_CS10},    // KC_F9
    {0, SW2_CS11, SW1_CS11, SW3_CS11},    // KC_F10
    {0, SW2_CS12, SW1_CS12, SW3_CS12},    // KC_F11
    {0, SW2_CS13, SW1_CS13, SW3_CS13},    // KC_F12
    {0, SW2_CS14, SW1_CS14, SW3_CS14},    // KC_PSCR
    {0, SW2_CS15, SW1_CS15, SW3_CS15},    // KC_SCRL
    {1, SW2_CS3, SW1_CS3, SW3_CS3},       // KC_PAUS
    {0, SW5_CS1, SW4_CS1, SW6_CS1},       // KC_GRV
    {0, SW5_CS2, SW4_CS2, SW6_CS2},       // KC_1
    {0, SW5_CS3, SW4_CS3, SW6_CS3},       // KC_2
    {0, SW5_CS4, SW4_CS4, SW6_CS4},       // KC_3
    {0, SW5_CS5, SW4_CS5, SW6_CS5},       // KC_4
    {0, SW5_CS6, SW4_CS6, SW6_CS6},       // KC_5
    {0, SW5_CS7, SW4_CS7, SW6_CS7},       // KC_6
    {0, SW5_CS8, SW4_CS8, SW6_CS8},       // KC_7
    {0, SW5_CS9, SW4_CS9, SW6_CS9},       // KC_8
    {0, SW5_CS10, SW4_CS10, SW6_CS10},    // KC_9
    {0, SW5_CS11, SW4_CS11, SW6_CS11},    // KC_0
    {0, SW5_CS12, SW4_CS12, SW6_CS12},    // KC_MINS
    {0, SW5_CS13, SW4_CS13, SW6_CS13},    // KC_EQL
    {0, SW5_CS15, SW4_CS15, SW6_CS15},    // KC_BSPC
    {1, SW2_CS4, SW1_CS4, SW3_CS4},       // KC_INS
    {1, SW2_CS5, SW1_CS5, SW3_CS5},       // KC_HOME
    {1, SW2_CS6, SW1_CS6, SW3_CS6},       // KC_PGUP
    {1, SW2_CS7, SW1_CS7, SW3_CS7},       // KC_NUM
    {1, SW2_CS8, SW1_CS8, SW3_CS8},       // KC_PSLS
    {1, SW2_CS9, SW1_CS9, SW3_CS9},       // KC_PAST
    {1, SW2_CS10, SW1_CS10, SW3_CS10},    // KC_PMNS
    {0, SW8_CS1, SW7_CS1, SW9_CS1},       // KC_TAB
    {0, SW8_CS2, SW7_CS2, SW9_CS2},       // KC_Q
    {0, SW8_CS3, SW7_CS3, SW9_CS3},       // KC_W
    {0, SW8_CS4, SW7_CS4, SW9_CS4},       // KC_E
    {0, SW8_CS5, SW7_CS5, SW9_CS5},       // KC_R
    {0, SW8_CS6, SW7_CS6, SW9_CS6},       // KC_T
    {0, SW8_CS7, SW7_CS7, SW9_CS7},       // KC_Y
    {0, SW8_CS8, SW7_CS8, SW9_CS8},       // KC_U
    {0, SW8_CS9, SW7_CS9, SW9_CS9},       // KC_I
    {0, SW8_CS10, SW7_CS10, SW9_CS10},    // KC_O
    {0, SW8_CS11, SW7_CS11, SW9_CS11},    // KC_P
    {0, SW8_CS12, SW7_CS12, SW9_CS12},    // KC_LBRC
    {0, SW8_CS13, SW7_CS13, SW9_CS13},    // KC_RBRC
    {0, SW8_CS14, SW7_CS14, SW9_CS14},    // KC_BSLS
    {1, SW2_CS11, SW1_CS11, SW3_CS11},    // KC_DEL
    {1, SW2_CS12, SW1_CS12, SW3_CS12},    // KC_END
    {1, SW2_CS13, SW1_CS13, SW3_CS13},    // KC_PGDN
    {1, SW2_CS14, SW1_CS14, SW3_CS14},    // KC_P7
    {1, SW2_CS15, SW1_CS15, SW3_CS15},    // KC_P8
    {1, SW11_CS3, SW10_CS3, SW12_CS3},    // KC_P9
    {1, SW5_CS4, SW4_CS4, SW6_CS4},       // KC_PPLS
    {0, SW11_CS1, SW10_CS1, SW12_CS1},    // KC_CAPS
    {0, SW11_CS2, SW10_CS2, SW12_CS2},    // KC_A
    {0, SW11_CS3, SW10_CS3, SW12_CS3},    // KC_S
    {0, SW11_CS4, SW10_CS4, SW12_CS4},    // KC_D
    {0, SW11_CS5, SW10_CS5, SW12_CS5},    // KC_F
    {0, SW11_CS6, SW10_CS6, SW12_CS6},    // KC_G
    {0, SW11_CS7, SW10_CS7, SW12_CS7},    // KC_H
    {0, SW11_CS8, SW10_CS8, SW12_CS8},    // KC_J
    {0, SW11_CS9, SW10_CS9, SW12_CS9},    // KC_K
    {0, SW11_CS10, SW10_CS10, SW12_CS10}, // KC_L
    {0, SW11_CS11, SW10_CS11, SW12_CS11}, // KC_SCLN
    {0, SW11_CS12, SW10_CS12, SW12_CS12}, // KC_QUOT
    {0, SW11_CS14, SW10_CS14, SW12_CS14}, // KC_ENT
    {1, SW5_CS9, SW4_CS9, SW6_CS9},       // KC_P4
    {1, SW5_CS7, SW4_CS7, SW6_CS7},       // KC_P5
    {1, SW5_CS5, SW4_CS5, SW6_CS5},       // KC_P6
    {0, SW11_CS16, SW10_CS16, SW12_CS16}, // KC_LSFT
    {1, SW8_CS15, SW7_CS15, SW9_CS15},    // KC_Z
    {1, SW8_CS14, SW7_CS14, SW9_CS14},    // KC_X
    {1, SW8_CS13, SW7_CS13, SW9_CS13},    // KC_C
    {1, SW8_CS12, SW7_CS12, SW9_CS12},    // KC_V
    {1, SW8_CS11, SW7_CS11, SW9_CS11},    // KC_B
    {1, SW8_CS10, SW7_CS10, SW9_CS10},    // KC_N
    {1, SW8_CS9, SW7_CS9, SW9_CS9},       // KC_M
    {1, SW8_CS8, SW7_CS8, SW9_CS8},       // KC_COMM
    {1, SW8_CS7, SW7_CS7, SW9_CS7},       // KC_DOT
    {1, SW8_CS6, SW7_CS6, SW9_CS6},       // KC_SLSH
    {1, SW8_CS4, SW7_CS4, SW9_CS4},       // KC_RSFT
    {1, SW5_CS16, SW4_CS16, SW6_CS16},    // KC_UP
    {1, SW5_CS10, SW4_CS10, SW6_CS10},    // KC_P1
    {1, SW5_CS8, SW4_CS8, SW6_CS8},       // KC_P2
    {1, SW5_CS6, SW4_CS6, SW6_CS6},       // KC_P3
    {1, SW5_CS3, SW4_CS3, SW6_CS3},       // KC_PENT
    {1, SW11_CS15, SW10_CS15, SW12_CS15}, // KC_LCTL
    {1, SW11_CS14, SW10_CS14, SW12_CS14}, // KC_LGUI
    {1, SW11_CS13, SW10_CS13, SW12_CS13}, // KC_LALT
    {1, SW11_CS11, SW10_CS11, SW12_CS11}, // KC_SPC
    {1, SW11_CS8, SW10_CS8, SW12_CS8},    // KC_RALT
    {1, SW11_CS6, SW10_CS6, SW12_CS6},    // MO(_FN)
    {1, SW11_CS5, SW10_CS5, SW12_CS5},    // KC_APP
    {1, SW11_CS4, SW10_CS4, SW12_CS4},    // KC_RCTL
    {1, SW8_CS3, SW7_CS3, SW9_CS3},       // KC_LEFT
    {1, SW8_CS2, SW7_CS2, SW9_CS2},       // KC_DOWN
    {1, SW8_CS1, SW7_CS1, SW9_CS1},       // KC_RGHT
    {1, SW5_CS1, SW4_CS1, SW6_CS1},       // KC_P0
    {1, SW5_CS2, SW4_CS2, SW6_CS2},       // KC_PDOT
    {1, SW5_CS11, SW4_CS11, SW6_CS11},    // Game
    {1, SW5_CS12, SW4_CS12, SW6_CS12},    // Macro
    {1, SW5_CS13, SW4_CS13, SW6_CS13},    // Scroll
    {1, SW5_CS14, SW4_CS14, SW6_CS14},    // Num
    {1, SW5_CS15, SW4_CS15, SW6_CS15},    // Caps
    {1, SW11_CS7, SW10_CS7, SW12_CS7},    // Logo
};

#    define LED_IDX_GAME (RGB_MATRIX_LED_COUNT - 6)
#    define LED_IDX_MACRO (RGB_MATRIX_LED_COUNT - 5)
#    define LED_IDX_SCROLL (RGB_MATRIX_LED_COUNT - 4)
#    define LED_IDX_NUM (RGB_MATRIX_LED_COUNT - 3)
#    define LED_IDX_CAPS (RGB_MATRIX_LED_COUNT - 2)

static void set_indicator(uint8_t index, bool on, uint8_t led_min, uint8_t led_max) {
    RGB_MATRIX_INDICATOR_SET_COLOR(index, on ? 255 : 0, on ? 255 : 0, on ? 255 : 0);
}

#    ifdef DYNAMIC_MACRO_ENABLE
static bool macro_recording = false;

bool dynamic_macro_record_start_kb(int8_t direction) {
    if (!dynamic_macro_record_start_user(direction)) return false;
    macro_recording = true;
    return true;
}

bool dynamic_macro_record_end_kb(int8_t direction) {
    if (!dynamic_macro_record_end_user(direction)) return false;
    macro_recording = false;
    return true;
}
#    endif

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    bool macro_on = false;
#    ifdef DYNAMIC_MACRO_ENABLE
    macro_on = macro_recording;
#    endif
    led_t led_state = host_keyboard_led_state();
    // Game = GUI lock, Macro = Dynamic macro recording
    set_indicator(LED_IDX_GAME, keymap_config.no_gui, led_min, led_max);
    set_indicator(LED_IDX_MACRO, macro_on, led_min, led_max);
    set_indicator(LED_IDX_SCROLL, led_state.scroll_lock, led_min, led_max);
    set_indicator(LED_IDX_NUM, led_state.num_lock, led_min, led_max);
    set_indicator(LED_IDX_CAPS, led_state.caps_lock, led_min, led_max);
    return true;
}
#endif
