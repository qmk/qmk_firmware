#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Layer 0, default layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ Esc │  F1 │  F2 │  F3 │  F4 │  F5 │  F6 ││ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │PrtSc│ Del │ Ins │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │ ` ~ │  1  │  2  │  3  │  4  │  5  │  6  ││  7  │  8  │  9  │  0  │ - _ │ = + │ Backspace │ Home│
   * ├─────┴─────┼─────┼─────┼─────┼─────┼─────┤├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┼─────┤
   * │    Tab    │  Q  │  W  │  E  │  R  │  T  ││  Y  │  U  │  I  │  O  │  P  │ [ { │ ] } │ \ | │ PgUp│
   * ├───────────┼─────┼─────┼─────┼─────┼─────┤├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │ Caps Lock │  A  │  S  │  D  │  F  │  G  ││  H  │  J  │  K  │  L  │ ; : │ ' " │   Enter   │ PgDn│
   * ├───────────┼─────┼─────┼─────┼─────┼─────┤├─────┼─────┼─────┼─────┼─────┼─────┴─────┬─────┼─────┤
   * │   Shift   │  Z  │  X  │  C  │  V  │  B  ││  N  │  M  │ , < │ . > │ / ? │   Shift   │ Up  │ End │
   * ├───────────┼─────┼─────┼─────┼─────┴─────┤├─────┴─────┼─────┼─────┼─────┴─────┬─────┼─────┼─────┤
   * │   Ctrl    │  Fn │ Alt │Super│   Space   ││   Fn      │BkSpc│ Alt │    Ctrl   │ Left│ Down│Right│
   * └───────────┴─────┴─────┴─────┴───────────┘└───────────┴─────┴─────┴───────────┴─────┴─────┴─────┘
   */

  [0] = LAYOUT(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_DEL,  KC_INS,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,       KC_BSPC,     KC_HOME,
       KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
       KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,      KC_ENT,      KC_PGDN,
       KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,     KC_RSFT,      KC_UP,   KC_END,
       KC_LCTL,     MO(1),   KC_LALT, KC_LGUI,    KC_SPC,             MO(1),       KC_BSPC,     KC_RALT,      KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  /* Layer 1, function layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │RESET│     │     │     │     │     │     ││     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │     │     │     │     │     │     │     ││     │     │     │     │     │     │           │     │
   * ├─────┴─────┼─────┼─────┼─────┼─────┼─────┤├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┼─────┤
   * │           │Home │ Up  │End  │PgUp │Mute ││PgUp │Home │ Up  │End  │     │     │     │     │     │
   * ├───────────┼─────┼─────┼─────┼─────┼─────┤├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │           │Left │Down │Right│PgDn │VolU ││PgDn │Left │Down │Right│     │     │           │     │
   * ├───────────┼─────┼─────┼─────┼─────┼─────┤├─────┼─────┼─────┼─────┼─────┼─────┴─────┬─────┼─────┤
   * │           │     │     │     │     │VolD ││MPly │MPrv │MNxt │     │     │           │     │     │
   * ├───────────┼─────┼─────┼─────┼─────┴─────┤├─────┴─────┼─────┼─────┼─────┴─────┬─────┼─────┼─────┤
   * │           │     │     │     │ Backspace ││           │     │     │           │     │     │     │
   * └───────────┴─────┴─────┴─────┴───────────┘└───────────┴─────┴─────┴───────────┴─────┴─────┴─────┘
   */

  [1] = LAYOUT(
  RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
       KC_TRNS,     KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_MUTE, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,     KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_VOLU, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
       KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_MPLY, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS,
       KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,      KC_BSPC,          KC_TRNS,     KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
