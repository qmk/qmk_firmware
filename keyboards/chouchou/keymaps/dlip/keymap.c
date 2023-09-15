// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "dlip.h"

enum my_layers {
    _TAIPO,
    _GAMING,
    _GAMEPAD,
    _GAMING2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_TAIPO] = LAYOUT_split_2x4_2(
       TP_TLP,        TP_TLR,    TP_TLM,       TP_TLI,          TP_TRI,     TP_TRM,     TP_TRR,     TP_TRP,
       TP_BLP,        TP_BLR,    TP_BLM,       TP_BLI,          TP_BRI,     TP_BRM,     TP_BRR,     TP_BRP,
                                 TP_LIT,       TP_LOT,          TP_ROT,     TP_RIT
    ),
    [_GAMING] = LAYOUT_split_2x4_2(
        KC_TAB,       KC_Q,      KC_W,         KC_E,            KC_U,       KC_I,        KC_O,      KC_P,
        KC_LSFT,      KC_A,      KC_S,         KC_D,            KC_J,       KC_K,        KC_L,      KC_SCLN,
                                 MO(_GAMING2), KC_SPC,          KC_ENTER,   KC_ESC
    ),
    [_GAMEPAD] = LAYOUT_split_2x4_2(
        XXXXXXX,     GP_BCK,    GP_DPU,        GP_STA,          GP_X,       GP_Y,        GP_RB,     GP_LB,
        GP_HOM,      GP_DPL,    GP_DPD,        GP_DPR,          GP_A,       GP_B,        GP_RT,     GP_LT,
                                MO(_GAMING2),  GP_DPU,          GP_LSB,     GP_RSB
    ),
    [_GAMING2] = LAYOUT_split_2x4_2(
        TO(_TAIPO),   KC_ESC,    KC_UP,        KC_ENTER,        XXXXXXX,    XXXXXXX,     XXXXXXX,  XXXXXXX,
        KC_BSPC,      KC_LEFT,   KC_DOWN,      KC_RIGHT,        XXXXXXX,    XXXXXXX,     XXXXXXX,  XXXXXXX,
                                 XXXXXXX,      XXXXXXX,         XXXXXXX,    XXXXXXX
    ),
};
    
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(_TAIPO)) {
        return taipo_process_record_user(keycode, record);
    } else if (IS_LAYER_ON(_GAMEPAD)) {
        return gamepad_process_record_user(keycode, record);
    }  else {
        return true;
    }
};

void matrix_scan_user(void) {
    taipo_matrix_scan_user();
}