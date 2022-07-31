#include QMK_KEYBOARD_H
#include "keymap_colemak.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x15(/* Colemak */
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, XXXXXXX,
        KC_TAB,  CM_Q,    CM_W,    CM_F,    CM_P,    CM_G,    CM_J,    CM_L,    CM_U,    CM_Y,    CM_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_BSPC, CM_A,    CM_R,    CM_S,    CM_T,    CM_D,    CM_H,    CM_N,    CM_E,    CM_I,    CM_O,    KC_QUOT, KC_ENT,  XXXXXXX, KC_PGUP,
        KC_LSFT, CM_Z,    CM_X,    CM_C,    CM_V,    CM_B,    CM_K,    CM_M,    CM_COMM, CM_DOT,  CM_SLSH, KC_RSFT, XXXXXXX, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, XXXXXXX, KC_LALT, MO(1),   KC_SPC,  XXXXXXX, KC_RALT, MO(1),   KC_RGUI, XXXXXXX, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_ortho_5x15(/* function */
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_SLEP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MPLY,
        _______, _______, XXXXXXX, _______, MO(1),   _______, XXXXXXX, _______, MO(1),   _______, XXXXXXX, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
};
