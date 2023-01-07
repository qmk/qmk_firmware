
 /* Copyright 2021 Dane Evans
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See thDan
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
  // SOFLE RGB
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

//#define PRINT_DB

#ifdef PRINT_DB
#   include <print.h>
#endif
#include "transactions.h"

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 20

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {LEDS_HF+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {LEDS_HF+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{LEDS_HF+15, 5, hsv},\
	  {LEDS_HF+22, 3, hsv},\
	  {LEDS_HF+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {LEDS_HF+ 10, 2, hsv}, \
	  {LEDS_HF+ 20, 2, hsv}, \
	  {LEDS_HF+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {LEDS_HF+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {LEDS_HF+ 7, 4, hsv}
#define SET_COL_0(hsv) \
	  {8, 4, hsv}, \
	  {8+LEDS_HF, 4, hsv}
#define SET_COL_1(hsv) \
	  {12, 4, hsv}, \
	  {12+LEDS_HF, 4, hsv}
#define SET_COL_2(hsv) \
	  {18, 4, hsv}, \
	  {18+LEDS_HF, 4, hsv}
#define SET_COL_3(hsv) \
	  {22, 4, hsv}, \
	  {22+LEDS_HF, 4, hsv}
#define SET_COL_4(hsv) \
	  {28, 4, hsv}, \
	  {28+LEDS_HF, 4, hsv}
#define SET_COL_5(hsv) \
	  {32, 4, hsv}, \
	  {32+LEDS_HF, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {LEDS_HF+ 25, 2, hsv}
#define SET_UNDERGLOW_INDICAT(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {LEDS_HF+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {LEDS_HF+1, 6, hsv}

//		{7, 4, hsv}, 
//	  {LEDS_HF+ 7, 4, hsv}, 
//		{25, 2, hsv}, 
//	  {LEDS_HF+ 25, 2, hsv}

// https://www.reddit.com/r/olkb/comments/5rk64g/press_both_shift_keys_for_capslock_in_qmk/
//bool process_record_user(uint16_t keycode, keyrecord_t *record)
//{ 
//    // Detect the activation of both Shifts 
//    if ((get_mods() & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) 
//    { 
//        // Toggle Caps_lock value 
//        tap_code(KC_CAPS); 
//    }
//
//    // Keep processing like normal, don't do anything to prevent that
//    return true;
//};


enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
//    _COLEMAK,
//	  _COLEMAKDH,
//    _LOWER,
//    _RAISE,
//    _ADJUST,
//    _NUMPAD,
//    _SWITCH

    _ALT,
    _NUM,
    _FN,
    _KB,
    _LCK
};

//enum custom_keycodes {
////    KC_QWERTY = SAFE_RANGE,
////    KC_COLEMAK,
////	  KC_COLEMAKDH,
////    KC_LOWER,
////    KC_RAISE,
////    KC_ADJUST,
////    KC_D_MUTE
//};

//#define BSPC_BACKSLASH_SWAP
//#define ALT_WIN_SWAP

#ifdef BSPC_BACKSLASH_SWAP
#  define KC_BSPC_ KC_BACKSLASH
#  define KC_BACKSLASH_ KC_BSPC
#else
#  define KC_BSPC_ KC_BSPC
#  define KC_BACKSLASH_ KC_BACKSLASH
#endif

#ifdef ALT_WIN_SWAP
#  define LALT_T_ LWIN_T
#  define LWIN_T_ LALT_T
#else
#  define LALT_T_ LALT_T
#  define LWIN_T_ LWIN_T
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC~ |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BKSP |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |TAB/M_M|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | M_A  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |DISCORD|------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTR | WIN  | LALT | SPACE| / M_Fn  /       \ M_Fn \  |SPACE | M_A  | M_M  | Ctrl |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_QWERTY] = LAYOUT(
         //,------------------------------------------------.                         ,---------------------------------------------------.
  QK_GESC,          KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC_,
         //|------+-------+--------+--------+--------+------|                        |--------+-------+--------+--------+--------+---------|
LT(_FN,KC_TAB),KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,                         KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    LT(_FN, KC_BACKSLASH_),
         //|------+-------+--------+--------+--------+------|                         |--------+-------+--------+--------+--------+---------|
LT(_ALT, KC_ESC),  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, LT(_NUM, KC_QUOT), //LALT_T_(KC_QUOT),
         //|------+-------+--------+--------+--------+------|  ===  |                 |  ===  |--------+-------+--------+--------+--------+---------|
  KC_LSFT,       KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,       KC_MPLY ,KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_UNDS),
         //|------+-------+--------+--------+--------+------|  ===  |             |  ===  |--------+-------+--------+--------+--------+---------|
  KC_LWIN, KC_LALT, KC_LCTL, KC_SPC, LT(_NUM,KC_ENT),                    KC_ENT, LT(_ALT, KC_SPC), RCTL_T(KC_BSPC_), RALT_T(KC_DEL), RWIN_T(KC_GRV)//LT(_FN, KC_DEL)
//  KC_LWIN, KC_LALT, KC_LCTL, KC_SPC, LT(_NUM,KC_ENT),                    KC_ENT, LT(_NUM, KC_SPC), LT(_ALT,KC_BSPC_), RCTL_T(KC_DEL), RWIN_T(KC_GRV)//LT(_FN, KC_DEL)
  //                     \--------+--------+--------+---------+-------|      |--------+---------+--------+---------+-------/
),
[_ALT] = LAYOUT(
  //-------------------------------------------------.                          ----------------------------------------------------.
  TG(_ALT),   KC_NO,  KC_NO, KC_UP, KC_INS,  KC_NO,                             KC_NO,   KC_NO,     KC_NO,    KC_NO,  KC_NO,  KC_DEL,
  //|------+-------+--------+--------+--------+------|                         |--------+-------+--------+--------+--------+---------|
  KC_TAB,  KC_PGUP,   KC_UP, KC_PGDN,  KC_DEL, KC_TILD,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END ,  KC_UNDS,  KC_PLUS ,
  //|------+-------+--------+--------+--------+------|                         |--------+-------+--------+--------+--------+---------|
 KC_GRV,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_BSPC_, KC_GRV,                            KC_LEFT, KC_DOWN,   KC_UP,  KC_RGHT, KC_MINUS, KC_EQL,
  //|------+-------+--------+--------+--------+------        |  ===  |  |  ===  |--------+-------+--------+--------+--------+---------|
 KC_LSFT,   KC_HOME, KC_RALT,  KC_END,  KC_NO, MO(_LCK),   KC_TRNS,      KC_TRNS,  KC_LBRC, KC_RBRC, KC_LCBR,  KC_RCBR,  KC_SLSH  , KC_TRNS,
  //|------+-------+--------+--------+--------+------|  ===  |              |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  //            \--------+--------+--------+---------+-------|             |--------+---------+--------+---------+-------/
),
[_NUM] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  TG(_NUM),  KC_SLASH,  KC_ASTR, KC_MINUS,   KC_PLUS, KC_BSPC_,                      KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_BSPC_,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR , KC_PERC,                  KC_CIRC,  KC_AMPR,   KC_ASTR,    KC_LPRN, KC_RPRN,  KC_PLUS,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_DOT,  KC_1 ,    KC_2 ,    KC_3,    KC_4,   KC_5,                         KC_6  ,   KC_7 ,   KC_8 , KC_9 ,   KC_0,  KC_EQL,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_COMM,  KC_6,    KC_7,     KC_8,    KC_9 , KC_0 ,  KC_TRNS,    KC_TRNS,  KC_NO,    KC_NO,   KC_COMM, KC_DOT, KC_SLSH, KC_TRNS,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
[_FN] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  MO(_LCK),  KC_F1,  KC_F2,   KC_F3,     KC_F4,   KC_F5,                      KC_F6,    KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  MO(_LCK),  KC_F11,   KC_F12,    KC_F13,  KC_F14, KC_F15,                   KC_F16,    KC_F17,   KC_F18,  KC_F11,  KC_F12,  MO(_LCK) ,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_CAPS,  KC_NO,  KC_NO,   KC_NO,  KC_SCRL,   KC_NUM,               KC_NO,  KC_NO,   KC_NO,    KC_NO,   KC_NO ,  KC_NO ,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_TRNS,  KC_PSCR, KC_SCRL,  KC_PAUSE,  KC_NO, MO(_LCK),  KC_TRNS,  KC_TRNS, KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_TRNS  ,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_KB),  MO(_KB),    KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
[_KB] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  TG(_KB), RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN,                    RGB_M_K, RGB_M_X,  RGB_M_G, RGB_M_T,  RGB_TOG,  RGB_TOG,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,  KC_NO,  KC_NO,    KC_NO,   KC_NO, KC_NO,                        KC_NO ,   KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO ,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,  KC_NO,   KC_NO,   KC_NO,  RGB_HUI, RGB_SAI,                     KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
 KC_TRNS, RGB_MOD,  KC_NO,  KC_NO,  RGB_HUD, RGB_SAD,  KC_TRNS,  KC_TRNS, KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_TRNS  ,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_TRNS,    KC_TRNS,    KC_TRNS,    SH_TG,      SH_TG,  KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
[_LCK] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  TG(_LCK),  KC_NO,  KC_NO,    KC_NO,   KC_NO, KC_NO,                        KC_NO ,   KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO ,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  TG(_FN),  KC_NO,  KC_NO,    KC_NO,   KC_NO, KC_NO,                        KC_NO ,   KC_NO,   KC_NO,    KC_NO,    KC_NO,  TG(_FN) ,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  TG(_ALT),  KC_NO,  KC_NO,   KC_NO,   KC_NO, KC_NO,                     KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO,  TG(_NUM),
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_CAPS, KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  TG(_KB),  KC_TRNS, KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_CAPS  ,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 TG(_KB), KC_TRNS, KC_TRNS, KC_TRNS,TG(_NUM),     KC_TRNS, TG(_ALT),    KC_TRNS,  KC_TRNS,   KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
//[_ALT] = LAYOUT(
//  //,------------------------------------------------.                    ,---------------------------------------------------.
//  KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO, KC_NO,                      KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO, KC_NO,                      KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO ,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO, KC_NO,                      KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//  KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO, KC_NO,  KC_NO,      KC_NO,  KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO  , KC_NO  ,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//                   KC_NO,    KC_NO,    KC_NO, KC_NO,  KC_NO,      KC_NO,    KC_NO,  KC_NO,   KC_NO,  KC_NO
//  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
//),

/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |DISCORD|------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |LShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
//[_COLEMAK] = LAYOUT(
//  //,------------------------------------------------.                    ,---------------------------------------------------.
//  KC_TRNS,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      LT(_SWITCH,KC_6),    KC_7,   KC_8,    KC_9,    KC_0,    KC_TRNS,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  KC_TRNS,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_TRNS,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  KC_TRNS,  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,   KC_E,    KC_I,    KC_O,    KC_TRNS,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//  KC_TRNS,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_TRNS,    KC_TRNS,KC_K,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
//  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
//),

/*
 * COLEMAK-DH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |DISCORD|------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |LShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
//[_COLEMAKDH] = LAYOUT(
//  //,------------------------------------------------.                    ,---------------------------------------------------.
//  KC_TRNS,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      LT(_SWITCH,KC_6),    KC_7,   KC_8,    KC_9,    KC_0,    KC_TRNS,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  KC_TRNS,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_TRNS,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  KC_TRNS,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,   KC_E,    KC_I,    KC_O,    KC_TRNS,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//  KC_TRNS,  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,  KC_TRNS,    KC_TRNS,KC_K,    KC_H,   KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
//  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
//),
//
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | trans|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
//[_LOWER] = LAYOUT(
//  //,------------------------------------------------.                    ,---------------------------------------------------.
//  _______,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_BSPC,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  _______,  KC_NO,  KC_NO,   KC_NO,   KC_WH_U, KC_PGUP,                   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_NO,   KC_DEL,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//  _______,  KC_NO,  KC_NO,   KC_NO,   KC_WH_D, KC_PGDN,_______,    _______,KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,    _______,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
//  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
//),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
//[_RAISE] = LAYOUT(
//  //,------------------------------------------------.                    ,---------------------------------------------------.
//  _______, _______ , _______ , _______ , _______ , _______,               _______,  _______  , _______,  _______ ,  _______ ,_______,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                KC_CIRC, KC_AMPR,KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                KC_MINS, KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//  _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,_______,    _______,KC_UNDS, KC_PLUS,KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
//  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
//),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RGB_TOG|hue^ |sat ^ | bri ^|      |COLEMAK|-------.   ,-------|desk <|      |      |desk >|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | mode | hue dn|sat d|bri dn|      |QWERTY|-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
//  [_ADJUST] = LAYOUT(
//  //,------------------------------------------------.                    ,---------------------------------------------------.
//  EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  RESET,   XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  RGB_TOG, RGB_HUI,RGB_SAI, RGB_VAI, KC_COLEMAKDH,KC_COLEMAK,             C(G(KC_LEFT)),KC_NO,KC_NO,C(G(KC_RGHT)),XXXXXXX, XXXXXXX,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//  RGB_MOD, RGB_HUD,RGB_SAD, RGB_VAD, XXXXXXX,KC_QWERTY,XXXXXXX,   XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
//    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
//),
/* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|      |      |      |      |      |                    |      |NumLck|      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |      |      |      |      |      |                    |   ^  |   7  |   8  |   9  |   *  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------.    ,-------|   -  |   4  |   5  |   6  |      |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------|    |-------|   +  |   1  |   2  |   3  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE | 0    |  .   | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
//[_NUMPAD] = LAYOUT(
//  //,------------------------------------------------.                    ,---------------------------------------------------.
//  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, KC_NLCK, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CIRC, KC_P7,  KC_P8,   KC_P9,   KC_ASTR, XXXXXXX,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MINS, KC_P4,  KC_P5,   KC_P6,   KC_EQL,  KC_PIPE,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______,   _______,KC_PLUS, KC_P1,  KC_P2,   KC_P3,   KC_SLSH, _______,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//              _______, OSM(MOD_MEH), _______, _______, _______,   _______, _______,  KC_P0,   KC_PDOT, _______
//  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
//),

/* SWITCH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | qwer | cole |col_dh| low  | raise| adj  |                    |numpad|      |      |      |      |RESET |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |EEP_RST|
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | SLEEP|      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE | 0    |  .   | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  // layer switcher
//[_SWITCH] = LAYOUT(
//  //,------------------------------------------------.                    ,---------------------------------------------------.
//  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  TO(0),   TO(1),   TO(2),   TO(3),   TO(4),   TO(5),                      TO(6),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RESET,
//  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
//  KC_NO,   KC_NO, KC_BRIU,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   EEP_RST,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//  KC_SYSTEM_SLEEP,KC_NO,KC_NO,KC_NO,  KC_NO,   KC_NO, KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
//  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
//                  KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
//  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
//
//	),
};

#ifdef RGBLIGHT_ENABLE

char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_BLUE)

);
const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_PINK)
);

// _NUM,
// Light on outer column and underglow
//const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
//	SET_UNDERGLOW_INDICAT(HSV_TEAL)
//
//);
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_alt_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_UNDERGLOW_INDICAT(HSV_TEAL)

    );
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_fn_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_PURPLE)
);

const rgblight_segment_t PROGMEM layer_lck_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_RED)
);
const rgblight_segment_t PROGMEM layer_kb_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_YELLOW)
);

const rgblight_segment_t PROGMEM indi_caps_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_0(HSV_WHITE)
);
const rgblight_segment_t PROGMEM indi_compose_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_1(HSV_WHITE)
);
const rgblight_segment_t PROGMEM indi_kana_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_2(HSV_WHITE)
);
const rgblight_segment_t PROGMEM indi_scroll_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_4(HSV_WHITE)
);
const rgblight_segment_t PROGMEM indi_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_5(HSV_WHITE)
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_GREEN)
//	SET_INDICATORS(HSV_ORANGE),
//    SET_UNDERGLOW(HSV_ORANGE),
//	SET_NUMPAD(HSV_BLUE),
//    {7, 4, HSV_ORANGE},
//    {25, 2, HSV_ORANGE},
//    {LEDS_HF+6, 4, HSV_ORANGE},
//    {LEDS_HF+25, 2, HSV_ORANGE}
    );
// _SWITCHER   // light up top row
//const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(
//	SET_UNDERGLOW_INDICAT(HSV_GREEN),
//	SET_NUMROW(HSV_GREEN)
//);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    
    layer_qwerty_lights,
	layer_alt_lights,
	layer_numpad_lights,
//	layer_num_lights,// overrides layer 1
    layer_fn_lights,
    layer_kb_lights,
    layer_lck_lights,
    indi_caps_lights,
    indi_compose_lights,
    indi_scroll_lights,
    indi_num_lights,
    indi_kana_lights
//	layer_switcher_lights,  // Overrides other layers
//	layer_colemakdh_lights
);


layer_state_t layer_state_set_user(layer_state_t state) {

	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));
//	rgblight_set_layer_state(7, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_COLEMAKDH));

	rgblight_set_layer_state(1, layer_state_cmp(state, _ALT));
	rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
	rgblight_set_layer_state(3, layer_state_cmp(state, _FN));
	rgblight_set_layer_state(4, layer_state_cmp(state, _KB));
	rgblight_set_layer_state(5, layer_state_cmp(state, _LCK));
//	rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
//	rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
//	rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
////	rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
//	rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
    return state;
}

//led_t g_led_state;

bool led_update_user(led_t led_state) {
//    g_led_state = led_state;
    rgblight_set_layer_state(6, led_state.caps_lock);
    rgblight_set_layer_state(7, led_state.compose);
    rgblight_set_layer_state(8, led_state.scroll_lock);
    rgblight_set_layer_state(9, led_state.num_lock);
    rgblight_set_layer_state(10, led_state.kana);
    //check RGBLIGHT_MAX_LAYERS
    return true;
}

#endif

#ifdef OLED_ENABLE

uint16_t keyCntr = 0;
#define OLED_SUGAR_HEIGHT 128

#define OLED_SUGAR_WIDTH  32

bool pixelInvert = false;
void setPixel(char * pixels, uint8_t h, uint8_t w, bool pix) {
//    oled_write_pixel(w, h, pix);
    uint16_t byteIdx = w + (h/8)*OLED_SUGAR_WIDTH;
    int8_t byteMask = 1<<(h%8);
    if(pixelInvert) pix = !pix;
    if(pix) {
        pixels[byteIdx] |= byteMask;
    } else {
        pixels[byteIdx] &= ~byteMask;
    }
}

bool getPixel(char * pixels, uint8_t h, uint8_t w) {
    uint16_t byteIdx = w + (h/8)*OLED_SUGAR_WIDTH;
    int8_t byteMask = 1<<(h%8);
    bool pix =  (pixels[byteIdx] & byteMask) != 0;
    if(pixelInvert) pix = !pix;
    return pix;
}

uint32_t rand_basic(void) {
    static uint32_t seed = 0;
    seed = 1664525*seed + 1013904223;
    return seed;
}

#define OLED_SUGAR_WITH_DOWN 1

#define OLED_SUGAR_PIXELS (OLED_SUGAR_HEIGHT*OLED_SUGAR_WIDTH)
#define OLED_SUGAR_BYTES (OLED_SUGAR_PIXELS/8)
typedef signed char lineIdx_t;
lineIdx_t* activeSugar = NULL;

char* pixels = NULL;


void oled_sugar(void) {
    //return;

    if (activeSugar == NULL) {
        activeSugar = malloc(OLED_SUGAR_HEIGHT);
        if (activeSugar != NULL) {
            memset( activeSugar, -1, OLED_SUGAR_HEIGHT );
        } else {
#ifdef PRINT_DB
            uprintf("activeSugar %X failed to inialise\n", activeSugar);
#endif
            return;
        }
    }

    if (pixels == NULL) {
        pixels = malloc(OLED_SUGAR_BYTES);
        if (pixels != NULL) {
            memset( pixels, 0, OLED_SUGAR_BYTES );
        } else {
#ifdef PRINT_DB
            uprintf("pixels %X failed to inialise\n", pixels);
#endif
            return;
        }

    }

    static uint8_t sugarCntr = 0;

   for(int16_t h = OLED_SUGAR_HEIGHT-2; h >= 0; h--) {
        lineIdx_t w = activeSugar[h];

        if(w < 0 || w >= OLED_SUGAR_WIDTH) {
            continue;
        }
        lineIdx_t wn = -1;
        bool left;
        bool right;
#ifdef OLED_SUGAR_WITH_DOWN 
        uint32_t r = rand_basic();
        const uint32_t thresh1 = UINT32_MAX/3;
        const uint32_t thresh2 = UINT32_MAX-thresh1;
        left  = r < thresh1;
        right = r > thresh2;
#else
        left = ((int32_t) rand_basic())<0;
        right = !left;
#endif
        if ( left ) {
            if( w > 0 ) {
                if(!getPixel(pixels, h+1, w-1)) {
                    wn = w - 1;
                }
            }
        } else if (right) {
            if ( w < OLED_SUGAR_WIDTH-1) {
                if(!getPixel(pixels, h+1, w+1)) {
                    wn = w + 1;
                }
            }
        } else { //centre
            if(!getPixel(pixels, h+1, w)) {
                wn = w ;
            }
        }
        if(wn == -1) {
            if(!getPixel(pixels, h+1, w)) {
                wn = w;
            }
        }
        if(wn != -1) {
            setPixel(pixels, h+1, wn, true);
            activeSugar[h+1] = wn;
            setPixel(pixels, h, w, false);
        }

        activeSugar[h] = -1;
    }
    if(sugarCntr != (keyCntr&0xFF)) {

        sugarCntr++;
        lineIdx_t w = OLED_SUGAR_WIDTH/2;
        bool left = false;
        if( ((int32_t) rand_basic())<0 ) {
            w--;
            left = true;
        }
        bool full = false;
        while(getPixel(pixels,0, w)) {
            if(left) {
                if (w == 0) {
                    w = OLED_SUGAR_WIDTH-1;
                } else if ( w == OLED_SUGAR_WIDTH/2) {
                    full = true;
                    break;
                } else {
                    w--;
                }
            } else {
                if (w == OLED_SUGAR_WIDTH-1) {
                    w = 0;
                } else if ( w == OLED_SUGAR_WIDTH/2-1) {
                    full = true;
                    break;
                } else {
                    w++;
                }
            }
        }

        if(!full) {
//        if(!getPixel(pixels, 0, w)) {
            setPixel(pixels, 0, w, true);
            activeSugar[0] = w;
        } else {
            pixelInvert = !pixelInvert;
            // we where not able to add a pixel (we where full so add one now that we have inverted)
            sugarCntr--;
            oled_sugar();
        }
    }
    rand_basic(); //just here to rotate the seed
    if(!is_oled_on()) {
        //OLED timedout so we will clear everything and start fresh
        memset( pixels, 0, OLED_SUGAR_BYTES );
        memset( activeSugar, -1, OLED_SUGAR_HEIGHT );
        oled_clear();
        pixelInvert = false;
    } else {
        oled_write_raw(pixels, OLED_SUGAR_BYTES);
    }
    
}

uint16_t keyCodeLast = 0;

//static void leftOled(void) {
//    // Print current mode
// //   oled_write_P(PSTR("\n"), false);
//  //  oled_write_ln_P(PSTR("@Pev"), false);
//  //  oled_write_ln_P(PSTR(""), false);
//  //  oled_write_ln_P(PSTR("v0.1"), false);
//  //  oled_write_ln_P(PSTR(""), false);
//
//	//snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state)
//
//
////    switch (get_highest_layer(default_layer_state)) {
////        case _QWERTY:
////            oled_write_ln_P(PSTR("Qwrt"), false);
////            break;
//////        case _COLEMAK:
//////            oled_write_ln_P(PSTR("Clmk"), false);
//////            break;
//////        case _COLEMAKDH:
//////            oled_write_ln_P(PSTR("CmkDH"), false);
//////            break;
////
////        default:
////            oled_write_ln_P(PSTR("Undef"), false);
////    }
//    oled_write_P(PSTR("\n\n"), false);
//    // Print current layer
//    //oled_write_ln_P(PSTR("LAYER"), false);
//    switch (get_highest_layer(layer_state)) {
////        case _COLEMAK:
//        case _QWERTY: //5 characters also creates a new line be default
////        case _COLEMAKDH:
//            oled_write_ln_P(PSTR("Base\n"), false);
//            break;
//
//        case _ALT:
//            oled_write_ln_P(PSTR("Alter"), false);
//            break;
//        case _NUM:
//            oled_write_ln_P(PSTR("M-Num"), false);
//            break;
//        case _FN:
//            oled_write_ln_P(PSTR("Func "), false);
//            break;
//        case _KB:
//            oled_write_ln_P(PSTR("KBset"), false);
//            break;
//
//        default:
//            oled_write_ln_P(PSTR("Undef"), false);
//    }
//    if(g_led_state.caps_lock) {
//        oled_write_P(PSTR("CapsL"), false);
//    } else {
//        oled_write_ln_P(PSTR(""), false);
//    }
//    if(g_led_state.num_lock) {
//        oled_write_P(PSTR("NumL "), false);
//    } else {
//        oled_write_ln_P(PSTR(""), false);
//    }
//    if(g_led_state.scroll_lock) {
//        oled_write_P(PSTR("ScrlL"), false);
//    } else {
//        oled_write_ln_P(PSTR(""), false);
//    }
//    oled_write_ln_P(PSTR(""), false);
//
//    char snum[5];
////    int8_t snumLen;
////    snumLen = ceil(log10(keyCntr));
//    itoa(keyCntr%100000, snum, 10);
////    if(snumLen < 5) {
////        snum[snumLen+1] = '\n';
////    }
//    oled_write_ln(snum, false);
////    oled_write_ln_P(snum, false);
//
////`    snumLen = ceil(log10(keyCntr)/log10(16));
////`    itoa(keyCodeLast, snum, 16);
////`    if(snumLen < 5) {
////`        snum[snumLen+1] = '\n';
////`    }
////`    oled_write(snum, false);
////`    oled_write_ln_P(PSTR(""), false);
//}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (true) { //is_keyboard_master()) {
        return OLED_ROTATION_270;
    } 
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        //leftOled();
        oled_sugar();
    } else {
        oled_sugar();
       // render_logo();
    }
    return false;
}

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    keyCntr = *((const uint16_t *)in_data);
}

#endif


void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
#ifdef OLED_ENABLE
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
#endif
	rgblight_mode(10);// haven't found a way to set this in a more useful way
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if(record->event.pressed) {
#ifdef OLED_ENABLE
        keyCntr++;
//        transaction_rpc_exec(USER_SYNC_A, 0, &m2s, sizeof(s2m), &s2m)
        transaction_rpc_send(USER_SYNC_A, sizeof(keyCntr), &keyCntr);
#endif
        keyCodeLast = keycode;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    static uint8_t cntr0;
    static uint8_t cntr1;
        if (index == 0) {
            if ((cntr0 & 1) == 1) {
#ifdef PRINT_DB
        print("Volume knob tunred\n");
#endif
                if (get_highest_layer(layer_state) == _KB) {
                    if (clockwise) {
                        rgblight_increase_val();
                    } else {
                        rgblight_decrease_val();
                    }
                } else if (get_highest_layer(layer_state) == _FN) {
                    if (clockwise) {
                        tap_code(KC_BRIU);
                    } else {
                        tap_code(KC_BRID);
                    }
                } else if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            }
            if (clockwise) {
                cntr0 += 1;
            } else {
                cntr0 -= 1;
            }
        } else if (index == 1) {
            if ((cntr1 & 1) == 1) {
                if (get_highest_layer(layer_state) == _KB) {
                    if (clockwise) {
                        rgblight_increase_val(); 
                    } else {
                        rgblight_decrease_val(); 
                    }
                } else if (get_highest_layer(layer_state) == _FN) {
                    if (clockwise) {
                        tap_code(KC_BRIU);
                    } else {
                        tap_code(KC_BRID);
                    }
                } else if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
            }
            if (clockwise) {
                cntr1 += 1;
            } else {
                cntr1 -= 1;
            }
        }
    return true;
}

#endif
