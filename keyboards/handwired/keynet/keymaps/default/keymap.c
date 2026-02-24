// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


enum layers {
  _QWERTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                                        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,                                     XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_MPLY,  XXXXXXX,               XXXXXXX,  XXXXXXX,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RCTL,
  //└────────┴────────┴────────┼────────┼────────┼────────┼─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_LWIN, KC_LALT, KC_TAB,    KC_SPC,  KC_ENT,  XXXXXXX,               KC_ENT,  KC_BSPC, KC_SPC,    KC_DEL,  KC_RALT, KC_RWIN
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  )
};
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(MS_WHLL, MS_WHLR)  }
};
#endif
