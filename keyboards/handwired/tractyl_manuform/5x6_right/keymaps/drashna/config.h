/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#define DEBOUNCE 45

#ifdef OLED_DRIVER_SH1107
#    undef OLED_DISPLAY_128X64
#endif

#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1200
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200
#define CHARYBDIS_MINIMUM_SNIPING_DPI 400
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 200

#define ENCODER_DEFAULT_POS 0x3


#define BOOTMAGIC_LITE_EEPROM_ROW          1
#define BOOTMAGIC_LITE_EEPROM_COLUMN       0
#define BOOTMAGIC_LITE_EEPROM_ROW_RIGHT    7
#define BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT 5
