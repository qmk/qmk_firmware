#include QMK_KEYBOARD_H
enum my_layers {
    _QWERTY = 0,
    _FNROW
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_65_ansi(
        KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, LM(_FNROW, MOD_LGUI),  KC_LALT,                            KC_SPC,                             KC_RALT,MO(_FNROW), MO(_FNROW),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
        [_FNROW] = LAYOUT_65_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, \
        _______, _______, _______, _______, _______,  LGUI(LSFT(KC_S)), RGB_SAI, _______, _______,_______, KC_PSCR, _______, _______, _______, KC_END, \
        _______, _______,_______, _______, _______,_______ ,RGB_SAD ,_______ , _______, LGUI(KC_L), _______, _______,          KC_WSCH, _______, \
        _______, _______, _______, _______, _______, RESET, _______, KC_MAIL, _______, _______, _______, _______,          KC_VOLU, _______, \
        _______, _______, _______,                            KC_MPLY,                            _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  \
    )
};

void matrix_init_user(void) {
    // rgblight_disable();
   rgblight_enable();
    // rgblight_sethsv(HSV_WHITE);
     rgblight_sethsv(0,255,255);
	rgblight_mode(1);

}
void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        rgblight_enable();

    } else {
        rgblight_disable();
    }
} 