#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  LAYOUT(
    KC_ESC,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, KC_PGUP,
    KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,         KC_PGDN,
    KC_LCTL,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,          KC_DEL,
    KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,                    MO(1),
	KC_NO,            KC_LALT, KC_LGUI,          KC_NO,            KC_SPC,           KC_NO,   KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT),

  LAYOUT(
	KC_PWR,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL, QK_BOOT,
    KC_CAPS,          RGB_RMOD,RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_TOG, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   KC_TRNS, KC_TRNS,         KC_TRNS,
    KC_TRNS,          KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,          KC_TRNS,         KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END,  KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,                  KC_TRNS,
	KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

bool led_update_user(led_t led_state) {
	if (led_state.caps_lock) {
		DDRD |= (1 << 1); PORTD &= ~(1 << 1);
	} else {
		DDRD &= ~(1 << 1); PORTD &= ~(1 << 1);
	}
	return false;
}
