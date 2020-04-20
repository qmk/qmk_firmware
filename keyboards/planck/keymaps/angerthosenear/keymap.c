#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_planck_grid( /* Qwerty */
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
  KC_LCTL, KC_LGUI, KC_LALT, BL_STEP, MO(3),   KC_SPC,  KC_SPC,  MO(2),   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
                                                // Space is repeated to accommodate for both spacebar wiring positions
),
[1] = LAYOUT_planck_grid( /* WASD + NumPad */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, KC_PMNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_PPLS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_PENT, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3),   KC_SPC,  KC_P0,   MO(2),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
[2] = LAYOUT_planck_grid( /* RAISE */
  KC_GRV,	KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
  KC_TRNS, FUNC(3), FUNC(4), LSFT(RSFT(KC_PAUSE)), KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  KC_TRNS, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,   KC_MPRV,  MO(2),     KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),
[3] = LAYOUT_planck_grid( /* LOWER */
  S(KC_GRV),  S(KC_1),    S(KC_2),    S(KC_3),    S(KC_4),    S(KC_5),    S(KC_6),    S(KC_7),    S(KC_8),    S(KC_9),    S(KC_0), KC_DEL,
  KC_TRNS, FUNC(3), FUNC(4), LSFT(RSFT(KC_PAUSE)), KC_TRNS, KC_TRNS, KC_TRNS, S(KC_MINS), S(KC_EQL),  S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3),     KC_TRNS,   KC_TRNS,   KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END
)
};


const uint16_t PROGMEM fn_actions[] = {
    [3] = ACTION_DEFAULT_LAYER_SET(0),
    [4] = ACTION_DEFAULT_LAYER_SET(1),

};
