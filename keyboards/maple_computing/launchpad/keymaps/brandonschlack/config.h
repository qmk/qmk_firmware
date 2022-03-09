/* Copyright 2020 Brandon Schlack
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

/* Underlight Configuration */
#ifdef RGB_DI_PIN
    #undef RGB_DI_PIN
    #define RGB_DI_PIN F4
    #undef RGBLED_NUM
    #define RGBLED_NUM 2  // Number of LEDs
#endif
#define RGBLIGHT_EFFECT_BREATHING // Only have Breathing Animation
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* Mouse Keys Configuration */
#define MK_3_SPEED
#define MK_W_INTERVAL_UNMOD 20
