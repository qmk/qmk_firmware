/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2018 Drashna Jaelre (Christopher Courtney) <drashna@live.com>
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

#include <stdbool.h>
#include <stdint.h>

bool dip_switch_update_kb(uint8_t index, bool active);
bool dip_switch_update_user(uint8_t index, bool active);
bool dip_switch_update_mask_user(uint32_t state);
bool dip_switch_update_mask_kb(uint32_t state);

void dip_switch_init(void);
void dip_switch_read(bool forced);
