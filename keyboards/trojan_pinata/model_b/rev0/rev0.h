/* Copyright 2024 Brian H (@Trojan_Pinata)
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

bool oled_task_user(void);
void suspend_power_down_user(void);
void oled_render_boot(bool bootloader);
bool shutdown_user(bool jump_to_bootloader);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
