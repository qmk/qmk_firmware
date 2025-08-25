/*
 * Copyright (C) 2022-2025 Jimmy Cassis <KernelOops@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "action_layer.h"

void system76_ec_rgb_eeprom(bool write);
void system76_ec_rgb_layer(layer_state_t state);
#ifdef SYSTEM76_EC
void system76_ec_unlock(void);
#endif
bool system76_ec_is_unlocked(void);
