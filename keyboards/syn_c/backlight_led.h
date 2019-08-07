/* Copyright 2019 kratsyn
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

void backlight_init(void);
void backlight_reset_cb(void);
bool backlight_is_enabled(void);
void backlight_enable(void);
void backlight_on(void);
void backlight_off(void);
void backlight_toggle(void);
void backlight_step(bool forward);
void backlight_rstep(void);
void backlight_level(uint8_t level);
bool backlight_is_breathing(void);
void backlight_breathing_on(void);
void backlight_breathing_off(void);
void backlight_breathing_toggle(void);
void _enable_cb(void);
void _disable_cb(void);
