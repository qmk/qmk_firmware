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
#include "config.h"
#include "host.h"
#include "keycodes.h"
#include "rgb_matrix.h"
#include "user_kb.h"
#include "ansi.h"

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

extern void light_speed_contol(uint8_t fast);
extern void light_level_control(uint8_t brighten);
extern void side_color_control(uint8_t dir);
extern void side_mode_a_control(uint8_t dir);
extern void side_mode_b_control(uint8_t dir);
extern void exit_light_sleep(void);

bool pre_process_record_kb(uint16_t keycode, keyrecord_t *record) {
    no_act_time     = 0;
    rf_linking_time = 0;

    // wakeup check for light sleep/no sleep - fire this immediately to not lose wake keys.
    if (f_wakeup_prepare) {
#if CONSOLE_ENABLE
        xprintf("Early wake with keycode |  %u | and record pressed? ( %u )\n", keycode, record->event.pressed);
#endif
        f_wakeup_prepare = 0;
        if (g_config.sleep_toggle) exit_light_sleep();
    }

    return pre_process_record_user(keycode, record);
}

/* qmk process record */
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    no_act_time     = 0;
    rf_linking_time = 0;

    if (!process_record_user(keycode, record)) {
        return false;
    }

#if CONSOLE_ENABLE
    uint8_t row     = record->event.key.row;
    uint8_t col     = record->event.key.col;
    uint8_t led_idx = get_led_index(row, col);
    xprintf("KL: row: %u, column: %u, led_idx: %u, pressed: %u\n", row, col, led_idx, record->event.pressed);
    // rgb_matrix_set_color(led_idx, 0xff,0xff,0xff);
#endif

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

        case SIDE_MOD_A:
            if (record->event.pressed) {
                side_mode_a_control(1);
            }
            return false;
        case SIDE_MOD_B:
            if (record->event.pressed) {
                side_mode_b_control(1);
            }
            return false;

        case SIDE_HUI:
            if (record->event.pressed) {
                side_color_control(1);
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
                g_config.sleep_toggle = !g_config.sleep_toggle;
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
        case TOG_POWER_ON_ANIMATION:
            if (record->event.pressed) {
                toggle_power_on_animation();
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
        rgb_matrix_set_color(get_led_index(0, 15), 0x00, 0x80, 0x00);
    }

    if (f_debounce_press_show) { // green numbers - press debounce
        rgb_matrix_set_color(two_digit_decimals_led(g_config.debounce_press_ms), 0x00, 0x80, 0x00);
        rgb_matrix_set_color(two_digit_ones_led(g_config.debounce_press_ms), 0x00, 0x80, 0x00);
    }
    if (f_debounce_release_show) { // red numbers - release deboucne
        rgb_matrix_set_color(two_digit_decimals_led(g_config.debounce_release_ms), 0x80, 0x00, 0x00);
        rgb_matrix_set_color(two_digit_ones_led(g_config.debounce_release_ms), 0x80, 0x00, 0x00);
    }

    if (f_sleep_timeout_show) { // cyan numbers - sleep timeout
        rgb_matrix_set_color(two_digit_decimals_led(g_config.sleep_timeout), 0x00, 0x80, 0x80);
        rgb_matrix_set_color(two_digit_ones_led(g_config.sleep_timeout), 0x00, 0x80, 0x80);
    }

    uint8_t showNumLock = 0;
    if (dev_info.link_mode != LINK_USB) {
        showNumLock = dev_info.rf_led & 0x01;
    } else {
        showNumLock = host_keyboard_led_state().num_lock;
    }

    if (showNumLock) {
        rgb_matrix_set_color(get_led_index(0, 14), 0x00, 0x80, 0x00);
    }

    rgb_matrix_set_color(RGB_MATRIX_LED_COUNT - 1, 0, 0, 0);

    if (g_config.toggle_custom_keys_highlight) {
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

                            if ((keycode >= SIDE_VAI && keycode <= SIDE_SPD) || keycode == TOG_POWER_ON_ANIMATION) {
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
                            } else if (keycode > KC_TRNS) {
                                rgb_matrix_set_color(index, 225, 65, 140);
                            }
                        }
                    }
                }
            }
        }
    }

    return rgb_matrix_indicators_advanced_user(led_min, led_max);
}

/* qmk housekeeping task */
void housekeeping_task_kb(void) {
    timer_pro();

    uart_receive_pro();

    uart_send_report_repeat();

    dev_sts_sync();

    long_press_key();

    dial_sw_scan();

    side_led_show();

    sleep_handle();
}

kb_config_t g_config;

void init_g_config(void) {
    g_config.sleep_toggle                 = DEFAULT_SLEEP_TOGGLE;
    g_config.usb_sleep_toggle             = DEFAULT_USB_SLEEP_TOGGLE;
    g_config.deep_sleep_toggle            = DEFAULT_DEEP_SLEEP_TOGGLE;
    g_config.sleep_timeout                = DEFAULT_SLEEP_TIMEOUT;
    g_config.power_show                   = DEFAULT_TOGGLE_POWER_ON_ANIMATION;
    g_config.debounce_press_ms            = DEBOUNCE;
    g_config.debounce_release_ms          = DEBOUNCE;
    g_config.caps_indicator_type          = DEFAULT_CAPS_INDICATOR_TYPE;
    g_config.side_mode_a                  = DEFAULT_SIDE_MODE_A;
    g_config.side_mode_b                  = DEFAULT_SIDE_MODE_B;
    g_config.side_brightness              = DEFAULT_SIDE_BRIGHTNESS;
    g_config.side_speed                   = DEFAULT_SIDE_SPEED;
    g_config.side_rgb                     = DEFAULT_SIDE_RGB;
    g_config.side_color                   = DEFAULT_SIDE_COLOR;
    g_config.battery_indicator_brightness = DEFAULT_BATTERY_INDICATOR_BRIGHTNESS;
    g_config.toggle_custom_keys_highlight = DEFAULT_LIGHT_CUSTOM_KEYS;
}

void load_config_from_eeprom(void) {
#ifdef VIA_ENABLE
    eeprom_read_block(&g_config, ((void *)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
#else
    eeconfig_read_kb_datablock(&g_config);
#endif
}

void save_config_to_eeprom(void) {
#ifdef VIA_ENABLE
    eeprom_update_block(&g_config, ((void *)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
#else
    eeconfig_update_kb_datablock(&g_config);
#endif
}

#ifdef VIA_ENABLE
void via_init_kb(void) {
    init_g_config();
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (eeconfig_is_enabled()) {
        load_config_from_eeprom();
    } else {
        save_config_to_eeprom();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void via_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]

    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_usb_sleep_toggle:
            g_config.usb_sleep_toggle = *value_data;
            break;
        case id_deep_sleep_toggle:
            g_config.deep_sleep_toggle = *value_data;
            break;
        case id_debounce_press:
            g_config.debounce_press_ms = *value_data;
            break;
        case id_debounce_release:
            g_config.debounce_release_ms = *value_data;
            break;
        case id_sleep_timeout:
            g_config.sleep_timeout = *value_data + 1;
            break;
        case id_caps_indicator_type:
            g_config.caps_indicator_type = *value_data;
            break;
        case id_sleep_toggle:
            g_config.sleep_toggle = *value_data;
            break;

        case id_side_light_mode_a:
            g_config.side_mode_a = *value_data;
            break;
        case id_side_light_mode_b:
            g_config.side_mode_b = *value_data;
            break;
        case id_side_light_speed:
            g_config.side_speed = *value_data;
            break;
        case id_side_light_color:
            g_config.side_color = *value_data;
            break;
        case id_side_light_brightness:
            g_config.side_brightness = *value_data;
            break;

        case id_power_on_animation:
            g_config.power_show = *value_data;
            break;
        case id_battery_indicator_brightness:
            g_config.battery_indicator_brightness = *value_data;
            break;
        case id_toggle_custom_keys_highlight:
            g_config.toggle_custom_keys_highlight = *value_data;
            break;
    }
#    if CONSOLE_ENABLE
    xprintf("[SET]VALUE_ID: %u DATA: %u\n", *value_id, *value_data);
#    endif
}

void via_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_usb_sleep_toggle:
            *value_data = g_config.usb_sleep_toggle;
            break;
        case id_deep_sleep_toggle:
            *value_data = g_config.deep_sleep_toggle;
            break;
        case id_debounce_press:
            *value_data = g_config.debounce_press_ms;
            break;
        case id_debounce_release:
            *value_data = g_config.debounce_release_ms;
            break;
        case id_sleep_timeout:
            *value_data = g_config.sleep_timeout - 1;
            break;
        case id_caps_indicator_type:
            *value_data = g_config.caps_indicator_type;
            break;
        case id_sleep_toggle:
            *value_data = g_config.sleep_toggle;
            break;

        case id_side_light_mode_a:
            *value_data = g_config.side_mode_a;
            break;
        case id_side_light_mode_b:
            *value_data = g_config.side_mode_b;
            break;
        case id_side_light_speed:
            *value_data = g_config.side_speed;
            break;
        case id_side_light_color:
            *value_data = g_config.side_color;
            break;
        case id_side_light_brightness:
            *value_data = g_config.side_brightness;
            break;

        case id_power_on_animation:
            *value_data = g_config.power_show;
            break;
        case id_battery_indicator_brightness:
            *value_data = g_config.battery_indicator_brightness;
            break;
        case id_toggle_custom_keys_highlight:
            *value_data = g_config.toggle_custom_keys_highlight;
            break;
    }
#    if CONSOLE_ENABLE
    xprintf("[GET]VALUE_ID: %u DATA: %u\n", *value_id, *value_data);
    xprintf("G_CONFIG_SIZE: %u \n", sizeof(g_config));
#    endif
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);

    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id)

        {
            case id_custom_set_value: {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                save_config_to_eeprom();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}
#endif
// led matrix config
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, A_6, B_6, C_6},    {0, A_7, B_7, C_7},    {0, A_8, B_8, C_8},    {0, A_9, B_9, C_9},    {0, A_10, B_10, C_10}, {0, A_11, B_11, C_11}, {0, A_12, B_12, C_12}, {1, A_1, B_1, C_1},    {1, A_2, B_2, C_2},    {1, A_3, B_3, C_3},    {1, A_4, B_4, C_4},    {1, A_5, B_5, C_5},    {1, A_6, B_6, C_6},    {1, A_7, B_7, C_7},    {1, A_9, B_9, C_9},    {1, A_8, B_8, C_8},

    {0, D_1, E_1, F_1},    {0, D_2, E_2, F_2},    {0, D_3, E_3, F_3},    {0, D_4, E_4, F_4},    {0, A_13, B_13, C_13}, {0, A_14, B_14, C_14}, {0, A_15, B_15, C_15}, {0, A_16, B_16, C_16}, {1, A_10, B_10, C_10}, {1, A_11, B_11, C_11}, {1, A_12, B_12, C_12}, {1, A_13, B_13, C_13}, {1, A_14, B_14, C_14}, {1, A_15, B_15, C_15}, {1, A_16, B_16, C_16},

    {0, D_5, E_5, F_5},    {0, D_6, E_6, F_6},    {0, D_7, E_7, F_7},    {0, D_8, E_8, F_8},    {0, D_9, E_9, F_9},    {0, D_10, E_10, F_10}, {0, D_11, E_11, F_11}, {1, D_1, E_1, F_1},    {1, D_2, E_2, F_2},    {1, D_3, E_3, F_3},    {1, D_4, E_4, F_4},    {1, D_5, E_5, F_5},    {1, D_6, E_6, F_6},    {1, D_7, E_7, F_7},    {1, D_8, E_8, F_8},

    {0, G_1, H_1, I_1},    {0, G_2, H_2, I_2},    {0, G_3, H_3, I_3},    {0, G_4, H_4, I_4},    {0, G_5, H_5, I_5},    {0, G_6, H_6, I_6},    {0, G_7, H_7, I_7},    {0, G_8, H_8, I_8},    {1, G_1, H_1, I_1},    {1, G_2, H_2, I_2},    {1, G_3, H_3, I_3},    {1, G_4, H_4, I_4},    {1, G_5, H_5, I_5},    {1, G_6, H_6, I_6},

    {0, J_1, K_1, L_1},    {0, J_2, K_2, L_2},    {0, J_3, K_3, L_3},    {0, J_4, K_4, L_4},    {0, J_5, K_5, L_5},    {0, J_6, K_6, L_6},    {0, J_7, K_7, L_7},    {0, J_8, K_8, L_8},    {1, J_1, K_1, L_1},    {1, J_2, K_2, L_2},    {1, J_3, K_3, L_3},    {1, J_4, K_4, L_4},    {1, J_5, K_5, L_5},    {1, J_8, K_8, L_8},

    {0, J_9, K_9, L_9},    {0, J_10, K_10, L_10}, {0, J_11, K_11, L_11}, {0, J_12, K_12, L_12}, {1, J_6, K_6, L_6},    {1, J_7, K_7, L_7},    {1, J_9, K_9, L_9},    {1, J_10, K_10, L_10}, {1, J_11, K_11, L_11},

    {0, A_1, B_1, C_1},    {0, A_2, B_2, C_2},    {0, A_3, B_3, C_3},    {0, A_4, B_4, C_4},    {0, A_5, B_5, C_5},

    {1, J_12, K_12, L_12}, {1, J_13, K_13, L_13}, {1, J_14, K_14, L_14}, {1, J_15, K_15, L_15}, {1, J_16, K_16, L_16},

    {0, D_12, E_12, F_12}, {0, D_13, E_13, F_13}, {0, D_14, E_14, F_14}, {0, D_15, E_15, F_15}, {0, D_16, E_16, F_16}, {0, G_16, H_16, I_16}, {0, G_15, H_15, I_15}, {0, G_14, H_14, I_14}, {0, G_13, H_13, I_13}, {0, G_12, H_12, I_12}, {0, G_11, H_11, I_11}, {0, G_10, H_10, I_10}, {0, G_9, H_9, I_9},    {0, J_16, K_16, L_16}, {0, J_15, K_15, L_15}, {0, J_14, K_14, L_14}, {0, J_13, K_13, L_13}, {1, D_16, E_16, F_16}, {1, D_15, E_15, F_15}, {1, D_14, E_14, F_14}, {1, D_13, E_13, F_13}, {1, D_12, E_12, F_12}, {1, D_11, E_11, F_11}, {1, D_10, E_10, F_10}, {1, D_9, E_9, F_9}, {1, G_7, H_7, I_7}, {1, G_8, H_8, I_8}, {1, G_9, H_9, I_9}, {1, G_10, H_10, I_10}, {1, G_11, H_11, I_11}, {1, G_12, H_12, I_12}, {1, G_13, H_13, I_13}, {1, G_14, H_14, I_14}, {1, G_15, H_15, I_15}, {1, G_16, H_16, I_16},
};
