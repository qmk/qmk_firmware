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
#include <stdbool.h>
#include <stdint.h>
#include "gem80-common.h"
#include "config.h"
#include "eeconfig.h"
#include "color.h"
#include "host.h"
#include "common/rf_driver.h"
#include "common/links.h"

DEV_INFO_STRUCT dev_info = {
    .rf_battery = 100,
    .link_mode  = LINK_USB,
    .rf_state   = RF_IDLE,
};
bool f_bat_hold              = 0;
bool f_sys_show              = 0;
bool f_sleep_show            = 0;
bool f_usb_sleep_show        = 0;
bool f_deep_sleep_show       = 0;
bool f_send_channel          = 0;
bool f_dial_sw_init_ok       = 0;
bool f_rf_sw_press           = 0;
bool f_dev_reset_press       = 0;
bool f_rgb_test_press        = 0;
bool f_debounce_press_show   = 0;
bool f_debounce_release_show = 0;
bool f_sleep_timeout_show    = 0;

uint8_t        rf_blink_cnt          = 0;
uint8_t        rf_sw_temp            = 0;
uint8_t        host_mode             = 0;
uint16_t       rf_linking_time       = 0;
uint16_t       rf_link_show_time     = 0;
uint32_t       no_act_time           = 0;
uint16_t       dev_reset_press_delay = 0;
uint16_t       rf_sw_press_delay     = 0;
uint16_t       rgb_test_press_delay  = 0;
uint16_t       rgb_led_last_act      = 0;
uint16_t       side_led_last_act     = 0;
host_driver_t *m_host_driver         = 0;
RGB            bat_pct_rgb           = {.r = 0x80, .g = 0x80, .b = 0x00};

extern bool               f_rf_new_adv_ok;
extern report_keyboard_t *keyboard_report;
extern report_nkro_t     *nkro_report;
extern host_driver_t      rf_host_driver;
extern uint8_t            logo_mode;
extern uint8_t            logo_light;
extern uint8_t            logo_speed;
extern uint8_t            logo_rgb;
extern uint8_t            logo_color;

/**
 * @brief  gpio initial.
 */
void gpio_init(void) {
    /* power on all LEDs */
    pwr_rgb_led_on();
    pwr_side_led_on();

    /* set side led pin output low */
    setPinOutput(DRIVER_SIDE_PIN);
    writePinLow(DRIVER_SIDE_PIN);

#if (WORK_MODE == THREE_MODE)
    /* config RF module pin */
    setPinOutput(NRF_WAKEUP_PIN);
    writePinHigh(NRF_WAKEUP_PIN);

    setPinInputHigh(NRF_TEST_PIN);

    /* reset RF module */
    setPinOutput(NRF_RESET_PIN);
    writePinLow(NRF_RESET_PIN);
    wait_ms(50);
    writePinHigh(NRF_RESET_PIN);

    /* connection mode switch pin */
    setPinInputHigh(DEV_MODE_PIN);
#endif
    /* config keyboard OS switch pin */
    setPinInputHigh(SYS_MODE_PIN);

    // open power
    setPinOutput(DC_BOOST_PIN);
    writePinHigh(DC_BOOST_PIN);

    setPinOutput(DRIVER_LED_CS_PIN);
    writePinLow(DRIVER_LED_CS_PIN);

    setPinOutput(DRIVER_SIDE_CS_PIN);
    writePinLow(DRIVER_SIDE_CS_PIN);
}

/**
 * @brief  long press key process.
 */
void long_press_key(void) {
    static uint32_t long_press_timer = 0;

    if (timer_elapsed32(long_press_timer) < 100) return;
    long_press_timer = timer_read32();

    // Open a new RF device
    if (f_rf_sw_press) {
#if (WORK_MODE == THREE_MODE)
        rf_sw_press_delay++;
        if (rf_sw_press_delay >= RF_LONG_PRESS_DELAY) {
            f_rf_sw_press = 0;

            dev_info.link_mode   = rf_sw_temp;
            dev_info.rf_channel  = rf_sw_temp;
            dev_info.ble_channel = rf_sw_temp;

            uint8_t timeout = 5;
            while (timeout--) {
                uart_send_cmd(CMD_NEW_ADV, 0, 1);
                wait_ms(20);
                uart_receive_pro();
                if (f_rf_new_adv_ok) break;
            }
        }
#endif
    } else {
        rf_sw_press_delay = 0;
    }

    // The device is restored to factory Settings
    if (f_dev_reset_press) {
        dev_reset_press_delay++;
        if (dev_reset_press_delay >= DEV_RESET_PRESS_DELAY) {
            f_dev_reset_press = 0;

            if (dev_info.link_mode != LINK_USB) {
                if (dev_info.link_mode != LINK_RF_24) {
                    dev_info.link_mode   = LINK_BT_1;
                    dev_info.ble_channel = LINK_BT_1;
                    dev_info.rf_channel  = LINK_BT_1;
                }
            } else {
                dev_info.ble_channel = LINK_BT_1;
                dev_info.rf_channel  = LINK_BT_1;
            }

            uart_send_cmd(CMD_SET_LINK, 10, 10);
            wait_ms(500);
            uart_send_cmd(CMD_CLR_DEVICE, 10, 10);

            void device_reset_show(void);
            void device_reset_init(void);

            eeconfig_init();
            device_reset_show();
            device_reset_init();

            if (dev_info.sys_sw_state == SYS_SW_MAC) {
                default_layer_set(1 << 0);
                keymap_config.nkro = 0;
            } else {
                default_layer_set(1 << 2);
                keymap_config.nkro = 1;
            }
        }
    } else {
        dev_reset_press_delay = 0;
    }

    // Enter the RGB test mode
    if (f_rgb_test_press) {
        rgb_test_press_delay++;
        if (rgb_test_press_delay >= RGB_TEST_PRESS_DELAY) {
            f_rgb_test_press = 0;
            rgb_test_show();
        }
    } else {
        rgb_test_press_delay = 0;
    }
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

/**
 * @brief  switch device link mode.
 * @param mode : link mode
 */
void switch_dev_link(uint8_t mode) {
    if (mode > LINK_USB) return;

    break_all_key();

    dev_info.link_mode = mode;

    dev_info.rf_state = RF_IDLE;
    f_send_channel    = 1;

    if (mode == LINK_USB) {
        host_mode = HOST_USB_TYPE;
        host_set_driver(m_host_driver);
        rf_link_show_time = 0;
    } else {
        host_mode = HOST_RF_TYPE;
        host_set_driver(&rf_host_driver);
    }
}

/**
 * @brief  scan dial switch.
 */
void dial_sw_scan(void) {
    uint8_t         dial_scan       = 0;
    static uint8_t  dial_save       = 0xf0;
    static uint8_t  debounce        = 0;
    static uint32_t dial_scan_timer = 0;
    static bool     f_first         = true;

    if (!f_first) {
        if (timer_elapsed32(dial_scan_timer) < 20) return;
    }
    dial_scan_timer = timer_read32();

#if (WORK_MODE == THREE_MODE)
    setPinInputHigh(DEV_MODE_PIN);
#endif
    setPinInputHigh(SYS_MODE_PIN);
#if (WORK_MODE == THREE_MODE)
    if (readPin(DEV_MODE_PIN)) dial_scan |= 0X01;
#endif
    if (readPin(SYS_MODE_PIN)) dial_scan |= 0X02;

    if (dial_save != dial_scan) {
        break_all_key();

        no_act_time       = 0;
        rf_linking_time   = 0;
        dial_save         = dial_scan;
        debounce          = 25;
        f_dial_sw_init_ok = 0;
        return;
    } else if (debounce) {
        debounce--;
        return;
    }

#if (WORK_MODE == THREE_MODE)
    if (dial_scan & 0x01) {
        if (dev_info.link_mode != LINK_USB) {
            switch_dev_link(LINK_USB);
        }
    } else {
        if (dev_info.link_mode != dev_info.rf_channel) {
            switch_dev_link(dev_info.rf_channel);
        }
    }
#endif

    if (dial_scan & 0x02) {
        if (dev_info.sys_sw_state != SYS_SW_MAC) {
            f_sys_show = 1;
            default_layer_set(1 << 0);
            dev_info.sys_sw_state = SYS_SW_MAC;
            keymap_config.nkro    = 0;
            break_all_key();
        }
    } else {
        if (dev_info.sys_sw_state != SYS_SW_WIN) {
            f_sys_show = 1;
            default_layer_set(1 << 2);
            dev_info.sys_sw_state = SYS_SW_WIN;
            keymap_config.nkro    = 1;
            break_all_key();
        }
    }

    if (f_dial_sw_init_ok == 0) {
        f_dial_sw_init_ok = 1;
        f_first           = false;

#if (WORK_MODE == THREE_MODE)
        if (dev_info.link_mode != LINK_USB) {
            host_set_driver(&rf_host_driver);
        }
#endif
    }
}

/**
 * @brief  power on scan dial switch.
 */
void dial_sw_fast_scan(void) {
    uint8_t dial_scan_dev  = 0;
    uint8_t dial_scan_sys  = 0;
    uint8_t dial_check_dev = 0;
    uint8_t dial_check_sys = 0;
    uint8_t debounce       = 0;
#if (WORK_MODE == THREE_MODE)
    setPinInputHigh(DEV_MODE_PIN);
#endif
    setPinInputHigh(SYS_MODE_PIN);

    // Debounce to get a stable state
    for (debounce = 0; debounce < 10; debounce++) {
        dial_scan_dev = 0;
        dial_scan_sys = 0;
#if (WORK_MODE == THREE_MODE)
        if (readPin(DEV_MODE_PIN))
            dial_scan_dev = 0x01;
        else
            dial_scan_dev = 0;
#endif
        if (readPin(SYS_MODE_PIN))
            dial_scan_sys = 0x01;
        else
            dial_scan_sys = 0;
        if ((dial_scan_dev != dial_check_dev) || (dial_scan_sys != dial_check_sys)) {
            dial_check_dev = dial_scan_dev;
            dial_check_sys = dial_scan_sys;
            debounce       = 0;
        }
        wait_ms(1);
    }

#if (WORK_MODE == THREE_MODE)
    // RF link mode
    if (dial_scan_dev) {
        if (dev_info.link_mode != LINK_USB) {
            switch_dev_link(LINK_USB);
        }
    } else {
        if (dev_info.link_mode != dev_info.rf_channel) {
            switch_dev_link(dev_info.rf_channel);
        }
    }
#endif
    // Win or Mac
    if (dial_scan_sys) {
        if (dev_info.sys_sw_state != SYS_SW_MAC) {
            default_layer_set(1 << 0);
            dev_info.sys_sw_state = SYS_SW_MAC;
            keymap_config.nkro    = 0;
            break_all_key();
        }
    } else {
        if (dev_info.sys_sw_state != SYS_SW_WIN) {
            // f_sys_show = 1;
            default_layer_set(1 << 2);
            dev_info.sys_sw_state = SYS_SW_WIN;
            keymap_config.nkro    = 1;
            break_all_key();
        }
    }
}

/**
 * @brief  timer process.
 */
void timer_pro(void) {
    static uint32_t interval_timer = 0;
    static bool     f_first        = true;

    if (f_first) {
        f_first        = false;
        interval_timer = timer_read32();
        m_host_driver  = host_get_driver();
    }

    // step 10ms
    if (timer_elapsed32(interval_timer) < TIMER_STEP) return;
    interval_timer = timer_read32();

    if (rf_link_show_time < RF_LINK_SHOW_TIME) rf_link_show_time++;

    if (no_act_time < 0xffffffff) no_act_time++;
#if (WORK_MODE == THREE_MODE)
    if (rf_linking_time < 0xffff) rf_linking_time++;
#endif
    if (rgb_led_last_act < 0xffff) rgb_led_last_act++;

    if (side_led_last_act < 0xffff) side_led_last_act++;
}

/**
 * @brief User config to default setting.
 */
void kb_config_reset(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
    rgb_matrix_set_speed(255 - RGB_MATRIX_SPD_STEP * 2);
    rgb_matrix_sethsv(RGB_DEFAULT_COLOR, 255, RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP * 2);

    init_g_config();
    // mark config as initiated
    g_config.been_initiated = 0x45;

    save_config_to_eeprom();
}

void load_eeprom_data(void) {
    load_config_from_eeprom();

    if (g_config.been_initiated != 0x45) {
        kb_config_reset();
        return;
    }
}
/**
 * @brief toggle usb sleep on/off
 */
void toggle_usb_sleep(void) {
    f_usb_sleep_show          = 1;
    g_config.usb_sleep_toggle = !g_config.usb_sleep_toggle;
    save_config_to_eeprom();
}

/**
 * @brief Toggle caps indication between side led / under key / off
 */
void toggle_caps_indication(void) {
    if (g_config.caps_indicator_type == CAPS_INDICATOR_OFF) {
        g_config.caps_indicator_type = CAPS_INDICATOR_SIDE; // set to initial state, when last state reached
    } else {
        g_config.caps_indicator_type += 1;
    }

    save_config_to_eeprom();
}

/**
 * @brief Updates RGB value for current bat percentage.
 */
void update_bat_pct_rgb(void) {
    uint8_t bat_pct = dev_info.rf_battery;

    if (bat_pct > 100) {
        bat_pct = 100;
    }
    // 120 hue is green, 0 is red on a 360 degree wheel but QMK is a uint8_t
    // so it needs to convert to relative to 255 - so green is actually 85.
    uint8_t h = 85;
    if (bat_pct <= 20) {
        h = 0; // red
    } else if (bat_pct <= 40) {
        h = 21; // orange
    } else if (bat_pct <= 80) {
        h = 43; // yellow
    }

    HSV hsv = {
        .h = h,
        .s = 255,
        .v = 128, // 50% max brightness
    };

    bat_pct_rgb = hsv_to_rgb_nocie(hsv); // this results in same calculation as color pickers.
}

/**
 * @brief Wrapper for rgb_matrix_set_color for sleep.c logic usage.
 */
void user_set_rgb_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (red || green || blue) {
        rgb_led_last_act = 0;
        pwr_rgb_led_on(); // turn on LEDs
    }
    rgb_matrix_set_color(index, red, green, blue);
}

/**
 * @brief Handle LED power
 * @note Turn off LEDs if not used to save some power. This is ported
 *       from older Nuphy leaks.
 */
void led_power_handle(void) {
    static uint32_t interval = 0;

    if (timer_elapsed32(interval) < 500) // only check once in a while, less flickering for unhandled cases
        return;

    interval = timer_read32();

    if (rgb_led_last_act > 100) { // 10ms intervals
        if (rgb_matrix_is_enabled() && rgb_matrix_get_val() != 0) {
            pwr_rgb_led_on();
        } else { // brightness is 0 or RGB off.
            pwr_rgb_led_off();
        }
    }

    if (side_led_last_act > 100) { // 10ms intervals
        if (g_config.side_brightness == 0) {
            pwr_side_led_off();
        } else {
            pwr_side_led_on();
        }
    }
}

uint8_t get_led_index(uint8_t row, uint8_t col) {
    return g_led_config.matrix_co[row][col];
}

/**
 * @brief get LED if for first digit from double digit number. Esc = 0
 */
uint8_t two_digit_decimals_led(uint8_t value) {
    if (value > 99) {
        return get_led_index(0, 0);
    }

    uint8_t dec = value / 10;

    uint8_t dec_led_idx = get_led_index(0, dec);

    return dec_led_idx;
}

/**
 * @brief get LED if for second digit from double digit number 0 = 0
 */
uint8_t two_digit_ones_led(uint8_t value) {
    if (value > 99) {
        return get_led_index(0, 0);
    }

    uint8_t ones = value % 10;
    if (ones == 0) {
        ones = 10;
    }
    uint8_t ones_led_idx = get_led_index(1, ones);

    return ones_led_idx;
}

void adjust_debounce(uint8_t dir, DEBOUNCE_EVENT debounce_event) {
#if DEBOUNCE > 0
    if (dir) {
        if (debounce_event == DEBOUNCE_PRESS && g_config.debounce_press_ms < 99) {
            g_config.debounce_press_ms += DEBOUNCE_STEP;
        } else if (debounce_event == DEBOUNCE_RELEASE && g_config.debounce_release_ms < 99) {
            g_config.debounce_release_ms += DEBOUNCE_STEP;
        }
    } else if (!dir) {
        if (debounce_event == DEBOUNCE_PRESS && g_config.debounce_press_ms > 0) {
            g_config.debounce_press_ms -= DEBOUNCE_STEP;
        } else if (debounce_event == DEBOUNCE_RELEASE && g_config.debounce_release_ms > 0) {
            g_config.debounce_release_ms -= DEBOUNCE_STEP;
        }
    }
    save_config_to_eeprom();
#endif
}

void adjust_sleep_timeout(uint8_t dir) {
    if (g_config.sleep_toggle) {
        if (g_config.sleep_timeout > 1 && !dir) {
            g_config.sleep_timeout -= SLEEP_TIMEOUT_STEP;
        } else if (g_config.sleep_timeout < 60 && dir) {
            g_config.sleep_timeout += SLEEP_TIMEOUT_STEP;
        }
        save_config_to_eeprom();
    }
}

uint32_t get_sleep_timeout(void) {
    if (!g_config.sleep_toggle) return 0;
    return g_config.sleep_timeout * 60 * 1000 / TIMER_STEP;
}

void toggle_deep_sleep(void) {
    f_deep_sleep_show          = 1;
    g_config.deep_sleep_toggle = !g_config.deep_sleep_toggle;
    save_config_to_eeprom();
}
