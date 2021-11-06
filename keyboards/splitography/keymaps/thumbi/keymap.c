/* Copyright 2021 Alexis Jeandeau
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

// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.
//
// To flash splitography firmware
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   Reset keyboard or press hw reset button on base (hole)
//
//   cd qmk_firmware/keyboards/splitography
//   sudo make KEYMAP=<keymap> dfu
//
//   sudo make clean           (good practice before flashing)
//   sudo make KEYMAP=<keymap> (to compile check)
//
// Package requirements (for arch linux)
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   avr-gcc-atmel
//   avr-libc-atmel
//   dfu-programmer
//
// Notes
// ▔▔▔▔▔
//   ** E R G O   W I D E   S P L I T ** Layout
//
//   Autocompletion tap dance key pairs (),[],{} are available from the
//   number/symbol layer, as well as, numerous (un)shift key values
//
// Code
// ▔▔▔▔
//   This source is shamelessly based on the "default" planck layout
//
// Change history
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   See http://thedarnedestthing.com/colophon

#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_steno.h"

#include "config.h"
#include "splitography.h"

extern keymap_config_t keymap_config;

enum keyboard_layers {
    _BASE = 0,
    _SHIFT,
    _LSHIFT,
    _RSHIFT,
    _GUIFN,
    _SYMBOL,
    _LSYMBOL,
    _RSYMBOL,
    _MOUSE,
    _NUMBER,
    _FNCKEY,
    _PLOVER,
    _EDIT,
    _TTCAPS,
    _TTFNCKEY,
    _TTCURSOR,
    _TTMOUSE,
    _TTNUMBER,
    _TTREGEX,
    _END_LAYERS,
};

enum keyboard_keycodes {
    BASE = SAFE_RANGE,
    BASE1,
    BASE2,
    LT_I,  // pseudo LT   (_SYMBOL, KC_I)                for shifted key-codes, see process_record_user()
    ML_BSLS,
    ML_EQL,
    PLOVER,
    PLOEXIT,
    SA_DLR,   // pseudo ALT_T(S(KC_4))                      for shifted key-codes, see process_record_user()
    SC_RPRN,  // pseudo CTL_T(S(KC_0))                      for shifted key-codes, see process_record_user()
    SS_LPRN,  // pseudo SFT_T(S(KC_9))                      for shifted key-codes, see process_record_user()
    SA_PERC,  // pseudo ALT_T(S(KC_5))                      for shifted key-codes, see process_record_user()
    SG_TILD,  // pseudo GUI_T(S(KC_GRV))                    for shifted key-codes, see process_record_user()
    SL_I,     // pseudo LT   (_EDIT, S(KC_I))               for shifted key-codes, see process_record_user()
    SL_DEL,   // pseudo LT   (_EDIT, KC_DEL)                for shifted key-codes, see process_record_user()
    SL_BSPC,  // pseudo LT   (S(_MOUSE), KC_BSPC)
    SL_PIPE,  // pseudo LT   (_EDIT, S(KC_BSLS))            for shifted key-codes, see process_record_user()
    SL_TAB,   // pseudo LT   (S(_MOUSE), KC_TAB)
    SM_G,     // pseudo MT   (MOD_LGUI | MOD_LSFT, S(KC_G)) for shifted key-codes, see process_record_user()
    SM_H,     // pseudo MT   (MOD_LGUI | MOD_LSFT, S(KC_H)) for shifted key-codes, see process_record_user()
    SM_I,     // pseudo MT   (MOD_LSFT, S(KC_I))            for shifted key-codes, see process_record_user()
    SM_CIRC,  // pseudo GUI_T(S(KC_6))                      for shifted key-codes, see process_record_user()
    SM_DLR,   // pseudo SFT_T(S(KC_4))                      for shifted key-codes, see process_record_user()
    SM_PERC,  // pseudo ALT_T(S(KC_5))                      for shifted key-codes, see process_record_user()
    SM_LPRN,  // pseudo CTL_T(S(KC_9))                      for shifted key-codes, see process_record_user()
    SS_A,     // pseudo SFT_T(S(KC_A))
    SS_T,     // pseudo SFT_T(S(KC_T))
    TT_ESC,
#if defined(STENO_ENABLE)
    PS_STNA = STN_A,
    PS_STNO = STN_O,
    PS_STNE = STN_E,
    PS_STNU = STN_U,
#else
    LT_C = LT(_SYMBOL, KC_C),
    LT_V = LT(_NUMBER, KC_V),
    LT_N = LT(_FNCKEY, KC_N),
    LT_M = LT(_GUIFN, KC_M),
#endif
    PS_BASE,
};

// modifier keys
#define AT_B ALT_T(KC_B)
#define GT_C GUI_T(KC_C)
#define MT_E MT(MOD_LCTL | MOD_LALT, KC_E)
#define ST_A SFT_T(KC_A)
#define ST_SPC SFT_T(KC_SPC)
#if defined(HOME_MODS)
#    define HOME_Q GUI_T(KC_Q)
#    define HOME_H CTL_T(KC_H)
#    define HOME_E ALT_T(KC_E)
#    define HOME_A SFT_T(KC_A)
#    define HOME_T SFT_T(KC_T)
#    define HOME_R ALT_T(KC_R)
#    define HOME_S CTL_T(KC_S)
#    define HOME_W GUI_T(KC_W)
#else
#    define HOME_Q KC_Q
#    define HOME_H KC_H
#    define HOME_E KC_E
#    define HOME_A KC_A
#    define HOME_T KC_T
#    define HOME_R KC_R
#    define HOME_S KC_S
#    define HOME_W KC_W
#endif

#include "common/tapdance.inc"

// keycodes
#define ___x___ KC_TRNS
#define ___fn__ KC_TRNS
#if defined(_______)
#    undef _______
#endif
#define _______ KC_NO

#if defined(HASKELL)
#    define HS_COLN TD_COLN
#    define HS_LT TD_LT
#    define HS_GT TD_GT
#    define HS_EQL TD_EQL
#else
#    define HS_COLN KC_COLN
#    define HS_LT KC_LT
#    define HS_GT KC_GT
#    define HS_EQL KC_EQL
#endif

#define COPY LCTL(KC_C)
#define CUT LCTL(KC_X)
#define EOT LCTL(KC_D)
#define NAK LCTL(KC_U)
#define PASTE LCTL(KC_V)
#define UNDO LCTL(KC_Z)
#define TMCOPY LALT(LCTL(KC_C))
#define TMPASTE LALT(LCTL(KC_V))
#define LT_BSPC LT(_RSYMBOL, KC_BSPC)  // see process_record_user() for extended handling
#define TT_BSPC LT(_TTCURSOR, KC_BSPC)
#define LT_DEL LT(_EDIT, KC_DEL)
#define LT_ESC LT(_LSYMBOL, KC_ESC)
#define LT_I LT(_LSHIFT, KC_I)
#define OS_ALT OSM(MOD_LALT)
#define OS_CTL OSM(MOD_LCTL)
#define OS_GUI OSM(MOD_LGUI)
#define OS_SFT OSM(MOD_LSFT)

#if defined(CENTER_TT)
#    define CNTR_TL TT(_TTFNCKEY)
#    define CNTR_TR TT(_TTCAPS)  // pseudo capslock to avoid TT key_timer conflicts
#    define CNTR_HL TT(_TTCURSOR)
#    define CNTR_HR TT(_TTMOUSE)
#    define CNTR_BL TT(_TTNUMBER)
#    define CNTR_BR TT(_TTREGEX)
#else
#    define CNTR_TL OSM(MOD_LALT | MOD_LCTL)
#    define CNTR_TR OSM(MOD_LGUI | MOD_LCTL)
#    define CNTR_HL OSM(MOD_LALT | MOD_LSFT)
#    define CNTR_HR OSM(MOD_LGUI | MOD_LSFT)
#    define CNTR_BL TD(_CAPS)
#    define CNTR_BR OSM(MOD_LSFT | MOD_LCTL)
#endif

// ........................................................ Default Alpha Layout

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#include "base_layout.inc"
#include "common/steno_layout.inc"

// ...................................................... Number / Function Keys

#include "common/number_fkey_layout.inc"

// ......................................................... Symbol / Navigation

#include "common/symbol_guifn_layout.inc"

// ............................................................... Toggle Layers

#if defined(CENTER_TT)
#    include "common/toggle_layout.inc"
#endif

// ......................................................... Short Cuts / Adjust

#include "common/chord_layout.inc"

};

// ........................................................... User Keycode Trap

#include "common/keycode_functions.inc"

#define BASE_1 1
#define BASE_2 2
#define BASE_12 3
static uint8_t base_n    = 0;
static uint8_t down_rule = 0;  // (1) substitute keycode (2) keycode+shift, see tap_lt()

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BASE1:
            if (record->event.pressed) {
                base_n = base_n | BASE_1;
                if (base_n == BASE_12) {
                    base_layer(0);
                }
            } else {
                base_n = base_n & ~BASE_1;
            }
            return false;
        case BASE2:
            if (record->event.pressed) {
                base_n = base_n | BASE_2;
                if (base_n == BASE_12) {
                    base_layer(0);
                }
            } else {
                base_n = base_n & ~BASE_2;
            }
            return false;
#if defined(HOME_MODS)
        case HOME_Q:
        case HOME_W:
            tap_mods(record, KC_LGUI);
            break;
        case HOME_H:
        case HOME_S:
            tap_mods(record, KC_LCTL);
            break;
        case HOME_E:
        case HOME_R:
            tap_mods(record, KC_LALT);
            break;
        case ST_SPC:
            if (map_shift(record, KC_RSFT, NOSHIFT, KC_ENT)) {
                unregister_code(KC_ENT);
                return false;
            }
        case HOME_A:
            tap_mods(record, KC_LSFT);
            break;
        case SM_I:
            mt_shift(record, KC_LSFT, 0, KC_I);
        case HOME_T:
            tap_mods(record, KC_RSFT);  // note: SFT_T actually uses KC_LSFT
            break;
        // special shift layer mappings
        case KC_DOT:
            if (record->event.pressed) {
                down_rule = 2;
            }  // dot+space/enter+shift shortcut, see tap_lt()
            else {
                down_rule = 0;
            }
            if (map_shift(record, KC_RSFT, SHIFT, KC_GRV)) {
                return false;
            }
            if (map_shift(record, KC_LSFT, SHIFT, KC_SLSH)) {
                return false;
            }
            break;
        case KC_QUES:
            down_rule = 0;  // trap layer switching timimg issue between . and ?
            break;
        case KC_COMM:
            if (map_shift(record, KC_RSFT, SHIFT, KC_1)) {
                return false;
            }
            if (map_shift(record, KC_LSFT, SHIFT, KC_1)) {
                return false;
            }
            break;
#endif
#if defined(CENTER_TT)
        case TT_ESC:
            if (map_shift(record, KC_LSFT, NOSHIFT, KC_TAB)) {
                return false;
            }
            tt_clear();  // exit TT layer
            return false;
#endif
        case KC_TAB:
            if (record->event.pressed) {
                down_rule = 1;
            }  // tab+enter thumb roll, see tap_lt()
            else {
                down_rule = 0;
            }
            if (raise_number(record, LEFT)) {
                return false;
            }
            break;
        case OS_ALT:
            tap_mods(record, KC_LALT);
            break;
        case OS_CTL:
            tap_mods(record, KC_LCTL);
            break;
        case OS_GUI:
            tap_mods(record, KC_LGUI);
            break;
        case SM_G:
            mt_shift(record, KC_LALT, KC_LSFT, KC_G);
            break;
        case SA_PERC:
            mt_shift(record, KC_LALT, 0, KC_5);
            break;
        case SG_TILD:
            mt_shift(record, KC_LGUI, 0, KC_GRV);
            break;
        case LT_I:
            if (map_shift(record, KC_LSFT, NOSHIFT, KC_SPC)) {
                return false;
            }
            if (raise_number(record, RIGHT)) {
                return false;
            }
            tap_layer(record, _LSHIFT);
            break;
        case TD_ENT:
            if (record->event.pressed) {
                tap_rule = down_rule;
            }  // down_rule persistance for tap_lt()
            break;
        case TD_SPC:
            if (record->event.pressed) {
                tap_rule = down_rule;
            }  // down_rule persistance for tap_lt()
            // trap potential repeating enter caused by tap dance definition
            if (map_shift(record, KC_RSFT, NOSHIFT, KC_ENT)) {
                unregister_code(KC_ENT);
                return false;
            }
            tap_layer(record, _RSHIFT);
            break;
        case LT_ESC:
            if (map_shift(record, KC_LSFT, NOSHIFT, KC_TAB)) {
                return false;
            }
            if (raise_number(record, LEFT)) {
                return false;
            }
#if defined(CENTER_TT)
            if (tt_keycode != 0) {
                tt_clear();  // exit TT layer
                return false;
            }
#endif
            tap_layer(record, _LSYMBOL);
            thumb_roll(record, LEFT, 0, 0, 0, _LSYMBOL, _RSYMBOL);
            break;
        case SL_TAB:
            thumb_roll(record, LEFT, SHIFT, KC_TAB, 0, _MOUSE, _RSYMBOL);
            break;
        case SL_DEL:
            thumb_roll(record, RIGHT, NOSHIFT, KC_DEL, 0, _MOUSE, _LSYMBOL);
            break;
        case TT_BSPC:
            if (map_shift(record, KC_RSFT, NOSHIFT, KC_DEL)) {
                return false;
            }
            break;
        case LT_BSPC:
            if (map_shift(record, KC_RSFT, NOSHIFT, KC_DEL)) {
                return false;
            }
            tap_layer(record, _RSYMBOL);
            thumb_roll(record, RIGHT, 0, 0, 0, _RSYMBOL, _LSYMBOL);
            break;
#if defined(CENTER_TT)
        case CNTR_TL:
        case CNTR_TR:
        case CNTR_HL:
        case CNTR_HR:
        case CNTR_BL:
        case CNTR_BR:
            // return to base layer first if different TT layer selected
            if (tt_keycode != keycode && tt_keycode != 0) {
                tt_clear();
            }
            tt_escape(record, keycode);
            break;
#endif
        case PLOVER:
            steno(record);
            return false;
        default:
            key_timer = 0;  // regular keycode, clear timer in custom/keycode_functions.h
    }
    return true;
}

#include "common/init.inc"
