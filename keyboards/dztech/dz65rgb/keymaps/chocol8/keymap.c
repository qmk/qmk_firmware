#include QMK_KEYBOARD_H

enum tofu68_layers {
	_MAQWERTY,
    _LIQWERTY,
	_FNM
};

enum tofu68_keycodes {
	MAQWER = SAFE_RANGE,
    LIQWER

};

#define FNM MO(_FNM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_MAQWERTY] = LAYOUT_65_ansi(
		KC_GESC, KC_1,     KC_2,     KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_BSPC, KC_DEL,  \
		KC_TAB,  KC_Q,     KC_W,     KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS, KC_PGUP, \
		KC_GRV,  KC_A,     KC_S,     KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,           KC_ENT,  KC_PGDN, \
		KC_LSPO, KC_Z,     KC_X,     KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSPC,           KC_UP,   KC_END,  \
		KC_LCTL, KC_LALT,  KC_LCMD,                   KC_SPC,                             FNM,     KC_RALT,  KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT  \
	),
	[_LIQWERTY] = LAYOUT_65_ansi(
		KC_GESC, KC_1,     KC_2,     KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_BSPC, KC_DEL,  \
		KC_TAB,  KC_Q,     KC_W,     KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS, KC_PGUP, \
		KC_GRV,  KC_A,     KC_S,     KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,           KC_ENT,  KC_PGDN, \
		KC_LSPO, KC_Z,     KC_X,     KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSPC,           KC_UP,   KC_END,  \
		KC_LCTL, KC_LGUI,  KC_LALT,                   KC_SPC,                             FNM,     KC_RALT,  KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT  \
	),
	[_FNM]    = LAYOUT_65_ansi(
		_______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   _______,  _______, _______, _______, \
		_______, RGB_TOG,  RGB_MOD, RGB_HUI ,RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______,  _______,  _______,   RESET, _______, \
		_______, _______,  _______, _______, _______, _______, _______, _______, _______, LIQWER,  _______,  _______,           _______, _______, \
		_______, _______,  _______, _______, _______, _______, _______,  MAQWER, _______, _______, _______,  _______,           _______, _______, \
		_______, _______,  _______,                   _______,                            _______, _______,  _______,  _______, _______, _______  \
	)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MAQWER:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MAQWERTY);
      }
      return false;
    case LIQWER:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LIQWERTY);
      }
      return false;
  }
  return true;
}
