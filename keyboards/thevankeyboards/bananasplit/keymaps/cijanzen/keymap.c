#include QMK_KEYBOARD_H

#define DEFAULT_LAYER   0
#define HHKB_NAV_LAYER  1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT_LAYER] = LAYOUT_hhkb_arrow(
    KC_ESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS,  KC_EQL,  KC_BSLS, KC_GRV,
    KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSPC,
    KC_CAPS,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_QUOT,       KC_ENT,
    KC_LSFT,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,  KC_DOT,  KC_SLSH,   KC_RSFT, MO(1),
    KC_LCTL,    KC_LGUI,    KC_LALT,    KC_SPC,    KC_SPC,     KC_SPC,    KC_RALT,  KC_RGUI,   _______, KC_MENU, KC_RCTL
  ),

  [HHKB_NAV_LAYER] = LAYOUT_hhkb_arrow(
    QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
    _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_PSCR,   KC_SCRL,   KC_PAUS,   KC_UP, _______, KC_DEL,
    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_HOME,   KC_PGUP, KC_LEFT,  KC_RGHT, KC_ENT,
    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_END,  KC_PGDN,  KC_DOWN,  _______, _______,
    _______,  _______,  _______, _______,      _______,      _______,  _______, _______,  _______, _______, _______
  )
};
