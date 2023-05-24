#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_all(
    KC_ESC,        KC_1,    KC_2,    KC_3,   KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,           KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
    KC_TAB,        KC_Q,    KC_W,    KC_E,   KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,           KC_LBRC, KC_RBRC, KC_BSPC,
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,   KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    LT(2, KC_SCLN), KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT,       KC_NUBS, KC_Z,    KC_X,   KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,         KC_SLSH, KC_UP,   KC_RSFT, MO(1),
    KC_LCTL,       KC_LALT, KC_LGUI,                     KC_SPC,           KC_RGUI, KC_RGUI,        KC_LEFT, KC_APP,  KC_RCTL
),

[1] = LAYOUT_all(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
    KC_CAPS, QK_BOOT,   _______, _______, _______, _______, _______, _______,  KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   _______, _______,
    _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______, KC_ASTR, KC_SLSH, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______, _______,
    RGB_MOD, _______, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, _______, KC_PLUS, KC_MINS, KC_END,  KC_PGDN, KC_DOWN, _______, BL_STEP, _______,
    RGB_TOG, RGB_VAD, RGB_VAI,                            _______,                   _______, _______, _______, _______, BL_TOGG
),

[2] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______
),

[3] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______
)

};
// clang-format on
