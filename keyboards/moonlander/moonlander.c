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

#ifdef DYNAMIC_MACRO_ENABLE
static bool is_dynamic_recording = false;

void dynamic_macro_record_start_user(void) { is_dynamic_recording = true; }

void dynamic_macro_record_end_user(int8_t direction) {
    is_dynamic_recording = false;
    ML_LED_3(false);
}
#endif

void moonlander_led_task(void) {
    if (is_launching) {
        ML_LED_1(false);
        ML_LED_2(false);
        ML_LED_3(false);
        ML_LED_4(false);
        ML_LED_5(false);
        ML_LED_6(false);

        ML_LED_1(true);
        wait_ms(250);
        ML_LED_2(true);
        wait_ms(250);
        ML_LED_3(true);
        wait_ms(250);
        ML_LED_4(true);
        wait_ms(250);
        ML_LED_5(true);
        wait_ms(250);
        ML_LED_6(true);
        wait_ms(250);
        ML_LED_1(false);
        wait_ms(250);
        ML_LED_2(false);
        wait_ms(250);
        ML_LED_3(false);
        wait_ms(250);
        ML_LED_4(false);
        wait_ms(250);
        ML_LED_5(false);
        wait_ms(250);
        ML_LED_6(false);
        wait_ms(250);
        is_launching = false;
        layer_state_set_kb(layer_state);
    }
#ifdef DYNAMIC_MACRO_ENABLE
    else if (is_dynamic_recording) {
        ML_LED_3(true);
        wait_ms(100);
        ML_LED_3(false);
        wait_ms(155);
    }
#endif
#if !defined(MOONLANDER_USER_LEDS)
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
        moonlander_led_task();
    }
}

void keyboard_pre_init_kb(void) {
    setPinOutput(B5);
    setPinOutput(B4);
    setPinOutput(B3);

    writePinLow(B5);
    writePinLow(B4);
    writePinLow(B3);

    chThdCreateStatic(waLEDThread, sizeof(waLEDThread), NORMALPRIO - 16, LEDThread, NULL);

    /* the array is initialized to 0, no need to re-set it here */
    // mcp23018_leds[0] = 0;  // blue
    // mcp23018_leds[1] = 0;  // green
    // mcp23018_leds[2] = 0;  // red

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
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C3_2,  C1_1,  C4_2}, // 1
    {0, C2_2,  C1_2,  C4_3},
    {0, C2_3,  C1_3,  C3_3},
    {0, C2_4,  C1_4,  C3_4},
    {0, C2_5,  C1_5,  C3_5},
    {0, C2_6,  C1_6,  C3_6},
    {0, C2_7,  C1_7,  C3_7},
    {0, C2_8,  C1_8,  C3_8},
    {0, C3_1,  C2_1,  C4_1},

    {0, C7_8,  C6_8,  C8_8}, // 10
    {0, C7_7,  C6_7,  C9_8},
    {0, C8_7,  C6_6,  C9_7},
    {0, C8_6,  C7_6,  C9_6},
    {0, C8_5,  C7_5,  C9_5},
    {0, C8_4,  C7_4,  C9_4},
    {0, C8_3,  C7_3,  C9_3},
    {0, C8_2,  C7_2,  C9_2},
    {0, C8_1,  C7_1,  C9_1},

    {0, C3_10,  C1_9,   C4_10}, // 19
    {0, C2_10,  C1_10,  C4_11},
    {0, C2_11,  C1_11,  C3_11},
    {0, C2_12,  C1_12,  C3_12},
    {0, C2_13,  C1_13,  C3_13},
    {0, C2_14,  C1_14,  C3_14},
    {0, C2_15,  C1_15,  C3_15},
    {0, C2_16,  C1_16,  C3_16},
    {0, C3_9,   C2_9,   C4_9},

    {0, C7_16,  C6_16,  C8_16}, // 28
    {0, C7_15,  C6_15,  C9_16},
    {0, C8_15,  C6_14,  C9_15},
    {0, C8_10,  C7_10,  C9_10},
    {0, C8_9,   C7_9,   C9_9},
    {0, C8_11,  C7_11,  C9_11},
    {0, C8_12,  C7_12,  C9_12},
    {0, C8_13,  C7_13,  C9_13},
    {0, C8_14,  C7_14,  C9_14},

    {1, C3_2,  C1_1,  C4_2}, // 1
    {1, C2_2,  C1_2,  C4_3},
    {1, C2_3,  C1_3,  C3_3},
    {1, C2_4,  C1_4,  C3_4},
    {1, C2_5,  C1_5,  C3_5},
    {1, C2_6,  C1_6,  C3_6},
    {1, C2_7,  C1_7,  C3_7},
    {1, C2_8,  C1_8,  C3_8},
    {1, C3_1,  C2_1,  C4_1},

    {1, C7_8,  C6_8,  C8_8}, // 10
    {1, C7_7,  C6_7,  C9_8},
    {1, C8_7,  C6_6,  C9_7},
    {1, C8_6,  C7_6,  C9_6},
    {1, C8_5,  C7_5,  C9_5},
    {1, C8_4,  C7_4,  C9_4},
    {1, C8_3,  C7_3,  C9_3},
    {1, C8_2,  C7_2,  C9_2},
    {1, C8_1,  C7_1,  C9_1},

    {1, C3_10,  C1_9,   C4_10}, // 19
    {1, C2_10,  C1_10,  C4_11},
    {1, C2_11,  C1_11,  C3_11},
    {1, C2_12,  C1_12,  C3_12},
    {1, C2_13,  C1_13,  C3_13},
    {1, C2_14,  C1_14,  C3_14},
    {1, C2_15,  C1_15,  C3_15},
    {1, C2_16,  C1_16,  C3_16},
    {1, C3_9,   C2_9,   C4_9},

    {1, C7_16,  C6_16,  C8_16}, // 28
    {1, C7_15,  C6_15,  C9_16},
    {1, C8_15,  C6_14,  C9_15},
    {1, C8_10,  C7_10,  C9_10},
    {1, C8_9,   C7_9,   C9_9},
    {1, C8_11,  C7_11,  C9_11},
    {1, C8_12,  C7_12,  C9_12},
    {1, C8_13,  C7_13,  C9_13},
    {1, C8_14,  C7_14,  C9_14},

};

led_config_t g_led_config = { {
    {   0,  5, 10, 15, 20, 25, 29 },
    {   1,  6, 11, 16, 21, 26, 30 },
    {   2,  7, 12, 17, 22, 27, 31 },
    {   3,  8, 13, 18, 23, 28, NO_LED },
    {   4,  9, 14, 19, 24, NO_LED, NO_LED },
    {  32, 33, 34, 35, NO_LED, NO_LED, NO_LED },
    {  65, 61, 56, 51, 46, 41, 36 },
    {  66, 62, 57, 52, 47, 42, 37 },
    {  67, 63, 58, 53, 48, 43, 38 },
    {  NO_LED, 64, 59, 54, 49, 44, 39 },
    {  NO_LED, NO_LED, 60, 55, 50, 45, 40 },
    {  NO_LED, NO_LED, NO_LED, 71, 70, 69, 68 },
}, {
    {   0,   0 }, {   0,  12 }, {   0,  25 }, {   0,  38 }, {   0,  51 },
    {  17,   0 }, {  17,  12 }, {  17,  25 }, {  17,  38 }, {  17,  51 },
    {  34,   0 }, {  34,  12 }, {  34,  25 }, {  34,  38 }, {  34,  51 },
    {  51,   0 }, {  51,  12 }, {  51,  25 }, {  51,  38 }, {  51,  51 },
    {  68,   0 }, {  68,  12 }, {  68,  25 }, {  68,  38 }, {  68,  51 },
    {  86,   0 }, {  86,  12 }, {  86,  25 }, {  86,  38 },
    { 105,   0 }, { 105,  12 }, { 105,  25 },
    {  90,  55 }, { 105,  68 }, { 116,  86 }, { 116, 59 },

    { 250,   0 }, { 250,  12 }, { 250,  25 }, { 250,  38 }, { 250,  51 },
    { 233,   0 }, { 233,  12 }, { 233,  25 }, { 233,  38 }, { 233,  51 },
    { 216,   0 }, { 216,  12 }, { 216,  25 }, { 216,  38 }, { 216,  51 },
    { 198,   0 }, { 198,  12 }, { 198,  25 }, { 198,  38 }, { 198,  51 },
    { 181,   0 }, { 181,  12 }, { 181,  25 }, { 181,  38 }, { 181,  51 },
    { 163,   0 }, { 163,  12 }, { 163,  25 }, { 163,  38 },
    { 146,   0 }, { 146,  12 }, { 146,  25 },
    { 161,  55 }, { 161,  68 }, { 146,  86 }, { 131, 59 }

}, {
    1, 1, 1, 1, 1, 4,
    4, 4, 4, 1, 4, 4,
    4, 4, 1, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 4,
    4, 4, 4, 1, 4, 4,
    4, 4, 1, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1
} };
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
        case AU_ON ... MUV_DE:
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

void keyboard_post_init_kb(void) {
    rgb_matrix_enable_noeeprom();
    keyboard_post_init_user();
}
#endif

#if defined(AUDIO_ENABLE) && defined(MUSIC_MAP)
// clang-format off
__attribute__ ((weak))
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_moonlander(
    58, 59, 60, 61, 62, 63, 64,    65, 66, 67, 68, 69, 70, 71,
    44, 45, 46, 47, 48, 49, 50,    51, 52, 53, 54, 55, 56, 57,
    30, 31, 32, 33, 34, 35, 36,    37, 38, 39, 40, 41, 42, 43,
    18, 19, 20, 21, 22, 23,            24, 25, 26, 27, 28, 29,
     8,  9, 10, 11, 12,      3,     4,     13, 14, 15, 16, 17,
                     0,  1,  2,     5,  6,  7
);
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

void matrix_init_kb(void) {
    keyboard_config.raw = eeconfig_read_kb();

    if (!keyboard_config.led_level && !keyboard_config.led_level_res) {
        keyboard_config.led_level = true;
        keyboard_config.led_level_res = 0b11;
        eeconfig_update_kb(keyboard_config.raw);
    }
#ifdef RGB_MATRIX_ENABLE
    if (keyboard_config.rgb_matrix_enable) {
        rgb_matrix_set_flags(LED_FLAG_ALL);
    } else {
        rgb_matrix_set_flags(LED_FLAG_NONE);
    }
#endif
    matrix_init_user();
}

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    keyboard_config.raw = 0;
    keyboard_config.rgb_matrix_enable = true;
    keyboard_config.led_level = true;
    keyboard_config.led_level_res = 0b11;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}
