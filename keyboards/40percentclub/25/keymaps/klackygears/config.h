/* Copyright 2020 klackygears
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
#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL


/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#ifdef RGBLIGHT_ENABLE
#define RGBLED_NUM 7    // Number of LEDs
#endif

 #ifdef RGB_DI_PIN
 #define RGBLIGHT_ANIMATIONS
 #define RGBLIGHT_HUE_STEP 8
 #define RGBLIGHT_SAT_STEP 8
 #define RGBLIGHT_VAL_STEP 8
 #endif
