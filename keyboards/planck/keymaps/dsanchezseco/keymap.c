#include QMK_KEYBOARD_H
#include "muse.h"

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ESC_CTL LCTL_T(KC_ESC)

extern keymap_config_t keymap_config;

enum planck_layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    ESC_CTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINUS,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_SFTENT,
    KC_LCTL, _______, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_RGUI, KC_RALT, _______, KC_RCTL
),

[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RIGHT,KC_RPRN,
    _______, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_LEFT, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, _______, KC_DOWN, KC_UP,   _______, _______, _______, _______, KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_RIGHT, KC_0,
    _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_EQL,  KC_LBRC, KC_RBRC,  KC_BSLS,
    _______, _______, _______, KC_DOWN, KC_UP,   _______, _______, _______, _______, KC_PGUP, KC_PGDN,  _______,
    _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______,  _______
),

[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, _______, _______, _______, _______, _______, KC_LEFT, _______, _______, _______,  _______,
    _______, KC_PSCR, _______, KC_DOWN, KC_UP,   _______, _______, _______, _______, _______, _______,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
)

};

//void matrix_init_user(void) {
//        eeconfig_init();
//}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
