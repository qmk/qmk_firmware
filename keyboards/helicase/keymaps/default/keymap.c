#include "helicase.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum telophase_layers
{
	_QWERTY,
	_LOWER,
	_RAISE,
	_ADJUST
};

enum telophase_keycodes
{
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST
};

// Fillers to make layering more clear
#define XXXXXXX KC_NO
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /*QWERTY*/
	{KC_ESC,    KC_GRV,   KC_1,      KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       KC_BSPC ,   KC_DEL  },
	{KC_MINS,   KC_TAB,   KC_Q,      KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,       KC_LBRC,    KC_RBRC },
        {KC_EQL,    KC_INS,   KC_A,      KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_QUOT,    KC_END  },
	{KC_LSFT,   KC_LSFT,  KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_ENT,     KC_ENT  },
	{KC_LCTL,   KC_LGUI,   KC_LALT, ADJUST,  LOWER,   KC_SPC,   KC_SPC,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN,    KC_UP,      KC_RIGHT}
}, 


[_LOWER] = {/*LOWER*/
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX,   XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC  },
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX,   XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL   },
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,   XXXXXXX,  KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE },
  {KC_LSFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  XXXXXXX,   XXXXXXX, KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______},
  { _______, _______, _______, _______, _______, _______,XXXXXXX,   XXXXXXX, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  }
}, 

[_RAISE] = {/*RAISE*/
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   XXXXXXX,   XXXXXXX,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   XXXXXXX,   XXXXXXX,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL },
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  XXXXXXX,   XXXXXXX,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS },
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, XXXXXXX,   XXXXXXX,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______  },
  {_______, _______, _______, _______, _______, _______,XXXXXXX,   XXXXXXX, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY   },
},

[_ADJUST] = {/*ADJUST*/
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    XXXXXXX,   XXXXXXX,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
  {_______, RESET  , _______, _______, _______, _______,  XXXXXXX,   XXXXXXX, _______, _______, _______, _______, _______,   KC_DEL },
  {_______, _______, _______, AU_ON,   AU_OFF,  _______,  XXXXXXX,   XXXXXXX, _______, _______,  _______, _______,  _______, _______},
  {_______, _______, _______, _______, _______, _______,  XXXXXXX,   XXXXXXX, _______, _______, _______,  KC_HOME, KC_INS, KC_RSFT  },
  {_______, _______, _______, _______, _______, _______,  XXXXXXX,   XXXXXXX,_______, _______, _______, _______, _______, _______   },
},


};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
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

void matrix_scan_user(void) {
		return;
};
