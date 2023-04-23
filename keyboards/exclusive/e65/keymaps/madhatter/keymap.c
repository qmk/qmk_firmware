#include QMK_KEYBOARD_H

enum keyboard_layers {
  _QWERTY, 
  _FNM
};

#define FNM MO(_FNM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_65_ansi_7u_wk_splitbs(
    QK_GESC, KC_1,    KC_2,   KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,KC_DEL, KC_HOME,
    KC_TAB,  KC_Q,    KC_W,   KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC,         KC_BSPC,KC_PGUP,
    KC_TILD, KC_A,    KC_S,   KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,         KC_PGDN,
    KC_LSFT,          KC_Z,   KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,KC_UP,  KC_END,
    KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                  FNM,              KC_LEFT,KC_DOWN,KC_RGHT
  ),

  [_FNM] = LAYOUT_65_ansi_7u_wk_splitbs(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, KC_DEL, KC_MPLY,
    _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______,          QK_BOOT, KC_VOLU,
    AG_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        EE_CLR,           KC_VOLD,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 KC_BTN1, KC_MS_U, KC_MNXT,
    _______, _______, _______,                   _______,                                     _______,                 KC_MS_L, KC_MS_D, KC_MS_R
  ),
};
