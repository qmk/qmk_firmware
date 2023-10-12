/* Copyright 2019-2021 Konstantin Đorđević <vomindoraan@gmail.com>
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

#include "rgb.h"

#ifdef RGBLIGHT_EFFECT_BREATHING
const uint8_t PROGMEM RGBLED_BREATHING_INTERVALS[] = { 20, 30, 5, 10 };
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
const uint8_t PROGMEM RGBLED_RAINBOW_MOOD_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
const uint8_t PROGMEM RGBLED_RAINBOW_SWIRL_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
const uint8_t PROGMEM RGBLED_SNAKE_INTERVALS[] = { 20, 50, 100 };
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
const uint8_t PROGMEM RGBLED_KNIGHT_INTERVALS[] = { 20, 50, 100 };
#endif

const HSV godspeed_blue     = { GODSPEED_BLUE };
const HSV godspeed_yellow   = { GODSPEED_YELLOW };
const HSV modern_dolch_cyan = { MODERN_DOLCH_CYAN };
const HSV modern_dolch_red  = { MODERN_DOLCH_RED };
