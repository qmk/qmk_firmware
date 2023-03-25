 
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
  KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
      LALT_T(KC_A),       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_ENT,
         LSFT_T(KC_Z),       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    RSFT_T(KC_DOT),
            KC_LCTL,                                      KC_SPC,                                          MO(1),      MO(2)
  ),

  [1] = LAYOUT(
  KC_ESC,    KC_UP,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_DEL,
      KC_LEFT,    KC_DOWN,    KC_RGHT,    _______,    _______,    _______,    _______,    _______,    KC_SCLN,    KC_QUOT,
         KC_LSFT,    KC_LGUI,    KC_LALT,    _______,    _______, RALT(KC_N),    _______,    _______,    KC_SLSH,
            _______,                                     _______,                                          _______,    MO(3)
  ),

  [2] = LAYOUT(
  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,    _______,
      KC_TAB,    _______,    _______,    _______,    _______,    _______,    _______,    KC_BSLS,    KC_MINS,    KC_EQL,
        KC_LSFT,    _______,    _______,    _______,    _______,    _______,   _______,    KC_LBRC,    KC_RBRC,
            _______,                                    _______,                                           _______,    _______
  ),

  [3] = LAYOUT(
  KC_GRV,    KC_VOLU,    _______,    _______,    _______,    KC_F,    KC_F2,    KC_F3,    KC_F4,    _______,    QK_BOOT,
      KC_MUTE,    KC_VOLD,    _______,    _______,    _______,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    _______,
         _______,    _______,    _______,    _______,    _______,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
            _______,                                     _______,                                          _______,    _______
  )


};
  