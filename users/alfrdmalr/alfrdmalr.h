/*
Copyright 2020 Alfred Maler @alfrdmalr

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or 
(at your option) any later version.

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with this program. If not, see <http://www.gnu/org/licenses/>.
*/

#pragma once
#include QMK_KEYBOARD_H

enum shared_layers {
  _QWERTY,
  _SETTINGS,
  _SYMBOLS,
  _NAVIGATION,
  _NUMPAD
};

// KEYCODES ============================================================================
#define NUMSPACE LT(_NUMPAD, KC_SPC)
#define NAVLAYER MO(_NAVIGATION)
#define SYMLAYER MO(_SYMBOLS)
#define SETLAYER MO(_SETTINGS)
#define CTRLSHFT C(KC_LSFT)
#define WINUNDO  C(KC_Z)
#define WINCOPY  C(KC_C)
#define WINCUT   C(KC_X)
#define WINPASTE C(KC_V)

// convenience keycodes/aliases for base modifiers
// bottom row
#define K41    CTRLSHFT
#define K42    KC_LGUI
#define K43    KC_LALT
#define K44    SYMLAYER
#define K45    NUMSPACE
#define K46    NUMSPACE
#define K47    SYMLAYER
#define K48    KC_RALT
#define K49    SETLAYER
#define K4A    MU_TOG

// leftmost column
#define K00    KC_ESC
#define K10    KC_TAB
#define K20    NAVLAYER
#define K30    KC_LSFT
#define K40    KC_LCTL

// rightmost column
#define K0B        KC_BSPC
#define K1B        KC_BSPC
#define K1B_ALT    KC_DEL // for 5x12 boards, keep backspace as the top-left key and add delete key
#define K2B        KC_QUOT
#define K3B        KC_RSFT
#define K4B        KC_LEAD

// LAYOUT WRAPPERS =====================================================================
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)  LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x12_wrapper(...)  LAYOUT_ortho_5x12(__VA_ARGS__)

// KEYCODE GROUPS ======================================================================
// MISC 
#define ______TRANS______    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
#define ____NUMROW_L0____    KC_1,     KC_2,     KC_3,     KC_4,     KC_5
#define ____NUMROW_R0____    KC_6,     KC_7,     KC_8,     KC_9,     KC_0
#define _____BASE_L4_____    K41,      K42,      K43,      K44,      K45
#define _____BASE_R4_____    K46,      K47,      K48,      K49,      K4A

/* QWERTY ==============================================================================
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NAV  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SHFT |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | SHFT |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | C/S  | LGUI | LALT | SYMB |  NUM/SPACE  | SYMB | RALT | SETT | MUTG | LEAD |
 * `-----------------------------------------------------------------------------------'
 */

// LEFT
// - CORE
#define ____QWERTY_L1____    KC_Q,   KC_W,   KC_E,     KC_R,    KC_T
#define ____QWERTY_L2____    KC_A,   KC_S,   KC_D,     KC_F,    KC_G
#define ____QWERTY_L3____    KC_Z,   KC_X,   KC_C,     KC_V,    KC_B

// RIGHT
// - CORE
#define ____QWERTY_R1____    KC_Y,   KC_U,   KC_I,     KC_O,    KC_P
#define ____QWERTY_R2____    KC_H,   KC_J,   KC_K,     KC_L,    KC_SCLN
#define ____QWERTY_R3____    KC_N,   KC_M,   KC_COMM,  KC_DOT,  KC_SLSH

/* NUMPAD ==============================================================================
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |  F9  |  F10 |  F11 |  F12 |      | NLCK  |   7  |   8  |   9  |   -  | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ESC  |  F5  |  F6  |  F7  |  F8  | SPC  | SPC  |   4  |   5  |   6  |   +  | ENTR |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |  F1  |  F2  |  F3  |  F4  | ALT  | CAPS |   1  |   2  |   3  |   /  | TRNS |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS | TRNS | TRNS | TRNS | TRNS |    TRNS     |   0  |   ,  |   .  |   *  | TRNS |
 * `-----------------------------------------------------------------------------------'
 */

// LEFT
// - CORE
#define ____NUMPAD_L1____    KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO
#define ____NUMPAD_L2____    KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_SPC
#define ____NUMPAD_L3____    KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_LALT

// - MODS
#define ____NUMPAD_L4____    ______TRANS______
#define K00_NUM    KC_TRNS
#define K10_NUM    KC_TRNS
#define K20_NUM    KC_TRNS
#define K30_NUM    KC_TRNS
#define K40_NUM    KC_TRNS

// RIGHT
// - CORE
#define ____NUMPAD_R1____    KC_NLCK,  KC_7,  KC_8,  KC_9,  KC_MINS
#define ____NUMPAD_R2____    KC_SPC,   KC_4,  KC_5,  KC_6,  KC_PLUS
#define ____NUMPAD_R3____    KC_CAPS,  KC_1,  KC_2,  KC_3,  KC_SLSH

// - MODS
#define ____NUMPAD_R4____    KC_TRNS,  KC_0,  KC_COMM,  KC_DOT,  KC_ASTR
#define K0B_NUM    KC_TRNS
#define K1B_NUM    KC_TRNS
#define K2B_NUM    KC_ENT
#define K3B_NUM    KC_TRNS
#define K4B_NUM    KC_TRNS

/* SYMBOLS =============================================================================
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |   #  |   $  |   {  |   }  |      |      |   ^  |   *  |   |  |   ~  | TRNS |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |   <  |   >  |   (  |   )  |      |      |   -  |   +  |   &  |   \  |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |   !  |   @  |   [  |   ]  |      |      |   _  |   =  |   %  |   /  | SHFT |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS | TRNS | TRNS | TRNS | TRNS |    TRNS     | TRNS | TRNS | TRNS | TRNS | TRNS |
 * `-----------------------------------------------------------------------------------'
 */

// LEFT
// - CORE
#define ____SYMBOL_L1____    KC_HASH,     KC_DOLLAR,  KC_LCBR,  KC_RCBR,  KC_NO
#define ____SYMBOL_L2____    KC_LABK,     KC_RABK,    KC_LPRN,  KC_RPRN,  KC_NO
#define ____SYMBOL_L3____    KC_EXCLAIM,  KC_AT,      KC_LBRC,  KC_RBRC,  KC_NO

// - MODS
#define ____SYMBOL_L4____    ______TRANS______
#define K00_SYM    KC_TRNS
#define K10_SYM    KC_TRNS
#define K20_SYM    KC_TRNS
#define K30_SYM    KC_TRNS
#define K40_SYM    KC_TRNS

// RIGHT
// - CORE
#define ____SYMBOL_R1____    KC_NO,  KC_CIRC,  KC_ASTR,  KC_PIPE,  KC_TILD
#define ____SYMBOL_R2____    KC_NO,  KC_MINS,  KC_PLUS,  KC_AMPR,  KC_BSLS
#define ____SYMBOL_R3____    KC_NO,  KC_UNDS,  KC_EQL,   KC_PERC,  KC_SLSH

// - MODS
#define ____SYMBOL_R4____    ______TRANS______
#define K0B_SYM    KC_TRNS
#define K1B_SYM    KC_TRNS
#define K2B_SYM    KC_GRV
#define K3B_SYM    KC_TRNS
#define K4B_SYM    KC_TRNS

/* NAVIGATION ==========================================================================
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |      |      | SPC  |  F5  |      | INS  | HOME | END  | TAB  | DEL  | TRNS |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS | SHFT | CTRl | ALT  | GUI  |      | LEFT | DOWN | UP   | RGHT |      | ENTR |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS | UNDO | CUT  | COPY | PSTE |      | SPC  | PGDO | PGUP |      |      | TRNS |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS | TRNS | TRNS | TRNS | TRNS |     ESC     | TRNS | TRNS | TRNS | TRNS | TRNS |
 * `-----------------------------------------------------------------------------------'
 */

// LEFT
// - CORE
#define __NAVIGATION_L1__    KC_NO,    KC_NO,     KC_SPC,   KC_F5,     KC_NO
#define __NAVIGATION_L2__    KC_LSFT,  KC_LCTRL,  KC_LALT,  KC_LGUI,   KC_NO
#define __NAVIGATION_L3__    WINUNDO,  WINCUT,    WINCOPY,  WINPASTE,  KC_NO

// - MODS
#define __NAVIGATION_L4__    _______,  _______,  _______,  _______,  KC_ESC
#define K00_NAV    KC_TRNS
#define K10_NAV    KC_TRNS
#define K20_NAV    KC_TRNS
#define K30_NAV    KC_TRNS
#define K40_NAV    KC_TRNS

// RIGHT
// - CORE
#define __NAVIGATION_R1__    KC_INS,   KC_HOME,  KC_END,   KC_TAB,    KC_DEL
#define __NAVIGATION_R2__    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  KC_NO
#define __NAVIGATION_R3__    KC_SPC,   KC_PGDN,  KC_PGUP,  KC_NO,     KC_NO

// - MODS
#define __NAVIGATION_R4__    KC_ESC,  _______,  _______,  _______,  _______
#define K0B_NAV    KC_TRNS
#define K1B_NAV    KC_TRNS
#define K2B_NAV    KC_ENT
#define K3B_NAV    KC_TRNS
#define K4B_NAV    KC_TRNS

/* SETTINGS ============================================================================
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | DBUG |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ASTG |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
// LEFT
// - CORE
#define ___SETTINGS_L1___    _______,  DEBUG,   _______,  _______,  _______
#define ___SETTINGS_L2___    _______,  MU_MOD,  AU_ON,    AU_OFF,   AG_NORM
#define ___SETTINGS_L3___    MUV_DE,   MUV_IN,  MU_ON,    MU_OFF,   MI_ON

// - MODS
#define ___SETTINGS_L4___    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
#define K00_SET    KC_NO
#define K10_SET    KC_NO
#define K20_SET    KC_NO
#define K30_SET    KC_ASTG
#define K40_SET    KC_NO

// RIGHT 
// - CORE
#define ___SETTINGS_R1___    TERM_ON,  TERM_OFF,  _______,  _______,  _______
#define ___SETTINGS_R2___    _______,  _______,   _______,  _______,  _______
#define ___SETTINGS_R3___    _______,  _______,   _______,  _______,  _______

// - MODS
#define ___SETTINGS_R4___  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,  KC_NO
#define K0B_SET    KC_NO
#define K1B_SET    KC_NO
#define K2B_SET    KC_NO
#define K3B_SET    KC_NO
#define K4B_SET    KC_NO