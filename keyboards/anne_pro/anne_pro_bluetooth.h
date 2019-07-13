/* Copyright 2019 Michiel Visser
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
#include "host_driver.h"

extern host_driver_t anne_pro_bluetooth_driver;

void anne_pro_bluetooth_init(void);
void anne_pro_bluetooth_update(void);

void anne_pro_bluetooth_on(void);
void anne_pro_bluetooth_off(void);
void anne_pro_bluetooth_broadcast(void);
