/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
bungooogoogo
*/

#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"
#include "keycodes.h"
#include "layer_lock.h"
#include "keymap_uk.h"

enum layers {
    _CDH,
    _MEDIA,
    _NAV,
    _MOUS,
    _SYM,
    _NUM,
    _FUN,
    _GAME,
};

enum keycodes {
    // Numword and switch app
	NUMWORD = SAFE_RANGE,
	OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
  	SW_APP,
    LLOCK,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_CDH] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,    UK_Q,    UK_W,    UK_F,    UK_P,    UK_B,                       UK_J,  UK_L,  UK_U,     UK_Y,   UK_QUOT,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_REP,    UK_A,    UK_R,    UK_S,    UK_T,    UK_G,                       UK_M,  UK_N,  UK_E,     UK_I,   UK_O,     KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TG(_GAME),    UK_Z,    UK_X,    UK_C,    UK_D,    UK_V,                       UK_K,  UK_H,  UK_COMM,  UK_DOT, UK_SLSH,  KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MED,   NAV, SHFT,            SYM,  NUM, FUN
                                      //`--------------------------'  `--------------------------'

  ),

    [_MEDIA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,  KC_NO,  KC_NO,     KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO, OS_CTRL,  OS_ALT,  OS_CMD,  OS_SHFT, KC_NO,                         KC_MRWD,  KC_VOLU, KC_VOLD, KC_MFFD, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,  KC_NO,  KC_NO,     KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_MSTP, KC_MPLY , KC_MUTE
                                      //`--------------------------'  `--------------------------'

  ),

    [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO, KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,                      KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  OS_CTRL, OS_ALT,  OS_CMD,   OS_SHFT,   KC_NO,                      KC_LEFT,  KC_DOWN, KC_UP, KC_RIGHT, KC_TAB, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO, KC_UNDO, KC_CUT, KC_COPY,  QK_REP,  KC_PSTE,                     KC_INS,  KC_HOME,  KC_PGUP,  KC_PGDN, KC_END, KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MOUS, KC_TRNS, KC_TRNS,      LAU, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'

  ),

    [_MOUS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                     KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO, OS_CTRL,  OS_ALT,  OS_CMD,  OS_SHFT,    KC_NO,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO,  KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                   KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_BTN1, KC_BTN2, KC_BTN3
                                      //`--------------------------'  `--------------------------'

  ),

    [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,   CLBRC,    AMPR,  ASTR,  KC_NUHS,  CRBRC,                           KC_NO,  KC_NO,    KC_NO,     KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,   COLLON,  DOLLA,    PERC,  CARROT,   PLUS,                          LAU,  OS_SHFT,  OS_CMD, OS_ALT, OS_CTRL,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,   UK_TILD,   EXCL,    DQUOT,   GBPD,   PIPE,                         KC_NO,  KC_NO,    KC_NO,  KC_NO, KC_NO,  KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          LPAR,   RPAR, KC_MINS,        KC_TRNS,  KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'

  ),



    [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,   UK_LBRC,    UK_7,   UK_8,  UK_9,  UK_RBRC,                         KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  UK_SCLN,    UK_4,   UK_5,  UK_6,  UK_EQL,                          KC_NO,  OS_SHFT,  OS_CMD, OS_ALT, OS_CTRL,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  UK_GRV,     UK_1,   UK_2 , UK_3,  UK_BSLS,                         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          UK_DOT, UK_0,  UNDRS,       KC_TRNS, KC_TRNS,  KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),


    [_FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_F12, KC_F7, KC_F8, KC_F9, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, KC_F11, KC_F4, KC_F5, KC_F6, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, KC_F10, KC_F1, KC_F2, KC_F3, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS,  KC_TRNS,   KC_ENT, KC_SPC, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

    [_GAME] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,    UK_Q,    UK_W,    UK_F,    UK_P,    UK_B,                       UK_J,  UK_L,  UK_U,     UK_Y,   UK_QUOT,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,   UK_A,    UK_R,    UK_S,    UK_T,    UK_G,                       UK_M,  UK_N,  UK_E,     UK_I,   UK_O,     KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,    UK_Z,    UK_X,    UK_C,    UK_D,    UK_V,                       UK_K,  UK_H,  UK_COMM,  UK_DOT, UK_SLSH,  KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_SPC, KC_LCTL, SHFT,            SYM,  NUM, FUN
                                      //`--------------------------'  `--------------------------'
 )
};


enum combo_events {
   // punctuation combos
   SHFT_COMBO,
   COMBO_LENGTH
 };



 uint16_t COMBO_LEN = COMBO_LENGTH;
// punctuation combos
 const uint16_t PROGMEM shft_combo[] = {UK_G, UK_M, COMBO_END};


 combo_t key_combos[] = {
   [SHFT_COMBO] = COMBO(shft_combo, SHFT),
 };



// caps word setup
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case UK_A ... UK_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case UK_1 ... UK_0:
        case KC_BSPC:
        case UK_MINS:
        case KC_DEL:
        case UK_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case NAV:
    case NUM:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case NAV:
    case NUM:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}


bool sw_app_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

  update_swapper(
                 &sw_app_active, KC_LGUI, KC_TAB, SW_APP,
                 keycode, record
                 );

  update_oneshot(
                 &os_shft_state, KC_LSFT, OS_SHFT,
                 keycode, record
                 );

  update_oneshot(
                 &os_ctrl_state, KC_LCTL, OS_CTRL,
                 keycode, record
                 );

  update_oneshot(
                 &os_alt_state, KC_LALT, OS_ALT,
                 keycode, record
                 );

  update_oneshot(
                 &os_cmd_state, KC_LCMD, OS_CMD,
                 keycode, record
                 );

  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

  return true;
}
