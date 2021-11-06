// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.
//
// To flash planck firmware
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
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
//   The navigation pad provides a single hand right thumb activated cluster
//   with left hand modifiers
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
//   See http://thedarnedestthing.com/colophon



//                === N O T E ===
//
// sudo CPATH=<keymap.c directory>/common make ...


#include "config.h"
#include "splitography.h"
#include "action_layer.h"
#ifdef STENO_ENABLE
#include "keymap_steno.h"
#endif
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum keyboard_layers {
  _BASE = 0
 ,_SHIFT
 ,_LSHIFT
 ,_RSHIFT
 ,_GUIFN
 ,_SYMBOL
 ,_LSYMBOL
 ,_RSYMBOL
 ,_MOUSE
 ,_NUMBER
 ,_FNCKEY
 ,_PLOVER
 ,_EDIT
 ,_TTCAPS
 ,_TTFNCKEY
 ,_TTCURSOR
 ,_TTMOUSE
 ,_TTNUMBER
 ,_TTREGEX
 ,_END_LAYERS
};

enum keyboard_keycodes {
  BASE = SAFE_RANGE
 ,BASE1
 ,BASE2
 ,LT_I      // pseudo LT   (_SYMBOL, KC_I) for shifted key-codes, see process_record_user()
 ,ML_BSLS
 ,ML_EQL
 ,PLOVER
 ,PLOEXIT
 ,SA_DLR    // pseudo ALT_T(S(KC_4))                      for shifted key-codes, see process_record_user()
 ,SC_RPRN   // pseudo CTL_T(S(KC_0))                      for shifted key-codes, see process_record_user()
 ,SS_LPRN   // pseudo SFT_T(S(KC_9))                      for shifted key-codes, see process_record_user()
 ,SA_PERC   // pseudo ALT_T(S(KC_5))                      for shifted key-codes, see process_record_user()
 ,SG_TILD   // pseudo GUI_T(S(KC_GRV))     for shifted key-codes, see process_record_user()
 ,SL_I      // pseudo LT   (_EDIT, S(KC_I))               for shifted key-codes, see process_record_user()
 ,SL_DEL    // pseudo LT   (_EDIT, KC_DEL)                for shifted key-codes, see process_record_user()
 ,SL_BSPC   // pseudo LT   (S(_MOUSE), KC_BSPC)
 ,SL_PIPE   // pseudo LT   (_EDIT, S(KC_BSLS))            for shifted key-codes, see process_record_user()
 ,SL_TAB    // pseudo LT   (S(_MOUSE), KC_TAB)
 ,SM_G      // pseudo MT   (MOD_LGUI | MOD_LSFT, S(KC_G)) for shifted key-codes, see process_record_user()
 ,SM_H      // pseudo MT   (MOD_LGUI | MOD_LSFT, S(KC_H)) for shifted key-codes, see process_record_user()
 ,SM_I      // pseudo MT   (MOD_LSFT, S(KC_I))            for shifted key-codes, see process_record_user()
 ,SM_CIRC   // pseudo GUI_T(S(KC_6))                      for shifted key-codes, see process_record_user()
 ,SM_DLR    // pseudo SFT_T(S(KC_4))                      for shifted key-codes, see process_record_user()
 ,SM_PERC   // pseudo ALT_T(S(KC_5))                      for shifted key-codes, see process_record_user()
 ,SM_LPRN   // pseudo CTL_T(S(KC_9))                      for shifted key-codes, see process_record_user()
 ,SM_W      // pseudo MT   (MOD_LGUI | MOD_LSFT, S(KC_W)) for shifted key-codes, see process_record_user()
 ,SS_A      // pseudo SFT_T(S(KC_A))
 ,SS_T      // pseudo SFT_T(S(KC_T))
 ,TT_ESC
#ifdef STENO_ENABLE
 ,PS_STNA = STN_A
 ,PS_STNO = STN_O
 ,PS_STNE = STN_E
 ,PS_STNU = STN_U
#else
 ,LT_C    = LT (_SYMBOL, KC_C)
 ,LT_V    = LT (_NUMBER, KC_V)
 ,LT_N    = LT (_FNCKEY, KC_N)
 ,LT_M    = LT (_GUIFN, KC_M)
#endif
 ,PS_BASE
};

// modifier keys
#define AT_B    ALT_T(KC_B)
#define GT_C    GUI_T(KC_C)
#define MT_E    MT   (MOD_LCTL | MOD_LALT, KC_E)
#define ST_A    SFT_T(KC_A)
#ifdef HOME_MODS
#define HOME_H  GUI_T(KC_H)
#define HOME_I  CTL_T(KC_I)
#define HOME_E  ALT_T(KC_E)
#define HOME_A  SFT_T(KC_A)
#define HOME_T  SFT_T(KC_T)
#define HOME_R  ALT_T(KC_R)
#define HOME_S  CTL_T(KC_S)
#define HOME_W  GUI_T(KC_W)
#else
#define HOME_H  KC_H
#define HOME_I  KC_I
#define HOME_E  KC_E
#define HOME_A  KC_A
#define HOME_T  KC_T
#define HOME_R  KC_R
#define HOME_S  KC_S
#define HOME_W  KC_W
#endif

#define S_DOWN  S    (KC_DOWN)
#define S_TAB   S    (KC_TAB)

#include "common/tapdance.h"

// keycodes
#define ___x___ KC_TRNS
#define ___fn__ KC_TRNS
#ifdef _______
#undef _______
#endif
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
#define LT_BSPC LT  (_SYMBOL, KC_BSPC)      // see process_record_user() for extended handling
#define LT_ESC  LT  (_NUMBER, KC_ESC)
#define ADJUST  MO  (_EDIT)
#define OS_ALT  OSM (MOD_LALT)
#define OS_CTL  OSM (MOD_LCTL)
#define OS_GUI  OSM (MOD_LGUI)
#define OS_SFT  OSM (MOD_LSFT)

#ifdef CENTER_TT
#define CNTR_TL TT  (_TTFNCKEY)
#define CNTR_TR     KC_CAPS
#define CNTR_HL TT  (_TTCURSOR)
#define CNTR_HR TT  (_TTMOUSE)
#define CNTR_BL TT  (_TTNUMBER)
#define CNTR_BR TT  (_TTREGEX)
#else
#define CNTR_TL OSM (MOD_LALT | MOD_LCTL)
#define CNTR_TR OSM (MOD_LGUI | MOD_LCTL)
#define CNTR_HL OSM (MOD_LALT | MOD_LSFT)
#define CNTR_HR OSM (MOD_LGUI | MOD_LSFT)
#define CNTR_BL TD(_CAPS)
#define CNTR_BR OSM (MOD_LSFT | MOD_LCTL)
#endif

// LT can only reference layers 0-15
#ifdef THUMB_0
#define LT_EQL  LT  (_EDIT, KC_EQL)
#else
#define LT_0    LT  (_EDIT, KC_0)
#endif

// ........................................................ Default Alpha Layout

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#include "base_layout.h"
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
          base_layer(0);
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
          base_layer(0);
        }
      }
      else {
        base_n = base_n & ~BASE_2;
      }
      return false;
#ifdef HOME_MODS
    case HOME_E:
    case HOME_R:
      tap_mods(record, KC_LALT);
      break;
    case HOME_H:
    case HOME_W:
      tap_mods(record, KC_LGUI);
      break;
    case HOME_I:
    case HOME_S:
      tap_mods(record, KC_LCTL);
      break;
    case HOME_A:
      tap_mods(record, KC_LSFT);
      break;
    case HOME_T:
      tap_mods(record, KC_RSFT);            // note: SFT_T actually uses KC_LSFT
      break;
    // special shift layer mappings
    case KC_DOT:
      if (hr_shift(record, KC_RSFT, SHIFT, KC_GRV)) {
        return false;
      }
      break;
    case KC_COMM:
      if (hr_shift(record, KC_RSFT, NOSHIFT, KC_GRV)) {
        return false;
      }
      break;
#endif
#ifdef CENTER_TT
    case TT_ESC:
      tt_clear();                           // exit TT layer
      return false;
#endif
    case LT_ESC:
#ifdef HOME_MODS
      if (hr_shift(record, KC_RSFT, SHIFT, KC_TAB)) {
        return false;
      }
#endif
#ifdef CENTER_TT
      if (tt_keycode != 0) {
        tt_clear();                         // exit TT layer
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
    case SM_H:
      // MT(MOD_LGUI | MOD_LSFT, S(KC_K))
      mt_shift(record, KC_LGUI, KC_LSFT, KC_H);
      break;
    case SM_W:
      // MT(MOD_LGUI | MOD_LSFT, S(KC_W))
      mt_shift(record, KC_LGUI, KC_LSFT, KC_W);
      break;
    case SM_PERC:
      // ALT_T(S(KC_5))
      mt_shift(record, KC_LALT, 0, KC_5);
      break;
    case LT_BSLS:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, KC_BSLS) left right combination layer, see #define LT_BSLS
      thumb_roll(record, LEFT, 0, 0, 0, _MOUSE, _SYMBOL);
      break;
    case LT_BSPC:
#ifdef HOME_MODS
      if (hr_shift(record, KC_LSFT, NOSHIFT, KC_DEL)) {
        return false;
      }
#endif
      tap_layer(record, _SYMBOL);
      // LT (_SYMBOL, KC_LEFT) left right combination layer
      thumb_roll(record, RIGHT, 0, 0, 0, _SYMBOL, _LSYMBOL);
      break;
    case SL_DEL:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_DEL)) left right combination layer
      thumb_roll(record, RIGHT, NOSHIFT, KC_DEL, 0, _MOUSE, _LSYMBOL);
      break;
    case TD_ENT:
#ifdef HOME_MODS
      if (hr_shift(record, KC_LSFT, SHIFT, KC_MINS)) {
        return false;
      }
#endif
      tap_layer(record, _RSYMBOL);
      // LT (_RSHIFT, KC_ENT) emulation, see tap dance enter
      break;
    case TD_SPC:
#ifdef HOME_MODS
      if (hr_shift(record, KC_RSFT, NOSHIFT, KC_MINS)) {
        return false;
      }
#endif
      tap_layer(record, _LSYMBOL);
      // LT (_LSHIFT, KC_SPC) left right combination layer, see tap dance TD_SPC
      thumb_roll(record, LEFT, 0, 0, 0, _LSYMBOL, _SYMBOL);
      break;
#ifdef CENTER_TT
    case CNTR_TL:
    case CNTR_TR:
    case CNTR_HL:
    case CNTR_HR:
    case CNTR_BL:
    case CNTR_BR:
      if (tt_keycode != keycode && tt_keycode != 0) {
        tt_clear();                         // return to base layer first if different TT layer selected
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
    case PLOVER:
      steno(record);
      return false;
    default:
      key_timer = 0;                        // regular keycode, clear timer in custom/keycode_functions.h
  }
  return true;
}

#include "common/init_audio.h"
