#include QMK_KEYBOARD_H

// To compile firmware:
// qmk_firmware$ qmk compile -kb dz60 -km vitvlkv

// To flash firmware:
// qmk_firmware$ qmk flash -kb dz60 -km vitvlkv

// Usefull docs:
// * https://docs.qmk.fm/#/keycodes
// * https://docs.qmk.fm/#/faq_keymap

// TODO: Set MO(1) + C = KC_GRV maybe?..

// TODO: Find a place for:
// * KC_CAPS
// * KC_SLCK (Scroll Lock)
// * KC_PAUS (Pause)
// * KC__VOLUP, KC__VOLDOWN, KC__MUTE
// * KC_BRIU, KC_BRID (Brightness Up/Down)
// * Mouse movement/click/wheel
// * RESET, DEBUG, EEP_RST, see https://docs.qmk.fm/#/quantum_keycodes

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_60_ansi_split_bs_rshift(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSPC,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        MO(1),            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(1),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_RALT, MO(1),   MO(2),   MO(3)
    ),

    LAYOUT_60_ansi_split_bs_rshift(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
        _______,          KC_PGUP, _______, _______, _______, _______, _______, _______, KC_UP,   _______, KC_PSCR, KC_INS,  _______, _______,
        _______,          KC_PGDN, _______, KC_HOME, KC_END,  KC_DEL,  KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______
    ),

    LAYOUT_60_ansi_split_bs_rshift(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______
    ),

    LAYOUT_60_ansi_split_bs_rshift(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______
    ),
};
