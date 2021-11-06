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
// To flash planck firmware
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   Reset keyboard or press hw reset button on base (hole)
//
//   cd qmk_firmware/keyboards/planck
//   sudo make KEYMAP=sdothum dfu
//
//   sudo make clean          (good practice before flashing)
//   sudo make KEYMAP=sdothum (to compile check)
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
//   The navigation pad provides a single hand right thumb activated cluster
//   with left hand modifiers
//
// Modifier clusters
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   The num and sym keys together access the navigation pad layer
//
//   ,-----------------------------------------------------------------------------------.
//   | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
//   `-----------------------------------------------------------------------------------'
//
// Hint
// ▔▔▔▔
//   For sculpted keycaps such as Cherry or OEM profile, reverse the Alt, Num,
//   Shift, Shift, Nav, Sym keycaps for more ergonomic thumb orientation and
//   actuation
//
// Code
// ▔▔▔▔
//   This source is shamelessly based on the "default" planck layout
//
// Change history
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   See http://thedarnedestthing.com/planck%20constant
//   See http://thedarnedestthing.com/planck%20done

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
#define AT_DOWN ALT_T(KC_DOWN)
#define CT_RGHT CTL_T(KC_RGHT)
#define GT_C GUI_T(KC_C)
#define GT_UP GUI_T(KC_UP)
#define MT_E MT(MOD_LCTL | MOD_LALT, KC_E)
#define MT_X MT(MOD_LALT | MOD_LSFT, KC_X)
#define ST_A SFT_T(KC_A)
#if defined(HOME_MODS)
#    define HOME_K CTL_T(KC_K)
#    define HOME_H GUI_T(KC_H)
#    define HOME_E ALT_T(KC_E)
#    define HOME_A SFT_T(KC_A)
#    define HOME_T SFT_T(KC_T)
#    define HOME_R ALT_T(KC_R)
#    define HOME_S GUI_T(KC_S)
#    define HOME_W CTL_T(KC_W)
#else
#    define HOME_K KC_K
#    define HOME_H KC_H
#    define HOME_E KC_E
#    define HOME_A KC_A
#    define HOME_T KC_T
#    define HOME_R KC_R
#    define HOME_S KC_S
#    define HOME_W KC_W
#endif

#define S_DOWN S(KC_DOWN)
#define S_RGHT S(KC_RGHT)
#define S_UP S(KC_UP)
#define S_TAB S(KC_TAB)

// keycodes
#define ___x___ KC_TRNS
#define ___fn__ KC_TRNS
#if defined(_______)
#    undef _______
#endif
#define _______ KC_NO

#define COPY LCTL(KC_C)
#define CUT LCTL(KC_X)
#define EOT LCTL(KC_D)
#define NAK LCTL(KC_U)
#define PASTE LCTL(KC_V)
#define UNDO LCTL(KC_Z)
#define TMCOPY LALT(LCTL(KC_C))
#define TMPASTE LALT(LCTL(KC_V))
#define LT_BSLS LT(_MOUSE, KC_BSLS)   // see process_record_user() for extended handling
#define LT_BSPC LT(_SYMBOL, KC_BSPC)  // see process_record_user() for extended handling
#define LT_ESC LT(_NUMBER, KC_ESC)
#define LT_TAB LT(_FNCKEY, KC_TAB)
#define ADJUST MO(_EDIT)
#define OS_ALT OSM(MOD_LALT)
#define OS_CTL OSM(MOD_LCTL)
#define OS_GUI OSM(MOD_LGUI)
#define OS_SFT OSM(MOD_LSFT)
#define OS_CALT OSM(MOD_LALT | MOD_LCTL)
#define OS_CGUI OSM(MOD_LGUI | MOD_LCTL)
#define OS_CSFT OSM(MOD_LSFT | MOD_LCTL)
#define OS_SALT OSM(MOD_LALT | MOD_LSFT)
#define OS_SGUI OSM(MOD_LGUI | MOD_LSFT)

#if defined(CENTER_TT)
#    define CNTR_TL TT(_TTFNCKEY)
#    define CNTR_TR KC_CAPS
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

#if defined(THUMB_0)
#    define LT_EQL LT(_EDIT, KC_EQL)
#else
#    define LT_0 LT(_EDIT, KC_0)
#endif
#if !defined(SHIFT_SYMBOLS)
#    define LT_A LT(_NUMSYM, KC_A)
#    define LT_LFTX LT(_SYMREG, KC_LEFT)
#endif

#include "common/tapdance.inc"

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
static uint8_t base_n = 0;

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
        case AT_DOWN:
#if defined(HOME_MODS)
        case HOME_E:
        case HOME_R:
#endif
            tap_mods(record, KC_LALT);
            break;
        case CT_RGHT:
#if defined(HOME_MODS)
        case HOME_K:
        case HOME_W:
#endif
            tap_mods(record, KC_LCTL);
            break;
        case GT_UP:
#if defined(HOME_MODS)
        case HOME_H:
        case HOME_S:
#endif
            tap_mods(record, KC_LGUI);
            break;
#if defined(HOME_MODS)
        case HOME_A:
        case HOME_T:
            tap_mods(record, KC_LSFT);
            break;
#endif
#if defined(CENTER_TT)
        case TT_ESC:
            tt_clear();  // exit TT layer
            return false;
#endif
        case LT_ESC:
#if defined(CENTER_TT)
            if (tt_keycode != 0) {
                tt_clear();  // exit TT layer
                return false;
            }
#endif
            tap_layer(record, _NUMBER);
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
        case SM_CIRC:
            // GUI_T(S(KC_6))
            mt_shift(record, KC_LGUI, 0, KC_6);
            break;
        case SM_DLR:
            // SFT_T(S(KC_4))
            mt_shift(record, KC_LSFT, 0, KC_4);
            break;
        case SM_G:
            // MT(MOD_LALT | MOD_LSFT, S(KC_G))
            mt_shift(record, KC_LALT, KC_LSFT, KC_G);
            break;
        case SM_LPRN:
            // CTL_T(S(KC_9))
            mt_shift(record, KC_LCTL, 0, KC_9);
            break;
        case SM_PERC:
            // ALT_T(S(KC_5))
            mt_shift(record, KC_LALT, 0, KC_5);
            break;
        case SL_PIPE:
            // LT (_EDIT, S(KC_BSLS)) emulation
            lt_shift(record, SHIFT, KC_BSLS, _EDIT);
            break;
        case SL_TAB:
            // LT (_FNCKEY, S(KC_TAB)) emulation
            lt_shift(record, SHIFT, KC_TAB, _FNCKEY);
            break;
        case TD_ENT:
            tap_layer(record, _RSHIFT);
            // LT (_RSHIFT, KC_ENT) emulation, see tap dance enter
            break;
        case LT_BSLS:
            tap_layer(record, _MOUSE);
            // LT (_MOUSE, KC_BSLS) left right combination layer, see #define LT_BSLS
            thumb_roll(record, LEFT, 0, 0, 0, _MOUSE, _SYMBOL);
            break;
        case LT_BSPC:
            tap_layer(record, _SYMBOL);
            // LT (_SYMBOL, KC_LEFT) left right combination layer
            thumb_roll(record, RIGHT, 0, 0, 0, _SYMBOL, _LSHIFT);
            break;
        case SL_DEL:
            tap_layer(record, _MOUSE);
            // LT (_MOUSE, S(KC_DEL)) left right combination layer
            thumb_roll(record, RIGHT, NOSHIFT, KC_DEL, 0, _MOUSE, _LSHIFT);
            break;
        case TD_SPC:
            tap_layer(record, _LSHIFT);
            // LT (_LSHIFT, KC_SPC) left right combination layer, see tap dance TD_SPC
            thumb_roll(record, LEFT, 0, 0, 0, _LSHIFT, _SYMBOL);
            break;
#if defined(CENTER_TT)
        case CNTR_TL:
        case CNTR_TR:
        case CNTR_HL:
        case CNTR_HR:
        case CNTR_BL:
        case CNTR_BR:
            if (tt_keycode != keycode && tt_keycode != 0) {
                tt_clear();  // return to base layer first if different TT layer selected
            }
            tt_keycode = keycode;
            break;
#endif
        case PS_BASE:
            if (record->event.pressed) {
                base_layer(0);
            }
            return false;
        case PLOVER:
            steno(record);
            return false;
        case PLOEXIT:
            steno_exit(record);
            return false;
    }
    return true;
}

#include "common/init.inc"
