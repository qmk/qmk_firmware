/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "voyager.h"
#include "raw_hid.h"

keyboard_config_t keyboard_config;

bool mcp23018_leds[2] = {0, 0};
bool is_launching     = false;

#ifdef DYNAMIC_MACRO_ENABLE
static bool is_dynamic_recording = false;

void dynamic_macro_record_start_user(int8_t direction) {
    is_dynamic_recording = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    is_dynamic_recording = false;
    STATUS_LED_3(false);
}
#endif

void voyager_led_task(void) {
#ifdef ORYX_ENABLE
    if (rawhid_state.rgb_control) return;
#endif
    if (is_launching) {
        STATUS_LED_1(false);
        STATUS_LED_2(false);
        STATUS_LED_3(false);
        STATUS_LED_4(false);

        STATUS_LED_1(true);
        wait_ms(250);
        STATUS_LED_2(true);
        wait_ms(250);
        STATUS_LED_3(true);
        wait_ms(250);
        STATUS_LED_4(true);
        wait_ms(250);
        STATUS_LED_1(false);
        wait_ms(250);
        STATUS_LED_2(false);
        wait_ms(250);
        STATUS_LED_3(false);
        wait_ms(250);
        STATUS_LED_4(false);
        wait_ms(250);
        is_launching = false;
        layer_state_set_kb(layer_state);
    }
#ifdef DYNAMIC_MACRO_ENABLE
    else if (is_dynamic_recording) {
        STATUS_LED_3(true);
        wait_ms(100);
        STATUS_LED_3(false);
        wait_ms(155);
    }
#endif
#if !defined(VOYAGER_USER_LEDS)
    else {
        layer_state_set_kb(layer_state);
    }
#endif
}

static THD_WORKING_AREA(waLEDThread, 128);
static THD_FUNCTION(LEDThread, arg) {
    (void)arg;
    chRegSetThreadName("LEDThread");
    while (true) {
        voyager_led_task();
    }
}

void keyboard_pre_init_kb(void) {
    // Initialize Reset pins
    setPinInput(A8);
    setPinOutput(A9);
    writePinLow(A9);

    setPinOutput(B5);
    setPinOutput(B4);
    setPinOutput(B3);

    writePinLow(B5);
    writePinLow(B4);
    writePinLow(B3);

    chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO - 16, LEDThread, NULL);
    keyboard_pre_init_user();
}

#if !defined(VOYAGER_USER_LEDS)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    if (is_launching || !keyboard_config.led_level) return state;
#ifdef ORYX_ENABLE
    if (rawhid_state.rgb_control) return state;
#endif
    uint8_t layer = get_highest_layer(state);

    STATUS_LED_1(layer & (1<<0));
    STATUS_LED_2(layer & (1<<1));
    STATUS_LED_3(layer & (1<<2));

#    if !defined(CAPS_LOCK_STATUS)
    STATUS_LED_4(layer & (1<<3));
#    endif
    return state;
}
#endif

#ifdef RGB_MATRIX_ENABLE
// clang-format off
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C2_2,  C1_2,  C4_3},
    {0, C2_3,  C1_3,  C3_3},
    {0, C2_4,  C1_4,  C3_4},
    {0, C2_5,  C1_5,  C3_5},
    {0, C2_6,  C1_6,  C3_6},
    {0, C2_7,  C1_7,  C3_7},
    {0, C2_8,  C1_8,  C3_8},
    {0, C8_1,  C7_1,  C9_1},
    {0, C8_2,  C7_2,  C9_2},
    {0, C8_3,  C7_3,  C9_3},
    {0, C8_4,  C7_4,  C9_4},
    {0, C8_5,  C7_5,  C9_5},
    {0, C8_6,  C7_6,  C9_6},
    {0, C2_10,  C1_10,  C4_11},
    {0, C2_11,  C1_11,  C3_11},
    {0, C2_12,  C1_12,  C3_12},
    {0, C2_13,  C1_13,  C3_13},
    {0, C2_14,  C1_14,  C3_14},
    {0, C2_15,  C1_15,  C3_15},
    {0, C2_16,  C1_16,  C3_16},
    {0, C8_9,  C7_9,  C9_9},
    {0, C8_10,  C7_10,  C9_10},
    {0, C8_11,  C7_11,  C9_11},
    {0, C8_12,  C7_12,  C9_12},
    {0, C8_13,  C7_13,  C9_13},
    {0, C8_14,  C7_14,  C9_14},

    {1, C2_7,  C1_7,  C3_7},
    {1, C2_6,  C1_6,  C3_6},
    {1, C2_5,  C1_5,  C3_5},
    {1, C2_4,  C1_4,  C3_4},
    {1, C2_3,  C1_3,  C3_3},
    {1, C2_2,  C1_2,  C4_3},

    {1, C8_5,  C7_5,  C9_5},
    {1, C8_4,  C7_4,  C9_4},
    {1, C8_3,  C7_3,  C9_3},
    {1, C8_2,  C7_2,  C9_2},
    {1, C8_1,  C7_1,  C9_1},
    {1, C2_8,  C1_8,  C3_8},

    {1, C2_14,  C1_14,  C3_14},
    {1, C2_13,  C1_13,  C3_13},
    {1, C2_12,  C1_12,  C3_12},
    {1, C2_11,  C1_11,  C3_11},
    {1, C2_10,  C1_10,  C4_11},
    {1, C8_6,  C7_6,  C9_6},

    {1, C8_12,  C7_12,  C9_12},
    {1, C8_11,  C7_11,  C9_11},
    {1, C8_10,  C7_10,  C9_10},
    {1, C8_9,  C7_9,  C9_9},
    {1, C2_16,  C1_16,  C3_16},
    {1, C2_15,  C1_15,  C3_15},

    {1, C8_14,  C7_14,  C9_14},
    {1, C8_13,  C7_13,  C9_13},
};

led_config_t g_led_config = { {
    {   NO_LED, 0,  1, 2, 3, 4, 5 },
    {   NO_LED, 6,  7, 8, 9, 10, 11 },
    {   NO_LED, 12, 13, 14, 15, 16, 17 },
    {   NO_LED, 18,  19, 20, 21, 22, NO_LED },
    {   NO_LED,  NO_LED, NO_LED, NO_LED, 23, NO_LED, NO_LED },
    {   24, 25, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },

    {  26, 27, 28, 29, 30, 31, NO_LED },
    {  32, 33, 34, 35, 36, 37, NO_LED },
    {  38, 39, 40, 41, 42, 43, NO_LED },
    {  NO_LED, 45, 46, 47, 48, 49, NO_LED },
    {  NO_LED, NO_LED, 44, NO_LED, NO_LED, NO_LED, NO_LED },
    {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 50, 51 },
}, {
    {0, 10}, {17, 10}, {34,8}, {52, 5}, {69, 8}, {86, 10},
    {0, 21}, {17, 21}, {34, 19}, {52, 17}, {69, 19}, {86, 21},
    {0, 32}, {17, 32}, {34, 30}, {52, 28}, {69, 30}, {86, 32},
    {0, 43}, {17, 43}, {34, 41}, {52, 39}, {69, 41}, {86, 43},
    {86, 53}, {96, 58},

    {138, 10}, {155, 10}, {172, 8}, {190, 5}, {207, 8}, {224, 10},
    {138, 21}, {155, 21}, {172, 19}, {190, 17}, {207, 19}, {224, 21},
    {138, 32}, {155, 32}, {172, 30}, {190, 28}, {207, 30}, {224, 32},
    {138, 43}, {155,43}, {172, 41}, {190, 39}, {207, 41}, {224, 43},
    {128, 58}, {138, 53}
}, {
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    1, 1, 4, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    4, 1, 1, 1
} };
// clang-format on

#endif

#ifdef SWAP_HANDS_ENABLE
// swap-hands action needs a matrix to define the swap
// clang-format off
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{6,6}, {5,6}, {4,6}, {3,6}, {2,6}, {1,6},{0,6}},
    {{6,7}, {5,7}, {4,7}, {3,7}, {2,7}, {1,7},{0,7}},
    {{6,8}, {5,8}, {4,8}, {3,8}, {2,8}, {1,8},{0,8}},
    {{6,9}, {5,9}, {4,9}, {3,9}, {2,9}, {1,9},{0,9}},
    {{6,10},{5,10},{4,10},{3,10},{2,10},{1,10},{0,10}},
    {{6,11},{5,11},{4,11},{3,11},{2,11},{1,11},{0,11}},
    /* Right hand, matrix positions */
    {{6,0}, {5,0}, {4,0}, {3,0}, {2,0}, {1,0},{0,0}},
    {{6,1}, {5,1}, {4,1}, {3,1}, {2,1}, {1,1},{0,1}},
    {{6,2}, {5,2}, {4,2}, {3,2}, {2,2}, {1,2},{0,2}},
    {{6,3}, {5,3}, {4,3}, {3,3}, {2,3}, {1,3},{0,3}},
    {{6,4}, {5,4}, {4,4}, {3,4}, {2,4}, {1,4},{0,4}},
    {{6,5}, {5,5}, {4,5}, {3,5}, {2,5}, {1,5},{0,5}},
};
// clang-format on

void keyboard_post_init_kb(void) {
    rgb_matrix_enable_noeeprom();
    keyboard_post_init_user();
}
#endif

#ifdef CAPS_LOCK_STATUS
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        STATUS_LED_4(led_state.caps_lock);
    }
    return res;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#if !defined(VOYAGER_USER_LEDS)
        case LED_LEVEL:
            if (record->event.pressed) {
                keyboard_config.led_level ^= 1;
                eeconfig_update_kb(keyboard_config.raw);
                if (keyboard_config.led_level) {
                    layer_state_set_kb(layer_state);
                } else {
                    STATUS_LED_1(false);
                    STATUS_LED_2(false);
                    STATUS_LED_3(false);
                    STATUS_LED_4(false);
                }
            }
            break;
#endif
#ifdef RGB_MATRIX_ENABLE
        case TOGGLE_LAYER_COLOR:
            if (record->event.pressed) {
                keyboard_config.disable_layer_led ^= 1;
                if (keyboard_config.disable_layer_led) rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            return false;
#endif
    }
    return true;
}

void matrix_init_kb(void) {
    keyboard_config.raw = eeconfig_read_kb();

    if (!keyboard_config.led_level && !keyboard_config.led_level_res) {
        keyboard_config.led_level     = true;
        keyboard_config.led_level_res = 0b11;
        eeconfig_update_kb(keyboard_config.raw);
    }
    matrix_init_user();
}

void eeconfig_init_kb(void) { // EEPROM is getting reset!
    keyboard_config.raw           = 0;
    keyboard_config.led_level     = true;
    keyboard_config.led_level_res = 0b11;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}
