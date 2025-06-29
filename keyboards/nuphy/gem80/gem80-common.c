/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "action.h"
#include "color.h"
#include "common/features/socd_cleaner.h"
#include "common/rf_driver.h"
#include "common/links.h"
#include "common/config.h"
#include "common/keycodes.h"
#include "common/via.h"
#include "config.h"
#include "host.h"
#include "keycodes.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "quantum.h"
#include "rgb_matrix.h"
#include "user_kb.h"

#ifdef VIA_ENABLE
#    include "eeprom.h"
#    include "via.h"
#else
#    include "eeconfig.h"
#endif

extern bool            f_rf_sw_press;
extern bool            f_sleep_show;
extern bool            f_dev_reset_press;
extern bool            f_rgb_test_press;
extern bool            f_bat_hold;
extern bool            f_debounce_press_show;
extern bool            f_debounce_release_show;
extern bool            f_sleep_timeout_show;
extern uint32_t        no_act_time;
extern uint8_t         rf_sw_temp;
extern uint16_t        rf_sw_press_delay;
extern uint16_t        rf_linking_time;
extern DEV_INFO_STRUCT dev_info;
extern uint8_t         rf_blink_cnt;

extern void light_speed_control(uint8_t fast);
extern void light_level_control(uint8_t brighten);
extern void side_color_control(uint8_t dir);
extern void side_mode_control(uint8_t dir);
extern void logo_light_speed_control(uint8_t fast);
extern void logo_light_level_control(uint8_t brighten);
extern void logo_side_color_control(uint8_t dir);
extern void logo_side_mode_control(uint8_t dir);
extern void exit_light_sleep(void);

bool pre_process_record_kb(uint16_t keycode, keyrecord_t *record) {
    no_act_time     = 0;
    rf_linking_time = 0;

    // wakeup check for light sleep/no sleep - fire this immediately to not lose wake keys.
    if (f_wakeup_prepare) {
        f_wakeup_prepare = 0;
        if (keyboard_config.common.sleep_toggle) exit_light_sleep();
    }

    return pre_process_record_user(keycode, record);
}

socd_cleaner_t socd_v = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_h = {{KC_A, KC_D}, SOCD_CLEANER_LAST};

/* qmk process record */
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    no_act_time     = 0;
    rf_linking_time = 0;

    if (!process_record_user(keycode, record)) {
        return false;
    }
    // socd handling
    if (!process_socd_cleaner(keycode, record, &socd_v)) {
        return false;
    }
    if (!process_socd_cleaner(keycode, record, &socd_h)) {
        return false;
    }

    switch (keycode) {
#if (WORK_MODE == THREE_MODE)
        case RF_DFU:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) return false;
                uart_send_cmd(CMD_RF_DFU, 10, 20);
            }
            return false;
#endif
        case LNK_USB:
            if (record->event.pressed) {
                break_all_key();
            } else {
                dev_info.link_mode = LINK_USB;
                uart_send_cmd(CMD_SET_LINK, 10, 10);
            }
            return false;

#if (WORK_MODE == THREE_MODE)
        case LNK_RF:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) {
                    rf_sw_temp    = LINK_RF_24;
                    f_rf_sw_press = 1;
                    break_all_key();
                }
            } else if (f_rf_sw_press) {
                f_rf_sw_press = 0;

                if (rf_sw_press_delay < RF_LONG_PRESS_DELAY) {
                    dev_info.link_mode   = rf_sw_temp;
                    dev_info.rf_channel  = rf_sw_temp;
                    dev_info.ble_channel = rf_sw_temp;
                    uart_send_cmd(CMD_SET_LINK, 10, 20);
                }
            }
            return false;

        case LNK_BLE1:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) {
                    rf_sw_temp    = LINK_BT_1;
                    f_rf_sw_press = 1;
                    break_all_key();
                }
            } else if (f_rf_sw_press) {
                f_rf_sw_press = 0;

                if (rf_sw_press_delay < RF_LONG_PRESS_DELAY) {
                    dev_info.link_mode   = rf_sw_temp;
                    dev_info.rf_channel  = rf_sw_temp;
                    dev_info.ble_channel = rf_sw_temp;
                    uart_send_cmd(CMD_SET_LINK, 10, 20);
                }
            }
            return false;

        case LNK_BLE2:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) {
                    rf_sw_temp    = LINK_BT_2;
                    f_rf_sw_press = 1;
                    break_all_key();
                }
            } else if (f_rf_sw_press) {
                f_rf_sw_press = 0;

                if (rf_sw_press_delay < RF_LONG_PRESS_DELAY) {
                    dev_info.link_mode   = rf_sw_temp;
                    dev_info.rf_channel  = rf_sw_temp;
                    dev_info.ble_channel = rf_sw_temp;
                    uart_send_cmd(CMD_SET_LINK, 10, 20);
                }
            }
            return false;

        case LNK_BLE3:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) {
                    rf_sw_temp    = LINK_BT_3;
                    f_rf_sw_press = 1;
                    break_all_key();
                }
            } else if (f_rf_sw_press) {
                f_rf_sw_press = 0;

                if (rf_sw_press_delay < RF_LONG_PRESS_DELAY) {
                    dev_info.link_mode   = rf_sw_temp;
                    dev_info.rf_channel  = rf_sw_temp;
                    dev_info.ble_channel = rf_sw_temp;
                    uart_send_cmd(CMD_SET_LINK, 10, 20);
                }
            }
            return false;
#endif
        case MAC_TASK:
            if (record->event.pressed) {
                host_consumer_send(0x029F);
            } else {
                host_consumer_send(0);
            }
            return false;

        case MAC_SEARCH:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_SPACE);
                wait_ms(50);
                unregister_code(KC_LGUI);
                unregister_code(KC_SPACE);
            }
            return false;

        case MAC_VOICE:
            if (record->event.pressed) {
                host_consumer_send(0xcf);
            } else {
                host_consumer_send(0);
            }
            return false;

        case MAC_CONSOLE:
            if (record->event.pressed) {
                host_consumer_send(0x02A0);
            } else {
                host_consumer_send(0);
            }
            return false;

        case MAC_DND:
            if (record->event.pressed) {
                host_system_send(0x9b);
            } else {
                host_system_send(0);
            }
            return false;

        case MAC_GLOBE:
            if (record->event.pressed) {
                host_consumer_send(0x029D);
            } else {
                host_consumer_send(0);
            }
            return false;

        case SIDE_VAI:
            if (record->event.pressed) {
                light_level_control(1);
            }
            return false;

        case SIDE_VAD:
            if (record->event.pressed) {
                light_level_control(0);
            }
            return false;

        case SIDE_MOD:
            if (record->event.pressed) {
                side_mode_control(1);
            }
            return false;

        case SIDE_HUI:
            if (record->event.pressed) {
                side_color_control(1);
            }
            return false;

        case SIDE_SPI:
            if (record->event.pressed) {
                light_speed_control(1);
            }
            return false;

        case SIDE_SPD:
            if (record->event.pressed) {
                light_speed_control(0);
            }
            return false;

        case AMBIENT_VAI:
            if (record->event.pressed) {
                logo_light_level_control(1);
            }
            return false;
        case AMBIENT_VAD:
            if (record->event.pressed) {
                logo_light_level_control(0);
            }
            return false;
        case AMBIENT_MOD:
            if (record->event.pressed) {
                logo_side_mode_control(1);
            }
            return false;
        case AMBIENT_HUI:
            if (record->event.pressed) {
                logo_side_color_control(1);
            }
            return false;
        case AMBIENT_SPI:
            if (record->event.pressed) {
                logo_light_speed_control(1);
            }
            return false;
        case AMBIENT_SPD:
            if (record->event.pressed) {
                logo_light_speed_control(0);
            }
            return false;

        case DEV_RESET:
            if (record->event.pressed) {
                f_dev_reset_press = 1;
                break_all_key();
            } else {
                f_dev_reset_press = 0;
            }
            return false;

        case SLEEP_MODE:
            if (record->event.pressed) {
                keyboard_config.common.sleep_toggle = !keyboard_config.common.sleep_toggle;
                f_sleep_show          = 1;
                save_config_to_eeprom();
            }
            return false;

        case BAT_SHOW:
            if (record->event.pressed) {
                f_bat_hold = !f_bat_hold;
            }
            return false;
        case WIN_LOCK:
            if (record->event.pressed) {
                keymap_config.no_gui = !keymap_config.no_gui;
                eeconfig_update_keymap(&keymap_config);
                break_all_key();
            } else
                unregister_code16(keycode);
            break;

        case RGB_TEST:
            f_rgb_test_press = record->event.pressed;
            return false;

        case SHIFT_GRV:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_GRV);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_GRV);
            }
            return false;

        case TOG_USB_SLP:
            if (record->event.pressed) {
                toggle_usb_sleep();
            }
            return false;
        case TOG_CAPS_IND:
            if (record->event.pressed) {
                toggle_caps_indication();
            }

            return false;

        case DEBOUNCE_PRESS_SHOW:
            if (record->event.pressed) {
                f_debounce_press_show = !f_debounce_press_show;
            }
            return false;

        case DEBOUNCE_PRESS_INC:
            if (record->event.pressed) {
                adjust_debounce(1, false);
            }
            return false;

        case DEBOUNCE_PRESS_DEC:
            if (record->event.pressed) {
                adjust_debounce(0, false);
            }
            return false;
        case DEBOUNCE_RELEASE_SHOW:
            if (record->event.pressed) {
                f_debounce_release_show = !f_debounce_release_show;
            }
            return false;

        case DEBOUNCE_RELEASE_INC:
            if (record->event.pressed) {
                adjust_debounce(1, true);
            }
            return false;

        case DEBOUNCE_RELEASE_DEC:
            if (record->event.pressed) {
                adjust_debounce(0, true);
            }
            return false;

        case SLEEP_TIMEOUT_SHOW:
            if (record->event.pressed) {
                f_sleep_timeout_show = !f_sleep_timeout_show;
            }
            return false;

        case SLEEP_TIMEOUT_INC:
            if (record->event.pressed) {
                adjust_sleep_timeout(1);
            }
            return false;

        case SLEEP_TIMEOUT_DEC:
            if (record->event.pressed) {
                adjust_sleep_timeout(0);
            }
            return false;
        case TOG_DEEP_SLEEP:
            if (record->event.pressed) {
                toggle_deep_sleep();
            }
            return false;
        case TOG_BAT_IND_NUM:
            if (record->event.pressed) {
                keyboard_config.custom.battery_indicator_numeric = !keyboard_config.custom.battery_indicator_numeric;
                save_config_to_eeprom();
            }
        case SOCDON: // Turn SOCD Cleaner on.
            if (record->event.pressed) {
                socd_cleaner_enabled = true;
            }
            return false;
        case SOCDOFF: // Turn SOCD Cleaner off.
            if (record->event.pressed) {
                socd_cleaner_enabled = false;
            }
            return false;
        case SOCDTOG: // Toggle SOCD Cleaner.
            if (record->event.pressed) {
                socd_cleaner_enabled = !socd_cleaner_enabled;
            }
            return false;
        case FW_VERSION:
            if (record->event.pressed) {
                SEND_STRING(CFW_VERSION);
            }
            return false;

        default:
            return true;
    }
    return true;
}

/* qmk keyboard post init */
void keyboard_post_init_kb(void) {
    gpio_init();

#if (WORK_MODE == THREE_MODE)
    rf_uart_init();
    wait_ms(500);
    rf_device_init();
#endif
    break_all_key();
    dial_sw_fast_scan();
    load_eeprom_data();
    keyboard_post_init_user();
}

bool rgb_matrix_indicators_kb(void) {
    if (rf_blink_cnt) {
        uint8_t col = 4;
        if (dev_info.link_mode >= LINK_BT_1 && dev_info.link_mode <= LINK_BT_3) {
            col = dev_info.link_mode;
        } else if (dev_info.link_mode == LINK_RF_24) {
            col = 4;
        }
        user_set_rgb_color(get_led_index(1, col), 0, 0, 0x80);
    }

    return true;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (keymap_config.no_gui) {
        // fixed position in top right corner, key position in matrix is (0,16), led index is (16)
        rgb_matrix_set_color(get_led_index(0, 16), 0x00, 0x80, 0x00);
    }

    if (f_debounce_press_show) { // green numbers - press debounce
        rgb_matrix_set_color(two_digit_decimals_led(keyboard_config.common.debounce_press_ms), 0x00, 0x80, 0x00);
        rgb_matrix_set_color(two_digit_ones_led(keyboard_config.common.debounce_press_ms), 0x00, 0x80, 0x00);
    }
    if (f_debounce_release_show) { // red numbers - release deboucne
        rgb_matrix_set_color(two_digit_decimals_led(keyboard_config.common.debounce_release_ms), 0x80, 0x00, 0x00);
        rgb_matrix_set_color(two_digit_ones_led(keyboard_config.common.debounce_release_ms), 0x80, 0x00, 0x00);
    }

    if (f_sleep_timeout_show) { // cyan numbers - sleep timeout
        rgb_matrix_set_color(two_digit_decimals_led(keyboard_config.common.sleep_timeout), 0x00, 0x80, 0x80);
        rgb_matrix_set_color(two_digit_ones_led(keyboard_config.common.sleep_timeout), 0x00, 0x80, 0x80);
    }

    if (keyboard_config.custom.show_socd_indicator && socd_cleaner_enabled) {
        rgb_matrix_set_color(get_led_index(2, 2), RGB_BLUE);
        rgb_matrix_set_color(get_led_index(3, 2), RGB_BLUE);
        rgb_matrix_set_color(get_led_index(3, 1), RGB_BLUE);
        rgb_matrix_set_color(get_led_index(3, 3), RGB_BLUE);
    }

    if (keyboard_config.custom.detect_numlock_state) {
        uint8_t showNumLock = 0;
        if (dev_info.link_mode != LINK_USB) {
            showNumLock = dev_info.rf_led & 0x01;
        } else {
            showNumLock = host_keyboard_led_state().num_lock;
        }

        if (showNumLock) {
            rgb_matrix_set_color(get_led_index(0, 15), 0x00, 0x80, 0x00);
        }
    }

    rgb_matrix_set_color(RGB_MATRIX_LED_COUNT - 1, 0, 0, 0);

    if (keyboard_config.custom.toggle_custom_keys_highlight) {
        uint8_t layer = get_highest_layer(layer_state);
        switch (layer) {
            case 0:
            case 2:
                break;
            default: {
                for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
                    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                        uint8_t index = g_led_config.matrix_co[row][col];

                        if (index >= led_min && index <= led_max && index != NO_LED) {
                            int keycode = keymap_key_to_keycode(layer, (keypos_t){col, row});

                            if (keycode >= AMBIENT_VAI && keycode <= AMBIENT_SPD) {
                                rgb_matrix_set_color(index, RGB_WHITE);
                            } else if (keycode >= SIDE_VAI && keycode <= SIDE_SPD) {
                                rgb_matrix_set_color(index, RGB_YELLOW);
                            } else if (keycode >= DEBOUNCE_PRESS_INC && keycode <= DEBOUNCE_PRESS_SHOW) {
                                rgb_matrix_set_color(index, 0, 255, 0);
                            } else if (keycode >= DEBOUNCE_RELEASE_INC && keycode <= DEBOUNCE_RELEASE_SHOW) {
                                rgb_matrix_set_color(index, 255, 0, 0);
                            } else if (keycode == SLEEP_MODE || keycode == TOG_USB_SLP || keycode == TOG_DEEP_SLEEP || (keycode >= SLEEP_TIMEOUT_INC && keycode <= SLEEP_TIMEOUT_SHOW)) {
                                rgb_matrix_set_color(index, RGB_CYAN);
                            } else if (keycode >= LNK_USB && keycode <= LNK_BLE3) {
                                if (dev_info.link_mode != LINK_USB) {
                                    rgb_matrix_set_color(index, RGB_BLUE);
                                }
                            } else if (keycode > KC_NUM_LOCK && keycode <= KC_KP_DOT) {
                                rgb_matrix_set_color(index, RGB_RED);
                            } else if (keycode >= SOCDON && keycode <= SOCDTOG) {
                                rgb_matrix_set_color(index, RGB_BLUE);
                            } else if (keycode > KC_TRNS) {
                                rgb_matrix_set_color(index, 225, 65, 140);
                            }
                        }
                    }
                }
            }
        }
    }

    if (f_bat_hold && keyboard_config.custom.battery_indicator_numeric) {
        rgb_matrix_set_color(two_digit_decimals_led(dev_info.rf_battery), 0x00, 0x80, 0x80);
        rgb_matrix_set_color(two_digit_ones_led(dev_info.rf_battery), 0x00, 0x80, 0x80);
    }

    return rgb_matrix_indicators_advanced_user(led_min, led_max);
}

/* qmk housekeeping task */
void housekeeping_task_kb(void) {
    timer_pro();

#if (WORK_MODE == THREE_MODE)
    uart_receive_pro();

    uart_send_report_repeat();

    dev_sts_sync();
#endif

    long_press_key();

    dial_sw_scan();

    side_led_show();

    sleep_handle();
}
