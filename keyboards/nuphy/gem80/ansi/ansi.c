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

#include "user_kb.h"
#include "ansi.h"
#include "usb_main.h"

extern bool            f_rf_sw_press;
extern bool            f_sleep_show;
extern bool            f_dev_reset_press;
extern bool            f_bat_num_show;
extern bool            f_rgb_test_press;
extern bool            f_bat_hold;
extern uint16_t        no_act_time;
extern uint8_t         rf_sw_temp;
extern uint16_t        rf_sw_press_delay;
extern uint16_t        rf_linking_time;
extern uint16_t        sleep_time_delay;
extern user_config_t   user_config;
extern DEV_INFO_STRUCT dev_info;
extern uint8_t         rf_blink_cnt;

extern void light_speed_contol(uint8_t fast);
extern void light_level_control(uint8_t brighten);
extern void side_colour_control(uint8_t dir);
extern void side_mode_control(uint8_t dir);
extern void logo_light_speed_contol(uint8_t fast);
extern void logo_light_level_control(uint8_t brighten);
extern void logo_side_colour_control(uint8_t dir);
extern void logo_side_mode_control(uint8_t dir);
extern void toggle_usb_sleep(void);

/* qmk process record */
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    no_act_time     = 0;
    rf_linking_time = 0;

    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case RF_DFU:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) return false;
                uart_send_cmd(CMD_RF_DFU, 10, 20);
            }
            return false;

        case LNK_USB:
            if (record->event.pressed) {
                break_all_key();
            } else {
                dev_info.link_mode = LINK_USB;
                uart_send_cmd(CMD_SET_LINK, 10, 10);
            }
            return false;

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
                side_colour_control(1);
            }
            return false;

        case SIDE_SPI:
            if (record->event.pressed) {
                light_speed_contol(1);
            }
            return false;

        case SIDE_SPD:
            if (record->event.pressed) {
                light_speed_contol(0);
            }
            return false;

        case LOGO_VAI:
            if (record->event.pressed) {
                logo_light_level_control(1);
            }
            return false;
        case LOGO_VAD:
            if (record->event.pressed) {
                logo_light_level_control(0);
            }
            return false;
        case LOGO_MOD:
            if (record->event.pressed) {
                logo_side_mode_control(1);
            }
            return false;
        case LOGO_HUI:
            if (record->event.pressed) {
                logo_side_colour_control(1);
            }
            return false;
        case LOGO_SPI:
            if (record->event.pressed) {
                logo_light_speed_contol(1);
            }
            return false;
        case LOGO_SPD:
            if (record->event.pressed) {
                logo_light_speed_contol(0);
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
                user_config.sleep_enable = !user_config.sleep_enable;
                f_sleep_show             = 1;
                eeconfig_update_kb_datablock(&user_config);
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
                eeconfig_update_keymap(keymap_config.raw);
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
            if (record -> event.pressed) {
                toggle_usb_sleep();
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
    rf_uart_init();
    wait_ms(500);
    rf_device_init();

    break_all_key();
    dial_sw_fast_scan();
    load_eeprom_data();
    keyboard_post_init_user();
}

bool rgb_matrix_indicators_user(void) {
    if (rf_blink_cnt && dev_info.link_mode >= LINK_BT_1 && dev_info.link_mode <= LINK_BT_3) {
        user_set_rgb_color(33 - dev_info.link_mode, 0, 0, 0x80);
    }

    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (keymap_config.no_gui) {
        rgb_matrix_set_color(16, 0x00, 0x80, 0x00);
    }

    rgb_matrix_set_color(RGB_MATRIX_LED_COUNT - 1, 0, 0, 0);
    return true;
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
