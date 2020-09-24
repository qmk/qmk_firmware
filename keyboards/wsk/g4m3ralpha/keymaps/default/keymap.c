#include QMK_KEYBOARD_H

enum g4m3ralpha_layers {
    _HOME,
    _FN,
    _FNCHAR,
    _FKEYS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HOME] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        LCTL_T(KC_Z), LALT_T(KC_X), LT(_FN, KC_C), LT(_FNCHAR, KC_V), LSFT_T(KC_SPC), RGUI_T(KC_B), RALT_T(KC_N), RCTL_T(KC_M)
    ),

    [_FN] = LAYOUT(
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,
        KC_TAB,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC,
        KC_LCTL, KC_LALT, KC_TRNS, MO(_FKEYS),       LSFT_T(KC_SPC),   KC_RGUI, KC_RALT, KC_RCTL
    ),

    [_FNCHAR] = LAYOUT(
        RGB_TOG, RGB_VAD, RGB_VAI, RGB_MOD, RGB_SPD,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_GRV,  KC_NO,   KC_MINS, KC_EQL,  KC_BSLS, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_BSPC,
        KC_LCTL, KC_LALT, MO(_FKEYS), KC_TRNS,       LSFT_T(KC_SPC),   KC_COMM, KC_DOT,  KC_SLSH
    ),

    [_FKEYS] = LAYOUT(
        RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_SPI,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_DEL,
        KC_LCTL, KC_LALT, KC_TRNS, KC_TRNS,          LSFT_T(KC_SPC),   KC_RGUI, KC_RALT, KC_RCTL
    ),
};

void matrix_init_user(void) {
    setPinOutput(D3);
    writePinLow(D3);
    setPinOutput(D2);
    writePinLow(D2);
    setPinOutput(D0);
    writePinLow(D0);
}

uint32_t layer_state_set_user(uint32_t state)
{
    if (state & (1<<1)) {
        writePinHigh(D3);
        writePinLow(D2);
    } else if (state & (1<<2)) {
        writePinLow(D3);
        writePinHigh(D2);
    } else if (state & (1<<3)) {
        writePinHigh(D3);
        writePinHigh(D2);
    } else {
        writePinLow(D3);
        writePinLow(D2);
    }
    return state;
}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(D0);
    } else {
        writePinLow(D0);
    }
}
