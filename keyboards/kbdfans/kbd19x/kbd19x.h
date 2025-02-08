/*
Copyright 2018 Jeff Shufelt <jshuf@puppyfish.com> @jshuf

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

#include "quantum.h"
#include "led.h"

inline void kbd19x_caps_led_on(void)    { gpio_write_pin_high(LED_CAPS_LOCK_PIN); }
inline void kbd19x_caps_led_off(void)   { gpio_write_pin_low(LED_CAPS_LOCK_PIN); }

inline void kbd19x_sclk_led_on(void)    { gpio_write_pin_high(LED_SCROLL_LOCK_PIN); }
inline void kbd19x_sclk_led_off(void)   { gpio_write_pin_low(LED_SCROLL_LOCK_PIN); }

inline void kbd19x_nmlk_led_on(void)    { gpio_write_pin_high(LED_NUM_LOCK_PIN); }
inline void kbd19x_nmlk_led_off(void)   { gpio_write_pin_low(LED_NUM_LOCK_PIN); }
