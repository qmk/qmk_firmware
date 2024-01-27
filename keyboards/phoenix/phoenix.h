/* Copyright 2019
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

inline void led_pin_on(uint8_t pin) { palSetPad(GPIOB, pin); };
inline void led_pin_off(uint8_t pin) { palClearPad(GPIOB, pin); };

inline void led1_on(void) { led_pin_on(8); };
inline void led2_on(void) { led_pin_on(5); };
inline void led3_on(void) { led_pin_on(6); };

inline void led1_off(void) { led_pin_off(8); };
inline void led2_off(void) { led_pin_off(5); };
inline void led3_off(void) { led_pin_off(6); };
