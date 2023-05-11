


#include QMK_KEYBOARD_H

// Keymap myee
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define LOW_SPC LT(_LOWER, KC_SPC)
#define RSE_SPC LT(_RAISE, KC_SPC)
#define ADJ_TAB LT(ADJUST, KC_TAB)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,   KC_BSPC,
        ADJ_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_ENT,
        KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,
        KC_LCTL, KC_LGUI,KC_LALT, LOW_SPC,       RSE_SPC,        KC_RGUI,KC_RALT, KC_RCTL
		),

	[_LOWER] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_UP,   KC_MINS, KC_EQL, KC_DEL,
		_______, _______, KC_ASTR, KC_LBRC, KC_RBRC, KC_QUOT, KC_DQUO, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSLS,
		_______, _______, _______, KC_LPRN, KC_RPRN, KC_HOME, KC_PGUP, KC_PGDN, KC_END, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______
		),
	
    [_RAISE] = LAYOUT(
        KC_GRV,  KC_LPRN, KC_RPRN, KC_DQUO, KC_QUOT, KC_SCLN, KC_COLON,KC_UNDS, KC_PLUS, _______, _______, KC_BSPC,
		_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
		_______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, BL_UP,   BL_DOWN
		),
	
    [_ADJUST] = LAYOUT(
        _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_SYSTEM_SLEEP, _______, _______, _______, _______, _______, _______, _______
		),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 
  switch (keycode) {
    
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
