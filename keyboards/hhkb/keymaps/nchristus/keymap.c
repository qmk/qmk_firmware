#include QMK_KEYBOARD_H
#include "nchristus.h"

#define BASE 0
#define HHKB 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = KEYMAP_wrapper( //  default layer
        KC_ESC,  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL,  KC_BSLS, KC_GESC,
        KC_TAB,  KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,   KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,   KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(HHKB),
        KC_LALT, KC_LGUI, KC_SPC, KC_RGUI,  KC_RALT),

    [HHKB] = KEYMAP_wrapper(
        KC_PWR,  _________________FUNC_LEFT_________________, _________________FUNC_RIGHT________________, KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, ___________________BLANK___________________, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   _______, KC_BSPC,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
        _______, _______, _______, _______, _______)
};

const uint16_t PROGMEM fn_actions[] = {

};
