#include QMK_KEYBOARD_H
#include OWLET60_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    // Base Layer
    LAYOUT_owlet60_full_bsp(
    k50,    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,    KC_EQL,     KC_BSPC,   KC_PGUP, \
    k51,    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,    KC_RBRC,    KC_BSLS,   KC_PGDOWN, \
    k52,    KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,    KC_ENT,                KC_HOME, \
            KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_B,   KC_N,   KC_N,   KC_COMM,KC_DOT, KC_SLSH,    KC_RSFT,    KC_UP,     KC_END, \
            KC_LCTRL,        KC_LALT,        KC_SPC, KC_LGUI,KC_SPC,                 KC_RALT,                    KC_LEFT,    KC_DOWN,   KC_RIGHT),
}