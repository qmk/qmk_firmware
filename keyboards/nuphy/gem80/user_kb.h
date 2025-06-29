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

#pragma once

#include "quantum/quantum.h"

typedef enum { DEBOUNCE_PRESS = 0, DEBOUNCE_RELEASE } DEBOUNCE_EVENT;

extern bool f_wakeup_prepare;
extern bool f_sleep_show;
extern bool f_usb_sleep_show;
extern bool f_deep_sleep_show;
extern bool f_dial_sw_init_ok;

void    side_speed_control(uint8_t dir);
void    side_light_control(uint8_t dir);
void    side_color_control(uint8_t dir);
void    side_mode_control(uint8_t dir);
void    side_led_show(void);
void    sleep_handle(void);
void    update_bat_pct_rgb(void);
void    rgb_test_show(void);
void    gpio_init(void);
void    long_press_key(void);
void    break_all_key(void);
void    switch_dev_link(uint8_t mode);
void    dial_sw_scan(void);
void    dial_sw_fast_scan(void);
void    timer_pro(void);
void    load_eeprom_data(void);
void    kb_config_reset(void);
void    user_set_rgb_color(int index, uint8_t red, uint8_t green, uint8_t blue);
uint8_t get_led_index(uint8_t row, uint8_t col);

void sleep_handle(void);
void led_power_handle(void);
void toggle_caps_indication(void);
void toggle_usb_sleep(void);

uint8_t  two_digit_decimals_led(uint8_t value);
uint8_t  two_digit_ones_led(uint8_t value);
void     adjust_debounce(uint8_t dir, DEBOUNCE_EVENT debounce_event);
uint32_t get_sleep_timeout(void);
void     adjust_sleep_timeout(uint8_t dir);

// led power control for sleep
void pwr_rgb_led_off(void);
void pwr_rgb_led_on(void);
void pwr_side_led_off(void);
void pwr_side_led_on(void);
void led_pwr_sleep_handle(void);
void led_pwr_wake_handle(void);
void toggle_deep_sleep(void);
