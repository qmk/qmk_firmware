#include QMK_KEYBOARD_H

enum piv3rt_layers {
    _DEF,
    _FNC,
    _RGB,
    _NUM,
    _LEG,
};

enum piv3rt_keycodes {
    RGBRST = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(
        KC_GESC,        KC_1,    KC_2,               KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,         KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,               KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,         KC_RBRC, KC_BSLS,
        CTL_T(KC_CAPS), KC_A,    KC_S,               KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,                  KC_ENT,
        KC_LSFT,                 KC_Z,               KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   RSFT_T(KC_SLSH), KC_UP,   LT(_RGB, KC_DEL),
        KC_LCTL,        KC_LGUI, LM(_FNC, MOD_LALT),                            KC_SPC,                    KC_RALT, MO(_FNC), KC_LEFT,         KC_DOWN, KC_RGHT
    ),
    [_FNC] = LAYOUT(
        TO(_NUM), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______,  _______, KC_UP,   _______, _______, _______, KC_CALC, _______, KC_INS,  _______, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
        _______,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP,          EEP_RST,
        _______,           _______, _______, _______, _______, _______, NK_TOGG, _______, _______, KC_END,  KC_PGDN, KC_VOLU, KC_MUTE,
        _______,  _______, _______,                            TO(_LEG),                  _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
    [_RGB] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RGB_TOG, _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______, _______, _______, RESET,
        _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPI, RGB_SPD, _______, _______,          EEP_RST,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            RGBRST,                    _______, _______, _______, _______, _______
    ),
    [_NUM] = LAYOUT(
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, _______,
        _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, TO(_DEF),
        _______, KC_P4,   KC_P5,   KC_P6,   _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______,          KC_PENT,
        _______,          KC_P1,   KC_P2,   KC_P3,   _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______,
        _______, KC_P0,   KC_PDOT,                            KC_PENT,                   KC_P0,   KC_PDOT, _______, _______, _______
    ),
    [_LEG] = LAYOUT(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,         KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,         KC_RBRC, KC_BSLS,
        CTL_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,                  KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   RSFT_T(KC_SLSH), KC_UP,   LT(_RGB, KC_DEL),
        KC_LCTL,        KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RALT, TO(_DEF), KC_LEFT,         KC_DOWN, KC_RGHT
    )
};

void reset_leds(void) {
    rgblight_enable();
    rgblight_sethsv(155, 255, 220);
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGBRST:
        if (record->event.pressed) {
            reset_leds();
        }
        return false;
        break;
    }
    return true;
};

void rgb_matrix_indicators_user(void) {
    uint8_t this_led = host_keyboard_leds();

    if (this_led & (1 << USB_LED_CAPS_LOCK)) {
        // Tab key = 27
        rgb_matrix_set_color(27, 0xFF, 0xFF, 0xFF);
    }
}
