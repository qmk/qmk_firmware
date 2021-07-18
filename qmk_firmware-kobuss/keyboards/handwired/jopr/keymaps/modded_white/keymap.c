#include QMK_KEYBOARD_H

#define _BL 0
#define _FN 1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_DEL,    KC_NO,   KC_CAPS, KC_SLCK, KC_PAUS,
        KC_NUHS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NUBS, KC_SLSH, KC_BSPC,           KC_PSCR, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,      KC_V,    KC_Y,    KC_D,    KC_COMM, KC_QUOT, KC_INT1, KC_J,    KC_M,    KC_L,    KC_U,    KC_LBRC, KC_RBRC, KC_ENT,        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_MHEN,       KC_A,    KC_T,    KC_H,    KC_E,    KC_B,    KC_MINS, KC_C,    KC_S,    KC_N,    KC_O,    KC_I,    KC_EQL,               KC_P4,   KC_P5,   KC_P6,              KC_PGUP, KC_INS,  KC_PGDN,
        KC_LSFT,   KC_GRV,  KC_P,    KC_K,    KC_G,    KC_W,    KC_Q,    KC_X,    KC_R,    KC_F,    KC_DOT,  KC_Z,    KC_RSFT,                  KC_P1,   KC_P2,   KC_P3,   KC_PENT,   KC_HOME, KC_UP,   KC_END,
        KC_LCTL,   KC_LWIN,   KC_LALT,   KC_SPC,                                                KC_RALT, KC_RWIN, LT(_FN,KC_APP), KC_RCTL,      KC_P0,            KC_PDOT,            KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT(
		_______,   _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,   _______,   KC_SYSREQ, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,
		_______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       KC_MSTP, KC_VOLU, _______, _______,
		_______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              KC_MPRV, KC_MPLY, KC_MNXT,            _______, KC_MUTE, _______,
		_______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                  KC_MUTE, KC_VOLD, _______, _______,   KC_VOLD, KC_MSTP, KC_VOLU,
		_______,   _______,   _______,   _______,                                                 _______,   _______,   _______,   _______,     _______,          _______,            KC_MPRV, KC_MPLY, KC_MNXT
    )
};

void led_set_user(uint8_t usb_led) {

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(F1);
	} else {
        writePinLow(F1);
    }

    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinHigh(F0);
	} else {
        writePinLow(F0);
    }
    
    if (!(IS_LED_ON(usb_led, USB_LED_NUM_LOCK))) {
        tap_code(KC_NUMLOCK);
    }
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool sysreq_led = false;
    if (record->event.pressed) {
        if (sysreq_led) {
            sysreq_led = false;
            writePinLow(F4);
        }
        else {
            switch(keycode) {
                case KC_SYSREQ:
                    sysreq_led = true;
                    writePinHigh(F4);
            }
        }
    }
    return true;
}