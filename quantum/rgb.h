/* Copyright 2017 Jack Humbert
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

#ifndef RGB_H
#define RGB_H

__attribute__((weak))
void rgblight_toggle(void) {};

__attribute__((weak))
void rgblight_step(void) {};

__attribute__((weak))
void rgblight_step_reverse(void) {};

__attribute__((weak))
void rgblight_increase_hue(void) {};

__attribute__((weak))
void rgblight_decrease_hue(void) {};

__attribute__((weak))
void rgblight_increase_sat(void) {};

__attribute__((weak))
void rgblight_decrease_sat(void) {};

__attribute__((weak))
void rgblight_increase_val(void) {};

__attribute__((weak))
void rgblight_decrease_val(void) {};

__attribute__((weak))
void rgblight_increase_speed(void) {};

__attribute__((weak))
void rgblight_decrease_speed(void) {};

#endif