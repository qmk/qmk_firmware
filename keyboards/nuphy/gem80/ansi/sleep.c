// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ansi.h"
#include "hal_usb.h"
#include "usb_main.h"
#include "user_kb.h"

extern DEV_INFO_STRUCT dev_info;
extern uint16_t        rf_linking_time;
extern uint16_t        no_act_time;
extern bool            f_goto_sleep;
extern bool            f_wakeup_prepare;

uint8_t uart_send_cmd(uint8_t cmd, uint8_t ack_cnt, uint8_t delayms);

/**
 * @brief  Sleep Handle.
 */
void Sleep_Handle(void) {
    static uint32_t delay_step_timer = 0;
    static uint8_t  usb_suspend_debounce;
    static bool f_usb_sleep = 0;

    /* 50ms interval */
    if (timer_elapsed32(delay_step_timer) < 50) return;
    delay_step_timer = timer_read32();

    if (f_goto_sleep) {
        f_goto_sleep = 0;

        if (dev_info.rf_state == RF_CONNECT)
            uart_send_cmd(CMD_SET_CONFIG, 5, 5);
        else
            uart_send_cmd(CMD_SLEEP, 5, 5);

        setPinOutput(DC_BOOST_PIN);
        writePinLow(DC_BOOST_PIN);

        setPinInput(DRIVER_LED_CS_PIN);
        setPinInput(DRIVER_SIDE_CS_PIN);

        f_wakeup_prepare = 1;
    } else if(f_usb_sleep) {
        setPinInput(DRIVER_LED_CS_PIN);
        setPinInput(DRIVER_SIDE_CS_PIN);
    } else {
        setPinOutput(DRIVER_LED_CS_PIN);
        writePinLow(DRIVER_LED_CS_PIN);
        setPinOutput(DRIVER_SIDE_CS_PIN);
        writePinLow(DRIVER_SIDE_CS_PIN);
    }

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

    if (f_goto_sleep || f_wakeup_prepare) return;

    if (dev_info.link_mode == LINK_USB) {
        if (USB_DRIVER.state == USB_SUSPENDED) {
            usb_suspend_debounce++;
            if (usb_suspend_debounce >= 20) {
                f_goto_sleep = 1;
            }
        } else {
            usb_suspend_debounce = 0;

        if (no_act_time >= SLEEP_TIME_DELAY) {
            f_usb_sleep = 1;
        } else {
            f_usb_sleep = 0;
        }
        }
    } else {
        f_usb_sleep = 0;
        if (dev_info.rf_state == RF_CONNECT) {
            if (no_act_time >= SLEEP_TIME_DELAY) {
                f_goto_sleep = 1;
            }
        } else if (rf_linking_time >= LINK_TIMEOUT) {
            rf_linking_time = 0;
            f_goto_sleep    = 1;
        }
    }


}

