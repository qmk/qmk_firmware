#include QMK_KEYBOARD_H

#define _BASE 0
#define LOCK LCTL(LGUI(KC_Q))
#define SFT_CMD LSFT(KC_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT( \
    LOCK,    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______, _______,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, \
    KC_VOLU, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   _______, _______,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, _______, \
    KC_VOLD, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   _______, _______,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, _______, _______, \
    KC_ESC,  KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   _______, _______,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, _______, _______, \
    KC_PGUP, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   _______, _______,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT, _______, _______, \
    KC_PGDN, KC_TAB,  SFT_CMD, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, _______, _______,        KC_ENT,  KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______ \
)
};
