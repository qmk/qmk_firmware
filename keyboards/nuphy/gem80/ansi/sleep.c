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

#include <stdint.h>
#include <stdbool.h>
#include "ansi.h"
#include "user_kb.h"
#include "hal_usb.h"
#include "usb_main.h"

// sleep control for leds
extern bool side_led_powered_off;
extern bool rgb_led_powered_off;

extern DEV_INFO_STRUCT dev_info;
extern uint16_t        rf_linking_time;
extern uint32_t        no_act_time;
extern bool            f_goto_sleep;

void clear_report_buffer(void);

/**
 * @brief  Light sleep by powering off LEDs.
 * @note This is Nuphy's "open sourced" sleep logic. It's not deep sleep.
 */
void enter_light_sleep(void) {
#if (WORK_MODE == THREE_MODE)
    if (dev_info.rf_state == RF_CONNECT)
        uart_send_cmd(CMD_SET_CONFIG, 5, 5);
    else
        uart_send_cmd(CMD_SLEEP, 5, 5);

    clear_report_buffer();
#endif

    // wired-only & 3-mode versions
    led_pwr_sleep_handle();
}

/**
 * @brief  Power back up LEDs on exiting light sleep.
 * @note This is Nuphy's "open sourced" wake logic. It's not deep sleep.
 */
void exit_light_sleep(void) {
    // NOTE: hack to force enable all leds
    rgb_led_powered_off  = 1;
    side_led_powered_off = 1;

    led_pwr_wake_handle();

#if (WORK_MODE == THREE_MODE)
    uart_send_cmd(CMD_HAND, 0, 1);
#endif
    if (dev_info.link_mode == LINK_USB) {
        usb_lld_wakeup_host(&USB_DRIVER);
        restart_usb_driver(&USB_DRIVER);
    }

#if (WORK_MODE == THREE_MODE)
    // flag for RF wakeup workload.
    dev_info.rf_state = RF_WAKE;
#endif
}

/**
 * @brief  Sleep Handle.
 */
void sleep_handle(void) {
    static uint32_t delay_step_timer     = 0;
    static uint8_t  usb_suspend_debounce = 0;
#if (WORK_MODE == THREE_MODE)
    static uint32_t rf_disconnect_time = 0;
#endif

    /* 50ms interval */
    if (timer_elapsed32(delay_step_timer) < 50) return;
    delay_step_timer = timer_read32();

    // sleep process;
    if (!g_config.sleep_enable) return;
    // get sleep_time_delay from eeprom
    uint32_t sleep_time_delay = get_sleep_timeout();

    if (f_goto_sleep) {
        // reset all counters
        f_goto_sleep    = 0;
        rf_linking_time = 0;
#if (WORK_MODE == THREE_MODE)
        rf_disconnect_time = 0;
#endif

        // light sleep if charging? Charging event might keep waking MCU. To be confirmed...
        // or if it's in USB mode but USB state is suspended
        break_all_key();
        enter_light_sleep();
        f_wakeup_prepare = 1; // only if light sleep.
    }

    // sleep check, won't reach here on deep sleep.
    if (f_goto_sleep || f_wakeup_prepare) return;

    if (dev_info.link_mode == LINK_USB) {
        if (USB_DRIVER.state == USB_SUSPENDED) {
            usb_suspend_debounce++;
            if (usb_suspend_debounce >= 20) {
                f_goto_sleep = 1;
            }
        } else {
            usb_suspend_debounce = 0;
            if (g_config.usb_sleep_toggle && no_act_time >= sleep_time_delay) {
                f_goto_sleep = 1;
            } else {
                f_goto_sleep = 0;
            }
        }
    }
#if (WORK_MODE == THREE_MODE)
    else if (no_act_time >= sleep_time_delay) {
        f_goto_sleep = 1;
    } else if (rf_linking_time >= LINK_TIMEOUT_ALT) {
        rf_linking_time = 0;
        f_goto_sleep    = 1;
    } else if (dev_info.rf_state == RF_DISCONNECT) {
        rf_disconnect_time++;
        if (rf_disconnect_time > 5 * 20) { // 5 seconds
            f_goto_sleep = 1;
        }
    } else if (dev_info.rf_state == RF_CONNECT) {
        rf_disconnect_time = 0;
    }
#endif
}
