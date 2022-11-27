/* Copyright 2018-2022 TheAmarin (@theamarin)
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
 
 
#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

#include "keymap_german.h"

#define MACROS_ENABLE

extern keymap_config_t keymap_config;

enum custom_keycodes {
  NEO2 = SAFE_RANGE,
  QWERTZ,
  WURST,
#ifdef MACROS_ENABLE
  DYNAMIC_MACRO_RANGE
#endif
};

#ifdef MACROS_ENABLE
#include "dynamic_macro.h"
#define MACRS DYN_REC_STOP
#define MAC1R DYN_REC_START1
#define MAC1P DYN_MACRO_PLAY1
#else
#define MACRS KC_TRNS
#define MAC1R KC_TRNS
#define MAC1P KC_TRNS
#endif


#define L_NEO    0 // NEO2
#define L_QWZ    2 // QWERTZ
#define L_COD    3 // NEO2 Layer 3 (Coding)
#define L_COD_AT 4 // NEO2 Layer 3 (Coding with AT)
#define L_MOV    5 // NEO2 Layer 4 (Movements)
#define L_FUN    6 // Function and media keys

#define MCOD MO(L_COD)
#define MCODAT MO(L_COD_AT)
#define MMOV MO(L_MOV)
#define MFUN MO(L_FUN)
#define YMCOD LT(L_COD, DE_Y)
#define AEMCOD MT(DE_HASH, DE_ADIA)
#define RALTF LM(L_FUN, MOD_RALT)

#define LALTTAB LALT(KC_TAB)
#define RALTTAB RALT(KC_TAB)
#define ME_MAXM LCTL(LGUI(KC_UP))

#define KC_ KC_TRNS
#define ____ KC_TRNS

/*
#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L_NEO] = LAYOUT_ortho_4x12(
  //,-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------.
     KC_TAB , DE_X  , DE_V  , DE_L  , DE_C  , DE_W  ,      DE_K  , DE_H  , DE_G  , DE_F  , DE_Q  , DE_SS ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
     MCODAT , DE_U  , DE_I  , DE_A  , DE_E  , DE_O  ,      DE_S  , DE_N  , DE_R  , DE_T  , DE_D  , YMCOD ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
     KC_LSFT,DE_UDIA,DE_ODIA,DE_ADIA, DE_P  , DE_Z  ,      DE_B  , DE_M  ,DE_COMM, DE_DOT, DE_J  ,KC_RSFT,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
     KC_LCTL,KC_LGUI,KC_LALT, SH_MON, MFUN  , MMOV  ,    KC_SPACE, SH_MON, MFUN  , KC_APP, RALTF ,KC_RCTL
  //`-------+-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------+-------'
  ),

  [L_QWZ] = LAYOUT_ortho_4x12(
  //,-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------.
     KC_TAB , DE_Q  , DE_W  , DE_E  , DE_R  , DE_T  ,      DE_Z  , DE_U  , DE_I  , DE_O  , DE_P  ,DE_UDIA,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
     KC_CAPS, DE_A  , DE_S  , DE_D  , DE_F  , DE_G  ,      DE_H  , DE_J  , DE_K  , DE_L  ,DE_ODIA,AEMCOD ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
     KC_LSFT, DE_Y  , DE_X  , DE_C  , DE_V  , DE_B  ,      DE_N  , DE_M  ,DE_COMM, DE_DOT, DE_SS ,KC_RSFT,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
     KC_LCTL,KC_LGUI,KC_LALT, ____  , MFUN  , MMOV  ,    KC_SPACE, ____  ,KC_RALT,KC_APP , RALTF ,KC_RCTL
  //`-------+-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------+-------'
  ),

  [L_COD] = LAYOUT_ortho_4x12(
  //,-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------.
     DE_ACUT,DE_EURO,DE_UNDS,DE_LBRC,DE_RBRC,DE_CIRC,     DE_EXLM,DE_LABK,DE_RABK,DE_EQL, DE_AMPR, DE_GRV,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  ,DE_BSLS,DE_SLSH,DE_LCBR,DE_RCBR,DE_ASTR,     DE_QUES,DE_LPRN,DE_RPRN,DE_MINS,DE_COLN, ____  ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  ,DE_HASH, DE_DLR,DE_PIPE,DE_TILD,DE_ACUT,     DE_PLUS,DE_PERC,DE_DQUO,DE_QUOT,DE_SCLN, ____  ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  , ____  , ____  , ____  , ____  , ____  ,      ____  , ____  , ____  , ____  , ____  , ____
  //`-------+-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------+-------'
  ),

  [L_COD_AT] = LAYOUT_ortho_4x12(
  //,-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------.
     DE_ACUT,DE_EURO,DE_UNDS,DE_LBRC,DE_RBRC,DE_CIRC,     DE_EXLM,DE_LABK,DE_RABK,DE_EQL, DE_AMPR, DE_GRV,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  ,DE_BSLS,DE_SLSH,DE_LCBR,DE_RCBR,DE_ASTR,     DE_QUES,DE_LPRN,DE_RPRN,DE_MINS,DE_COLN, DE_AT ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  ,DE_HASH, DE_DLR,DE_PIPE,DE_TILD,DE_ACUT,     DE_PLUS,DE_PERC,DE_DQUO,DE_QUOT,DE_SCLN, ____  ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  , ____  , ____  , ____  , ____  , ____  ,      ____  , ____  , ____  , ____  , ____  , ____
  //`-------+-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------+-------'
  ),

  [L_MOV] = LAYOUT_ortho_4x12(
  //,-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------.
      ____  ,KC_PGUP,KC_BSPC, KC_UP ,KC_DEL, KC_PGDN,      ____  , KC_7  , KC_8  , KC_9  ,DE_PLUS,DE_MINS,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  ,KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_END ,      ____  , KC_4  , KC_5  , KC_6  ,DE_COMM, DE_DOT,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  ,KC_ESC ,KC_TAB ,KC_INS, KC_ENTER,____  ,      KC_0  , KC_1  , KC_2  , KC_3  ,DE_SCLN, ____  ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  , ____  , ____  , ____  , ____  , ____  ,      ____  , KC_0  , ____  , ____  , ____  , ____ 
  //`-------+-------+-------+-------+-------+-------'    `-------+-------+-------+-------+-------+-------'
  ),

  [L_FUN] = LAYOUT_ortho_4x12(
  //,-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------.
      ____  , AU_ON ,KC_VOLD,ME_MAXM,KC_VOLU, WURST ,      MAC1R , KC_F7 , KC_F8 , KC_F9 , KC_F12,KC_PSCR,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  ,KC_MSTP,KC_MPRV,KC_MPLY,KC_MNXT, NEO2  ,      MACRS , KC_F4 , KC_F5 , KC_F6 , KC_F11,KC_BRK ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  , AU_OFF,KC_TAB ,KC_INS ,KC_ENTER,QWERTZ,      MAC1P , KC_F1 , KC_F2 , KC_F3 , KC_F10, ____  ,
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
      ____  , ____  , ____  , ____  , ____  , ____  ,      ____  , ____  , ____  , ____  , ____  , ____
  //|-------+-------+-------+-------+-------+-------|    |-------+-------+-------+-------+-------+-------|
  ),

};

#ifdef AUDIO_ENABLE
float tone_qwertz[][2]   = SONG(QWERTY_SOUND);
float tone_neo2[][2]     = SONG(DVORAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTZ:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwertz);
        #endif
        persistent_default_layer_set(1UL<<L_QWZ);
      }
      return false;
      
    case NEO2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_neo2);
        #endif
        persistent_default_layer_set(1UL<<L_NEO);
      }
      return false;

    case WURST:
      if(record->event.pressed) {
        // Nothing to do
      }
      return false;
  }
  return true;
}


void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  static uint8_t old_layer = 0;
  static bool layer_has_changed = true;

  if (old_layer != layer) {
    layer_has_changed = true;
    old_layer = layer;
  }

  if (layer_has_changed) {
    layer_has_changed = false;

    switch (layer) {
      case L_COD:
      case L_COD_AT:
        backlight_set(1);
        break;
      case L_MOV:
        backlight_set(3);
        break;
      default:
        backlight_set(0);
        break;
    }
  }
}
