/* Copyright 2023 KANATSU Minoru <dev@orum.in>
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
/* Bluetooth Low Energy Protocol for QMK, Adafruit BLE UART friends extended functions
 * Author: KANATSU Minoru, 2023
 */

#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern bool bluefruit_le_delbonds(void);
extern bool bluefruit_le_reconnect(void);

#ifdef __cplusplus
}
#endif
