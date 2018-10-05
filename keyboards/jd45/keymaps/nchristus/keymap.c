#include QMK_KEYBOARD_H
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define _QWRTY 0
#define _LOWER 1
#define _RAISE 2
#define _ARROW 3
#define _ADJST 4

#define RAISE LT(_RAISE, KC_ENT)
#define LOWER LT(_LOWER, KC_SPC)
#define ARROW MO(_ARROW)

#define CTL_ESC CTL_T(KC_ESC)

// Force quit dialog
#define C_O_ESC LALT(LGUI(KC_ESC))

// Mac sleep
#define MAC_LOK LALT(LGUI(KC_PWR))

// 1Password
#define OPW_OPN LALT(LGUI(KC_BSLS))
#define OPW_CPY S(LGUI(KC_C))

// Screenshotting
#define SCR_FLL S(LGUI(KC_3))
#define SCR_CRP S(LGUI(KC_4))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWRTY] = LAYOUT_JD45(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_BSPC,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LALT, ARROW,   KC_LGUI, KC_LGUI, RAISE,   LOWER,   KC_RGUI, KC_RGUI, KC_RCTL, ARROW
  ),
  [_LOWER] = LAYOUT_JD45(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______,
    _______, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_RAISE] = LAYOUT_JD45(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_ARROW] = LAYOUT_JD45(
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, KC_LEFT, KC_RGHT, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOWN, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_ADJST] = LAYOUT_JD45(
    C_O_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,
    _______, _______, _______, OPW_CPY, OPW_OPN, _______, SCR_FLL, SCR_CRP, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    MAC_LOK, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )
};

uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJST);
  return state;
}
