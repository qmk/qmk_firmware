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
#include "ansi.h"
#include "config.h"
#include "eeconfig.h"
#include "color.h"
#include "host.h"
#include "common/config.h"
#include "common/rf_driver.h"
#include "common/links.h"

// Forward declarations for weak functions from common/config.c
void pwr_rgb_led_on(void);
void pwr_rgb_led_off(void);

// These are defined in common/ files
extern DEV_INFO_STRUCT dev_info;
extern bool            f_send_channel;
extern uint8_t         host_mode;
extern uint16_t        rf_link_show_time;
extern host_driver_t  *m_host_driver;

// These are defined in common/keyboard.c and common/timer.c
extern bool     f_bat_hold;
extern bool     f_sys_show;
extern bool     f_sleep_show;
extern bool     f_usb_sleep_show;
extern bool     f_deep_sleep_show;
extern bool     f_dial_sw_init_ok;
extern bool     f_rf_sw_press;
extern bool     f_dev_reset_press;
extern bool     f_rgb_test_press;
extern bool     f_debounce_press_show;
extern bool     f_debounce_release_show;
extern bool     f_sleep_timeout_show;
extern uint8_t  rf_blink_cnt;
extern uint8_t  rf_sw_temp;
extern uint16_t rf_linking_time;
extern uint32_t no_act_time;
extern uint16_t dev_reset_press_delay;
extern uint16_t rf_sw_press_delay;
extern uint16_t rgb_test_press_delay;
extern uint16_t rgb_led_last_act;
extern uint16_t side_led_last_act;

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
    setPinInputHigh(DEVICE_MODE_PIN);
    /* config keyboard OS switch pin */
    setPinInputHigh(OS_MODE_PIN);

    // open power
    setPinOutput(DC_BOOST_PIN);
    writePinHigh(DC_BOOST_PIN);
}
