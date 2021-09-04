#include QMK_KEYBOARD_H

enum layout_dz60rgb {
    _QWERTY,
    _DIR,
    _FULL_DIR,
    _FN,
};

#define CT_CAPS     CTL_T(KC_CAPS)
#define SH_SLSH     RSFT_T(KC_SLSH)
#define LT_DIR      LT(_DIR, KC_D)
#define FN          MO(_FN)
#define F_DIR       MO(_FULL_DIR)
#define F_WORD      A(KC_RGHT)
#define B_WORD      A(KC_LEFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CT_CAPS, KC_A,    KC_S,    LT_DIR,  KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SH_SLSH, KC_UP,   KC_DEL,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RGUI, FN,      KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_DIR] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, F_WORD,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, F_DIR,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______,          _______, _______, _______, _______, B_WORD,  _______, _______, _______, _______, _______, KC_PGUP, _______,
        _______, _______, _______,                            _______,                   _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    [_FULL_DIR] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        RESET,   RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, RGB_SPD, RGB_SPI, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, KC_VOLU, KC_MUTE,
        _______, _______, _______,                            KC_MPLY,                   _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
};
