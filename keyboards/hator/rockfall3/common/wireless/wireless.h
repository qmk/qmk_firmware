/* Copyright (C) 2024 koosikus
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

#include "transport.h"
#include "lowpower.h"
#include "module.h"

void wireless_init(void);
void wireless_devs_change(uint8_t old_devs, uint8_t new_devs, bool reset);
uint8_t wireless_get_current_devs(void);
void wireless_pre_task(void);
void wireless_post_task(void);
