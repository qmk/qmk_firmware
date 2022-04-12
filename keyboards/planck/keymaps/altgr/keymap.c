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
//   #define PRIVATE_STRING includes private_string.h, a user defined code
//   block for the PRIV tap dance e.g. SEND_STRING("secret messape"),
//   see function private()
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
//   #ifdef/#endif block structures are not indented, as syntax highlighting
//   in vim is sufficient for identification
//
//   c++ commenting style is used throughout
//
// Change history
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   See http://thedarnedestthing.com/planck%20constant
//   See http://thedarnedestthing.com/planck%20done



//                === N O T E ===
//
// sudo CPATH=<keymap.c directory>/common make ...


#include QMK_KEYBOARD_H
#ifdef STENO_ENABLE
#include "keymap_steno.h"
#endif

extern keymap_config_t keymap_config;

enum planck_layers {
  _BASE = 0
 ,_SHIFT
 ,_LSHIFT
 ,_RSHIFT
 ,_PLOVER
 ,_NUMBER
 ,_SYMBOL
 ,_FNCKEY
 ,_MOUSE
#ifdef CENTER_TT
 ,_TTNUMBER
 ,_TTREGEX
 ,_TTFNCKEY
 ,_TTCURSOR
 ,_TTMOUSE
#endif
#ifndef SHIFT_SYMBOLS
 ,_NUMSYM
 ,_SYMREG
#endif
 ,_EDIT
 ,_QWERTY
 ,_ADJUST
 ,_END_LAYERS
};

enum planck_keycodes {
  BASE = SAFE_RANGE
 ,BASE1
 ,BASE2
 ,PLOVER
 ,PLOEXIT
 ,SM_CIRC   // pseudo GUI_T(S(KC_6))                      for shifted key-codes, see process_record_user()
 ,SM_DLR    // pseudo SFT_T(S(KC_4))                      for shifted key-codes, see process_record_user()
 ,SM_G      // pseudo MT   (MOD_LALT | MOD_LSFT, S(KC_G)) for shifted key-codes, see process_record_user()
 ,SM_K      // pseudo MT   (MOD_LGUI | MOD_LSFT, S(KC_K)) for shifted key-codes, see process_record_user()
 ,SM_PERC   // pseudo ALT_T(S(KC_5))                      for shifted key-codes, see process_record_user()
 ,SM_LPRN   // pseudo CTL_T(S(KC_9))                      for shifted key-codes, see process_record_user()
 ,SM_W      // pseudo MT   (MOD_LGUI | MOD_LSFT, S(KC_W)) for shifted key-codes, see process_record_user()
 ,SL_LEFT   // pseudo LT   (_MOUSE, S(KC_LEFT))           for shifted key-codes, see process_record_user()
 ,SP_DEL    // pseudo LT   (_MOUSE, KC_DEL)               for shifted key-codes, see process_record_user()
 ,SL_PIPE   // pseudo LT   (_ADJUST, S(KC_BSLS))          for shifted key-codes, see process_record_user()
 ,SL_TAB    // pseudo LT   (_FNCKEY, S(KC_TAB))           for shifted key-codes, see process_record_user()
#ifdef CENTER_TT
 ,TT_ESC
#endif
#ifdef STENO_ENABLE
 ,PS_STNA = STN_A
 ,PS_STNO = STN_O
 ,PS_STNE = STN_E
 ,PS_STNU = STN_U
#else
 ,LT_C    = LT (_NUMBER, KC_C)
 ,LT_V    = LT (_FNCKEY, KC_V)
 ,LT_N    = LT (_EDIT,   KC_N)
 ,LT_M    = LT (_SYMBOL, KC_M)
#endif
 ,PS_BASE
};

// modifier keys
#define AT_B    ALT_T(KC_B)
#define AT_DOWN ALT_T(KC_DOWN)
#define CT_RGHT CTL_T(KC_RGHT)
#define GT_C    GUI_T(KC_C)
#define GT_UP   GUI_T(KC_UP)
#define MT_E    MT   (MOD_LCTL | MOD_LALT, KC_E)
#define MT_X    MT   (MOD_LALT | MOD_LSFT, KC_X)
#define ST_A    SFT_T(KC_A)
#ifdef HOME_MODS
#define HOME_K  GUI_T(KC_K)
#define HOME_H  CTL_T(KC_H)
#define HOME_E  ALT_T(KC_E)
#define HOME_A  SFT_T(KC_A)
#if defined(BEAKLMU) || defined(BEAKLSP) || defined(BEAKLGR)
#define HOME_T  SFT_T(KC_T)
#define HOME_R  ALT_T(KC_R)
#define HOME_S  CTL_T(KC_S)
#define HOME_W  GUI_T(KC_W)
#else
#define HOME_T  SFT_T(KC_T)
#define HOME_S  ALT_T(KC_S)
#define HOME_N  GUI_T(KC_N)
#define HOME_B  CTL_T(KC_B)
#endif
#else
#define HOME_K  KC_K
#define HOME_H  KC_H
#define HOME_E  KC_E
#define HOME_A  KC_A
#define HOME_T  KC_T
#define HOME_S  KC_S
#define HOME_N  KC_N
#define HOME_B  KC_B
#endif

#define S_DOWN  S    (KC_DOWN)
#define S_LEFT  S    (KC_LEFT)
#define S_RGHT  S    (KC_RGHT)
#define S_TAB   S    (KC_TAB)
#define S_UP    S    (KC_UP)

#include "common/tapdance.h"

// keycodes
#define ___x___ KC_TRNS
#define ___fn__ KC_TRNS
#undef  _______
#define _______ KC_NO

#define COPY    LCTL(KC_C)
#define CUT     LCTL(KC_X)
#define EOT     LCTL(KC_D)
#define NAK     LCTL(KC_U)
#define PASTE   LCTL(KC_V)
#define UNDO    LCTL(KC_Z)
#define TMCOPY  LALT(LCTL(KC_C))
#define TMPASTE LALT(LCTL(KC_V))
#define LT_BSLS LT  (_MOUSE,  KC_BSLS)      // see process_record_user() for extended handling
#define LT_BSPC LT  (_EDIT,   KC_BSPC)
#define SP_LEFT LT  (_EDIT,   KC_LEFT)
#define LT_ESC  LT  (_NUMBER, KC_ESC)
#define LT_LEFT LT  (_SYMBOL, KC_LEFT)      // see process_record_user() for extended handling
#define SP_BSPC LT  (_SYMBOL, KC_BSPC)      // see process_record_user() for extended handling
#define LT_TAB  LT  (_FNCKEY, KC_TAB)
#define LT_INS  LT  (_FNCKEY, KC_INS)
#define LT_ALTG LT  (_FNCKEY, KC_RALT)
#define ADJUST  MO  (_ADJUST)
#define OS_ALT  OSM (MOD_LALT)
#define OS_CTL  OSM (MOD_LCTL)
#define OS_GUI  OSM (MOD_LGUI)
#define OS_SFT  OSM (MOD_LSFT)
#define OS_CALT OSM (MOD_LALT | MOD_LCTL)
#define OS_CGUI OSM (MOD_LGUI | MOD_LCTL)
#define OS_CSFT OSM (MOD_LSFT | MOD_LCTL)
#define OS_SALT OSM (MOD_LALT | MOD_LSFT)
#define OS_SGUI OSM (MOD_LGUI | MOD_LSFT)

#ifdef CENTER_TT
#ifdef BEAKLSP
#define CNTR_TL OSM (MOD_LSFT)
#else
#define CNTR_TL TT  (_TTFNCKEY)
#endif
#define CNTR_TR KC_CAPS
#define CNTR_HL TT  (_TTCURSOR)
#define CNTR_HR TT  (_TTMOUSE)
#define CNTR_BL TT  (_TTNUMBER)
#define CNTR_BR TT  (_TTREGEX)
#else
#define CNTR_TL OSM (MOD_LALT | MOD_LCTL)
#define CNTR_TR OSM (MOD_LGUI | MOD_LCTL)
#define CNTR_HL OSM (MOD_LALT | MOD_LSFT)
#define CNTR_HR OSM (MOD_LGUI | MOD_LSFT)
#define CNTR_BL TD  (_CAPS)
#define CNTR_BR OSM (MOD_LSFT | MOD_LCTL)
#endif

#ifdef THUMB_0
#define LT_EQL  LT  (_ADJUST, KC_EQL)
#else
#define LT_0    LT  (_ADJUST, KC_0)
#endif
#ifndef SHIFT_SYMBOLS
#define LT_A    LT  (_NUMSYM, KC_A)
#define LT_LFTX LT  (_SYMREG, KC_LEFT)
#endif

// ........................................................ Default Alpha Layout

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#include "beakl.h"
#include "colemak.h"
#include "qwerty.h"
#include "common/steno_layout.h"

// ...................................................... Number / Function Keys

#include "common/number_fkey_layout.h"

// ......................................................... Symbol / Navigation

#include "common/symbol_guifn_layout.h"

// ............................................................... Toggle Layers

#ifdef CENTER_TT
#include "common/toggle_layout.h"
#endif

// ......................................................... Short Cuts / Adjust

#include "common/chord_layout.h"

};

// ...................................................................... Sounds

#include "common/sounds.h"

// ........................................................... User Keycode Trap

#include "common/keycode_functions.h"

#define BASE_1  1
#define BASE_2  2
#define BASE_12 3
static uint8_t base_n = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    case BASE1:
      if (record->event.pressed) {
        base_n = base_n | BASE_1;
        if (base_n == BASE_12) {
          base_layer();
        }
      }
      else {
        base_n = base_n & ~BASE_1;
      }
      return false;
    case BASE2:
      if (record->event.pressed) {
        base_n = base_n | BASE_2;
        if (base_n == BASE_12) {
          base_layer();
        }
      }
      else {
        base_n = base_n & ~BASE_2;
      }
      return false;
    case AT_DOWN:
#ifdef HOME_MODS
    case HOME_E:
#if defined(BEAKLMU) || defined(BEAKLSP) || defined(BEAKLGR)
    case HOME_R:
#else
    case HOME_S:
#endif
#endif
      tap_mods(record, KC_LALT);
      break;
    case CT_RGHT:
#ifdef HOME_MODS
    case HOME_K:
#if defined(BEAKLMU) || defined(BEAKLSP) || defined(BEAKLGR)
    case HOME_W:
#else
    case HOME_B:
#endif
#endif
      tap_mods(record, KC_LGUI);
      break;
    case GT_UP:
#ifdef HOME_MODS
    case HOME_H:
#if defined(BEAKLMU) || defined(BEAKLSP) || defined(BEAKLGR)
    case HOME_S:
#else
    case HOME_N:
#endif
#endif
      tap_mods(record, KC_LCTL);
      break;
#ifdef HOME_MODS
    case HOME_A:
    case HOME_T:
      tap_mods(record, KC_LSFT);
      break;
#endif
#ifdef CENTER_TT
    case TT_ESC:
      clear_tt();                           // exit TT layer
      return false;
#endif
    case LT_ESC:
#ifdef CENTER_TT
      if (tt_keycode != 0) {
        clear_tt();                         // exit TT layer
        return false;
      }
#endif
      tap_layer(record, _NUMBER);
      break;
    case LT_LEFT:
    case SP_BSPC:
      tap_layer(record, _SYMBOL);
      // LT (_SYMBOL, KC_LEFT) left right combination layer
      thumb_layer(record, RIGHT, 0, 0, _SYMBOL, _LSHIFT);
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
    case SM_K:
      // MT(MOD_LGUI | MOD_LSFT, S(KC_K))
      mt_shift(record, KC_LGUI, KC_LSFT, KC_K);
      break;
    case SM_W:
      // MT(MOD_LGUI | MOD_LSFT, S(KC_W))
      mt_shift(record, KC_LGUI, KC_LSFT, KC_W);
      break;
    case SM_LPRN:
      // CTL_T(S(KC_9))
      mt_shift(record, KC_LCTL, 0, KC_9);
      break;
    case SM_PERC:
      // ALT_T(S(KC_5))
      mt_shift(record, KC_LALT, 0, KC_5);
      break;
    case LT_BSLS:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, KC_BSLS) left right combination layer, see #define LT_BSLS
      thumb_layer(record, LEFT, 0, 0, _MOUSE, _SYMBOL);
      break;
    case SL_LEFT:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_LEFT)) left right combination layer
      thumb_layer(record, RIGHT, SHIFT, KC_LEFT, _MOUSE, _LSHIFT);
      break;
    case SP_DEL:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_LEFT)) left right combination layer
      thumb_layer(record, RIGHT, NOSHIFT, KC_DEL, _MOUSE, _LSHIFT);
      break;
    case SL_PIPE:
      // LT (_ADJUST, S(KC_BSLS)) emulation
      lt_shift(record, KC_BSLS, _ADJUST);
      break;
    case SL_TAB:
      // LT (_FNCKEY, S(KC_TAB)) emulation
      lt_shift(record, KC_TAB, _FNCKEY);
      break;
    case TD_ENT:
      tap_layer(record, _RSHIFT);
      // LT (_RSHIFT, KC_ENT) emulation, see tap dance enter
      break;
    case TD_SPC:
      tap_layer(record, _LSHIFT);
      // LT (_LSHIFT, KC_SPC) left right combination layer, see tap dance TD_SPC
      thumb_layer(record, LEFT, 0, 0, _LSHIFT, _SYMBOL);
      break;
#ifdef CENTER_TT
    case CNTR_TL:
    case CNTR_TR:
    case CNTR_HL:
    case CNTR_HR:
    case CNTR_BL:
    case CNTR_BR:
      if (tt_keycode != keycode && tt_keycode != 0) {
        clear_tt();                         // return to base layer first if different TT layer selected
      }
      tt_keycode = keycode;
      break;
#endif
// #ifdef STENO_ENABLE
//     case PS_STNA:
//       stn_layer(record, STN_A, _NUMBER);
//       break;
//     case PS_STNO:
//       stn_layer(record, STN_O, _FNCKEY);
//       break;
//     case PS_STNE:
//       stn_layer(record, STN_E, _EDIT);
//       break;
//     case PS_STNU:
//       stn_layer(record, STN_U, _SYMBOL);
//       break;
// #endif
    case PS_BASE:
      if (record->event.pressed) {
        base_layer();
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

#include "common/init.h"
