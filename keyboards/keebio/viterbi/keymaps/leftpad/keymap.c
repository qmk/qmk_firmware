#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_ortho_5x14(
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
   _______, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, _______,\
   _______, KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, _______,\
   _______, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  _______,\
   _______, KC_GRV,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,   KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, KC_BSLS, _______ \
  ),

  [_LOWER] = LAYOUT_ortho_5x14(
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
   _______,  KC_GRV, KC_COMM,   KC_7,    KC_8,    KC_9,  KC_DOT,   KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_VOLU, _______, _______,\
   _______, KC_TILD, KC_MINS,   KC_4,    KC_5,    KC_6,  KC_EQL,   KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_MUTE, _______, _______,\
   _______, _______, KC_UNDS,   KC_1,    KC_2,    KC_3, KC_PPLS,   _______, _______, _______, _______, KC_VOLD, _______, _______,\
   _______, _______, _______,   KC_0,    KC_0, _______, _______,   _______, _______, _______, _______, _______, _______, _______ \
  ),

  [_RAISE] = LAYOUT_ortho_5x14(
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
   _______, _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  _______, _______, KC_LPRN, KC_RPRN, _______, _______, _______,\
   _______, _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,  _______,  KC_INS, KC_LBRC, KC_RBRC, KC_PIPE, _______, _______,\
   _______, _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,  _______,  KC_DEL, KC_LABK, KC_RABK, KC_SLSH, KC_BSLS, _______,\
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______ \
  ),

  [_ADJUST] = LAYOUT_ortho_5x14(
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,\
   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______ \
  )

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
