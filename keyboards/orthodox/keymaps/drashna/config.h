/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 150
#undef PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)
#define ONESHOT_TAP_TOGGLE 2



/* key combination for command */
#ifdef IS_COMMAND
#undef IS_COMMAND
#endif
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT)) \
)


#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLED_NUM 16     // Number of LEDs
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#endif // RGBLIGHT_ENABLE

#ifdef AUDIO_ENABLE
#define C6_AUDIO
#define STARTUP_SONG SONG(ZELDA_TREASURE)
#endif

#endif
