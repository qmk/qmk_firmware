#include QMK_KEYBOARD_H

#define _BL 0
#define _AL 1
#define _UL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_UP,   KC_DOT,
        _______, KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC,  KC_SPC,  MO(_AL), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_AL] = LAYOUT(
         KC_GRV,      KC_1,      KC_2,      KC_3,         KC_4,        KC_5,       KC_6,      KC_7,     KC_8,      KC_9,      KC_0, KC_DEL,
         KC_TAB,     KC_F1,     KC_F2,     KC_F3,        KC_F4,       KC_F5,      KC_F6,     KC_F7,    KC_F8,     KC_F9,    KC_ENT,
        _______,   _______, KC_SCOLON,  KC_QUOTE,  KC_LBRACKET, KC_RBRACKET,  KC_BSLASH,  KC_MINUS,  KC_EQUAL,   KC_PGUP,  KC_SLASH,
        _______,   _______,   _______,   _______,      MO(_UL),     TG(_UL),    _______,   KC_HOME,  KC_PGDN,    KC_END
    ),

    [_UL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),
    };
