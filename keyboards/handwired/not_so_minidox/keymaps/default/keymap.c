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

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST  RESET
#define KC_CAD  LCTL(LALT(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
// ,-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------.
    KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,             KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_BSPC,
// |-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------|
    KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,             KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,
// |-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------|
    KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,             KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH, KC_ENT,
// '-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------'
                              KC_LGUI,KC_LOWR, KC_SPC,       KC_SPC,KC_RASE,KC_RALT
                          // `-------+-------+-------`     `-------+-------+-------`
   ),

  [_LOWER] = LAYOUT(
// ,-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------.
     KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,             KC_6,   KC_7,   KC_8,   KC_9,   KC_0, KC_DEL,
// |-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------|
    _______,_______,_______,_______,_______,_______,          _______,_______,_______,KC_LCBR,KC_RCBR,KC_BSLS,
// |-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------|
    _______,_______,_______,_______,_______,_______,          _______,_______,_______,_______,_______,_______,
// '-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------'
                              _______,_______,_______,      _______,_______,_______
                          // `-------+-------+-------`     `-------+-------+-------`
  ),

  [_RAISE] = LAYOUT(
 // ,-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------.
      KC_GRV,KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,          KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN, KC_DEL,
 // |-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,KC_MINS, KC_EQL,          _______,  KC_UP,_______,KC_LBRC,KC_RBRC,KC_PIPE,
 // |-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,_______,          KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,
 // '-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------'
                               _______,_______,_______,      _______,_______,_______
                           // `-------+-------+-------`     `-------+-------+-------`
   ),
  [_ADJUST] = LAYOUT(
// ,-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------.
    _______,_______,_______,_______, KC_RST,_______,          _______,_______,_______,_______,_______, KC_CAD,
// |-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------|
    _______,_______,_______,_______,_______,_______,          _______,_______,_______,_______,_______,_______,
// |-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------|
    _______,_______,_______,_______,_______,_______,          _______,_______,_______,_______,_______,_______,
// '-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------'
                              _______,_______,_______,      _______,_______,_______
                          // `-------+-------+-------`     `-------+-------+-------`
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
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_ADJUST);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
