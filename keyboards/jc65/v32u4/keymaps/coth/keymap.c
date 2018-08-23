#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
      KC_GESC, KC_1,    KC_2,   KC_3,     KC_4,     KC_5,     KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, KC_INS,
      KC_TAB,  KC_Q,    KC_W,   KC_E,     KC_R,     KC_T,     KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL,
      KC_LCTL, KC_A,    KC_S,   KC_D,     KC_F,     KC_G,     KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
      KC_LSFT, KC_NUBS, KC_Z,   KC_X,     KC_C,     KC_V,     KC_B,    KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
      KC_LALT, KC_LCTL, KC_LGUI, KC_SPACE, KC_SPACE, KC_SPACE, MO(1),  KC_NO, MO(2),  KC_LEFT, KC_DOWN, KC_RGHT
      ),
  [1] = LAYOUT(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,   KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_BTN2, KC_MS_U, KC_BTN1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_UP,   KC_HOME,  KC_END,  KC_DEL,  KC_TRNS,
      KC_CAPS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_LEFT,  KC_DOWN, KC_RGHT, KC_TRNS, KC_VOLU,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN,  KC_PGUP, KC_TRNS,  KC_TRNS, KC_PGUP, KC_VOLD,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME,  KC_PGDN, KC_END
      ),
  [2] = LAYOUT(
      RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_MOD, RGB_RMOD, BL_STEP, BL_TOGG, KC_TRNS, KC_TRNS, RESET,
      KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS,  RGB_TOG,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_INC,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, RGB_HUD, RGB_SAD, RGB_VAD, KC_TRNS,  RGB_HUD,  RGB_HUI, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC,   KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD,  RGB_VAI,  KC_TRNS, KC_TRNS, RGB_MOD, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
      ),
};
