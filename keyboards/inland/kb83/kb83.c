/* Copyright (C) 2022 jonylee@hfd
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

#include "quantum.h"

// clang-format off
#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {1, CB1_CA1,   CB2_CA1,   CB3_CA1},
    {1, CB1_CA2,   CB2_CA2,   CB3_CA2},
    {1, CB1_CA3,   CB2_CA3,   CB3_CA3},
    {1, CB1_CA4,   CB2_CA4,   CB3_CA4},
    {1, CB1_CA5,   CB2_CA5,   CB3_CA5},
    {1, CB1_CA6,   CB2_CA6,   CB3_CA6},
    {1, CB1_CA7,   CB2_CA7,   CB3_CA7},
    {1, CB1_CA8,   CB2_CA8,   CB3_CA8},
    {1, CB1_CA9,   CB2_CA9,   CB3_CA9},
    {1, CB1_CA10,  CB2_CA10,  CB3_CA10},
    {1, CB1_CA11,  CB2_CA11,  CB3_CA11},
    {1, CB1_CA12,  CB2_CA12,  CB3_CA12},
    {1, CB1_CA13,  CB2_CA13,  CB3_CA13},
    {1, CB1_CA14,  CB2_CA14,  CB3_CA14},

    {0, CB1_CA1,   CB2_CA1,   CB3_CA1},
    {0, CB1_CA2,   CB2_CA2,   CB3_CA2},
    {0, CB1_CA3,   CB2_CA3,   CB3_CA3},
    {0, CB1_CA4,   CB2_CA4,   CB3_CA4},
    {0, CB1_CA5,   CB2_CA5,   CB3_CA5},
    {0, CB1_CA6,   CB2_CA6,   CB3_CA6},
    {0, CB1_CA7,   CB2_CA7,   CB3_CA7},
    {0, CB1_CA8,   CB2_CA8,   CB3_CA8},
    {0, CB1_CA9,   CB2_CA9,   CB3_CA9},
    {0, CB1_CA10,  CB2_CA10,  CB3_CA10},
    {0, CB1_CA11,  CB2_CA11,  CB3_CA11},
    {0, CB1_CA12,  CB2_CA12,  CB3_CA12},
    {0, CB1_CA13,  CB2_CA13,  CB3_CA13},
    {0, CB1_CA14,  CB2_CA14,  CB3_CA14},
    {1, CB4_CA1,   CB5_CA1,   CB6_CA1},
    
    {0, CB4_CA1,   CB5_CA1,   CB6_CA1},
    {0, CB4_CA2,   CB5_CA2,   CB6_CA2},
    {0, CB4_CA3,   CB5_CA3,   CB6_CA3},
    {0, CB4_CA4,   CB5_CA4,   CB6_CA4},
    {0, CB4_CA5,   CB5_CA5,   CB6_CA5},
    {0, CB4_CA6,   CB5_CA6,   CB6_CA6},
    {0, CB4_CA7,   CB5_CA7,   CB6_CA7},
    {0, CB4_CA8,   CB5_CA8,   CB6_CA8},
    {0, CB4_CA9,   CB5_CA9,   CB6_CA9},
    {0, CB4_CA10,  CB5_CA10,  CB6_CA10},
    {0, CB4_CA11,  CB5_CA11,  CB6_CA11},
    {0, CB4_CA12,  CB5_CA12,  CB6_CA12},
    {0, CB4_CA13,  CB5_CA13,  CB6_CA13},
    {0, CB4_CA14,  CB5_CA14,  CB6_CA14},
    {1, CB4_CA2,   CB5_CA2,   CB6_CA2},

    {0, CB7_CA1,   CB8_CA1,   CB9_CA1},
    {0, CB7_CA2,   CB8_CA2,   CB9_CA2},
    {0, CB7_CA3,   CB8_CA3,   CB9_CA3},
    {0, CB7_CA4,   CB8_CA4,   CB9_CA4},
    {0, CB7_CA5,   CB8_CA5,   CB9_CA5},
    {0, CB7_CA6,   CB8_CA6,   CB9_CA6},
    {0, CB7_CA7,   CB8_CA7,   CB9_CA7},
    {0, CB7_CA8,   CB8_CA8,   CB9_CA8},
    {0, CB7_CA9,   CB8_CA9,   CB9_CA9},
    {0, CB7_CA10,  CB8_CA10,  CB9_CA10},
    {0, CB7_CA11,  CB8_CA11,  CB9_CA11},
    {0, CB7_CA12,  CB8_CA12,  CB9_CA12},
    {0, CB7_CA13,  CB8_CA13,  CB9_CA13},
    {1, CB4_CA3,   CB5_CA3,   CB6_CA3},
 
    {0, CB10_CA1,   CB11_CA1,   CB12_CA1},
    {0, CB10_CA2,   CB11_CA2,   CB12_CA2},
    {0, CB10_CA3,   CB11_CA3,   CB12_CA3},
    {0, CB10_CA4,   CB11_CA4,   CB12_CA4},
    {0, CB10_CA5,   CB11_CA5,   CB12_CA5},
    {0, CB10_CA6,   CB11_CA6,   CB12_CA6},
    {0, CB10_CA7,   CB11_CA7,   CB12_CA7},
    {0, CB10_CA8,   CB11_CA8,   CB12_CA8},
    {0, CB10_CA9,   CB11_CA9,   CB12_CA9},
    {0, CB10_CA10,  CB11_CA10,  CB12_CA10},
    {0, CB10_CA11,  CB11_CA11,  CB12_CA11},
    {0, CB10_CA12,  CB11_CA12,  CB12_CA12},
    {1, CB4_CA7,   CB5_CA7,   CB6_CA7},
    {1, CB4_CA4,   CB5_CA4,   CB6_CA4},

    {0, CB10_CA13,  CB11_CA13,  CB12_CA13},
    {0, CB10_CA14,  CB11_CA14,  CB12_CA14},
    {0, CB10_CA15,  CB11_CA15,  CB12_CA15},
    {0, CB10_CA16,  CB11_CA16,  CB12_CA16},

    {0, CB7_CA14,  CB8_CA14,  CB9_CA14},
    {0, CB7_CA15,  CB8_CA15,  CB9_CA15},
    {0, CB7_CA16,  CB8_CA16,  CB9_CA16},

    {0, CB4_CA15,  CB5_CA15,  CB6_CA15},
    {1, CB4_CA6,   CB5_CA6,   CB6_CA6},
    {1, CB4_CA5,   CB5_CA5,   CB6_CA5},

    {1, CB7_CA1,   CB8_CA1,   CB9_CA1},
    {1, CB7_CA2,   CB8_CA2,   CB9_CA2},
    {1, CB7_CA3,   CB8_CA3,   CB9_CA3},
    {1, CB7_CA4,   CB8_CA4,   CB9_CA4},
    {1, CB7_CA5,   CB8_CA5,   CB9_CA5},
   
    {1, CB10_CA1,   CB11_CA1,   CB12_CA1},
    {1, CB10_CA2,   CB11_CA2,   CB12_CA2},
    {1, CB10_CA3,   CB11_CA3,   CB12_CA3},
    {1, CB10_CA4,   CB11_CA4,   CB12_CA4},
    {1, CB10_CA5,   CB11_CA5,   CB12_CA5},
};

led_config_t g_led_config = {
    {
        {  0,       1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13, NO_LED,     NO_LED},
        {  14,      15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27, NO_LED,     28},
        {  29,      30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42, NO_LED,     43},
        {  44,      45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     NO_LED, 56,     NO_LED, 57},
        {  58,      59,     60,     61,     62,     63,     64,     65,     66,     67,     68, NO_LED,     NO_LED, 69,     70,     71},
        {  72,      73,     74, NO_LED, NO_LED,     75, NO_LED, NO_LED, NO_LED,     76,     77,     78,     NO_LED, 79,     80,     81}
    },
    {
        {  0,  0}, //  0
        { 14,  0}, //  1
        { 29,  0}, //  2
        { 44,  0}, //  3
        { 59,  0}, //  4
        { 74,  0}, //  5
        { 89,  0}, //  6
        {104,  0}, //  7
        {119,  0}, //  8
        {134,  0}, //  9
        {149,  0}, // 10
        {164,  0}, // 11
        {179,  0}, // 12
        {194,  0}, // 13

        {  0, 12}, // 14
        { 14, 12}, // 15
        { 28, 12}, // 16
        { 42, 12}, // 17
        { 56, 12}, // 18
        { 70, 12}, // 19
        { 84, 12}, // 20
        { 98, 12}, // 21
        {112, 12}, // 22
        {126, 12}, // 23
        {140, 12}, // 24
        {154, 12}, // 25
        {168, 12}, // 26
        {182, 12}, // 27
        {224, 12}, // 28

        {  0, 25}, // 29
        { 14, 25}, // 30
        { 28, 25}, // 31
        { 42, 25}, // 32
        { 56, 25}, // 33
        { 70, 25}, // 34
        { 84, 25}, // 35
        { 98, 25}, // 36
        {112, 25}, // 37
        {126, 25}, // 38
        {140, 25}, // 39
        {154, 25}, // 40
        {168, 25}, // 41
        {182, 25}, // 42
        {224, 25}, // 43

        {  0, 38}, // 44
        { 28, 38}, // 45
        { 42, 38}, // 46
        { 56, 38}, // 47
        { 70, 38}, // 48
        { 84, 38}, // 49
        { 98, 38}, // 50
        {112, 38}, // 51
        {126, 38}, // 52
        {140, 38}, // 53
        {154, 38}, // 54
        {168, 38}, // 55
        {182, 38}, // 56
        {224, 38}, // 57

        {  0, 51}, // 58
        { 18, 51}, // 59
        { 37, 51}, // 60
        { 56, 51}, // 61
        { 74, 51}, // 62
        { 93, 51}, // 63
        {112, 51}, // 64
        {130, 51}, // 65
        {149, 51}, // 66
        {168, 51}, // 67
        {186, 51}, // 68
        {200, 51}, // 69
        {214, 51}, // 70
        {224, 51}, // 71

        {  0, 64}, // 72
        { 18, 64}, // 73
        { 37, 64}, // 74
        { 92, 64}, // 75
        {140, 64}, // 76
        {154, 64}, // 77
        {168, 64}, // 78
        {196, 64}, // 80
        {210, 64}, // 81
        {224, 64},  // 82

        {0,   0}, //  68 LED 1
        {0,   16}, //  69 LED 2
        {0,   32}, //  70 LED 3
        {0,   48}, //  71 LED 4
        {0,   64}, //  72 LED 5

        {224, 0 }, //  78 LED 12
        {224, 16}, //  79 LED 13
        {224, 32}, //  80 LED 14
        {224, 48}, //  81 LED 15
        {224, 64}, //  82 LED 16
    },
    {
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,       
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, 
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, 
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,      4, 
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,      4,  4, 
		4,  4,  4,          4,              4,  4,  4,  4,  4,  4,
        2,  2,  2,  2,  2, 
        2,  2,  2,  2,  2,     
    }
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    // caps lock red
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(44, 255, 0, 0);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(44, 0, 0, 0);
        }
    }
    // GUI lock red
    if (keymap_config.no_gui) {
        RGB_MATRIX_INDICATOR_SET_COLOR(73, 255, 0, 0);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(73, 0, 0, 0);
        }
    }
    return true;
}

#endif

enum __layers {
    WIN_B,
    WIN_FN,
    MAC_B,
    MAC_FN
};

enum colors { 
    WHITE, 
    RED, 
    GREEN, 
    BLUE 
};
enum colors led_color_status = WHITE;

// clang-format on
static bool     fn_make_flag     = false;
static bool     Lkey_flag        = false;
static bool     reset_glint_flag = false;
static bool     while_test_flag  = false;
static bool     alarm_flag       = false;
static uint16_t current_time     = 0;
static uint8_t  glint_cnt        = 0;
static uint16_t scancode         = 0;
static uint8_t  alarm_cnt        = 0;
static uint8_t  RGB_HSV_level;

hsv_t hsv;

void led_test(uint8_t color);
void clear_eeprom(void);
void rgb_hsv_updata_user(void);

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? MAC_B : WIN_B));
    }
    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case MO(WIN_FN):
        case MO(MAC_FN):
            fn_make_flag = record->event.pressed;
            return true;
        case KC_ESC:
            if (fn_make_flag && record->event.pressed) {
                Lkey_flag    = true;
                current_time = timer_read();
                scancode     = KC_ESC;
                return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_END:
            if (fn_make_flag && record->event.pressed) {
                if (while_test_flag) {
                    while_test_flag = false;
                    rgb_matrix_init();
                } else {
                    Lkey_flag    = true;
                    current_time = timer_read();
                    scancode     = KC_END;
                }
                return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_LEFT:
            if (while_test_flag == true) {
                if (record->event.pressed) {
                    if (glint_cnt == 0)
                        glint_cnt = 3;
                    else
                        glint_cnt--;
                    if ((glint_cnt % 4) == 0) {
                        rgb_matrix_sethsv_noeeprom(HSV_WHITE);
                    } else if ((glint_cnt % 4) == 1) {
                        rgb_matrix_sethsv_noeeprom(HSV_RED);
                    } else if ((glint_cnt % 4) == 2) {
                        rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                    } else if ((glint_cnt % 4) == 3) {
                        rgb_matrix_sethsv_noeeprom(HSV_BLUE);
                    }
                }
                return false;
            }
            return true;
        case KC_RGHT:
            if (while_test_flag == true) {
                if (record->event.pressed) {
                    glint_cnt++;
                    if (glint_cnt >= 4) glint_cnt = 0;

                    if ((glint_cnt % 4) == 0) {
                        rgb_matrix_sethsv_noeeprom(HSV_WHITE);
                    } else if ((glint_cnt % 4) == 1) {
                        rgb_matrix_sethsv_noeeprom(HSV_RED);
                    } else if ((glint_cnt % 4) == 2) {
                        rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                    } else if ((glint_cnt % 4) == 3) {
                        rgb_matrix_sethsv_noeeprom(HSV_BLUE);
                    }
                }
                return false;
            }
            return true;
        case DF(WIN_B):
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();
                set_single_persistent_default_layer(WIN_B);
                return false;
            }
            return true;
        case DF(MAC_B):
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();
                set_single_persistent_default_layer(MAC_B);
                return false;
            }
            return true;

        case QK_RGB_MATRIX_VALUE_UP:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) < 4) {
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case QK_RGB_MATRIX_VALUE_DOWN:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) > 0) {
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case QK_RGB_MATRIX_SATURATION_UP:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_sat() / (UINT8_MAX / 4)) < 4) {
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.s = (uint8_t)(UINT8_MAX / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case QK_RGB_MATRIX_SATURATION_DOWN:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_sat() / (UINT8_MAX / 4)) > 0) {
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.s = (uint8_t)(UINT8_MAX / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case QK_RGB_MATRIX_HUE_UP:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_hue() / (UINT8_MAX / 6)) < 6) {
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.h = (uint8_t)(UINT8_MAX / 6) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case QK_RGB_MATRIX_HUE_DOWN:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_hue() / (UINT8_MAX / 6)) > 0) {
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.h = (uint8_t)(UINT8_MAX / 6) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case QK_RGB_MATRIX_SPEED_UP:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_speed() / (UINT8_MAX / 4)) < 4) {
                    RGB_HSV_level++;
                    rgb_matrix_set_speed((uint8_t)(UINT8_MAX / 4) * RGB_HSV_level);
                }
            }
            return false;
        case QK_RGB_MATRIX_SPEED_DOWN:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_speed() / (UINT8_MAX / 4)) > 0) {
                    RGB_HSV_level--;
                    rgb_matrix_set_speed((uint8_t)(UINT8_MAX / 4) * RGB_HSV_level);
                }
            }
            return false;
        case QK_RGB_MATRIX_TOGGLE:
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
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;

        default:
            return process_record_user(keycode, record);
    }
}

void housekeeping_task_kb(void) {
    if (Lkey_flag) {
        if (scancode == KC_ESC) {
            if (timer_elapsed(current_time) >= 3000) {
                Lkey_flag = false;
                clear_eeprom();

                current_time     = timer_read();
                reset_glint_flag = true;
                glint_cnt        = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
        } else if (scancode == KC_END) {
            if (timer_elapsed(current_time) >= 3000) {
                Lkey_flag = false;
                clear_eeprom();

                while_test_flag = true;
                glint_cnt       = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            }
        }
    } else if (reset_glint_flag) {
        if ((timer_elapsed(current_time)) >= 300) {
            current_time = timer_read();
            if (((glint_cnt++) & 0x01) == 0) {
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            } else {
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
            if (glint_cnt >= 7) {
                glint_cnt        = 0;
                reset_glint_flag = false;
                rgb_matrix_init();
            }
        }
    } else if (alarm_cnt != 0) {
        alarm_cnt--;
        if (alarm_cnt == 0) {
            alarm_flag = true;
            rgb_matrix_toggle_noeeprom();
            current_time = timer_read();
        }
    } else if (alarm_flag) {
        if ((timer_elapsed(current_time)) >= 200) {
            rgb_matrix_toggle_noeeprom();
            alarm_flag = 0;
        }
    }
}

void led_test(uint8_t color) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);

    switch (color) {
        case WHITE:
            rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            break;

        case RED:
            rgb_matrix_sethsv_noeeprom(HSV_RED);
            break;

        case GREEN:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            break;

        case BLUE:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            break;
    }
}

void clear_eeprom(void) {
    layer_state_t default_layer_temp = default_layer_state;
    eeconfig_init();
    default_layer_set(default_layer_temp);

#ifdef VIA_ENABLE
    // This resets the layout options
    via_set_layout_options(VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT);
    // This resets the keymaps in EEPROM to what is in flash.
    dynamic_keymap_reset();
    // This resets the macros in EEPROM to nothing.
    dynamic_keymap_macro_reset();
#endif

    rgb_matrix_enable_noeeprom();
}

void rgb_hsv_updata_user(void) {
    rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
}
