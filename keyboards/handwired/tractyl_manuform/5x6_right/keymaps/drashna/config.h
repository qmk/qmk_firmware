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

#undef OLED_DISPLAY_128X64
#define OLED_DISPLAY_128X128
#define OLED_BRIGHTNESS 200

#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1200
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200
#define CHARYBDIS_MINIMUM_SNIPING_DPI 400
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 200

#define BOOTMAGIC_LITE_EEPROM_ROW          1
#define BOOTMAGIC_LITE_EEPROM_COLUMN       0
#define BOOTMAGIC_LITE_EEPROM_ROW_RIGHT    7
#define BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT 5


#define DRV2605L_FB_ERM_LRA         0
#define DRV2605L_GREETING       DRV2605L_EFFECT_750_MS_ALERT_100
#define DRV2605L_DEFAULT_MODE   DRV2605L_EFFECT_BUZZ_1_100
