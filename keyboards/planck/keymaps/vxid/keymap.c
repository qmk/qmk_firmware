#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,    KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,  KC_F,  KC_G,    KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,    KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
    KC_LCTL, KC_LGUI, KC_LALT, LOWER, RAISE, KC_MINS, KC_SPC, KC_EQL, KC_LBRC, KC_RBRC, KC_QUOT, KC_GRV
),

[_LOWER] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______,  _______, KC_DEL,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______
),

[_RAISE] = LAYOUT_planck_grid(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_planck_grid(
    QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
