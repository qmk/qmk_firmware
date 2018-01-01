/*
Copyright 2017 Christopher Courtney <drashna@live.com> @drashna

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

#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Define layer names 
#define _QWERTY 0
#define _NUMLOCK 0
#define _COLEMAK 1
#define _DVORAK 2
#define _WORKMAN 3
#define _NAV 5
#define _COVECUBE 6
#define _SYMB 8
#define _GAMEPAD 9
#define _DIABLO 10
#define _MOUS 11
#define _MACROS 12
#define _MEDIA 13
#define _LOWER 14
#define _RAISE 15
#define _ADJUST 16


//define modifiers
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK  (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))

#ifndef RGBLIGHT_ANIMATIONS // add "EXTRA_FLADS=-DDRASHNA_SETRGB" to enable this ... but don't
#define rgblight_set_blue        rgblight_setrgb (0x00,  0x00, 0xFF);
#define rgblight_set_red         rgblight_setrgb (0xFF,  0x00, 0x00);
#define rgblight_set_green       rgblight_setrgb (0x00,  0xFF, 0x00);
#define rgblight_set_orange      rgblight_setrgb (0xFF,  0x80, 0x00);
#define rgblight_set_teal        rgblight_setrgb (0x00,  0xFF, 0xFF);
#define rgblight_set_magenta     rgblight_setrgb (0xFF,  0x00, 0xFF);
#define rgblight_set_yellow      rgblight_setrgb (0xFF,  0xFF, 0x00);
#define rgblight_set_purple      rgblight_setrgb (0x7A,  0x00, 0xFF);
#define rgblight_set_white       rgblight_setrgb (0xFF,  0xFF, 0xFF);
#else
#define rgblight_set_blue        rgblight_sethsv (0xFF,  0xFF, 0xFF);
#define rgblight_set_red         rgblight_sethsv (0x00,  0xFF, 0xFF);
#define rgblight_set_green       rgblight_sethsv (0x78,  0xFF, 0xFF);
#define rgblight_set_orange      rgblight_sethsv (0x1E,  0xFF, 0xFF);
#define rgblight_set_teal        rgblight_sethsv (0xB4,  0xFF, 0xFF);
#define rgblight_set_magenta     rgblight_sethsv (0x12C, 0xFF, 0xFF);
#define rgblight_set_yellow      rgblight_sethsv (0x3C,  0xFF, 0xFF);
#define rgblight_set_purple      rgblight_sethsv (0x10E, 0xFF, 0xFF);
#define rgblight_set_white       rgblight_sethsv (0x00,  0x00, 0xFF);
#endif // DRASHNA_SETRGB

extern bool is_overwatch;
extern bool rgb_layer_change;

enum userspace_custom_keycodes {
  EPRM = SAFE_RANGE, // can always be here
  VRSN,
  KC_QWERTY,
  KC_COLEMAK,
  KC_DVORAK,
  KC_WORKMAN,
  LOWER,
  RAISE,
  ADJUST,
  KC_DIABLO_CLEAR,
  KC_OVERWATCH,
  KC_SALT,
  KC_MORESALT,
  KC_SALTHARD,
  KC_GOODGAME,
  KC_SYMM,
  KC_JUSTGAME,
  KC_GLHF,
  KC_TORB,
  KC_AIM,
  KC_C9,
  KC_GGEZ,
  KC_MAKE,
  KC_RESET,
  KC_RGB_T,
  KC_SECRET_1,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
  NEW_SAFE_RANGE //use "NEWPLACEHOLDER for keymap specific codes
};

#ifdef TAP_DANCE_ENABLE
enum {
  TD_D3_1 = 0,
  TD_D3_2,
  TD_D3_3,
  TD_D3_4
};
#endif

#ifdef TAP_DANCE_ENABLE
#define KC_D3_1 TD(TD_D3_1)
#define KC_D3_2 TD(TD_D3_2)
#define KC_D3_3 TD(TD_D3_3)
#define KC_D3_4 TD(TD_D3_4)
#else
#define KC_D3_1 KC_1
#define KC_D3_2 KC_2
#define KC_D3_3 KC_3
#define KC_D3_4 KC_4
#endif

#define QMK_KEYS_PER_SCAN 8

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SLEEP
#endif

#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

#endif
