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

#include "moonlander.h"

keyboard_config_t keyboard_config;

bool mcp23018_leds[3] = {0, 0, 0};
bool is_launching     = false;

#if defined(DEFERRED_EXEC_ENABLE)
#    if defined(DYNAMIC_MACRO_ENABLE)
deferred_token dynamic_macro_token = INVALID_DEFERRED_TOKEN;

static uint32_t dynamic_macro_led(uint32_t trigger_time, void *cb_arg) {
    static bool led_state = true;
    if (!is_launching) {
        led_state = !led_state;
        ML_LED_3(led_state);
    }
    return 100;
}

bool dynamic_macro_record_start_kb(int8_t direction) {
    if (!dynamic_macro_record_start_user(direction)) {
        return false;
    }
    if (dynamic_macro_token == INVALID_DEFERRED_TOKEN) {
        ML_LED_3(true);
        dynamic_macro_token = defer_exec(100, dynamic_macro_led, NULL);
    }
    return true;
}

bool dynamic_macro_record_end_kb(int8_t direction) {
    if (!dynamic_macro_record_end_user(direction)) {
        return false;
    }
    if (cancel_deferred_exec(dynamic_macro_token)) {
        dynamic_macro_token = INVALID_DEFERRED_TOKEN;
        ML_LED_3(false);
    }
    return false;
}
#    endif

static uint32_t startup_exec(uint32_t trigger_time, void *cb_arg) {
    static uint8_t startup_loop = 0;

    switch (startup_loop++) {
        case 0:
            ML_LED_1(true);
            ML_LED_2(false);
            ML_LED_3(false);
            ML_LED_4(false);
            ML_LED_5(false);
            ML_LED_6(false);
            break;
        case 1:
            ML_LED_2(true);
            break;
        case 2:
            ML_LED_3(true);
            break;
        case 3:
            ML_LED_4(true);
            break;
        case 4:
            ML_LED_5(true);
            break;
        case 5:
            ML_LED_6(true);
            break;
        case 6:
            ML_LED_1(false);
            break;
        case 7:
            ML_LED_2(false);
            break;
        case 8:
            ML_LED_3(false);
            break;
        case 9:
            ML_LED_4(false);
            break;
        case 10:
            ML_LED_5(false);
            break;
        case 11:
            ML_LED_6(false);
            break;
        case 12:
            is_launching = false;
            layer_state_set_kb(layer_state);
            return 0;
    }
    return 250;
}
#endif

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(B5);
    gpio_set_pin_output(B4);
    gpio_set_pin_output(B3);

    gpio_write_pin_low(B5);
    gpio_write_pin_low(B4);
    gpio_write_pin_low(B3);

    keyboard_pre_init_user();
}

#if !defined(MOONLANDER_USER_LEDS)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    if (is_launching || !keyboard_config.led_level) return state;
    bool LED_1 = false;
    bool LED_2 = false;
    bool LED_3 = false;
    bool LED_4 = false;
    bool LED_5 = false;
#if !defined(CAPS_LOCK_STATUS)
    bool LED_6 = false;
#endif

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 1:
            LED_1 = true;
            LED_4 = true;
            break;
        case 2:
            LED_2 = true;
            LED_5 = true;
            break;
        case 3:
            LED_3 = true;
#if !defined(CAPS_LOCK_STATUS)
            LED_6 = true;
#endif
            break;
        case 4:
            LED_4 = true;
            break;
        case 5:
            LED_5 = true;
            break;
        case 6:
#if !defined(CAPS_LOCK_STATUS)
            LED_6 = true;
#endif
            break;
        default:
            break;
    }

    ML_LED_1(LED_1);
    ML_LED_2(LED_2);
    ML_LED_3(LED_3);
    ML_LED_4(LED_4);
    ML_LED_5(LED_5);
#if !defined(CAPS_LOCK_STATUS)
    ML_LED_6(LED_6);
#endif

    return state;
}
#endif

#ifdef RGB_MATRIX_ENABLE
// clang-format off
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
    {0, C3_2,  C1_1,  C4_2},
    {0, C2_2,  C1_2,  C4_3},
    {0, C2_3,  C1_3,  C3_3},
    {0, C2_4,  C1_4,  C3_4},
    {0, C2_5,  C1_5,  C3_5},
    {0, C2_6,  C1_6,  C3_6},
    {0, C2_7,  C1_7,  C3_7},
    {0, C2_8,  C1_8,  C3_8},
    {0, C3_1,  C2_1,  C4_1},

    {0, C7_8,  C6_8,  C8_8},
    {0, C7_7,  C6_7,  C9_8},
    {0, C8_7,  C6_6,  C9_7},
    {0, C8_6,  C7_6,  C9_6},
    {0, C8_5,  C7_5,  C9_5},
    {0, C8_4,  C7_4,  C9_4},
    {0, C8_3,  C7_3,  C9_3},
    {0, C8_2,  C7_2,  C9_2},
    {0, C8_1,  C7_1,  C9_1},

    {0, C3_10,  C1_9,   C4_10},
    {0, C2_10,  C1_10,  C4_11},
    {0, C2_11,  C1_11,  C3_11},
    {0, C2_12,  C1_12,  C3_12},
    {0, C2_13,  C1_13,  C3_13},
    {0, C2_14,  C1_14,  C3_14},
    {0, C2_15,  C1_15,  C3_15},
    {0, C2_16,  C1_16,  C3_16},
    {0, C3_9,   C2_9,   C4_9},

    {0, C7_16,  C6_16,  C8_16},
    {0, C7_15,  C6_15,  C9_16},
    {0, C8_15,  C6_14,  C9_15},
    {0, C8_10,  C7_10,  C9_10},
    {0, C8_9,   C7_9,   C9_9},
    {0, C8_11,  C7_11,  C9_11},
    {0, C8_12,  C7_12,  C9_12},
    {0, C8_13,  C7_13,  C9_13},
    {0, C8_14,  C7_14,  C9_14},

    {1, C3_2,  C1_1,  C4_2},
    {1, C2_2,  C1_2,  C4_3},
    {1, C2_3,  C1_3,  C3_3},
    {1, C2_4,  C1_4,  C3_4},
    {1, C2_5,  C1_5,  C3_5},
    {1, C2_6,  C1_6,  C3_6},
    {1, C2_7,  C1_7,  C3_7},
    {1, C2_8,  C1_8,  C3_8},
    {1, C3_1,  C2_1,  C4_1},

    {1, C7_8,  C6_8,  C8_8},
    {1, C7_7,  C6_7,  C9_8},
    {1, C8_7,  C6_6,  C9_7},
    {1, C8_6,  C7_6,  C9_6},
    {1, C8_5,  C7_5,  C9_5},
    {1, C8_4,  C7_4,  C9_4},
    {1, C8_3,  C7_3,  C9_3},
    {1, C8_2,  C7_2,  C9_2},
    {1, C8_1,  C7_1,  C9_1},

    {1, C3_10,  C1_9,   C4_10},
    {1, C2_10,  C1_10,  C4_11},
    {1, C2_11,  C1_11,  C3_11},
    {1, C2_12,  C1_12,  C3_12},
    {1, C2_13,  C1_13,  C3_13},
    {1, C2_14,  C1_14,  C3_14},
    {1, C2_15,  C1_15,  C3_15},
    {1, C2_16,  C1_16,  C3_16},
    {1, C3_9,   C2_9,   C4_9},

    {1, C7_16,  C6_16,  C8_16},
    {1, C7_15,  C6_15,  C9_16},
    {1, C8_15,  C6_14,  C9_15},
    {1, C8_10,  C7_10,  C9_10},
    {1, C8_9,   C7_9,   C9_9},
    {1, C8_11,  C7_11,  C9_11},
    {1, C8_12,  C7_12,  C9_12},
    {1, C8_13,  C7_13,  C9_13},
    {1, C8_14,  C7_14,  C9_14},
};
// clang-format on
#endif

#ifdef AUDIO_ENABLE
bool music_mask_kb(uint16_t keycode) {
    switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case AU_ON ... AU_PREV:
        case QK_BOOT:
        case QK_CLEAR_EEPROM:
            return false;
        default:
            return music_mask_user(keycode);
    }
}
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
#endif

#if defined(AUDIO_ENABLE) && defined(MUSIC_MAP)
// clang-format off
__attribute__ ((weak))
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = {
    {58, 59, 60, 61, 62, 63, 64},
    {44, 45, 46, 47, 48, 49, 50},
    {30, 31, 32, 33, 34, 35, 36},
    {18, 19, 20, 21, 22, 23,  0},
    { 8,  9, 10, 11, 12,  0,  0},
    { 0,  1,  2,  3,  0,  0,  0},
    {65, 66, 67, 68, 69, 70, 71},
    {51, 52, 53, 54, 55, 56, 57},
    {37, 38, 39, 40, 41, 42, 43},
    { 0, 24, 25, 26, 27, 28, 29},
    { 0,  0, 13, 14, 15, 16, 17},
    { 0,  0,  0,  4,  5,  6,  7}
};
// clang-format on
#endif

#ifdef CAPS_LOCK_STATUS
void led_update_ports(led_t led_state) {
    ML_LED_6(led_state.caps_lock);
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch (keycode) {
#if !defined(MOONLANDER_USER_LEDS)
        case LED_LEVEL:
            if (record->event.pressed) {
                keyboard_config.led_level ^= 1;
                eeconfig_update_kb(keyboard_config.raw);
                if (keyboard_config.led_level) {
                    layer_state_set_kb(layer_state);
                } else {
                    ML_LED_1(false);
                    ML_LED_2(false);
                    ML_LED_3(false);
                    ML_LED_4(false);
                    ML_LED_5(false);
                    ML_LED_6(false);
                }
            }
            break;
#endif
#ifdef RGB_MATRIX_ENABLE
        case TOGGLE_LAYER_COLOR:
            if (record->event.pressed) {
                keyboard_config.disable_layer_led ^= 1;
                if (keyboard_config.disable_layer_led) rgb_matrix_set_color_all(0, 0, 0);
                eeconfig_update_kb(keyboard_config.raw);
            }
            break;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        keyboard_config.rgb_matrix_enable = false;
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        keyboard_config.rgb_matrix_enable = true;
                    } break;
                }
                eeconfig_update_kb(keyboard_config.raw);
            }
            return false;
#endif
    }
    return true;
}

void keyboard_post_init_kb(void) {
    keyboard_config.raw = eeconfig_read_kb();

    if (!keyboard_config.led_level && !keyboard_config.led_level_res) {
        keyboard_config.led_level = true;
        keyboard_config.led_level_res = 0b11;
        eeconfig_update_kb(keyboard_config.raw);
    }
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
#endif
#if defined(DEFERRED_EXEC_ENABLE)
    is_launching = true;
    defer_exec(500, startup_exec, NULL);
#endif
    keyboard_post_init_user();
}

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    keyboard_config.raw = 0;
    keyboard_config.rgb_matrix_enable = true;
    keyboard_config.led_level = true;
    keyboard_config.led_level_res = 0b11;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}
