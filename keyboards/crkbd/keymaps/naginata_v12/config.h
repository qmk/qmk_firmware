/* Copyright 2018-2019 eswai <@eswai>
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

#undef PRODUCT
#define PRODUCT   Crkbd Naginata Style V12

// 薙刀式
#define NAGINATA_TATEGAKI
// #define NAGINATA_YOKOGAKI
#define NAGINATA_EDIT_WIN // JP106
// #define NAGINATA_EDIT_MAC // JP106
// #define MAC_LIVE_CONVERSION // Macでライブ変換をオンにしている場合
#define COMBO_COUNT 2
// 薙刀式

/* Select hand configuration */

#define MASTER_LEFT
#define USE_SERIAL_PD2

#define TAPPING_TERM 300
#define USB_MAX_POWER_CONSUMPTION 100