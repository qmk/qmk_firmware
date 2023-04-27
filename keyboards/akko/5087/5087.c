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

static uint16_t map_current_time = 0;
static bool     pwron_flag       = false;

// clang-format off
#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    /*row0*/
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
    {1, A_15,  B_15,  C_15},
    {1, A_16,  B_16,  C_16},

    /*row1*/
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
    {1, D_1,    E_1,   F_1},
    {1, D_2,    E_2,   F_2},
    {1, D_3,    E_3,   F_3},

    /*row2*/
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
    {1, G_1,   H_1,   I_1},
    {1, G_2,   H_2,   I_2},
    {1, G_3,   H_3,   I_3},

    /*row3*/
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
    {0, G_13,  H_13,  I_13},

    /*row4*/
    {0, J_1,   K_1,   L_1},
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
    {1,  J_4,   K_4,  L_4},

    /*row5*/
    {0, J_13,  K_13,  L_13},
    {0, J_14,  K_14,  L_14},
    {0, J_15,  K_15,  L_15},
    {0, J_16,  K_16,  L_16},
    {0, G_14,  H_14,  I_14},
    {0, G_15,  H_15,  I_15},
    {0, G_16,  H_16,  I_16},
    {0, D_15,  E_15,  F_15},
    {1,  J_1,   K_1,  L_1},
    {1,  J_2,   K_2,  L_2},
    {1,  J_3,   K_3,  L_3},
};

led_config_t g_led_config = {
    {
        {  0,       1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12, NO_LED,     13,     14,     15},
        {  16,      17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31,     32},
        {  33,      34,     35,     36,     37,     38,     39,     40,     41,     42,     43,     44,     45,     46,     47,     48,     49},
        {  50,      51,     52,     53,     54,     55,     56,     57,     58,     59,     60,     61, NO_LED,     62, NO_LED, NO_LED, NO_LED},
        {  63,      64,     65,     66,     67,     68,     69,     70,     71,     72,     73, NO_LED, NO_LED,     74, NO_LED,     75, NO_LED},
        {  76,      77,     78, NO_LED, NO_LED,     79, NO_LED, NO_LED, NO_LED,     80,     81,     82, NO_LED,     83,     84,     85,     86},
    },
    {
        //ROW0
        {0,  0 }, //0
        {24,  0 }, //1
        {38,  0 }, //2
        {52,  0 }, //3
        {66,  0 }, //4
        {82,  0 }, //5
        {96,  0 }, //6
        {110,  0 }, //7
        {124,  0 }, //8
        {140,  0 }, //9
        {154,  0 }, //10
        {168,  0 }, //11
        {182,  0 }, //12
        {196,  0 }, //13
        {210,  0 }, //14
        {224,  0 }, //15
        // ROW1
        {0,  12}, // 16
        {13,  12}, // 17
        {26,  12}, // 18
        {39,  12}, // 19
        {52,  12}, // 20
        {65,  12}, // 21
        {79,  12}, // 22
        {92,  12}, // 23
        {105,  12}, // 24
        {118,  12}, // 25
        {131,  12}, // 26
        {144,  12}, // 27
        {158,  12}, // 28
        {171,  12}, // 29
        {184,  12}, // 30
        {197,  12}, // 31
        {210,  12}, // 32
        //ROW2
        {0,  26 }, //33
        {14,  26 }, //34
        {28,  26 }, //35
        {42,  26 }, //36
        {56,  26 }, //37
        {70,  26 }, //38
        {84,  26 }, //39
        {98,  26 }, //40
        {112,  26 }, //41
        {126,  26 }, //42
        {140,  26 }, //43
        {154,  26 }, //44
        {168,  26 }, //45
        {182,  26 }, //46
        {196,  26 }, //47
        {210,  26 }, //48
        {224,  26 }, //49
        //ROW3
        {0,  38 }, //50
        {14,  38 }, //51
        {28,  38 }, //52
        {42,  38 }, //53
        {56,  38 }, //54
        {70,  38 }, //55
        {84,  38 }, //56
        {98,  38 }, //57
        {112,  38 }, //58
        {126,  38 }, //59
        {140,  38 }, //60
        {154,  38 }, //61
        {182,  38 }, //62
        //ROW4
        {0,  51 }, //63
        {14,  51 }, //64
        {28,  51 }, //65
        {42,  51 }, //66
        {56,  51 }, //67
        {70,  51 }, //68
        {84,  51 }, //69
        {98,  51 }, //70
        {112,  51 }, //71
        {126,  51 }, //72
        {140,  51 }, //73
        {182,  51 }, //74
        {210,  51 }, //75
        //ROW5
        {0,  64 }, //76
        {14,  64 }, //77
        {28,  64 }, //78
        {70,  64 }, //79
        {126,  64 }, //80
        {140,  64 }, //81
        {154,  64 }, //82
        {182,  64 }, //83
        {196,  64 }, //84
        {210,  64 }, //85
        {224,  64 }, //86
    },
    {
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,      4,  4,  4,
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,      4,
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,          4,      4,
		4,  4,  4,          4,              4,  4,  4,      4,  4,  4,  4,
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
    }
    return true;
}

#endif // RGB_MATRIX_ENABLE

void led_test(uint8_t color);
void clear_eeprom(void);

enum __layers { WIN_B, WIN_W, WIN_FN, MAC_B, MAC_W, MAC_FN };
enum colors { WHITE, RED, GREEN, BLUE };
enum colors led_color_status = WHITE;

// clang-format on
typedef union {
    uint32_t raw;
    struct {
        bool MacMode_flag : 1;
        bool _WASD_layer_flag : 1;
    };
} kb_config_t;

kb_config_t kb_config;

static bool     fn_make_flag     = false;
static bool     Rwin_make_flag   = false;
static bool     Lwin_make_flag   = false;
static bool     Lkey_flag        = false;
static bool     reset_glint_flag = false;
static bool     while_test_flag  = false;
static bool     alarm_flag       = false;
static uint16_t current_time     = 0;
static uint8_t  glint_cnt        = 0;
static uint16_t scancode         = 0;
static uint8_t  alarm_cnt        = 0;
static uint8_t  RGB_HSV_level;
HSV             hsv;

void keyboard_post_init_kb(void) {
    kb_config.raw = eeconfig_read_kb(); // Read status from EEPROM
    if (kb_config.MacMode_flag) { 
        layer_on(MAC_B);
    }
    if (kb_config._WASD_layer_flag) {
        kb_config.MacMode_flag ? layer_on(MAC_W) : layer_on(WIN_W);
    }
}

void led_init_ports(void) {
    // set our LED pings as output
    setPinOutput(LED_CAPS_LOCK_PIN); // LED1 Num Lock
    writePinLow(LED_CAPS_LOCK_PIN);
    setPinOutput(LED_MAC_OS_PIN); // LDE2 MAC\WIN
    writePinLow(LED_MAC_OS_PIN);
    setPinOutput(LED_WIN_LOCK_PIN); // LED3 Win Lock
    writePinLow(LED_WIN_LOCK_PIN);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
        writePin(LED_MAC_OS_PIN, kb_config.MacMode_flag);
        writePin(LED_WIN_LOCK_PIN, keymap_config.no_gui);
    }
    return res;
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifndefine DISABLE_5085_KEYCODES
        case MO(WIN_FN):
        case MO(MAC_FN):
            fn_make_flag = record->event.pressed;
            return true;
        case KC_RGUI:
            if (kb_config.MacMode_flag) {
                return true;
            }
            Rwin_make_flag = false;
            if (record->event.pressed) {
                if (Lwin_make_flag) {
                    Lkey_flag    = true;
                    current_time = timer_read();
                    scancode     = KC_LGUI;
                    return false;
                } else {
                    Rwin_make_flag = true;
                }
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_LGUI:
            if (kb_config.MacMode_flag) {
                return true;
            }
            Lwin_make_flag = false;
            if (record->event.pressed) {
                if (Rwin_make_flag) {
                    Lkey_flag    = true;
                    current_time = timer_read();
                    scancode     = KC_LGUI;
                    return false;
                } else {
                    Lwin_make_flag = true;
                }
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_RALT:
            if (!kb_config.MacMode_flag) {
                return true;
            }
            Rwin_make_flag = false;
            if (record->event.pressed) {
                if (Lwin_make_flag) {
                    Lkey_flag    = true;
                    current_time = timer_read();
                    scancode     = KC_LGUI;
                    return false;
                } else {
                    Rwin_make_flag = true;
                }
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_LALT:
            if (!kb_config.MacMode_flag) {
                return true;
            }
            Lwin_make_flag = false;
            if (record->event.pressed) {
                if (Rwin_make_flag) {
                    Lkey_flag    = true;
                    current_time = timer_read();
                    scancode     = KC_LGUI;
                    return false;
                } else {
                    Lwin_make_flag = true;
                }
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
                layer_state_set(1 << WIN_B);
                kb_config.MacMode_flag     = false;
                kb_config._WASD_layer_flag = false;
                eeconfig_update_kb(kb_config.raw);
            }
            return false;
        case DF(MAC_B):
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();

                set_single_persistent_default_layer(MAC_B);
                layer_state_set(1 << MAC_B);
                keymap_config.no_gui = 0;
                eeconfig_update_keymap(keymap_config.raw);
                kb_config.MacMode_flag     = true;
                kb_config._WASD_layer_flag = false;
                eeconfig_update_kb(kb_config.raw);
            }
            return false;
        case TG(WIN_W):
            if (record->event.pressed) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time                 = timer_read();
                kb_config._WASD_layer_flag = !layer_state_is(WIN_W);
                eeconfig_update_kb(kb_config.raw);
            }
            return true;
        case TG(MAC_W):
            if (record->event.pressed) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time                 = timer_read();
                kb_config._WASD_layer_flag = !layer_state_is(MAC_W);
                eeconfig_update_kb(kb_config.raw);
            }
            return true;
        case GU_TOGG:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time = timer_read();
                writePin(LED_WIN_LOCK_PIN, !keymap_config.no_gui);
            }
            return true;
        case RGB_VAI:
            if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) < 4) {
                if (!record->event.pressed) {
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                    rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
                } else {
                    if (!alarm_flag) {
                        alarm_cnt = 2;
                    }
                }
            }
            return false;
        case RGB_VAD:
            if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) > 0) {
                if (!record->event.pressed) {
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                    rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
                } else {
                    if (!alarm_flag) {
                        alarm_cnt = 2;
                    }
                }
            }
            return false;
        case RGB_SAI:
            if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_sat() / (UINT8_MAX / 4)) < 4) {
                if (!record->event.pressed) {
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.s = (uint8_t)(UINT8_MAX / 4) * RGB_HSV_level;
                    rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
                } else {
                    if (!alarm_flag) {
                        alarm_cnt = 2;
                    }
                }
            }

            return false;
        case RGB_SAD:
            if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_sat() / (UINT8_MAX / 4)) > 0) {
                if (!record->event.pressed) {
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.s = (uint8_t)(UINT8_MAX / 4) * RGB_HSV_level;
                    rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
                } else {
                    if (!alarm_flag) {
                        alarm_cnt = 2;
                    }
                }
            }
            return false;
        case RGB_HUI:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_cnt     = 2;
                RGB_HSV_level = (uint8_t)rgb_matrix_get_hue() / (UINT8_MAX / 6);
                RGB_HSV_level++;
                RGB_HSV_level %= 7;
                rgb_matrix_config.hsv.h = (uint8_t)(UINT8_MAX / 6) * RGB_HSV_level;
                rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
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
#endif //DISABLE_5087_KEYKODES
        default:
            return true;
    }
}

void housekeeping_task_kb(void) {
    if (Lkey_flag) {
        if (scancode == KC_LGUI) {
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
        if ((timer_elapsed(current_time)) >= 50) {
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
        // layer_state_set(1<<MAC_B);
    } else {
        set_single_persistent_default_layer(WIN_B);
        // layer_state_set(1<<WIN_B);
    }
    layer_off(WIN_W);
    layer_off(MAC_W);
    kb_config._WASD_layer_flag = false;
    eeconfig_update_kb(kb_config.raw);
    keymap_config.no_gui = false;
    writePin(LED_WIN_LOCK_PIN, keymap_config.no_gui);
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
