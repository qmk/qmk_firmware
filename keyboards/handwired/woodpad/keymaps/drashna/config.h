/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#ifdef TAP_DANCE_ENABLE
#define TAPPING_TERM 200
#endif // TAP_DANCE_ENABLE

#define CATERINA_BOOTLOADER


#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLED_NUM 7     // Number of LEDs
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#endif // RGBLIGHT_ENABLE



#endif
