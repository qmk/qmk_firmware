/* Copyright 2017 Fred Sundvik
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

#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include "visualizer.h"
#include "led.h"

void ergodox_led_lower_on (void);
void ergodox_led_raise_on (void);
void ergodox_led_adjust_on (void);

void ergodox_led_lower_off (void);
void ergodox_led_raise_off (void);
void ergodox_led_adjust_off (void);

void ergodox_led_lower_set (uint8_t n);
void ergodox_led_raise_set (uint8_t n);
void ergodox_led_adjust_set (uint8_t n);

#endif /* VISUALIZER_H_ */
