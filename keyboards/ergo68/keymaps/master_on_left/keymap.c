#include QMK_KEYBOARD_H
/*
extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,--------------------------------------------------------.   ,-------------------------------------------------------.
 * | Esc    | 1     | 2     | 3     | 4     | 5     | Bs    |   | Esc   | 6     | 7     | 8     | 9     | 0     | BS    |
 * |--------|-------|-------|-------|-------|-------|-------|   |-------|-------|-------|-------|-------|-------|-------|
 * | Tab    | Q     | W     | E     | R     | T     | Enter |   | Tab   | Y     | U     | I     | O     | P     | \     |
 * |--------|-------|-------|-------|-------|-------|       |   |       |-------|-------|-------|-------|-------|-------|
 * | Caps   | A     | S     | D     | F     | G     |-------|   |-------| H     | J     | K     | L     | ;     | Enter |
 * |--------|-------|-------|-------|-------|-------| [     |   | ]     |-------|-------|-------|-------|-------|-------|
 * | Shift  | Z     | X     | C     | V     | B     |       |   |       | N     | M     | ,     | .     | /     | Shift |
 * |--------|-------|-------|-------|-----------------------'   `-----------------------|-------|-------|-------|-------|
 * | Ctrl   | Win   | MO(2) | Alt   |       ,---------------.   ,---------------.       | MO(1) | MO(2) | Alt   | Ctrl  |
 * `--------------------------------'       | Lt(1) | `     |   | '     |       |       `-------------------------------'
 *                                          | Space |-------|   |-------| Space |
 *                                          |       | Lt(2)=|   | -     |       |
 *                                          `---------------'   `---------------'
 */
[0] = LAYOUT_ergo68( \
  KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_BSPC,        KC_ESC,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_ENT,         KC_TAB,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_BSLS, \
  KC_CAPS,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_LBRC,        KC_RBRC,    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_ENT, \
  KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   XXXXXXX,        XXXXXXX,    KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT, \
  KC_LCTL,  KC_LGUI,MO(2),  KC_LALT,LT(1,KC_SPC), LT(2,KC_EQL), KC_GRV,   KC_QUOT,    KC_MINS,KC_SPC, MO(1),  MO(2), KC_RALT,KC_RCTL \
),

/* Lower
 * ,--------------------------------------------------------.   ,-------------------------------------------------------.
 * |        | F1    | F2    | F3    | F4    | F5    | F11   |   | F12   | F6    | F7    | F8    | F9    | F10   | DEL   |
 * |--------|-------|-------|-------|-------|-------|-------|   |-------|-------|-------|-------|-------|-------|-------|
 * |        | !     | @     | #     | $     | %     | Home  |   | Pgup  | ^     | &     | *     | (     | )     |       |
 * |--------|-------|-------|-------|-------|-------|       |   |       |-------|-------|-------|-------|-------|-------|
 * |        | WH_L  | WH_R  | Btn3  | Btn1  | Btn2  |-------|   |-------| Left  | Down  | Up    | Right | '     |       |
 * |--------|-------|-------|-------|-------|-------| End   |   | Pgdn  |-------|-------|-------|-------|-------|-------|
 * |        |       |       |       |       |       |       |   |       | WBak  | WH_D  | WH_U  | WFwd  |       |       |
 * |--------|-------|-------|-------|-----------------------'   `-----------------------|-------|-------|-------|-------|
 * |        |       |       |       |       ,---------------.   ,---------------.       |       |       |       |       |
 * `--------------------------------'       |       | Volu  |   |       |       |       `-------------------------------'
 *                                          |       |-------|   |-------| Space |
 *                                          |       | Vold  |   | Del   |       |
 *                                          `---------------'   `---------------'
 */
[1] = LAYOUT_ergo68( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,     KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_DEL, \
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_HOME,    KC_PGUP, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, _______, \
  _______, KC_WH_L, KC_WH_R, KC_BTN3, KC_BTN1, KC_BTN2, KC_END,     KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_QUOT, _______, \
  _______, _______, _______, _______, _______, _______, XXXXXXX,    XXXXXXX, KC_WBAK, KC_WH_D, KC_WH_U, KC_WFWD,  _______, _______, \
  _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU,    _______, KC_DEL,  KC_SPC,  _______, _______,  _______, _______ \
),

/* Raise
 * ,--------------------------------------------------------.   ,-------------------------------------------------------.
 * |        |       |       |       |       |       |       |   | RESET |       |       |       |       |       |       |
 * |--------|-------|-------|-------|-------|-------|-------|   |-------|-------|-------|-------|-------|-------|-------|
 * |        |       |       |       |       |       |       |   |       |       |       | MS_U  |       |       |       |
 * |--------|-------|-------|-------|-------|-------|       |   |       |-------|-------|-------|-------|-------|-------|
 * |        |       |       | BTN3  | BTN1  | BTN2  |-------|   |-------|       | MS_L  |       | MS_R  |       |       |
 * |--------|-------|-------|-------|-------|-------|       |   |       |-------|-------|-------|-------|-------|-------|
 * |        |       | WH_L  | WH_R  | WH_D  | WH_U  |       |   |       |       |       | MS_D  |       |       |       |
 * |--------|-------|-------|-------|-----------------------'   `-----------------------|-------|-------|-------|-------|
 * |        |       |       |       |       ,---------------.   ,---------------.       |       |       | RGBM  | RGBT  |
 * `--------------------------------'       |       |       |   |       |       |       `-------------------------------'
 *                                          |       |-------|   |-------|       |
 *                                          |       |       |   |       |       |
 *                                          `---------------'   `---------------'
 */
[2] = LAYOUT_ergo68( \
  _______, _______, _______, _______, _______, _______, _______,    RESET,   _______, _______, _______, _______,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, KC_MS_U, _______,  _______, _______, \
  _______, _______, _______, KC_BTN3, KC_BTN1, KC_BTN2, _______,    _______, _______, KC_MS_L, _______, KC_MS_R,  _______, _______, \
  _______, _______, KC_WH_L, KC_WH_R, KC_WH_D, KC_WH_U, XXXXXXX,    XXXXXXX, _______, _______, KC_MS_D, _______,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,  RGB_MOD, RGB_TOG \
),

};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}
*/

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRD |= (1 << 5); PORTD &= ~(1 << 5);
    } else {
        DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
    }
}
