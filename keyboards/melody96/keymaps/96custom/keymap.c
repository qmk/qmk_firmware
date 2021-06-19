#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_HOME,  KC_END, KC_PGUP, KC_PGDN,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_DEL, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,          KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,                    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   MO(1),   KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT),
    
    LAYOUT(
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LGUI(LSFT(KC_S)), KC_MAIL, _______, KC_MYCM, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NLCK, _______, _______, _______,
    _______, _______, _______, _______, _______, LGUI(LSFT(KC_S)), _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, LGUI(KC_L), _______, _______, _______,                   _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, RESET,  _______, _______, _______, _______, _______, _______,          KC_VOLU, _______, _______, _______, _______,
    _______, _______, _______,                            KC_MPLY,                            _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______, KC_CALC),
    };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        rgblight_enable_noeeprom();
    } else {
        rgblight_disable_noeeprom();
    }
}