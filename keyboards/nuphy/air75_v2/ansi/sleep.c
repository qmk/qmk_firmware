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
#include "hal_usb.h"
#include "usb_main.h"

extern user_config_t   user_config;
extern DEV_INFO_STRUCT dev_info;
extern uint16_t        rf_linking_time;
extern uint16_t        no_act_time;
extern bool            f_goto_sleep;
extern bool            f_wakeup_prepare;

uint8_t uart_send_cmd(uint8_t cmd, uint8_t ack_cnt, uint8_t delayms);

/**
 * @brief  Sleep Handle.
 */
void sleep_handle(void) {
    static uint32_t delay_step_timer = 0;
    static uint8_t  usb_suspend_debounce = 0;
    static uint32_t rf_disconnect_time = 0;

    /* 50ms interval */
    if (timer_elapsed32(delay_step_timer) < 50) return;
    delay_step_timer = timer_read32();

    // sleep process
    if (f_goto_sleep) {
        f_goto_sleep = 0;

        if(user_config.sleep_enable) {
            if (dev_info.rf_state == RF_CONNECT)
                uart_send_cmd(CMD_SET_CONFIG, 5, 5);
            else
                uart_send_cmd(CMD_SLEEP, 5, 5);

            // power off led
            setPinOutput(DC_BOOST_PIN);
            writePinLow(DC_BOOST_PIN);

            setPinInput(DRIVER_LED_CS_PIN);
            setPinInput(DRIVER_SIDE_CS_PIN);
        }

        f_wakeup_prepare = 1;
    }

    // wakeup check
    if (f_wakeup_prepare && (no_act_time < 10)) {
        f_wakeup_prepare = 0;

        writePinHigh(DC_BOOST_PIN);

        setPinOutput(DRIVER_LED_CS_PIN);
        writePinLow(DRIVER_LED_CS_PIN);
        setPinOutput(DRIVER_SIDE_CS_PIN);
        writePinLow(DRIVER_SIDE_CS_PIN);

        uart_send_cmd(CMD_HAND, 0, 1);

        if (dev_info.link_mode == LINK_USB) {
            usb_lld_wakeup_host(&USB_DRIVER);
            restart_usb_driver(&USB_DRIVER);
        }
    }

    // sleep check
    if (f_goto_sleep || f_wakeup_prepare)
        return;
    if (dev_info.link_mode == LINK_USB) {
        if (USB_DRIVER.state == USB_SUSPENDED) {
            usb_suspend_debounce++;
            if (usb_suspend_debounce >= 20) {
                f_goto_sleep = 1;
            }
        } else {
            usb_suspend_debounce = 0;
        }
    } else if (dev_info.rf_state == RF_CONNECT) {
        rf_disconnect_time = 0;
        if (no_act_time >= SLEEP_TIME_DELAY) {
            f_goto_sleep = 1;
        }
    } else if (rf_linking_time >= LINK_TIMEOUT) {
        rf_linking_time = 0;
        f_goto_sleep    = 1;
    } else if (dev_info.rf_state == RF_DISCONNECT) {
        rf_disconnect_time++;
        if (rf_disconnect_time > 5 * 20) {
            rf_disconnect_time = 0;
            f_goto_sleep = 1;
        }
    }
}
