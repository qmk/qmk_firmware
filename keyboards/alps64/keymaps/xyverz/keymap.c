#include QMK_KEYBOARD_H
extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
  _DVORAK,
  _QWERTY,
  _COLEMAK,
  _ADJUST
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  COLEMAK,
  QWERTY,
  ADJUST
};

// Useful defines
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DVORAK] = LAYOUT_aek_103( \
			KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, \
			KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, \
			ADJUST,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT, \
			KC_LSFT,          KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
			KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                               KC_RGUI, KC_RALT, KC_RCTL \
		),
	[_COLEMAK] = LAYOUT_aek_103( \
			KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
			KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, \
			ADJUST,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT, \
			KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
			KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                               KC_RGUI, KC_RALT, KC_RCTL \
		),
	[_QWERTY] = LAYOUT_aek_103( \
			KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
			KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
			ADJUST,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
			KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
			KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                               KC_RGUI, KC_RALT, KC_RCTL \
		),
	[_ADJUST] = LAYOUT_aek_103( \
			KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, \
			KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   DVORAK,  QWERTY,  COLEMAK, \
			KC_TRNS, KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO, \
			KC_NO,            KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_CAPS, \
			KC_NO,   KC_NO,   KC_NO,                     KC_INS,                                               KC_NO,   KC_NO,   RESET \
		)
};


uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
  }
  return true;
}