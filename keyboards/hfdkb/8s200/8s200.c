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
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |   R location
 *   |   |     G location
 *   |   |     |     B location
 *   |   |     |     | */
    {1, SW3_CS1,   SW2_CS1,   SW1_CS1},
    {1, C_2,   B_2,   A_2},
    {1, C_3,   B_3,   A_3},
    {1, C_4,   B_4,   A_4},
    {1, C_5,   B_5,   A_5},
    {1, C_6,   B_6,   A_6},
    {1, C_7,   B_7,   A_7},
    {1, C_8,   B_8,   A_8},
    {1, C_9,   B_9,   A_9},
    {1, C_10,  B_10,  A_10},
    {1, C_11,  B_11, A_11},
    {1, C_12,  B_12, A_12},
    {1, C_13,  B_13, A_13},
    {1, C_14,  B_14, A_14},
    {1, C_15,  B_15, A_15},
    {1, C_16,  B_16, A_16},

    {0, F_1,   E_1,   D_1},
    {0, F_2,   E_2,   D_2},
    {0, F_3,   E_3,   D_3},
    {0, F_4,   E_4,   D_4},
    {0, F_5,   E_5,   D_5},
    {0, F_6,   E_6,   D_6},
    {0, F_7,   E_7,   D_7},
    {0, F_8,   E_8,   D_8},
    {0, F_9,   E_9,   D_9},
    {0, F_10,  E_10,  D_10},
    {0, F_11,  E_11,  D_11},
    {0, F_12,  E_12,  D_12},
    {0, F_13,  E_13,  D_13},
    {1, F_1,   E_1,   D_1},

    {0, I_1,   H_1,   G_1},
    {0, I_2,   H_2,   G_2},
    {0, I_3,   H_3,   G_3},
    {0, I_4,   H_4,   G_4},
    {0, I_5,   H_5,   G_5},
    {0, I_6,   H_6,   G_6},
    {0, I_7,   H_7,   G_7},
    {0, I_8,   H_8,   G_8},
    {0, I_9,   H_9,   G_9},
    {0, I_10,  H_10,  G_10},
    {0, I_11,  H_11,  G_11},
    {0, I_12,  H_12,  G_12},
    {0, I_13,  H_13,  G_13},
    {1, F_5,   E_5,   D_5},
    {1, F_2,   E_2,   D_2},

    {0, L_1,   K_1,   J_1},
    {0, L_3,   K_3,   J_3},
    {0, L_4,   K_4,   J_4},
    {0, L_5,   K_5,   J_5},
    {0, L_6,   K_6,   J_6},
    {0, L_7,   K_7,   J_7},
    {0, L_8,   K_8,   J_8},
    {0, L_9,   K_9,   J_9},
    {0, L_10,  K_10,  J_10},
    {0, L_11,  K_11,  J_11},
    {0, L_12,  K_12,  J_12},
    {1, F_9,   E_9,   D_9},
    {1, F_8,   E_8,   D_8},
    {1, F_6,   E_6,   D_6},
    {1, F_3,   E_3,   D_3},

    {0, L_13,  K_13,  J_13},
    {0, L_14,  K_14,  J_14},
    {0, L_15,  K_15,  J_15},
    {0, L_16,  K_16,  J_16},

    {0, I_14,  H_14,  G_14},

    {0, I_15,  H_15,  G_15},
    {0, I_16,  H_16,  G_16},
    {0, F_14,  E_14,  D_14},
    {0, F_15,  E_15,  D_15},
    {0, F_16,  E_16,  D_16},
    {1, F_7,   E_7,   D_7},
    {1, F_4,   E_4,   D_4},

    {0, L_2,   K_2,   J_2},
    {1, D_10,  E_10,  F_10},
    {1, D_11,  E_11,  F_11},
};
#endif
// clang-format on
typedef union {
    uint32_t raw;
    struct {
        bool    first_boot;
        uint8_t rgb_mode;
    };
} keyboard_config_t;
keyboard_config_t keyboard_config;

uint8_t  rgb_test_en;
uint8_t  rgb_test_index;
uint32_t long_pressed_time;
uint16_t long_pressed_keycode;
uint8_t  all_blink_cnt;
uint32_t all_blink_time;
RGB      all_blink_color;
uint8_t  single_blink_cnt;
uint8_t  single_blink_index;
RGB      single_blink_color;
uint32_t single_blink_time;
uint8_t  EE_CLR_blink_cnt;
RGB      EE_CLR_blink_color;
uint32_t EE_CLR_blink_time;

const uint8_t rgb_test_color_table[][3] = {
    {RGB_WHITE},
    {RGB_RED},
    {RGB_GREEN},
    {RGB_BLUE},
};
// clang-format off
static uint8_t rgb_matrix_effects_table[] = {
    RGB_MATRIX_BREATHING,
    RGB_MATRIX_SOLID_COLOR,
    RGB_MATRIX_CYCLE_LEFT_RIGHT,
    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,
    RGB_MATRIX_CYCLE_OUT_IN_DUAL,
    RGB_MATRIX_DUAL_BEACON,
    RGB_MATRIX_RAINBOW_BEACON,
    RGB_MATRIX_RAINDROPS,
    RGB_MATRIX_SOLID_REACTIVE,
};

// clang-format on
bool process_record_kb(uint16_t keycode, keyrecord_t *record) { // 处理键盘按键事件
    if (process_record_user(keycode, record) != true) {         // 自定义按键处理
        return false;                                           // 用户已处理了按键事件无需进一步处理
    }
    switch (keycode) {
        case SW_OS1:
            if (record->event.pressed) {
                long_pressed_time    = timer_read32();
                long_pressed_keycode = SW_OS1;
            } else {
                long_pressed_time = 0;
            }
            break;
        case RGB_TEST:
            if (record->event.pressed) {
                long_pressed_time    = timer_read32();
                long_pressed_keycode = RGB_TEST;
            } else {
                long_pressed_time = 0;
            }
            break;
        case NK_TOGG:
            if (record->event.pressed) {
                long_pressed_time    = timer_read32();
                long_pressed_keycode = NK_TOGG;
            } else {
                long_pressed_time = 0;
            }
            return false;
        case EE_CLR:
            if (record->event.pressed) {
                long_pressed_time    = timer_read32();
                long_pressed_keycode = EE_CLR;
            } else {
                long_pressed_time = 0;
            }
            return false;
        case KC_DEL:
            if (record->event.pressed) {
                if (rgb_test_en) {
                    rgb_test_en = false;
                    return false;
                }
            }
            break;
        case KC_DOWN:
            if (record->event.pressed) {
                if (rgb_test_en) {
                    rgb_test_index++;
                    rgb_test_index %= 4;
                    return false;
                }
            }
            break;
        case RGB_SPI:
            if (record->event.pressed) {
                rgb_matrix_increase_speed();
                if (rgb_matrix_get_speed() >= 255) {
                    rgb_matrix_config.speed = 255;
                }
            }
            return false;
        case RGB_SPD:
            if (record->event.pressed) {
                rgb_matrix_decrease_speed();
                if (rgb_matrix_get_speed() <= 27) {
                    rgb_matrix_config.speed = 27;
                }
            }
            return false;
        // case GU_TOGG:
        //     if (record->event.pressed) {
        //     } else {
        //         if (keymap_config.no_gui) {
        //             single_blink_time  = timer_read32();
        //             single_blink_cnt   = 2;
        //             single_blink_index = 74;
        //             single_blink_color = (RGB){100, 100, 100};
        //         }
        //     }
        //     break;
        case RGB_MOD:
            if (record->event.pressed) {
                keyboard_config.rgb_mode++;
                if (keyboard_config.rgb_mode > (sizeof(rgb_matrix_effects_table) / sizeof(rgb_matrix_effects_table[0]))) {
                    keyboard_config.rgb_mode = 0;
                }
                eeconfig_update_user(keyboard_config.raw);
                if (keyboard_config.rgb_mode == 9) {
                    // rgb_matrix_disable_noeeprom();
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_set_color_all(0, 0, 0);
                } else {
                    // rgb_matrix_enable();
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_mode(rgb_matrix_effects_table[keyboard_config.rgb_mode]);
                }
                // if (rgb_matrix_get_mode() == RGB_MATRIX_NONE) {
                // }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                if (keyboard_config.rgb_mode == 9) {
                    return false;
                }
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
        default:
            break;
    }
    return true;
}

void matrix_init_kb(void) {
#ifdef RGB_DRIVER_SDB_PIN
    setPinOutputOpenDrain(RGB_DRIVER_SDB_PIN);
    writePinHigh(RGB_DRIVER_SDB_PIN);
#endif

    matrix_init_user();
}

void keyboard_post_init_kb() {
    // rgb_matrix_config.hsv.h = 170;
    // rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    keyboard_config.raw = eeconfig_read_user();
    rgb_matrix_mode(rgb_matrix_effects_table[keyboard_config.rgb_mode]);
    if (keyboard_config.rgb_mode == 9) {
        // rgb_matrix_disable_noeeprom();
        rgb_matrix_set_flags(LED_FLAG_NONE);
        rgb_matrix_set_color_all(0, 0, 0);
    }

    keyboard_post_init_user(); // call matrix_init_user() at the end of this function
}

void housekeeping_task_kb(void) {
    if (!keyboard_config.first_boot) {
        keymap_config.nkro = 1; // 全键无冲
        eeconfig_update_keymap(keymap_config.raw);
        keyboard_config.first_boot = 1;
        rgb_matrix_config.hsv.h    = 170;
        eeconfig_update_user(keyboard_config.raw);
        // HSV hsv = rgb_matrix_get_hsv();
        // hsv.h = 170;
        // RGB rgb = hsv_to_rgb(hsv);
        // rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }

#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
    if ((timer_elapsed32(long_pressed_time) > 2000) && (long_pressed_time)) { // 检查是否有按键长按
        long_pressed_time = 0;
        switch (long_pressed_keycode) {
            case RGB_TEST:
                rgb_test_en = 1;
                break;
            case SW_OS1:
                if (get_highest_layer(default_layer_state) == 0) { // MAC_BASE
                    set_single_persistent_default_layer(2);
                    keymap_config.no_gui = 0;
                    eeconfig_update_keymap(keymap_config.raw); // Write default value to EEPROM now
                    single_blink_time  = timer_read32();
                    single_blink_cnt   = 2;
                    single_blink_index = 73;
                    single_blink_color = (RGB){100, 100, 100};
                } else if (get_highest_layer(default_layer_state) == 2) { // WIN_BASE
                    set_single_persistent_default_layer(0);
                    single_blink_time  = timer_read32();
                    single_blink_cnt   = 2;
                    single_blink_index = 73;
                    single_blink_color = (RGB){.r = 0, .g = 0, .b = 100};
                }
                break;
            case NK_TOGG:
                keymap_config.nkro = !keymap_config.nkro;
                eeconfig_update_keymap(keymap_config.raw);
                single_blink_time  = timer_read32();
                single_blink_cnt   = 6;
                single_blink_index = 13;
                single_blink_color = (RGB){100, 100, 100};
                break;
            case EE_CLR:
                // eeconfig_update_rgb_matrix_default();

                EE_CLR_blink_time = timer_read32();
                EE_CLR_blink_cnt  = 6;
                // EE_CLR_blink_index = 64;
                EE_CLR_blink_color = (RGB){.r = 100, .g = 100, .b = 100};
                break;
            default:
                break;
        }
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_indicators_advanced_user(led_min, led_max) != true) {
        return false;
    }
    // rgb_matrix_set_color(73, 0, 0, 0);
    // rgb_matrix_set_color(74, 0, 0, 0);

    if (rgb_test_en) {
        rgb_matrix_set_color_all(rgb_test_color_table[rgb_test_index][0], rgb_test_color_table[rgb_test_index][1], rgb_test_color_table[rgb_test_index][2]);
    }

    /*************************************************************************************/
    if (all_blink_cnt) { // 全键闪烁
        rgb_matrix_set_color_all(0, 0, 0);
        if (timer_elapsed32(all_blink_time) > 300) {
            all_blink_time = timer_read32();
            all_blink_cnt--;
        }
        if (all_blink_cnt & 0x1) {
            rgb_matrix_set_color_all(all_blink_color.r, all_blink_color.g, all_blink_color.b);
        }
    }

    if (single_blink_cnt) { // 单键闪烁
        if (timer_elapsed32(single_blink_time) > 300) {
            single_blink_time = timer_read32();
            single_blink_cnt--;
        }
        if (single_blink_cnt % 2) {
            rgb_matrix_set_color(single_blink_index, single_blink_color.r, single_blink_color.g, single_blink_color.b);
        } else {
            rgb_matrix_set_color(single_blink_index, 0, 0, 0);
        }
    }
    /*************************************************************************************/
    if (EE_CLR_blink_cnt) { // 复位闪烁
        if (EE_CLR_blink_cnt % 2) {
            rgb_matrix_set_color(73, EE_CLR_blink_color.r, EE_CLR_blink_color.g, EE_CLR_blink_color.b);
            rgb_matrix_set_color(74, EE_CLR_blink_color.r, EE_CLR_blink_color.g, EE_CLR_blink_color.b);
        } else {
            rgb_matrix_set_color(73, 0, 0, 0);
            rgb_matrix_set_color(74, 0, 0, 0);
        }
        if (timer_elapsed32(EE_CLR_blink_time) > 300) {
            if (EE_CLR_blink_cnt > 0) {
                EE_CLR_blink_time = timer_read32();
                EE_CLR_blink_cnt--;
            }
            if (!EE_CLR_blink_cnt) {
                eeconfig_init();
                eeconfig_update_rgb_matrix_default();
                keyboard_config.rgb_mode = 0;
                rgb_matrix_mode(rgb_matrix_effects_table[keyboard_config.rgb_mode]);
                // rgb_matrix_set_color_all(RGB_BLUE);
                rgb_matrix_config.hsv.h = 170;
                eeconfig_update_user(keyboard_config.raw); // Write default value to EEPROM now
                keymap_config.no_gui = 0;
                keymap_config.nkro   = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
        }
    }
    /*************************************************************************************/
    // caps lock red
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(72, 100, 100, 100);
    } else {
        rgb_matrix_set_color(72, 0, 0, 0);
    }

    if (keymap_config.no_gui) {
        rgb_matrix_set_color(61, 100, 100, 100);
    }

    return true;
}
