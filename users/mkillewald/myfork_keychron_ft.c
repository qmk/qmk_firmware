/* Copyright 2023 @ Mike Killewald (https://github.com/mkillewald)
 * forked from keychron_ft_common.c (https://www.keychron.com)
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

#include "myfork_keychron_ft.h"
#include "mkillewald.h"
#include "layers.h"

// clang-format off
enum {
    FACTORY_TEST_CMD_BACKLIGHT = 0x01,
    FACTORY_TEST_CMD_JUMP_TO_BL,
    FACTORY_TEST_CMD_EEPROM_CLEAR
};
// clang-format on

deferred_token      combo_exec_token;
uint16_t            key_press_status    = 0;
uint8_t             factory_reset_count = 0;
extern matrix_row_t matrix[MATRIX_ROWS];

#if defined(SPLIT_KEYBOARD)
#    if defined(RGB_MATRIX_ENABLE)
uint8_t led_state        = 0;
uint8_t light_test_state = 0;
HSV     hsv;
#    endif
#endif

static uint32_t LED_flash_300ms(uint32_t trigger_time, void *cb_arg) {
    if (factory_reset_count++ > 6) {
        factory_reset_count = 0;
#if defined(RGB_MATRIX_ENABLE)
    if (is_win_mode()) { 
        set_win_base_rgb();
    } else {
        set_mac_base_rgb();
    }
#    ifdef SPLIT_KEYBOARD
        rgb_matrix_mode_noeeprom(led_state);
        rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
#    endif
#endif
        return 0; // no repeat
    }
    return 300;  // repeat 300ms
}

static void factory_reset(void) {
    defer_exec(300, LED_flash_300ms, NULL);
    factory_reset_count++;
    layer_state_t default_layer = default_layer_state;
    eeconfig_init();
    default_layer_set(default_layer);
    led_test_mode = LED_TEST_MODE_OFF;
#if defined(LED_MATRIX_ENABLE)
    if (!led_matrix_is_enabled()) {
        led_matrix_enable();
    }
    led_matrix_init();
#endif
#if defined(RGB_MATRIX_ENABLE)
    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_enable();
    }
    rgb_matrix_init();
#    ifdef SPLIT_KEYBOARD
    led_state = rgb_matrix_get_mode();
    hsv       = rgb_matrix_get_hsv();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#    endif
#endif
}

static uint32_t combo_exec_3s(uint32_t trigger_time, void *cb_arg) {
    if (key_press_status == KEY_PRESS_FACTORY_RESET) {
        factory_reset();
    } else if (key_press_status == KEY_PRESS_LED_TEST) {
#if defined(SPLIT_KEYBOARD)
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
        led_test_mode = LED_TEST_MODE_WHITE;
#if defined(LED_MATRIX_ENABLE)
        if (!led_matrix_is_enabled()) {
            led_matrix_enable_noeeprom();
        }
#endif
#if defined(RGB_MATRIX_ENABLE)
        if (!rgb_matrix_is_enabled()) {
            rgb_matrix_enable_noeeprom();
        }
#endif
    }
    key_press_status = 0;
    return 0;  // no repeat
}

__attribute__((weak))
bool process_record_myfork_keychron_ft(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#if defined(FN_KEY1) || defined(FN_KEY2)
#    ifdef FN_KEY1
        case FN_KEY1: /* fall through */
#    endif
#    if defined(FN_KEY2)
        case FN_KEY2:
#    endif
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_STEP_0;
            } else {
                key_press_status &= ~KEY_PRESS_STEP_0;
                cancel_deferred_exec(combo_exec_token);
            }
            return true;
#endif
#if defined(RESET_KEY1) && defined(RESET_KEY2)
        case RESET_KEY1:
#    if defined(RESET_KEY1_ALT)
        case RESET_KEY1_ALT:
#    endif
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_STEP_1;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    combo_exec_token = defer_exec(3000, combo_exec_3s, NULL);
                }
            } else {
                key_press_status &= ~KEY_PRESS_STEP_1;
                cancel_deferred_exec(combo_exec_token);
            }
            return true;
        case RESET_KEY2:
#    if defined(RESET_KEY2_ALT)
        case RESET_KEY2_ALT:
#    endif
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_STEP_2;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    combo_exec_token = defer_exec(3000, combo_exec_3s, NULL);
                }
            } else {
                key_press_status &= ~KEY_PRESS_STEP_2;
                cancel_deferred_exec(combo_exec_token);
            }
            return true;
#endif
#if defined(BL_TEST_KEY1) && defined(BL_TEST_KEY2)
        case BL_TEST_KEY1:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_STEP_3;
                if (led_test_mode) {
                    if (++led_test_mode >= LED_TEST_MODE_MAX) {
                        led_test_mode = LED_TEST_MODE_WHITE;
                    }
                } else if (key_press_status == KEY_PRESS_LED_TEST) {
                    combo_exec_token = defer_exec(3000, combo_exec_3s, NULL);
                }
            } else {
                key_press_status &= ~KEY_PRESS_STEP_3;
                cancel_deferred_exec(combo_exec_token);
            }
            return true;
        case BL_TEST_KEY2:
#    if defined(BL_TEST_KEY2_ALT1)
        case BL_TEST_KEY2_ALT1:
#    endif
#    if defined(BL_TEST_KEY2_ALT2)
        case BL_TEST_KEY2_ALT2:
#    endif
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_STEP_4;
                if (led_test_mode) {
                    led_test_mode = LED_TEST_MODE_OFF;
#    if defined(RGB_MATRIX_ENABLE)
                    if (is_win_mode()) {
                        set_win_base_rgb();
                    } else {
                        set_mac_base_rgb();
                    }
#    endif
                } else if (key_press_status == KEY_PRESS_LED_TEST) {
                    combo_exec_token = defer_exec(3000, combo_exec_3s, NULL);
                }
            } else {
                key_press_status &= ~KEY_PRESS_STEP_4;
                cancel_deferred_exec(combo_exec_token);
            }
            return true;
#endif
        default:
            return true;
    }
}

#if defined(LED_MATRIX_ENABLE)
bool led_matrix_indicators_advanced_myfork_keychron_ft(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_count) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            led_matrix_set_value(i, factory_reset_count % 2 ? 0 : UINT8_MAX);
        }
    }
    return true;
}
#endif

#if defined(RGB_MATRIX_ENABLE)
bool rgb_matrix_indicators_advanced_myfork_keychron_ft(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_count) {
        if (rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
            if (factory_reset_count % 2) {
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            } else {
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
        } else {
            for (uint8_t i = led_min; i <= led_max; i++) {
                rgb_matrix_set_color(i, factory_reset_count % 2 ? 0 : RGB_RED);
            }
        }
    } else if (led_test_mode) {
        switch (led_test_mode) {
            case LED_TEST_MODE_WHITE:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_WHITE);
                }
                break;
            case LED_TEST_MODE_RED:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_RED);
                }
                break;
            case LED_TEST_MODE_GREEN:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_GREEN);
                }
                break;
            case LED_TEST_MODE_BLUE:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_BLUE);
                }
                break;
            default:
                break;
        }
    }
    return true;
}
#endif
