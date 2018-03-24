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
#define _MODS 4
//#define _MISC 5
#define _NAV 6
#define _COVECUBE 7
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
#define rgblight_set_white       rgblight_sethsv (0,  0x00, 255);
#define rgblight_set_red         rgblight_sethsv (0,  255, 255);
#define rgblight_set_coral       rgblight_sethsv (16, 176, 255);
#define rgblight_set_orange      rgblight_sethsv (39,  255, 255);
#define rgblight_set_goldenrod   rgblight_sethsv (43,  218, 218);
#define rgblight_set_gold        rgblight_sethsv (51,  255, 255);
#define rgblight_set_yellow      rgblight_sethsv (60,  255, 255);
#define rgblight_set_chartreuse  rgblight_sethsv (90, 255, 255);
#define rgblight_set_green       rgblight_sethsv (120,  255, 255);
#define rgblight_set_springgreen rgblight_sethsv (150,  255, 255);
#define rgblight_set_turquoise   rgblight_sethsv (174,  90, 112);
#define rgblight_set_teal        rgblight_sethsv (180,  255, 128);
#define rgblight_set_cyan        rgblight_sethsv (180,  255, 255);
#define rgblight_set_azure       rgblight_sethsv (186,  102, 255);
#define rgblight_set_blue        rgblight_sethsv (240,  255, 255);
#define rgblight_set_purple      rgblight_sethsv (270, 255, 255);
#define rgblight_set_magenta     rgblight_sethsv (300, 255, 255);
#define rgblight_set_pink        rgblight_sethsv (330, 128, 255);

//#define rgblight_set_        rgblight_sethsv (0, 255, 255);
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
  KC_FXCL,
  NEW_SAFE_RANGE //use "NEWPLACEHOLDER for keymap specific codes
};

#ifdef TAP_DANCE_ENABLE
enum {
  TD_D3_1 = 0,
  TD_D3_2,
  TD_D3_3,
  TD_D3_4
};
#endif // TAP_DANCE_ENABLE


// Custom Keycodes for Diablo 3 layer
// But since TD() doesn't work when tapdance is disabled
// We use custom codes here, so we can substituet the right stuff
#ifdef TAP_DANCE_ENABLE
#define KC_D3_1 TD(TD_D3_1)
#define KC_D3_2 TD(TD_D3_2)
#define KC_D3_3 TD(TD_D3_3)
#define KC_D3_4 TD(TD_D3_4)
#else // TAP_DANCE_ENABLE
#define KC_D3_1 KC_1
#define KC_D3_2 KC_2
#define KC_D3_3 KC_3
#define KC_D3_4 KC_4
#endif // TAP_DANCE_ENABLE

// OSM keycodes, to keep things clean and easy to change
#define KC_MLSF OSM(MOD_LSFT)
#define KC_MRSF OSM(MOD_RSFT)
#define ONESHOT_TIMEOUT 3000

#define QMK_KEYS_PER_SCAN 8

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SLEEP
#endif // RGBLIGHT_ENABLE

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT

// Disable action_get_macro and fn_actions, since we don't use these
// and it saves on space in the firmware.
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// If we're still using the official Faux Clicky feature, substituet codes
// so that we don't have any unused/blank keys.
#ifdef FAUXCLICKY_ENABLE
#define AUD_ON  FC_ON
#define AUD_OFF FC_OFF
#else // FAUXCLICKY_ENABLE
#define AUD_ON  AU_ON
#define AUD_OFF AU_OFF
#endif // FAUXCLICKY_ENABLE



// Since our quirky block definitions are basically a list of comma separated 
// arguments, we need a wrapper in order for these definitions to be 
// expanded before being used as arguments to the LAYOUT_xxx macro.
#define LAYOUT_ergodox_wrapper(...)   LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define KEYMAP_wrapper(...)           KEYMAP(__VA_ARGS__)


// Blocks for each of the four major keyboard layouts
// Organized so we can quickly adapt and modify all of them
// at once, rather than for each keyboard, one at a time.
// And this allows wor much cleaner blocks in the keymaps.
// For instance Tap/Hold for Control on all of the layouts

// NOTE: These are all the same length.  If you do a search/replace
//       then you need to add/remove underscores to keep the
//       lengths consistent. 

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________  CTL_T(KC_Z),   KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  CTL_T(KC_SLASH)


#define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________       KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________ CTL_T(KC_Z),   KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  CTL_T(KC_SLASH)


#define _________________DVORAK_L1_________________        KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________        KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________  CTL_T(KC_SCLN),KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________        KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________        KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________        KC_B,    KC_M,    KC_W,    KC_V,    CTL_T(KC_Z)


#define _________________WORKMAN_L1________________       KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________WORKMAN_L2________________       KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________WORKMAN_L3________________ CTL_T(KC_SCLN),KC_Q,    KC_J,   KC_K,     KC_X

#define _________________WORKMAN_R1________________       KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________WORKMAN_R2________________       KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________WORKMAN_R3________________       KC_B,    KC_M,    KC_W,    KC_V,    CTL_T(KC_Z)



// Since we have 4 default layouts (QWERTY, DVORAK, COLEMAK and WORKMAN),
// this allows us to quickly modify the bottom row for all of the layouts
// so we don't have to alter it 4 times and hope that we haven't missed
// anything
#define ___________ERGODOX_BOTTOM_LEFT_____________       KC_QUOT, KC_MEH,  KC_LBRC, KC_RBRC
#define ___________ERGODOX_BOTTOM_RIGHT____________       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT


#endif
