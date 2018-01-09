#include "planck.h"

#define ______ KC_TRNS
#define XXXXXX KC_NO

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV,
	DYNAMIC_MACRO_RANGE
};
#include "dynamic_macro.h"

enum { // layers
	lyr_base,
	lyr_rMod,
	// lyr_rMod_cap is not needed since we can just shift for the same result
	lyr_lMod,
	lyr_lMod_cap,
	lyr_lMod_num,
	lyr_lMod_punc1,
	lyr_lMod_punc2,
	lyr_lMod_move,
	lyr_lMod_fn,
	lyr_mouse,
	lyr_mouse_wheel,
	lyr_COUNT
};
enum { // custom keycodes
	CKC_LMOD = SAFE_RANGE,
	CKC_RMOD,
	CKC_MOUSE_ON,
	CKC_MOUSE_OFF
};


const uint16_t PROGMEM keymaps[lyr_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
[lyr_base] = {
  {KC_ESC,  KC_G,    KC_T,    KC_H,    KC_W,     KC_K,   KC_Q,   KC_Y,     KC_O,         KC_U,    KC_J,    KC_BSPC},
  {KC_TAB,  KC_D,    KC_L,    KC_R,    KC_S,     KC_B,   KC_X,   KC_E,     KC_A,         KC_I,    KC_N,    KC_ENT},
  {KC_CAPS, KC_C,    KC_M,    KC_V,    KC_F,     KC_P,   KC_Z,   KC_UNDS,  KC_QUOT,      KC_COMM, KC_DOT,  KC_DEL},
  {XXXXXX,  KC_MPRV, KC_MPLY, KC_MNXT, CKC_LMOD, KC_SPC, KC_SPC, CKC_RMOD, CKC_MOUSE_ON, KC_MUTE, KC_VOLD, KC_VOLU}
},
[lyr_rMod] = {
  {______,  ______, ______, ______, ______, ______, XXXXXX, XXXXXX,       DYN_MACRO_PLAY1,  DYN_MACRO_PLAY1,  XXXXXX,  XXXXXX},
  {______,  ______, ______, ______, ______, ______, XXXXXX, XXXXXX,       KC_LSFT,          KC_LCTL,          KC_LALT, KC_LGUI},
  {XXXXXX,  ______, ______, ______, ______, ______, XXXXXX, DYN_REC_STOP, DYN_REC_START1,   DYN_REC_START2,   XXXXXX,  XXXXXX},
  {XXXXXX,  XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_SPC, KC_SPC, ______,       XXXXXX,           XXXXXX,           XXXXXX,  XXXXXX}
},
[lyr_lMod] = {
  {XXXXXX,  XXXXXX,  XXXXXX,  MO(lyr_lMod_punc1), MO(lyr_lMod_fn),   XXXXXX, KC_Q,   KC_Y,    KC_O,    KC_U,    KC_J,   KC_BSPC},
  {KC_LGUI, KC_LALT, KC_LCTL, MO(lyr_lMod_cap),   MO(lyr_lMod_num),  XXXXXX, KC_X,   KC_E,    KC_A,    KC_I,    KC_N,   KC_ENT},
  {XXXXXX,  XXXXXX,  XXXXXX,  MO(lyr_lMod_punc2), MO(lyr_lMod_move), XXXXXX, KC_Z,   KC_UNDS, KC_QUOT, KC_COMM, KC_DOT, KC_DEL},
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,             ______,            KC_SPC, KC_SPC, XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, XXXXXX}
},
[lyr_lMod_cap] = {
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, XXXXXX, XXXXXX, LSFT(KC_Q), LSFT(KC_Y), LSFT(KC_O), LSFT(KC_U), LSFT(KC_J), LSFT(KC_BSPC)},
  {KC_LGUI, KC_LALT, KC_LCTL, ______, XXXXXX, XXXXXX, LSFT(KC_X), LSFT(KC_E), LSFT(KC_A), LSFT(KC_I), LSFT(KC_N), LSFT(KC_ENT)},
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, XXXXXX, XXXXXX, LSFT(KC_Z), KC_QUES,    KC_DQT,     KC_SCOLON,  KC_COLN,    LSFT(KC_DEL)},
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, ______, KC_SPC, KC_SPC,     XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX}
},
[lyr_lMod_num] = {
  {KC_LGUI, KC_LALT, KC_LCTL, XXXXXX, XXXXXX, XXXXXX, KC_PLUS, KC_7,   KC_8,   KC_9,   KC_ASTR,  KC_BSPC},
  {KC_LGUI, KC_LALT, KC_LCTL, XXXXXX, ______, XXXXXX, KC_MINS, KC_4,   KC_5,   KC_6,   KC_SLASH, KC_ENT},
	{KC_LGUI, KC_LALT, KC_LCTL, XXXXXX, XXXXXX, XXXXXX, KC_0,    KC_1,   KC_2,   KC_3,   KC_DOT,   KC_DEL},
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, ______, KC_SPC, KC_SPC,  XXXXXX, XXXXXX, XXXXXX, XXXXXX,   XXXXXX}
},
[lyr_lMod_punc1] = {
  {KC_LGUI, KC_LALT, KC_LCTL, ______, XXXXXX, XXXXXX, XXXXXX, KC_AMPR, KC_LCBR, KC_RCBR, KC_PIPE, KC_BSPC},
  {KC_LGUI, KC_LALT, KC_LCTL, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_EQL,  KC_LPRN, KC_RPRN, KC_PERC, KC_ENT},
	{KC_LGUI, KC_LALT, KC_LCTL, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_LT,   KC_LBRC, KC_RBRC, KC_GT,   KC_DEL},
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, ______, KC_SPC, KC_SPC, XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX}
},
[lyr_lMod_punc2] = {
  {KC_LGUI, KC_LALT, KC_LCTL, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX,  KC_TILD, KC_CIRC, KC_GRAVE,  KC_BSPC},
	{KC_LGUI, KC_LALT, KC_LCTL, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_EXLM, KC_HASH, KC_AT,   KC_BSLASH, KC_ENT},
	{KC_LGUI, KC_LALT, KC_LCTL, ______, XXXXXX, XXXXXX, XXXXXX, KC_DLR,  XXXXXX,  XXXXXX,  XXXXXX,    KC_DEL},
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, ______, KC_SPC, KC_SPC, XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,    XXXXXX}
},
[lyr_lMod_move] = {
  {KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXX, XXXXXX, XXXXXX,  KC_HOME, KC_UP,   KC_END,  XXXXXX, KC_BSPC},
  {KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXX, XXXXXX, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXX, KC_ENT},
	{KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, ______, XXXXXX, KC_PGDN, XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, KC_DEL},
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  ______, KC_SPC, KC_SPC,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, XXXXXX}
},
[lyr_lMod_fn] = {
  {KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, ______, XXXXXX, XXXXXX, KC_F9,  KC_F10, KC_F11, KC_F12, XXXXXX},
  {KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXX, XXXXXX, XXXXXX, KC_F5,  KC_F6,  KC_F7,  KC_F8,  XXXXXX},
	{KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXX, XXXXXX, XXXXXX, KC_F1,  KC_F2,  KC_F3,  KC_F4,  XXXXXX},
  {XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  ______, KC_SPC, KC_SPC, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX}
},
[lyr_mouse] = {
  {XXXXXX, XXXXXX, XXXXXX,  KC_MS_U, XXXXXX,              XXXXXX,  XXXXXX,  KC_BTN3, KC_LSFT,      KC_LCTL, KC_LALT, KC_LGUI},
  {XXXXXX, XXXXXX, KC_MS_L, KC_MS_D, KC_MS_R,             XXXXXX,  XXXXXX,  KC_BTN1, KC_LSFT,      KC_LCTL, KC_LALT, KC_LGUI},
	{XXXXXX, XXXXXX, XXXXXX,  XXXXXX,  XXXXXX,              XXXXXX,  XXXXXX,  KC_BTN2, KC_LSFT,      KC_LCTL, KC_LALT, KC_LGUI},
  {XXXXXX, XXXXXX, XXXXXX,  XXXXXX,  MO(lyr_mouse_wheel), KC_ACL0, KC_ACL0, KC_ACL2, TO(lyr_base), XXXXXX,  XXXXXX,  XXXXXX}
},
[lyr_mouse_wheel] = {
  {______, ______, ______,  KC_WH_U, ______,  ______, ______, ______, ______, ______, ______, ______},
  {______, ______, KC_WH_L, KC_WH_D, KC_WH_R, ______, ______, ______, ______, ______, ______, ______},
	{______, ______, ______,  ______,  ______,  ______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______,  ______,  ______,  ______, ______, ______, XXXXXX, ______, ______, ______}
}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (!process_record_dynamic_macro(keycode, record)) return false;
	bool asUsual = false;
  switch(keycode) {
    case CKC_LMOD:
      if (record->event.pressed) {
        clear_keyboard();
				layer_on(lyr_lMod);
      } else {
				clear_keyboard();
        layer_clear();
      }
      break;
    case CKC_RMOD:
      if (record->event.pressed) {
        clear_keyboard();
				layer_on(lyr_rMod);
      } else {
				clear_keyboard();
        layer_clear();
      }
      break;
    case CKC_MOUSE_ON:
      if (record->event.pressed) {
        clear_keyboard();
				layer_on(lyr_mouse);
      }
      break;
    case CKC_MOUSE_OFF:
      if (record->event.pressed) {
				clear_keyboard();
        layer_clear();
			}
      break;
		default: asUsual = true;
  }
  return asUsual;
}
