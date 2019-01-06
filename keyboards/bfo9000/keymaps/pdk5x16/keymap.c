#include QMK_KEYBOARD_H

#define _BASE 0
#define _FUNCTION 15

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,  KC_INS,        _______,     KC_DEL,         KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   _______, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_PGUP, KC_CAPS,       _______,     KC_MUTE,        KC_HOME, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,   _______, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PGDN, LSFT(KC_LBRC), _______,     LSFT(KC_RBRC),  KC_END,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,   _______, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI, KC_LALT,       _______,     KC_RALT,        KC_RGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,   _______, \
    KC_VOLD, KC_VOLU, KC_GRV,  KC_LBRC, KC_RBRC, KC_BSPC, KC_TAB,  KC_LCTL,       _______,     KC_RCTL,        KC_ENT,  KC_SPC,  KC_DOWN, KC_UP,   KC_LEFT, KC_RGHT, MO(_FUNCTION), _______, \
    _______, _______, _______, _______, _______, _______, _______, _______,       _______,     _______,        _______, _______, _______, _______, _______, _______, _______,   _______  \
),

[_FUNCTION] = LAYOUT( \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,         _______,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______,       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG, _______, _______,       _______,     _______, _______, RGB_TOG, RGB_VAI, RGB_SAI, RGB_HUI, _______, _______, _______, \
    _______, _______, RGB_VAD, RGB_SAD, RGB_HUD, _______, _______, _______,       _______,     _______, _______, _______, RGB_VAD, RGB_SAD, RGB_HUD, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______,       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______,       _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)
};
