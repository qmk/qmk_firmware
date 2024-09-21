// Copyright 2020-2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QW] = LAYOUT_ortho_5x13(
       KC_ESC, KC_1   , KC_2    , KC_3   , KC_4    , KC_5  , KC_6  , KC_7  , KC_8   , KC_9   , KC_0   , KC_MINS, KC_BSPC ,
       KC_TAB, KC_Q   , KC_W    , KC_E   , KC_R    , KC_T  , KC_Y  , KC_U  , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC ,
      KC_NUHS, KC_A   , KC_S    , KC_D   , KC_F    , KC_G  , KC_H  , KC_J  , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT  ,
      SC_LSPO, KC_NUBS, KC_Z    , KC_X   , KC_C    , KC_V  , KC_B  , KC_N  , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_SLSH ,
      KC_LCTL, KC_LGUI, TT(_LWR), KC_LALT, TT(_RSE), KC_SPC, KC_SPC, KC_SPC, KC_RALT, SC_RSPC, KC_LEFT, KC_DOWN, KC_RGHT),

  [_LWR] = LAYOUT_ortho_5x13(
       KC_GRV , KC_MUTE, KC_VOLU, KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, G(KC_P), KC_SLEP, KC_WAKE, KC_PSCR, KC_DEL , KC_EQL  ,
       KC_BTN3, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
       KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
       _______, KC_BTN1, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_U, _______ ,
       _______, KC_BTN4, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),

  [_RSE] = LAYOUT_ortho_5x13(
      KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12  ,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
      KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_U, _______ ,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R),

  [_ADJ] = LAYOUT_ortho_5x13(
      RGB_MOD, RGB_RMOD, A(KC_F2), _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_T , RGB_M_SW,
      RGB_HUI, RGB_HUD , RGB_M_P , _______, QK_BOOT  , _______, _______, _______, _______, _______, _______, _______ , RGB_M_SN,
      RGB_SAI, RGB_SAD , RGB_M_B , _______, _______, _______, _______, _______, _______, _______, _______, _______ , RGB_M_K ,
      RGB_VAI, RGB_VAD , RGB_M_R , _______, _______, _______, _______, _______, _______, _______, _______, _______ , RGB_M_X ,
      RGB_TOG, _______ , _______ , _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_TW, RGB_M_G),

};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QW]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
#if defined(RGBLIGHT_ENABLE)
    [_LWR] = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_RSE] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_ADJ] = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
#    else
    [_LWR] = {ENCODER_CCW_CW(KC_MNXT, KC_MPRV)},
    [_RSE] = {ENCODER_CCW_CW(KC_MFFD, KC_MRWD)},
    [_ADJ] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
#endif
};
#endif
