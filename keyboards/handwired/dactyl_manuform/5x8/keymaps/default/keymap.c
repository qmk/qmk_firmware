#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN     1
#define _NUMPAD 2

// Some basic macros
#define TASK   LCTL(LSFT(KC_ESC))
#define TAB_R  LCTL(KC_TAB)
#define TAB_L  LCTL(LSFT(KC_TAB))
#define TAB_RO LCTL(LSFT(KC_T))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x8(
        // left hand
        KC_A,   KC_B,    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,
        KC_C,   KC_D,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_LBRC,
        KC_E,   KC_F,   KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   TAB_RO,
        KC_G,   KC_H,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
        KC_I,   KC_J, KC_K,   KC_L,
                                    KC_1, KC_2,
                                    KC_3, KC_3,
                                    KC_4, KC_5,
        // right hand
                          KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,   KC_GRV,
                          KC_RBRC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,   KC_GRV,
                      TG(_NUMPAD), KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_GRV,
                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT),   KC_GRV,
                                            KC_LEFT, KC_UP,    KC_DOWN,  KC_RGHT,
             KC_BSPC, KC_ENT,
             KC_PGUP, KC_PGDN,
             KC_LCTL, KC_LALT
    ),
};
