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
#include "hal_usb.h"
#include "usb_main.h"
#include "mcu_pwr.h"

extern user_config_t   user_config;
extern DEV_INFO_STRUCT dev_info;
extern uint16_t        rf_linking_time;
extern uint16_t        rf_link_timeout;
extern uint16_t        no_act_time;
extern bool            f_goto_sleep;
extern bool            f_wakeup_prepare;
extern uint16_t        sleep_time_delay;

void set_side_rgb(uint8_t r, uint8_t g, uint8_t b);
void set_logo_rgb(uint8_t r, uint8_t g, uint8_t b);
void side_rgb_refresh(void);

void deep_sleep_handle(void) {
    break_all_key(); // reset keys before sleeping for new QMK lifecycle to handle on wake.

    // Visual cue for deep sleep on side LED.
    pwr_side_led_on();
    wait_ms(50); // give some time to ensure LED powers on.
    set_side_rgb(0x99, 0x00, 0x00);
    set_logo_rgb(0x99, 0x00, 0x00);
    side_rgb_refresh();
    wait_ms(500);

    // Sync again before sleeping. Without this, the wake keystroke is more likely to be lost.
    dev_sts_sync();

    enter_deep_sleep(); // puts the board in WFI mode and pauses the MCU
    exit_deep_sleep();  // This gets called when there is an interrupt (wake) event.

    // Change any LED's state so the LED driver flushes after turning on for solid colours.
    // Without doing this, the WS2812 driver wouldn't flush as the previous state is the same as current.
    rgb_matrix_set_color_all(0, 0, 0);
    side_rgb_refresh();
    no_act_time = 0; // required to not cause an immediate sleep on first wake
}

/**
 * @brief  Sleep Handle.
 */
void sleep_handle(void) {
    static uint32_t delay_step_timer     = 0;
    static uint8_t  usb_suspend_debounce = 0;
    static uint32_t rf_disconnect_time   = 0;

    /* 50ms interval */
    if (timer_elapsed32(delay_step_timer) < 50) return;
    delay_step_timer = timer_read32();

    // sleep process;
    if (f_goto_sleep) {
        // reset all counters
        f_goto_sleep       = 0;
        rf_disconnect_time = 0;
        rf_linking_time    = 0;

        if (user_config.sleep_enable) {
            bool deep_sleep = 1;
            // light sleep if charging? Charging event might keep waking MCU. To be confirmed...
            if (dev_info.rf_charge & 0x01) {
                deep_sleep = 0;
            }
            // or if it's in USB mode but USB state is suspended
            // TODO: How to detect if USB is unplugged? I only use RF so not a big deal I guess...
            else if (dev_info.link_mode == LINK_USB && USB_DRIVER.state == USB_SUSPENDED) {
                deep_sleep = 0;
            }

            if (deep_sleep) {
                deep_sleep_handle();
                return; // don't need to do anything else
            } else {
                enter_light_sleep();
            }
        }
        f_wakeup_prepare = 1; // only if light sleep.
    }

    // wakeup check
    // we only arrive here on light sleep.
    if (f_wakeup_prepare) {
        if (no_act_time < 10) { // activity wake up
            f_wakeup_prepare = 0;
            if (user_config.sleep_enable) exit_light_sleep();
        }
        // No longer charging? Go deep sleep.
        // TODO: don't really know true charge bit logic. I'm just guessing here.
        else if (user_config.sleep_enable && (dev_info.rf_charge & 0x01) == 0) {
            f_wakeup_prepare = 0;
            deep_sleep_handle();
            return;
        }
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
        }
    } else if (no_act_time >= sleep_time_delay) {
        f_goto_sleep = 1;
    } else if (rf_linking_time >= user_config.rf_link_timeout) {
        f_goto_sleep = 1;
    } else if (dev_info.rf_state == RF_DISCONNECT) {
        rf_disconnect_time++;
        if (rf_disconnect_time > 5 * 20) { // 5 seconds
            f_goto_sleep = 1;
        }
    } else if (dev_info.rf_state == RF_CONNECT) {
        rf_disconnect_time = 0;
    }
}

