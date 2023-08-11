/* Copyright 2017 MechMerlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"
#include "led.h"

// Functions for setting LEDs on toggle keys
inline void caps_led_on(void)     { writePinHigh(LED_CAPS_LOCK_PIN); }
inline void caps_led_off(void)    { writePinLow(LED_CAPS_LOCK_PIN); }

inline void num_led_on(void)      { writePinHigh(LED_NUM_LOCK_PIN); }
inline void num_led_off(void)     { writePinLow(LED_NUM_LOCK_PIN); }

inline void scroll_led_on(void)   { writePinHigh(LED_SCROLL_LOCK_PIN); }
inline void scroll_led_off(void)  { writePinLow(LED_SCROLL_LOCK_PIN); }
