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
#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
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

    {0, J_13,  K_13,  L_13},
    {0, J_14,  K_14,  L_14},
    {0, J_15,  K_15,  L_15},
    {0, J_16,  K_16,  L_16},
    {0, D_13,  E_13,  F_13},
    {0, D_14,  E_14,  F_14},
    {0, D_15,  E_15,  F_15},
    {0, G_13,  H_13,  I_13},
    {0, G_14,  H_14,  I_14},
    {0, G_15,  H_15,  I_15},
    {0, G_16,  H_16,  I_16},
};

#endif

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(12, 255, 0, 0);
    }

    return true;
}
#endif
enum colors {
    WHITE,
    RED,
    GREEN,
    BLUE
};
enum colors led_color_status = WHITE;

static bool     Lkey_flag           = false;
static bool     reset_glint_flag    = false;
static bool     while_test_flag     = false;
static uint16_t current_time        = 0;
static uint8_t  glint_cnt           = 0;
static uint16_t scancode           = 0;

#ifndef DISABLE_MK47_KEYCODES
static bool     fn_make_flag        = false;
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
#ifndef DISABLE_MK47_KEYCODES
        case MO(1):
            fn_make_flag = record->event.pressed;
            return true;
        case KC_DEL:
            if (fn_make_flag && record->event.pressed) {
                    Lkey_flag           = true;
                    current_time     = timer_read();
                    scancode = KC_DEL;
                    return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_SPC:
            if (fn_make_flag && record->event.pressed) {
                if (while_test_flag) {
                    while_test_flag = false;
                    rgb_matrix_init();
                } else {
                    Lkey_flag    = true;
                    current_time = timer_read();
                    scancode     = KC_SPC;
                }
                return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case RGB_VAI:
            if (record->event.pressed) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) < 4) {
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_VAD:
            if (record->event.pressed) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) > 0) {
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_HUI:
            if (record->event.pressed) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_hue() / (UINT8_MAX / 9)) < 9) {
                    RGB_HSV_level++;
                }else{
                    RGB_HSV_level = 1;
                }
                rgb_matrix_config.hsv.h = (uint8_t)(UINT8_MAX / 9) * RGB_HSV_level;
                rgb_hsv_updata_user();
            }
            return false;

        case RGB_SPI:
            if (record->event.pressed) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_speed() / (UINT8_MAX / 5)) < 5) {
                    RGB_HSV_level++;
                    rgb_matrix_set_speed((uint8_t)(UINT8_MAX / 5) * RGB_HSV_level);
                }
            }
            return false;
        case RGB_SPD:
            if (record->event.pressed) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_speed() / (UINT8_MAX / 5)) > 0) {
                    RGB_HSV_level--;
                    rgb_matrix_set_speed((uint8_t)(UINT8_MAX / 5) * RGB_HSV_level);
                }
            }
            return false;
#endif
        default:
            return true;
    }
}

void housekeeping_task_kb(void) {
    if (Lkey_flag) {
        if (scancode == KC_DEL) {
            if (timer_elapsed(current_time) >= 5000) {
                Lkey_flag = false;
                clear_eeprom();

                current_time  = timer_read();
                reset_glint_flag = true;
                glint_cnt = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
        } else if (scancode == KC_SPC) {
            if (timer_elapsed(current_time) >= 3000) {
                Lkey_flag = false;
                clear_eeprom();

                while_test_flag = true;
                glint_cnt = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            }
        }
    } else if (reset_glint_flag) {
        if ((timer_elapsed(current_time)) >= 300) {
            current_time = timer_read();
            if (((glint_cnt++) & 0x01 )== 0) {
                rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            } else {
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
            if (glint_cnt >= 3) {
                glint_cnt          = 0;
                reset_glint_flag = false;
                rgb_matrix_init();
            }
        }

    } else if (while_test_flag) {
        if ((timer_elapsed(current_time)) >= 1500) {
            current_time = timer_read();
            if ((glint_cnt%3) == 0) {
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            } else if ((glint_cnt%3)== 1) {
                rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            } else if ((glint_cnt%3)== 2) {
                rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            }
            glint_cnt++;
            if (glint_cnt >= 30) {
                glint_cnt       = 0;
                while_test_flag = false;
                rgb_matrix_init();
            }
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
