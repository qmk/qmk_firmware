#include QMK_KEYBOARD_H

// Layer shorthand
enum layer {
  _BASE,
  _LOWER,
  _RAISE,
  _FN
};

#define LOWER MO(1)
#define RAISE MO(2)
#define FN    MO(3)

// Mac sleep
#define __SLEEP S(LCTL(KC_POWER))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_hhkb(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_SLCK, KC_PSCR, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_HOME, KC_PGUP, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_END,  KC_PGDN, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL,  KC_INS,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
           KC_CAPS, KC_LALT, KC_LGUI, RAISE,        KC_SPC,           KC_SPC,      LOWER,   KC_RGUI, KC_RALT, KC_RCTL
  ),

  [_LOWER] = LAYOUT_ortho_hhkb(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_PAUS, KC_NLCK, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_GRV,  KC_BSLS, _______, _______, _______, \
           _______, _______, _______, _______,       _______,       _______,       _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_ortho_hhkb(
  _______, KC_F11,  KC_F12,  _______, _______, _______, KC_PAUS, KC_NLCK, _______, _______, _______, _______, _______, _______, \
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_TILD, KC_PIPE, _______, _______, _______, \
           _______, _______, _______, _______,       _______,       _______,       _______, _______, _______, _______
  ),

  [_FN] = LAYOUT_ortho_hhkb(
  __SLEEP, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, \
  _______, QK_BOOT, _______, KC_MPRV, KC_MNXT, _______, RGB_SAI, RGB_HUI, _______, _______, _______, _______, _______, _______, \
  _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, _______, RGB_SAD, RGB_HUD, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, \
  _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, \
           _______, _______, _______, _______,       _______,       _______,       _______, _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _FN);
}
