#include "action.h"
#include "config.h"
#include "eeconfig.h"
#include "host.h"
#include "keys.h"
#include "debounce.h"
#include "quantum.h"
#include "wait.h"
#include "features/socd_cleaner.h"
#include "side.h"
#include "ambient.h"
#include "rf_driver.h"

extern uint8_t         f_dev_reset_press;
extern uint8_t         f_sleep_show;
extern uint8_t         f_bat_hold;
extern uint8_t         f_rgb_test_press;
extern uint8_t         f_debounce_press_show;
extern uint8_t         f_debounce_release_show;
extern uint8_t         f_sleep_timeout_show;
extern keymap_config_t keymap_config;
extern DEV_INFO_STRUCT dev_info;
extern bool            f_rf_sw_press;
extern uint8_t         rf_sw_temp;
extern uint16_t        rf_sw_press_delay;
extern uint16_t        rf_linking_time;
extern uint32_t        no_act_time;
extern bool            f_wakeup_prepare;

extern void exit_light_sleep(void);

__attribute__((weak)) socd_cleaner_t socd_v = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
__attribute__((weak)) socd_cleaner_t socd_h = {{KC_A, KC_D}, SOCD_CLEANER_LAST};

__attribute__((weak)) bool pre_process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // wakeup check for light sleep/no sleep - fire this immediately to not lose wake keys.
    if (f_wakeup_prepare) {
        f_wakeup_prepare = 0;
        if (keyboard_config.common.sleep_toggle) exit_light_sleep();
    }

    return pre_process_record_user(keycode, record);
}

bool process_record_nuphy(uint16_t keycode, keyrecord_t *record) {
    no_act_time     = 0;
    rf_linking_time = 0;

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
                side_brightness_control(1);
            }
            return false;

        case SIDE_VAD:
            if (record->event.pressed) {
                side_brightness_control(0);
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
                side_speed_control(1);
            }
            return false;

        case SIDE_SPD:
            if (record->event.pressed) {
                side_speed_control(0);
            }
            return false;

        case AMBIENT_VAI:
            if (record->event.pressed) {
                ambient_brightness_control(1);
            }
            return false;
        case AMBIENT_VAD:
            if (record->event.pressed) {
                ambient_brightness_control(0);
            }
            return false;
        case AMBIENT_MOD:
            if (record->event.pressed) {
                ambient_mode_control(1);
            }
            return false;
        case AMBIENT_HUI:
            if (record->event.pressed) {
                ambient_color_control(1);
            }
            return false;
        case AMBIENT_SPI:
            if (record->event.pressed) {
                ambient_speed_control(1);
            }
            return false;
        case AMBIENT_SPD:
            if (record->event.pressed) {
                ambient_speed_control(0);
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
                f_sleep_show                        = 1;
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
            return false;
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
        case TOG_POWER_ON_ANIMATION:
            if (record->event.pressed) {
                keyboard_config.common.power_on_animation = !keyboard_config.common.power_on_animation;
                save_config_to_eeprom();
            }
            return false;
    }

    return true;
}

/**
 * @brief  Release all keys, clear keyboard report.
 */
void break_all_key(void) {
    bool nkro_temp = keymap_config.nkro;

    clear_weak_mods();
    clear_mods();
    clear_keyboard();

    // break nkro key
    keymap_config.nkro = 1;
    memset(nkro_report, 0, sizeof(report_nkro_t));
    host_nkro_send(nkro_report);
    wait_ms(10);

    // break byte key
    keymap_config.nkro = 0;
    memset(keyboard_report, 0, sizeof(report_keyboard_t));
    host_keyboard_send(keyboard_report);
    wait_ms(10);

    keymap_config.nkro = nkro_temp;

    void clear_report_buffer(void);
    clear_report_buffer();
}
