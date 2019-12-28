#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Layer 0, default layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │PrtSc│ Del │ Ins │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │  7  │  8  │  9  │  0  │ - _ │ = + │ Backspace │ Home│
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┼─────┤
   * │  Y  │  U  │  I  │  O  │  P  │ [ { │ ] } │ \ | │ PgUp│
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │  H  │  J  │  K  │  L  │ ; : │ ' " │   Enter   │ PgDn│
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┬─────┼─────┤
   * │  N  │  M  │ , < │ . > │ / ? │   Shift   │ Up  │ End │
   * ├─────┴─────┼─────┼─────┼─────┴─────┬─────┼─────┼─────┤
   * │   Space   │ Alt │ Fn  │    Ctrl   │ Left│ Down│Right│
   * └───────────┴─────┴─────┴───────────┴─────┴─────┴─────┘
   */

  [0] = LAYOUT(
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_DEL,  KC_INS,
    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,       KC_BSPC,     KC_HOME,
    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,      KC_ENT,      KC_PGDN,
    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,     KC_RSFT,      KC_UP,   KC_END,
        KC_SPC,       KC_RALT, MO(1),       KC_RCTL,      KC_LEFT, KC_DOWN, KC_RGHT
  ),

  /* Layer 1, function layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │     │     │     │     │     │     │           │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┼─────┤
   * │     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │     │     │     │     │     │     │           │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┬─────┼─────┤
   * │     │     │     │     │     │           │     │     │
   * ├─────┴─────┼─────┼─────┼─────┴─────┬─────┼─────┼─────┤
   * │           │     │     │           │     │     │     │
   * └───────────┴─────┴─────┴───────────┴─────┴─────┴─────┘
   */

  [1] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS,
          KC_TRNS,    KC_TRNS, KC_TRNS,       KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
