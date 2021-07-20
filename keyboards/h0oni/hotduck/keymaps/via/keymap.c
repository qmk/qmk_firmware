#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  [0] = LAYOUT_all(
      KC_ESC,   KC_1,       KC_2,       KC_3,      KC_4,        KC_5,      KC_6,      KC_7,      KC_8,      KC_9,     \
      KC_TAB,   KC_Q,       KC_W,       KC_E,      KC_R,        KC_T,      KC_Y,      KC_U,      KC_I,      KC_0,     \
      KC_CAPS,  KC_A,       KC_S,       KC_D,      KC_F,        KC_G,      KC_J,      KC_K,      KC_L,      KC_O,     \
      KC_LSFT,  KC_Z,       KC_X,       KC_C,      KC_V,        KC_H,      KC_COMM,   KC_DOT,    KC_SCLN,   KC_P,     \
      KC_LCTL,  KC_LALT,    KC_LGUI,    KC_SPC,    KC_B,        KC_N,      KC_M,      KC_RGUI,   KC_SLSH,   KC_LBRC,  \
      KC_RALT,  KC_RCTL,    KC_RSFT,    KC_ENT,    KC_QUOT,     KC_BSLS,   KC_RBRC,   KC_BSPC,   KC_EQL,    KC_MINS,  \
      KC_LEFT,  KC_DOWN,    KC_RIGHT,    KC_UP,    KC_PGDOWN,   KC_END,    KC_DEL,    KC_PGUP,   KC_HOME,   KC_INS    ),

};
