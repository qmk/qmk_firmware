/* Copyright 2021 @nstickney
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

// Changes from Bastyl defaults
#ifdef MASTER_RIGHT
#    undef MASTER_RIGHT
#endif

// Turn off RGB lights when computer is sleeping
#define RGBLIGHT_SLEEP

// https://beta.docs.qmk.fm/developing-qmk/qmk-reference/config_options#features-that-can-be-disabled
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// Turn off all possible RGB animations
#ifdef RGB_ANIMATIONS
#    undef RGB_ANIMATIONS
#endif
#ifdef RGB_EFFECT_ALTERNATING
#    undef RGB_EFFECT_ALTERNATING
#endif
#ifdef RGB_EFFECT_BREATHING
#    undef RGB_EFFECT_BREATHING
#endif
#ifdef RGB_EFFECT_CHRISTMAS
#    undef RGB_EFFECT_CHRISTMAS
#endif
#ifdef RGB_EFFECT_KNIGHT
#    undef RGB_EFFECT_KNIGHT
#endif
#ifdef RGB_EFFECT_RAINBOW_MOOD
#    undef RGB_EFFECT_RAINBOW_MOOD
#endif
#ifdef RGB_EFFECT_RAINBOW_SWIRL
#    undef RGB_EFFECT_RAINBOW_SWIRL
#endif
#ifdef RGB_EFFECT_RGB_TEST
#    undef RGB_EFFECT_RGB_TEST
#endif
#ifdef RGB_EFFECT_SNAKE
#    undef RGB_EFFECT_SNAKE
#endif
#ifdef RGB_EFFECT_STATIC_GRADIENT
#    undef RGB_EFFECT_STATIC_GRADIENT
#endif
#ifdef RGB_EFFECT_TWINKLE
#    undef RGB_EFFECT_TWINKLE
#endif
