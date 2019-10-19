/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#ifndef CONFIG_USER_H
#define CONFIG_USER_H



#define PERMISSIVE_HOLD

#define PREVENT_STUCK_MODIFIERS
//#define TAPPING_FORCE_HOLD

#undef TAPPING_FORCE_HOLD
#undef TAPPING_TERM
#define TAPPING_TERM 150
#define IGNORE_MOD_TAP_INTERRUPT

#define SSD1306OLED

// place overrides here

// If you need more program area, try select and reduce rgblight modes to use.

// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
//   #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
     #define RGBLIGHT_EFFECT_SNAKE
     #undef  RGBLIGHT_EFFECT_SNAKE_LENGTH
     #define RGBLIGHT_EFFECT_SNAKE_LENGTH 20
//   #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
//   #define RGBLIGHT_EFFECT_BEAM
//   #define RGBLIGHT_EFFECT_HYPER
//   #define RGBLIGHT_EFFECT_RAINBOW_SPARKLE
#endif

#endif /* CONFIG_USER_H */


//#define QMK_ESC_OUTPUT F4 // usually COL
//#define QMK_ESC_INPUT D4 // usually ROW
//#define QMK_LED B0
//#define QMK_SPEAKER C6

//#define EE_HANDS
#undef PRODUCT
#define PRODUCT klackygears Helix Keyboard

//#define OLED_FONT_H "keyboards/helix/rev2/keymaps/klackygears/glcdfont.c"
