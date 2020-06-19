#include QMK_KEYBOARD_H

#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // layer 0
  LAYOUT_directional(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT,         KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_RSFT, KC_RSFT,
      KC_LCTL, KC_LGUI, KC_LALT, LT(5,KC_SPC), LT(5,KC_SPC), LT(5,KC_SPC), LT(3,KC_LEFT), KC_DOWN, ______, KC_UP, KC_RIGHT
      ),

  // layer 1 toggle hardware caps layer
  LAYOUT_directional(
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      LT(4,KC_ENT), ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______
      ),
  //layer 2 toggle space layer
  LAYOUT_directional(
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, KC_SPC, KC_SPC, KC_SPC, ______, ______, ______, ______, ______
      ),

  // layer 3 FN
  LAYOUT_directional(
      KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12, ______, RESET,
      KC_TILD, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______, ______, ______, ______, ______,
      TG(1), BL_TOGG, BL_STEP, BL_INC, BL_DEC, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, TG(2), TG(2), TG(2), ______, ______, ______, ______, ______
      ),

  // layer 4 caps
  LAYOUT_directional(
      KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12, ______, ______,
      KC_TILD, KC_DEL, KC_UP,LSFT(LCTL(KC_TAB)), LCTL(KC_TAB), ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, KC_LEFT, KC_DOWN, KC_RIGHT, LCTL(KC_W), ______, ______, ______, ______, ______, ______, ______,
      ______, ______, KC_LPRN, KC_RPRN, KC_BSPC, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, KC_BSPC, KC_BSPC, KC_BSPC, ______, ______, ______, ______, ______
      ),

  // layer 5 space
  LAYOUT_directional(
      KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12, ______, ______,
      KC_TILD, KC_LCBR, KC_RCBR, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL, KC_BSLS, ______, ______, ______, ______, ______, ______,
      ______, ______, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, KC_PIPE, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______
      ),
};
