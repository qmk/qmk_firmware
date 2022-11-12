#include QMK_KEYBOARD_H
#include "mreel.h"

#define LAYOUT_wrapped(...) LAYOUT_80_with_macro(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DF_MAC] = LAYOUT_wrapped(
    KC_MUTE,          KC_ESC,  _________________FROW_1TO5_________________, KC_F6,   _________________FROW_7TO10_______, KC_F11,  KC_F12,  KC_DEL,  KC_INS,
    KC_F1,   KC_F2,   KC_GRV,  ________________NUMBER_1TO5________________, KC_6,    ________________NUMBER_7TO0_______, KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC, KC_HOME,
    KC_F3,   KC_F4,   KC_TAB,  _______________QWERTY_Q_TO_T_______________, _______________QWERTY_Y_TO_P_______________, KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
    KC_F5,   KC_F6,   KC_CAPS, _______________QWERTY_A_TO_G_______________, _______________QWERTY_H_TO_SCLN____________, KC_QUOT,          KC_ENT,  KC_PGUP,
    KC_F7,   KC_F8,   KC_LSFT, _______________QWERTY_Z_TO_B_______________, _______________QWERTY_N_TO_SLSH____________, KC_RSFT, KC_UP,   KC_PGDN,
    KC_F9,   KC_F10,  KC_LCTL, KC_LALT, KC_LGUI, MO(1),   KC_SPC,  KC_SPC,           MO(1),   KC_SPC,  KC_RALT, KC_RCTL, KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_WIN] = LAYOUT_wrapped(
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RGB_HUI, RGB_HUD, KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,
    RGB_SAI, RGB_SAD, RGB_TOG, RGB_MOD, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RGB_VAI, RGB_VAD, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}
