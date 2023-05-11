#include QMK_KEYBOARD_H

// Helpful defines
#define ESC_CTL     CTL_T(KC_ESCAPE)            // Tap for Esc, hold for Ctrl
#define FL_KCF LT(1,KC_F)
#define FL_KCJ LT(1,KC_J)
#define CMD_ENT LGUI(LSFT(KC_ENT))

enum custom_keycodes {
  HASHRKT = SAFE_RANGE,
  CLNEQLS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( /* Base */
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSLS, LGUI(KC_C),
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, LGUI(KC_V),
		ESC_CTL,          KC_A,    KC_S,    KC_D,    FL_KCF,  KC_G,    KC_H,    FL_KCJ,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,          KC_UP,   KC_PGDN,
		CMD_ENT, KC_LALT, KC_LGUI,          KC_SPC,           KC_SPC,           KC_SPC,                    MO(2),   KC_GRV,  KC_LEFT, KC_DOWN, KC_RGHT
	),
	[1] = LAYOUT( /* FL */
		KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,  KC_VOLU,
		_______,          HASHRKT, _______, KC_LCBR, KC_RCBR, _______, _______, KC_UNDS, KC_PLUS, KC_PIPE,  _______, _______, _______, _______, KC_VOLD,
		_______,          CLNEQLS, _______, KC_LBRC, KC_RBRC, _______, _______, KC_MINS, KC_EQL,  KC_BSLS,  KC_TILD, KC_GRV,           _______, KC_HOME,
		_______,          _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,          _______, KC_END,
		_______, _______, _______,          _______,          _______,          _______,                    _______, _______, _______, _______, _______
	),
	[2] = LAYOUT( /* FN */
		QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,  _______,
		KC_CAPS,          _______, KC_UP,   _______, _______, _______, KC_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
		_______,          KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_VOLD, KC_VOLU, KC_P4,   KC_P5,   KC_P6,   _______, _______,          _______, _______,
		_______,          KC_RCTL, KC_RGUI, KC_RALT, _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   _______, _______,          KC_PGUP, _______,
		_______, _______, _______,          _______,          _______,          _______,                   _______, _______, KC_HOME, KC_PGDN, KC_END
	)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case HASHRKT:
      if (record->event.pressed) {
        SEND_STRING("=>");
      }
      break;
    case CLNEQLS:
      if (record->event.pressed) {
        SEND_STRING(":=");
      }
      break;
  }
  return true;
}
