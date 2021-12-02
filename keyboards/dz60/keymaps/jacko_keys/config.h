/* Copyright 2020 Simon Paul Jackson, BEng.
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

//Use just Linux mode input. Or change
#define UNICODE_SELECTED_MODES UC_LNX
//#define UNICODE_SELECTED_MODES UC_WIN
//#define UNICODE_SELECTED_MODES UC_MAC
//#define UNICODE_SELECTED_MODES UC_LNX UC_WIN UC_MAC

//Somehow is no longer some feature, so not needed.
//#define RGBLIGHT_SLEEP

//So the patterns move.
//#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

//Allow lighting indication layers.
#define RGBLIGHT_LAYERS

//A default setting. Can go up to 32.
//#define RGBLIGHT_MAX_LAYERS 8

//Keeps status LEDs on even if RGB animations are off.
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

//Can blink layers if needed.
//#define RGBLIGHT_LAYER_BLINK

//To release and not have stuck keys when layer changes on held key.
#define STRICT_LAYER_RELEASE

//OVERRIDES GENERAL FOR BOARD
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#undef LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#undef LOCKING_RESYNC_ENABLE
