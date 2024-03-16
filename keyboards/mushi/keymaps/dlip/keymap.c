// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "dlip.h"

enum mylayers {
    _BSE,
    _NNM,
    _MED,
    _TPO
};

#define KC_SFT_C MT(MOD_LSFT, KC_C)
#define KC_ALT_R MT(MOD_LALT, KC_R)
#define KC_GUI_S MT(MOD_LGUI, KC_S)
#define KC_CTL_T MT(MOD_LCTL, KC_T)
#define KC_CAG_V LCAG_T(KC_V)
#define KC_CAG_SCLN LCAG_T(KC_SCLN)
#define KC_CTL_N MT(MOD_LCTL, KC_N)
#define KC_GUI_E MT(MOD_LGUI, KC_E)
#define KC_ALT_I MT(MOD_LALT, KC_I)
#define KC_SFT_A MT(MOD_LSFT, KC_A)

#define KC_NNM MO(_NNM)
#define KC_MED MO(_MED)
#define KC_OS_SFT OSM(MOD_LSFT)
#define KC_MED_SPC LT(_MED, KC_SPC)

#define KC_SFT_DEL MT(MOD_LSFT, KC_DEL)
#define KC_ALT_LFT MT(MOD_LALT, KC_LEFT)
#define KC_GUI_DWN MT(MOD_LGUI, KC_DOWN)
#define KC_CTL_RGT MT(MOD_LCTL, KC_RIGHT)
#define KC_CAG_PGDN LCAG_T(KC_PGDN)

#define KC_CAG_2 LCAG_T(KC_2)
#define KC_ALT_6 MT(MOD_LALT, KC_6)
#define KC_GUI_5 MT(MOD_LGUI, KC_5)
#define KC_CTL_4 MT(MOD_LCTL, KC_4)
#define KC_SFT_0 MT(MOD_LSFT, KC_0)

#define KC_ALT_MPRV MT(MOD_LALT, KC_MPRV)
#define KC_GUI_MPLY MT(MOD_LGUI, KC_MPLY)
#define KC_CTL_MNXT MT(MOD_LCTL, KC_MNXT)

#define KC_COMBO KC_BSPC
#define KC_COMBO_SFT KC_OS_SFT
#define KC_COMBO_ALT1 KC_MED_SPC
#define KC_COMBO_ALT2 KC_NNM

#include "g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BSE] = LAYOUT_split_3x5_3(
         KC_W,     KC_L,     KC_Y,     KC_P,     KC_B,             KC_Z,      KC_F,     KC_O,        KC_U,     KC_QUOT,
         KC_SFT_C, KC_ALT_R, KC_GUI_S, KC_CTL_T, KC_G,             KC_M,      KC_CTL_N, KC_GUI_E,    KC_ALT_I, KC_SFT_A,
         KC_Q,     KC_J,     KC_CAG_V, KC_D,     KC_K,             KC_X,      KC_H,     KC_CAG_SCLN, KC_COMMA, KC_DOT,
                             KC_MED,   KC_NNM,   KC_MED_SPC,       KC_OS_SFT, KC_BSPC,  QK_REPEAT_KEY
    ),
    [_NNM] = LAYOUT_split_3x5_3(
         KC_GRV,     KC_ESC,     KC_UP,       KC_ENT,     KC_LBRC,        KC_RBRC,  KC_7,     KC_8,     KC_9,     KC_BSLS,
         KC_SFT_DEL, KC_ALT_LFT, KC_GUI_DWN,  KC_CTL_RGT, KC_TAB,         KC_EQL,   KC_CTL_4, KC_GUI_5, KC_ALT_6, KC_SFT_0,
         KC_HOME,    KC_PGUP,    KC_CAG_PGDN, KC_END,     KC_BSPC,        KC_MINUS, KC_1,     KC_CAG_2, KC_3,     KC_SLSH,
                                 KC_TRNS,     KC_TRNS,    KC_TRNS,        KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
    [_MED] = LAYOUT_split_3x5_3(
         G(KC_Z), G(KC_X),     G(KC_C),     G(KC_V),     KC_VOLU,        TO(_TPO), KC_F7,   KC_F8, KC_F9, KC_F11,
         KC_LSFT, KC_ALT_MPRV, KC_GUI_MPLY, KC_CTL_MNXT, KC_VOLD,        KC_NO,    KC_F4,   KC_F5, KC_F6, KC_F10,
         C(KC_Z), C(KC_X),     C(KC_C),     C(KC_V),     KC_PSCR,        KC_NO,    KC_F1,   KC_F2, KC_F3, KC_F12,
                               KC_TRNS,     KC_TRNS,     KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS
    ),
    [_TPO] = LAYOUT_split_3x5_3(
         TP_TLP, TP_TLR, TP_TLM, TP_TLI, KC_NO,          TO(_BSE), TP_TRI,  TP_TRM, TP_TRR, TP_TRP,
         TP_BLP, TP_BLR, TP_BLM, TP_BLI, KC_NO,          KC_NO,    TP_BRI,  TP_BRM, TP_BRR, TP_BRP,
         KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_NO,    KC_NO,   KC_NO,  KC_NO, KC_NO,
                         KC_NO,  TP_LIT, TP_LOT,         TP_ROT,   TP_RIT,  KC_NO
    ),
    // [_BLANK] = LAYOUT_split_3x5_3(
    //      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //                    KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO
    // ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(_TPO)) {
        return taipo_process_record_user(keycode, record);
    }  else {
        return true;
    }
};

void matrix_scan_user(void) {
    taipo_matrix_scan_user();
}
