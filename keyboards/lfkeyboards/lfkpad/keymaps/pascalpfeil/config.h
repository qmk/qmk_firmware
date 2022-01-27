/* Copyright 2021 Pascal Pfeil
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

/* 1000Hz USB polling */
#define USB_POLLING_INTERVAL_MS 1

/* Send up to 4 key press events per scan */
#define QMK_KEYS_PER_SCAN 4

/* Force NKRO on boot up */
#define FORCE_NKRO

#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGB_DISABLE_TIMEOUT 900000
