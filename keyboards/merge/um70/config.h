/* Copyright 2021 duoshock 
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

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B7 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, D6, D4 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define SPLIT_USB_DETECT
#define MASTER_LEFT
#define SPLIT_MODS_ENABLE

#define RGB_DI_PIN D3
#define RGBLIGHT_SPLIT
#define RGBLED_NUM 83
#define RGBLED_SPLIT { 39, 44 }
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#endif
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 150

#define B6_AUDIO

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif
