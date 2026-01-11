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

#define PRNT_WIN LGUI(LSFT(KC_S))
#define PRNT_UBU LCTL(KC_LBRC)
#define ALT_F4 RALT(KC_F4)
#define SFT_TAB LSFT(KC_TAB)
#define CS_C RCS(KC_C)
#define CS_ESC RCS(KC_ESC)
#define SPC_2 LT(2, KC_SPC)
#define ENT_KM1 LT(6, KC_ENT)

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
    F13_PM,
    F13_PS,
    F13_SMIN,
    F13_SPLU,
    F13_TMN,
    F13_TF,
    F13_RT,
    REDO,
    ENT_F13,
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
                                          KC_LALT, ENT_KM1,   MO(1),      MO(3),   SPC_2, KC_RCTL
                                      //`--------------------------'  `--------------------------'

  ),


      [layer1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX,   MO(8), XXXXXXX,                      KC_COMM,    KC_9,    KC_8,    KC_7, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_RCTL, KC_LSFT, KC_MINS,                       KC_DOT,    KC_6,    KC_5,    KC_4, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,   MO(7),   MO(6), KC_SLSH,                         KC_0,    KC_3,    KC_2,    KC_1, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT, _______,      MO(4), XXXXXXX, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),


     [layer2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_F12,   KC_F9,   KC_F8,   KC_F7, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_RCTL, KC_LSFT, XXXXXXX,                       KC_F11,   KC_F6,   KC_F5,   KC_F4, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_F10,   KC_F3,   KC_F2,   KC_F1, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT, _______,    _______, _______, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),


      [layer3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     PRNT_UBU, KC_PGUP, XXXXXXX,    CS_C, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_RCTL, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, SFT_TAB, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   MO(5),                     PRNT_WIN, KC_PGDN,  ALT_F4,  CS_ESC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,  KC_ENT,   MO(4),    _______,  KC_SPC, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),


      [layer4] = LAYOUT_split_3x6_3(
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


    [layer5] = LAYOUT_split_3x6_3(
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


    [layer6] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX,F13_SMIN,F13_SPLU, XXXXXXX,                       F13_PM, F13_SFL, F13_SFR,   F13_Q, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  F13_TF, XXXXXXX,   MO(7), KC_LSFT, F13_TMN,                        F13_H,   F13_J,   F13_K,   F13_L,   F13_I, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, F13_MIN, F13_PLU, XXXXXXX,                        F13_4,   F13_3,   F13_2,   F13_1,  F13_PS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, _______, _______,    F13_UNS,  F13_RT, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),


    [layer7] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, F13_SFL, F13_SFR, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      F13_LFT, F13_DWN,  F13_UP, F13_RGT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   F13_X,   F13_Y, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    F13_UNS,  F13_RT, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  )
};

// combos
const uint16_t PROGMEM esc_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM back_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM ent_combo[] = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM righ_alt[] = {KC_DOT, KC_SLASH, COMBO_END};
const uint16_t PROGMEM right_sft[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM spc_combo[] = {KC_S, KC_F, COMBO_END};

combo_t key_combos[] = {
    COMBO(esc_combo, KC_ESC),
    COMBO(back_combo, KC_BSPC),
    COMBO(copy_combo, LCTL(KC_C)),
    COMBO(cut_combo, LCTL(KC_X)),
    COMBO(paste_combo, LCTL(KC_V)),
    COMBO(ent_combo, KC_ENT),
    COMBO(undo_combo, LCTL(KC_Z)),
    COMBO(del_combo, KC_DEL),
    COMBO(righ_alt, KC_RALT),
    COMBO(right_sft, KC_RSFT),
    COMBO(spc_combo, KC_SPC),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      if (record->event.pressed) {
          idle_timer = timer_read32();  // Reset the idle timer on key press
          oled_on();  // Use custom function to turn OLED on
      }

    switch (keycode) {
        case REDO:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_Z);
            } else {
                unregister_code(KC_Z);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;
        case F13_L:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_L);
            } else {
                unregister_code(KC_L);
                unregister_code(KC_F13);
            }
            return false;
        case F13_UNS:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_SCLN);
            } else {
                unregister_code(KC_SCLN);
                unregister_code(KC_F13);
            }
            return false;
        case F13_K:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_K);
            } else {
                unregister_code(KC_K);
                unregister_code(KC_F13);
            }
            return false;
        case F13_J:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_J);
            } else {
                unregister_code(KC_J);
                unregister_code(KC_F13);
            }
            return false;
        case F13_H:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_H);
            } else {
                unregister_code(KC_H);
                unregister_code(KC_F13);
            }
            return false;
        case F13_I:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_I);
            } else {
                unregister_code(KC_I);
                unregister_code(KC_F13);
            }
            return false;
        case F13_Q:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_Q);
            } else {
                unregister_code(KC_Q);
                unregister_code(KC_F13);
            }
            return false;
        case F13_MIN:
            if (record->event.pressed) {
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
              register_code16(KC_EQL);
          } else {
              unregister_code16(KC_PLUS);
              unregister_code(KC_EQL);
          }
          return false;
        case F13_SFL:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_LBRC);
            } else {
                unregister_code(KC_LBRC);
                unregister_code(KC_F13);
            }
            return false;
        case F13_SFR:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_RBRC);
            } else {
                unregister_code(KC_RBRC);
                unregister_code(KC_F13);
            }
            return false;
        case F13_X:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_X);
            } else {
                unregister_code(KC_X);
                unregister_code(KC_F13);
            }
            return false;
        case F13_Y:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_Y);
            } else {
                unregister_code(KC_Y);
                unregister_code(KC_F13);
            }
            return false;
        case F13_LFT:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
                unregister_code(KC_F13);
            }
            return false;
        case F13_DWN:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_DOWN);
            } else {
                unregister_code(KC_DOWN);
                unregister_code(KC_F13);
            }
            return false;
        case F13_UP:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_UP);
            } else {
                unregister_code(KC_UP);
                unregister_code(KC_F13);
            }
            return false;
        case F13_RGT:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_RIGHT);
            } else {
                unregister_code(KC_RIGHT);
                unregister_code(KC_F13);
            }
            return false;
        case F13_8:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_8);
            } else {
                unregister_code(KC_8);
                unregister_code(KC_F13);
            }
            return false;
        case F13_7:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_7);
            } else {
                unregister_code(KC_7);
                unregister_code(KC_F13);
            }
            return false;
        case F13_6:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_6);
            } else {
                unregister_code(KC_6);
                unregister_code(KC_F13);
            }
            return false;
        case F13_5:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_5);
            } else {
                unregister_code(KC_5);
                unregister_code(KC_F13);
            }
            return false;
        case F13_4:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_4);
            } else {
                unregister_code(KC_4);
                unregister_code(KC_F13);
            }
            return false;
        case F13_3:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_3);
            } else {
                unregister_code(KC_3);
                unregister_code(KC_F13);
            }
            return false;
        case F13_2:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_2);
            } else {
                unregister_code(KC_2);
                unregister_code(KC_F13);
            }
            return false;
        case F13_1:
            if (record->event.pressed) {

                register_code(KC_F13);
                register_code(KC_1);
            } else {
                unregister_code(KC_1);
                unregister_code(KC_F13);
            }
            return false;
        case F13_ENT:
            if (record->event.pressed) {

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
                register_code16(KC_PLUS);
            } else {
                unregister_code16(KC_PLUS);
                unregister_code(KC_F13);
            }
            return false;
        case F13_PM:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_LSFT);
                register_code(KC_ENT);
            } else {
                unregister_code(KC_ENT);
                unregister_code(KC_LSFT);
                unregister_code(KC_F13);
            }
            return false;
        case F13_PS:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_P);
            } else {
                unregister_code(KC_P);
                unregister_code(KC_F13);
            }
            return false;
        case F13_TMN:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_LSFT);
                register_code(KC_F);
            } else {
                unregister_code(KC_F);
                unregister_code(KC_LSFT);
                unregister_code(KC_F13);
            }
            return false;
        case F13_TF:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_LSFT);
                register_code(KC_T);
            } else {
                unregister_code(KC_T);
                unregister_code(KC_LSFT);
                unregister_code(KC_F13);
            }
            return false;
          case F13_RT:
            if (record->event.pressed) {
                register_code(KC_F13);
                register_code(KC_LSFT);
                register_code(KC_R);
            } else {
                unregister_code(KC_R);
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
  static const char PROGMEM imageR[]  = {
    // 'watson', 32x128px
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,248,248,112,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,248,254, 62, 14,128,128,128,128,128,128,128,128,128,192,240,240,160,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,255,255, 31,  0,  0,  0,  0,128,224,240,224,  0,  0,  0,  0,  0,128,224,248,254, 31, 15,129,128,192,192,129,193,129,  1,  1,  1,129,241,255,255, 15,  3,  1,  1,129,193,225,241,241, 99,131,195,192,192,192,192,128,  0,  0,192,192,192,  0,  0,128,192,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,255,255, 15,  0,192,240, 60, 31,  7,  3,255,255,  0,128,224,248,254, 31, 15,  1, 56, 60,127, 55, 27, 29, 63, 63,127, 51, 48, 24, 28,127,127,239, 96, 48,216,204,254,255,127, 19, 24, 12, 30, 63,127, 97,112, 59, 31, 15,122,255,127, 55, 24, 12,  6, 31, 63,127, 55, 48, 24, 12,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 63, 63, 30,  7,  3,  0,  0,  0,  0,  0, 31, 63, 62, 31,  7,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  };

  if (!is_keyboard_master()) {
    oled_write_raw_P(imageR, sizeof(imageR));
  } else {
    oled_render_anim();
  }
  return false;
}

#endif
