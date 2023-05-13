/* Copyright (C) 2023 jonylee@hfd
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

static bool     pwron_flag       = false;
static uint16_t map_current_time = 0;
// clang-format off
#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {1, A_1,   B_1,   C_1},
    {1, A_2,   B_2,   C_2},
    {1, A_3,   B_3,   C_3},
    {1, A_4,   B_4,   C_4},
    {1, A_5,   B_5,   C_5},
    {1, A_6,   B_6,   C_6},
    {1, A_7,   B_7,   C_7},
    {1, A_8,   B_8,   C_8},
    {1, A_9,   B_9,   C_9},
    {1, A_10,  B_10,  C_10},
    {1, A_11,  B_11,  C_11},
    {1, A_12,  B_12,  C_12},
    {1, A_13,  B_13,  C_13},
    {1, A_14,  B_14,  C_14},

    {0, A_1,   B_1,   C_1},
    {0, A_2,   B_2,   C_2},
    {0, A_3,   B_3,   C_3},
    {0, A_4,   B_4,   C_4},
    {0, A_5,   B_5,   C_5},
    {0, A_6,   B_6,   C_6},
    {0, A_7,   B_7,   C_7},
    {0, A_8,   B_8,   C_8},
    {0, A_9,   B_9,   C_9},
    {0, A_10,  B_10,  C_10},
    {0, A_11,  B_11,  C_11},
    {0, A_12,  B_12,  C_12},
    {0, A_13,  B_13,  C_13},
    {0, A_14,  B_14,  C_14},
    {1, D_1,   E_1,   F_1},

    {0, D_1,   E_1,   F_1},
    {0, D_2,   E_2,   F_2},
    {0, D_3,   E_3,   F_3},
    {0, D_4,   E_4,   F_4},
    {0, D_5,   E_5,   F_5},
    {0, D_6,   E_6,   F_6},
    {0, D_7,   E_7,   F_7},
    {0, D_8,   E_8,   F_8},
    {0, D_9,   E_9,   F_9},
    {0, D_10,  E_10,  F_10},
    {0, D_11,  E_11,  F_11},
    {0, D_12,  E_12,  F_12},
    {0, D_13,  E_13,  F_13},
    {0, D_14,  E_14,  F_14},
    {1, D_2,   E_2,   F_2},

    {0, G_1,   H_1,   I_1},
    {0, G_2,   H_2,   I_2},
    {0, G_3,   H_3,   I_3},
    {0, G_4,   H_4,   I_4},
    {0, G_5,   H_5,   I_5},
    {0, G_6,   H_6,   I_6},
    {0, G_7,   H_7,   I_7},
    {0, G_8,   H_8,   I_8},
    {0, G_9,   H_9,   I_9},
    {0, G_10,  H_10,  I_10},
    {0, G_11,  H_11,  I_11},
    {0, G_12,  H_12,  I_12},
    {0, A_15,  B_15,  C_15},
    {0, G_13,  H_13,  I_13},
    {1, D_3,   E_3,   F_3},

    {0, J_1,   K_1,   L_1},
    {0, A_16,  B_16,  C_16},
    {0, J_2,   K_2,   L_2},
    {0, J_3,   K_3,   L_3},
    {0, J_4,   K_4,   L_4},
    {0, J_5,   K_5,   L_5},
    {0, J_6,   K_6,   L_6},
    {0, J_7,   K_7,   L_7},
    {0, J_8,   K_8,   L_8},
    {0, J_9,   K_9,   L_9},
    {0, J_10,  K_10,  L_10},
    {0, J_11,  K_11,  L_11},
    {0, J_12,  K_12,  L_12},
    {1, D_7,   E_7,   F_7},
    {1, D_4,   E_4,   F_4},

    {0, J_13,  K_13,  L_13},
    {0, J_14,  K_14,  L_14},
    {0, J_15,  K_15,  L_15},
    {0, J_16,  K_16,  L_16},

    {0, G_14,  H_14,  I_14},
    {0, G_15,  H_15,  I_15},
    {0, G_16,  H_16,  I_16},

    {0, D_15,  E_15,  F_15},
    {1, D_6,   E_6,   F_6},
    {1, D_5,   E_5,   F_5},

    {1, G_1,   H_1,   I_1},
    {1, G_2,   H_2,   I_2},
    {1, G_3,   H_3,   I_3},
    {1, G_4,   H_4,   I_4},
    {1, G_5,   H_5,   I_5},
    {1, G_6,   H_6,   I_6},
    {1, G_7,   H_7,   I_7},
    {1, G_8,   H_8,   I_8},
    {1, G_9,   H_9,   I_9},
    {1, G_10,  H_10,  I_10},
    {1, G_11,  H_11,  I_11},

    {1, J_1,   K_1,   L_1},
    {1, J_2,   K_2,   L_2},
    {1, J_3,   K_3,   L_3},
    {1, J_4,   K_4,   L_4},
    {1, J_5,   K_5,   L_5},
    {1, J_6,   K_6,   L_6},
    {1, J_7,   K_7,   L_7},
    {1, J_8,   K_8,   L_8},
    {1, J_9,   K_9,   L_9},
    {1, J_10,  K_10,  L_10},
    {1, J_11,  K_11,  L_11},
};

led_config_t g_led_config = {
    {
        {  0,       1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13, NO_LED,     NO_LED},
        {  14,      15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27, NO_LED,     28},
        {  29,      30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42, NO_LED,     43},
        {  44,      45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     57,     NO_LED, 58},
        {  59,      60,     61,     62,     63,     64,     65,     66,     67,     68,     69,     70,     NO_LED, 71,     72,     73},
        {  74,      75,     76, NO_LED, NO_LED,     77, NO_LED, NO_LED, NO_LED,     78,     79,     80,     NO_LED, 81,     82,     83}
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
        {196, 38}, // 57
        {224, 38}, // 57

        {  0, 51}, // 58
        { 14, 51}, // 59
        { 28, 51}, // 59
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
        {0,   6}, //  69 LED 2
        {0,   13}, //  70 LED 3
        {0,   19}, //  71 LED 4
        {0,   25}, //  72 LED 5
        {0,   32}, //  73 LED 6
        {0,   38}, //  74 LED 7
        {0,   45}, //  75 LED 8
        {0,   51}, //  73 LED 9
        {0,   57}, //  74 LED 10
        {0,   64}, //  75 LED 11

        {224, 0 }, //  78 LED 12
        {224, 6 }, //  79 LED 13
        {224, 13}, //  80 LED 14
        {224, 19}, //  81 LED 15
        {224, 25}, //  82 LED 16
        {224, 32}, //  83 LED 17
        {224, 38}, //  84 LED 18
        {224, 45}, //  82 LED 19
        {224, 51}, //  83 LED 20
        {224, 57}, //  84 LED 21
        {224, 64}  //  85 LED 22
    },
    {
        4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
        4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
        4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
        4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
        4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
        4,  4,  4,          4,              4,  4,  4,  4,  4,  4,
        2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
        2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2
    }
};

// clang-format on
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (pwron_flag == false) {
        map_current_time = timer_read();
        if (map_current_time < 3000) {
            rgb_matrix_set_color_all(150, 150, 150);
        }
        if (map_current_time >= 3000) {
            pwron_flag = true;
            if (!rgb_matrix_get_flags()) {
                rgb_matrix_set_flags(LED_FLAG_NONE);
                rgb_matrix_set_color_all(0, 0, 0);
            }
        }
    }else {
        if (host_keyboard_led_state().caps_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(44, 255, 255, 255);
        } else {
            if (!rgb_matrix_get_flags()) {
                RGB_MATRIX_INDICATOR_SET_COLOR(44, 0, 0, 0);
            }
        }
        if (keymap_config.no_gui) {
            RGB_MATRIX_INDICATOR_SET_COLOR(75, 255, 255, 255);
        } else {
            if (!rgb_matrix_get_flags()) {
                RGB_MATRIX_INDICATOR_SET_COLOR(75, 0, 0, 0);
            }
        }
    }
    return true;
}

#endif

enum __layers { WIN_B, WIN_W, WIN_FN, MAC_B, MAC_W, MAC_FN };

enum colors { WHITE, RED, GREEN, BLUE };
enum colors led_color_status = WHITE;

static bool     Lkey_flag        = false;
static bool     reset_glint_flag = false;
static bool     while_test_flag  = false;
static bool     alarm_flag       = false;
static uint16_t current_time     = 0;
static uint8_t  glint_cnt        = 0;
static uint16_t scancode         = 0;
static uint8_t  alarm_cnt        = 0;

#ifndef DISABLE_M1_KEYCODES
static bool     fn_make_flag     = false;
static uint8_t  RGB_HSV_level;
#endif

HSV hsv;

void led_test(uint8_t color);
void clear_eeprom(void);
void rgb_hsv_updata_user(void);

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifndef DISABLE_M1_KEYCODES
        case MO(WIN_FN):
        case MO(MAC_FN):
            fn_make_flag = record->event.pressed;
            return true;
        case KC_GRV:
            if (fn_make_flag && record->event.pressed) {
                Lkey_flag    = true;
                current_time = timer_read();
                scancode     = KC_GRV;
                return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_LCTL:
            if (fn_make_flag && record->event.pressed) {
                if (while_test_flag) {
                    while_test_flag = false;
                    rgb_matrix_init();
                } else {
                    Lkey_flag    = true;
                    current_time = timer_read();
                    scancode     = KC_LCTL;
                }
                return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case DF(WIN_B):
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();
                set_single_persistent_default_layer(WIN_B);
                layer_state_set(1<<WIN_B);
            }
            return false;
        case DF(MAC_B):
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();
                set_single_persistent_default_layer(MAC_B);
                layer_state_set(1<<MAC_B);
                keymap_config.no_gui     = 0;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
        case TG(WIN_W):
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();
                if (layer_state_cmp(default_layer_state, WIN_W)) {
                    set_single_persistent_default_layer(WIN_B);
                    layer_off(WIN_W);
                } else {
                    set_single_persistent_default_layer(WIN_W);
                    layer_on(WIN_W);
                }
            }
            return false;
        case TG(MAC_W):
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();
                if (layer_state_cmp(default_layer_state, MAC_W)) {
                    set_single_persistent_default_layer(MAC_B);
                    layer_off(MAC_W);
                } else {
                    set_single_persistent_default_layer(MAC_W);
                    layer_on(MAC_W);
                }
            }
            return false;
        case GU_TOGG:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();
            }
            return true;
        case RGB_VAI:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) < 4) {
                    alarm_cnt = 2;
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_VAD:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) > 0) {
                    alarm_cnt = 2;
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_SAI:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_sat() / (UINT8_MAX / 4)) < 4) {
                    alarm_cnt = 2;
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.s = (uint8_t)(UINT8_MAX / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_SAD:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_sat() / (UINT8_MAX / 4)) > 0) {
                    alarm_cnt = 2;
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.s = (uint8_t)(UINT8_MAX / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_HUI:
            if ((record->event.pressed) && (alarm_flag == 0)) {
                alarm_cnt = 2;
                RGB_HSV_level = (uint8_t)rgb_matrix_get_hue() / (UINT8_MAX / 6);
                RGB_HSV_level++;
                RGB_HSV_level %= 7;
                rgb_matrix_config.hsv.h = (uint8_t)(UINT8_MAX / 6) * RGB_HSV_level;
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_SPI:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_speed() / (UINT8_MAX / 4)) < 4) {
                    alarm_cnt = 2;
                    RGB_HSV_level++;
                    rgb_matrix_set_speed((uint8_t)(UINT8_MAX / 4) * RGB_HSV_level);
                }
            }
            return false;
        case RGB_SPD:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_speed() / (UINT8_MAX / 4)) > 0) {
                    alarm_cnt = 2;
                    RGB_HSV_level--;
                    rgb_matrix_set_speed((uint8_t)(UINT8_MAX / 4) * RGB_HSV_level);
                }
            }
            return false;
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
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;
#endif
        default:
            return true;
    }
}

void housekeeping_task_kb(void) {
    if (Lkey_flag) {
        if (scancode == KC_GRV) {
            if (timer_elapsed(current_time) >= 3000) {
                Lkey_flag = false;
                clear_eeprom();

                current_time     = timer_read();
                reset_glint_flag = true;
                glint_cnt        = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
        } else if (scancode == KC_LCTL) {
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
                rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            } else {
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
            if (glint_cnt >= 3) {
                glint_cnt        = 0;
                reset_glint_flag = false;
                rgb_matrix_init();
            }
        }

    } else if (while_test_flag) {
        if ((timer_elapsed(current_time)) >= 1000) {
            current_time = timer_read();
            if ((glint_cnt % 4) == 0) {
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            } else if ((glint_cnt % 4) == 1) {
                rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            } else if ((glint_cnt % 4) == 2) {
                rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            } else if ((glint_cnt % 4) == 3) {
                rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            }
            glint_cnt++;
            if (glint_cnt >= 30) {
                glint_cnt       = 0;
                while_test_flag = false;
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
    eeconfig_init();
    if (layer_state_is(MAC_B)) {
        set_single_persistent_default_layer(MAC_B);
    } else {
        set_single_persistent_default_layer(WIN_B);
    }
    layer_off(WIN_W);
    layer_off(MAC_W);
    keymap_config.no_gui = 0;
    eeconfig_update_keymap(keymap_config.raw);
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
