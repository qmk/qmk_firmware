#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layer shorthand
#define _BL 0
#define _LW 1
#define _RS 2

enum layer_keycodes {
    QWERTY = SAFE_RANGE, LOWER, RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base Layer
   * .-----------------------------------------------------------------------.
   * | ESC | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | \|  |
   * |-----------------------------------------------------------------------|
   * | TAB   | A   | S   | D   | F   | G   | H   | J   | K   | L   | ENTER   |
   * |-----------------------------------------------------------------------|
   * | LSHIFT | Z   | X    | C   | V   | B   | N   | M   | ,<  | .>  | /?    |
   * |-----------------------------------------------------------------------|
   * | LCTRL | LGUI | LALT | SPACE   | BACKSPACE      | LW     | RS  | RALT  |
   * '-----------------------------------------------------------------------'
   */
  [_BL] = LAYOUT(
    GRAVE_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,     KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,     KC_J,   KC_K,    KC_L,    KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,     KC_M,   KC_COMM, KC_DOT,  KC_SLSH,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_BSPC, LOWER, RAISE, KC_RALT
  ),

  /* Function Layer
   * .-----------------------------------------------------------------------.
   * | GRV | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   | -_  |
   * |-----------------------------------------------------------------------|
   * |       | =+  | UP  |     |     |     | [{  | ]}  | ;:  | '"  |         |
   * |-----------------------------------------------------------------------|
   * |        | LEFT| DOWN |RIGHT|     |     |     |     |     |     |       |
   * |-----------------------------------------------------------------------|
   * |       |      |      |         | DELETE         |        |     |       |
   * '-----------------------------------------------------------------------'
   */

  [_LW] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TRNS, KC_EQL,  KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LCTL, KC_LGUI, KC_LALT, KC_TRNS, KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS
  ),

  /* Second Function Layer
   * .-----------------------------------------------------------------------.
   * | RST | F1  | F2  | F3  | F4  | F5  | F6  |     | HOME| PGUP|     |     |
   * |-----------------------------------------------------------------------|
   * |      | F7  | F8  | F9  | F10 | F11 | F12 |     | END | PGDN|          |
   * |-----------------------------------------------------------------------|
   * |       |RGBtog|RGBmod|RGBhud|RGBhui|RGBvad|RGBvai|RGBsad|RGBsai|BL|    |
   * |-----------------------------------------------------------------------|
   * |       |      |      |         |                |        |     |       |
   * '-----------------------------------------------------------------------'
   */
  [_RS] = LAYOUT(
    RESET,   KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_TRNS, KC_HOME, KC_PGUP,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_END,  KC_PGDN,  KC_TRNS,
    KC_TRNS, RGB_TOG, RGB_SMOD, RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, RGB_SAD, RGB_SAI, BL_STEP,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

};

const uint16_t PROGMEM fn_actions[] = {

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if(record->event.pressed){
        layer_on(_LW);
      } else {
        layer_off(_LW);
      }
      return false;
      break;
    case RAISE:
      if(record->event.pressed){
        layer_on(_RS);
      } else {
        layer_off(_RS);
      }
      return false;
      break;
  }
  return true;
};
