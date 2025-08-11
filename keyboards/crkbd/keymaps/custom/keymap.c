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
*/

#include QMK_KEYBOARD_H
#include "print.h"
#include "global_vars.h"

#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 200 //Switch to fast animation when over words per minute
#define ANIM_FRAME_TIME 45

#define MOD_SPC SFT_T(KC_SPC)
#define MOD_ENT LT(layer4, KC_ENT)
#define MOD_TAB GUI_T(KC_TAB)
#define ALT_TAB LALT(KC_TAB)
#define PRNT_WIN LGUI(LSFT(KC_S))
#define PRNT_UBU LCTL(KC_LBRC)
#define GUI_L LGUI(KC_L)
#define ALT_F4 RALT(KC_F4)
#define SFT_TAB LSFT(KC_TAB)
#define CS_C RCS(KC_C)
#define CS_ESC RCS(KC_ESC)
#define SFT_CPY RCS(KC_C)
#define SFT_PST RCS(KC_V)
#define CTRL_A C(KC_A)
#define ALT_SPC ALT_T(KC_SPC)
#define ALT_4 LALT(KC_4)
#define ALT_5 LALT(KC_5)
#define ALT_6 LALT(KC_6)
#define ALT_SFL LALT(KC_LBRC)
#define ALT_SFR LALT(KC_RBRC)
#define ALT_PLU LALT(KC_EQL)

enum layers {
    layer0,
    layer1,
    layer2,
    layer3,
    layer4,
    layer5,
    layer6,
    layer7,
};

enum custom_keycodes {
    F13_L = SAFE_RANGE,
    F13_K,
    F13_J,
    F13_H,
    F13_MIN,
    F13_ENT,
    F13_I,
    F13_Q,
    F13_UNS,
    F13_PLU,
    F13_SFL,
    F13_SFR,
    F13_X,
    F13_Y,
    F13_LFT,
    F13_DWN,
    F13_UP,
    F13_RGT,
    F13_8,
    F13_7,
    F13_6,
    F13_5,
    F13_4,
    F13_3,
    F13_2,
    F13_1,
    F13_SMIN,
    F13_SPLU,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [layer0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_HOME,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_END,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT,   MO(1),      MO(2), MOD_SPC, KC_RCTL
                                      //`--------------------------'  `--------------------------'

  ),

    [layer1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX,    KC_7,    KC_8,    KC_9,   MO(7),                       KC_F10,   KC_F9,   KC_F8,   KC_F7, XXXXXXX, KC_HOME,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_0,    KC_4,    KC_5,    KC_6,  KC_DOT,                       KC_F11,   KC_F6,   KC_F5,   KC_F4, KC_COMM,  KC_END,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   MO(5),    KC_1,    KC_2,    KC_3,   MO(5),                       KC_F12,   KC_F3,   KC_F2,   KC_F1, XXXXXXX, KC_LGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT, _______,      MO(3), ALT_SPC, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [layer2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX,  CTRL_A, XXXXXXX,                     PRNT_UBU, KC_PGUP,   GUI_L,    CS_C, XXXXXXX, KC_HOME,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, SFT_TAB,  KC_END,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, SFT_CPY, SFT_PST,   MO(4),                     PRNT_WIN, KC_PGDN,  ALT_F4,  CS_ESC, XXXXXXX, KC_LGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT,   MO(3),    _______,  KC_SPC, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [layer3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_CAPS, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR,   KC_LT,                        KC_GT, KC_LCBR, KC_RCBR, KC_MINS, KC_PLUS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,  KC_DQT,                      KC_PIPE, KC_LPRN, KC_RPRN,  KC_EQL, KC_UNDS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD,  KC_GRV, KC_QUOT,                      KC_BSLS, KC_LBRC, KC_RBRC,   KC_LT,   KC_GT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT, _______,    _______,  KC_SPC, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [layer4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      DT_PRNT,   DT_UP, DT_DOWN, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+- -------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  QK_RBT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT, _______,    _______,  KC_SPC, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [layer5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      F13_MIN, F13_ENT,   F13_I,   F13_Q, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        F13_H,   F13_J,   F13_K,   F13_L, F13_UNS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      F13_PLU, F13_SFL, F13_SFR, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT, _______,      MO(6), KC_LSFT, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),


    [layer6] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     F13_SMIN,   F13_X,   F13_Y, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      F13_LFT, F13_DWN,  F13_UP, F13_RGT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     F13_SPLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT, _______,    _______, KC_LSFT, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),


    [layer7] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        F13_8,   F13_7,   F13_6,   F13_5, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        F13_4,   F13_3,   F13_2,   F13_1, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT, _______,    _______,  KC_LSFT, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  )
};
// combos
const uint16_t PROGMEM esc_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM back_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM back2_combo[] = {KC_F5, KC_F6, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM ent_combo[] = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM gui_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM del2_combo[] = {KC_F2, KC_F3, COMBO_END};
const uint16_t PROGMEM select_all_combo[] = {KC_F5, KC_F6, COMBO_END};

combo_t key_combos[] = {
    COMBO(esc_combo, KC_ESC),
    COMBO(back_combo, KC_BSPC),
    COMBO(back2_combo, KC_BSPC),
    COMBO(copy_combo, KC_COPY),
    COMBO(cut_combo, KC_CUT),
    COMBO(paste_combo, KC_PASTE),
    COMBO(ent_combo, KC_ENT),
    COMBO(undo_combo, KC_UNDO),
    COMBO(gui_combo, KC_LGUI),
    COMBO(del_combo, KC_DEL),
    COMBO(del2_combo, KC_DEL),
    COMBO(select_all_combo, CTRL_A),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      if (record->event.pressed) {
          idle_timer = timer_read32();  // Reset the idle timer on key press
          oled_on();  // Use custom function to turn OLED on
      }

    switch (keycode) {
        case KC_COPY:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_LCTL);
                register_code(KC_C);
            } else {
                unregister_code(KC_C);
                unregister_code(KC_LCTL);
            }
            return false; // Skip further processing of KC_COPY
        case KC_CUT:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_LCTL);
                register_code(KC_X);
            } else {
                unregister_code(KC_X);
                unregister_code(KC_LCTL);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_LCTL);
                register_code(KC_V);
            } else {
                unregister_code(KC_V);
                unregister_code(KC_LCTL);
            }
            return false; // Skip further processing of KC_COPY
        case KC_FIND:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_LCTL);
                register_code(KC_F);
            } else {
                unregister_code(KC_F);
                unregister_code(KC_LCTL);
            }
            return false; // Skip further processing of KC_COPY
        case KC_UNDO:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_LCTL);
                register_code(KC_Z);
            } else {
                unregister_code(KC_Z);
                unregister_code(KC_LCTL);
            }
            return false; // Skip further processing of KC_COPY
        case F13_L:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_L);
            } else {
                unregister_code(KC_L);
                unregister_code(KC_F13);
            }
            return false;
        case F13_UNS:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_SCLN);
            } else {
                unregister_code(KC_SCLN);
                unregister_code(KC_F13);
            }
            return false;
        case F13_K:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_K);
            } else {
                unregister_code(KC_K);
                unregister_code(KC_F13);
            }
            return false;
        case F13_J:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_J);
            } else {
                unregister_code(KC_J);
                unregister_code(KC_F13);
            }
            return false;
        case F13_H:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_H);
            } else {
                unregister_code(KC_H);
                unregister_code(KC_F13);
            }
            return false;
        case F13_I:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_I);
            } else {
                unregister_code(KC_I);
                unregister_code(KC_F13);
            }
            return false;
        case F13_Q:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_Q);
            } else {
                unregister_code(KC_Q);
                unregister_code(KC_F13);
            }
            return false;
        case F13_MIN:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_MINS);
            } else {
                unregister_code(KC_MINS);
                unregister_code(KC_F13);
            }
            return false;
        case F13_PLU:
          if (record->event.pressed) {
              register_code(KC_F13);
              register_code16(KC_PLUS);
          } else {
              unregister_code16(KC_PLUS);
              unregister_code(KC_F13);
          }
          return false;
        case F13_SFL:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_LBRC);
            } else {
                unregister_code(KC_LBRC);
                unregister_code(KC_F13);
            }
            return false;
        case F13_SFR:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_RBRC);
            } else {
                unregister_code(KC_RBRC);
                unregister_code(KC_F13);
            }
            return false;
        case F13_X:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_X);
            } else {
                unregister_code(KC_X);
                unregister_code(KC_F13);
            }
            return false;
        case F13_Y:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_Y);
            } else {
                unregister_code(KC_Y);
                unregister_code(KC_F13);
            }
            return false;
        case F13_LFT:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
                unregister_code(KC_F13);
            }
            return false;
        case F13_DWN:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_DOWN);
            } else {
                unregister_code(KC_DOWN);
                unregister_code(KC_F13);
            }
            return false;
        case F13_UP:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_UP);
            } else {
                unregister_code(KC_UP);
                unregister_code(KC_F13);
            }
            return false;
        case F13_RGT:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_RIGHT);
            } else {
                unregister_code(KC_RIGHT);
                unregister_code(KC_F13);
            }
            return false;
        case F13_8:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_8);
            } else {
                unregister_code(KC_8);
                unregister_code(KC_F13);
            }
            return false;
        case F13_7:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_7);
            } else {
                unregister_code(KC_7);
                unregister_code(KC_F13);
            }
            return false;
        case F13_6:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_6);
            } else {
                unregister_code(KC_6);
                unregister_code(KC_F13);
            }
            return false;
        case F13_5:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_5);
            } else {
                unregister_code(KC_5);
                unregister_code(KC_F13);
            }
            return false;
        case F13_4:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_4);
            } else {
                unregister_code(KC_4);
                unregister_code(KC_F13);
            }
            return false;
        case F13_3:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_3);
            } else {
                unregister_code(KC_3);
                unregister_code(KC_F13);
            }
            return false;
        case F13_2:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_2);
            } else {
                unregister_code(KC_2);
                unregister_code(KC_F13);
            }
            return false;
        case F13_1:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_1);
            } else {
                unregister_code(KC_1);
                unregister_code(KC_F13);
            }
            return false;
        case F13_ENT:
            if (record->event.pressed) {
                // Send Ctrl + C
                register_code(KC_F13);
                register_code(KC_ENT);
            } else {
                unregister_code(KC_ENT);
                unregister_code(KC_F13);
            }
            return false;
        case F13_SMIN:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_LSFT);
                register_code(KC_MINS);
            } else {
                unregister_code(KC_MINS);
                unregister_code(KC_LSFT);
                unregister_code(KC_F13);
            }
            return false;
        case F13_SPLU:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_LSFT);
                register_code16(KC_PLUS);
            } belse {
                unregister_code16(KC_PLUS);
                unregister_code(KC_LSFT);
                unregister_code(KC_F13);
            }
            return false;
    }
    return true;
}


#ifdef OLED_ENABLE
#include "ame.c"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

bool oled_task_user() {
//   static const char PROGMEM imageL[] = {
//     // 'amelia', 32x128px
// 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240, 56,220,252,248,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
// 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 32, 48,112,112, 48, 48, 48,176,240,240,120, 60, 63, 55, 51, 49,240,252,255, 63, 49, 48,112,240,224,192,  0,128,224,240,240,240, 32,128,192,192,192,  0,  0,  0,  0,128,192,192,192,128,  0,192,248,255, 63,  7,  0,  0,216,222, 31,  6,  0,  0,  0,128,192,192,192,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
// 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 15,  7,  3,  0,  0,  0,  0,192,248,255, 63,  7,  0,  0,  0, 48,126,127, 63, 28,  6, 11, 63, 63, 31, 12,  7, 11, 31, 63, 51, 24, 12, 30, 63, 55, 55, 55, 27, 12, 30, 63,127, 99, 48, 24, 12, 31, 63, 63, 48, 24, 28, 62, 63, 27, 13, 15, 63, 63, 49, 24, 12,  6,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
// 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 32,120,126, 31,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 31, 31,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//   };

  static const char PROGMEM imageR[]  = {
    // 'watson', 32x128px
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,248,248,112,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,248,254, 62, 14,128,128,128,128,128,128,128,128,128,192,240,240,160,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,255,255, 31,  0,  0,  0,  0,128,224,240,224,  0,  0,  0,  0,  0,128,224,248,254, 31, 15,129,128,192,192,129,193,129,  1,  1,  1,129,241,255,255, 15,  3,  1,  1,129,193,225,241,241, 99,131,195,192,192,192,192,128,  0,  0,192,192,192,  0,  0,128,192,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,255,255, 15,  0,192,240, 60, 31,  7,  3,255,255,  0,128,224,248,254, 31, 15,  1, 56, 60,127, 55, 27, 29, 63, 63,127, 51, 48, 24, 28,127,127,239, 96, 48,216,204,254,255,127, 19, 24, 12, 30, 63,127, 97,112, 59, 31, 15,122,255,127, 55, 24, 12,  6, 31, 63,127, 55, 48, 24, 12,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 63, 63, 30,  7,  3,  0,  0,  0,  0,  0, 31, 63, 62, 31,  7,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  };

  if (!is_keyboard_master()) {
    // oled_write_raw_P(imageR, sizeof(imageR));
    oled_write_raw_P(imageR, sizeof(imageR));
    // oled_scroll_left();
  } else {
    // oled_write_raw_P(imageL, sizeof(imageL));
    // oled_write_raw_P(imageL, sizeof(imageL));
    oled_render_anim();
  }
  return false;
}

#endif
