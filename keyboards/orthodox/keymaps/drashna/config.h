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

#include "config_common.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#ifndef TAPPING_TERM
#define TAPPING_TERM 200
#endif

<<<<<<< HEAD
#define FORCE_NKRO

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> Update to keymaps

>>>>>>> Add workman layer to planck
=======
>>>>>>> Tweaked RGB lighting stuff
/* key combination for command */
#ifdef IS_COMMAND
#undef IS_COMMAND
#endif
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT)) \
)


<<<<<<< HEAD
#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLED_NUM 16     // Number of LEDs
=======
<<<<<<< HEAD
=======
>>>>>>> Add workman layer to planck
#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
<<<<<<< HEAD
#define RGBLED_NUM 12     // Number of LEDs
>>>>>>> Tweaked RGB lighting stuff
=======
#define RGBLED_NUM 16     // Number of LEDs
>>>>>>> Update to keymaps
=======
#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLED_NUM 12     // Number of LEDs
>>>>>>> Tweaked RGB lighting stuff
>>>>>>> Tweaked RGB lighting stuff
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#endif // RGBLIGHT_ENABLE

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Add forced NKRO

<<<<<<< HEAD
#endif
=======
=======
#define FORCE_NKRO
<<<<<<< HEAD
<<<<<<< HEAD
#ifndef FORCE_NKRO
=======
#ifdef FORCE_NKRO
>>>>>>> Add forced NKRO
=======
#ifndef FORCE_NKRO
>>>>>>> Updated macros and added workman keymaps
#define NKRO_EPSIZE 32
#endif
>>>>>>> Add forced NKRO

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Added default layer (qwerty/colemak/dvorak) detection to RGB Underglow
=======
>>>>>>> Updated macros and added workman keymaps
#endif
>>>>>>> Tweaked RGB lighting stuff
=======
#define PERMISSIVE_HOLD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Updated macros and added workman keymaps
=======
>>>>>>> Remove force NKRO

<<<<<<< HEAD
#endif
=======

#endif
<<<<<<< HEAD
>>>>>>> Added default layer (qwerty/colemak/dvorak) detection to RGB Underglow
=======
>>>>>>> Tweaked RGB lighting stuff
>>>>>>> Tweaked RGB lighting stuff
=======
=======
=======
>>>>>>> Updated macros and added workman keymaps
>>>>>>> Updated macros and added workman keymaps

#endif
>>>>>>> Added default layer (qwerty/colemak/dvorak) detection to RGB Underglow
>>>>>>> Added default layer (qwerty/colemak/dvorak) detection to RGB Underglow
