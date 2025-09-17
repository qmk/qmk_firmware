#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_split_3x5_3(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                        KC_LGUI, TL_LOWR, KC_SPC,     KC_ENT,  TL_UPPR, KC_RGUI
  ),

  [1] = LAYOUT_split_3x5_3(
      KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,       KC_5,    KC_6,    KC_7,    KC_8,    KC_9,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,    KC_RALT, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        KC_LGUI, _______, KC_SPC,     KC_ENT,  _______, KC_RGUI
  ),

  [2] = LAYOUT_split_3x5_3(
      KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,     KC_RCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_RALT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                        KC_LGUI, _______, KC_SPC,     KC_ENT,  _______, KC_RGUI
  ),

  [3] = LAYOUT_split_3x5_3(
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        KC_LGUI, _______, KC_SPC,     KC_ENT,  _______, KC_RGUI
  )

};
