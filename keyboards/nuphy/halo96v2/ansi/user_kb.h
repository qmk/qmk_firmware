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
#include "common/config.h"
#include "common/debounce.h"

extern bool f_wakeup_prepare;
extern bool f_sleep_show;
extern bool f_usb_sleep_show;
extern bool f_deep_sleep_show;
extern bool f_dial_sw_init_ok;

void side_speed_control(uint8_t dir);
void side_light_control(uint8_t dir);
void side_color_control(uint8_t dir);
void side_mode_control(uint8_t dir);
void side_led_show(void);
void sleep_handle(void);
void update_bat_pct_rgb(void);
void rgb_test_show(void);
void gpio_init(void);
void break_all_key(void);
void switch_dev_link(uint8_t mode);
void dial_sw_fast_scan(void);
void user_set_rgb_color(int index, uint8_t red, uint8_t green, uint8_t blue);

// Wrappers for common functions
void light_speed_control(uint8_t fast);
void light_level_control(uint8_t brighten);
