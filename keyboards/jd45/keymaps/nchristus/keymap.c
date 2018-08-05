#include QMK_KEYBOARD_H
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define LOWER F(1)
#define RAISE F(2)
#define CTL_ESC CTL_T(KC_ESC)
#define GUI_SEM GUI_T(KC_SCLN)
#define ALT_QUO ALT_T(KC_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_JD45(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_BSPC,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    GUI_SEM, ALT_QUO,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LALT, KC_LCTL, KC_LGUI, KC_LGUI, RAISE,   LOWER,   KC_RGUI, KC_RGUI, KC_RCTL, KC_RALT
  ),
  [_LOWER] = LAYOUT_JD45(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_JD45(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______
  )
};

const uint16_t PROGMEM fn_actions[] = {
 [1] = ACTION_LAYER_TAP_KEY(1, KC_SPC),
 [2] = ACTION_LAYER_TAP_KEY(2, KC_ENT)
};
