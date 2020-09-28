#include QMK_KEYBOARD_H

// Layer shorthand
#define _QW 0
#define _FN 1

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

#define FN_CAPS  LT(_FN, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | GESC   | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | Del    | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      | Mute   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | FN(CPS)| A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | Vol-   | Vol+   | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | Home   | PGUP   | UP     | PGDWN  |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | Del    | ENTER  | LALT   |                             SPACE                            | End    | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_MUTE,
    FN_CAPS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_VOLD, KC_VOLU, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_HOME, KC_PGUP, KC_UP,   KC_PGDN,
    KC_LCTL, KC_MPRV, KC_MNXT, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, KC_END,  KC_LEFT, KC_DOWN, KC_RGHT
  ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | XXXXXXX| F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | _______| _______|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | _______| P7     | P8     | P9     | +      | P*     | XXXXXXX| PR SCR | SCR LK | PAUSE  | XXXXXXX| BL_DEC | BL_INC | RGB HD | RGB HI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | _______| P4     | P5     | P6     | NumLk  | CALC   | XXXXXXX| POWER  | XXXXXXX| RESET  | XXXXXXX| BL_BRTG| BL_STEP| RGB SD | RGB SI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | _______| P1     | P2     | P3     | -      | P/     | XXXXXXX| OS     |  PLAY  | PREV   | NXT    | BL_OFF | BL_ON  | RGB VD | RGB VI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | _______| P0     | P.     | PENT   |                             SPACE                            | BL_TOGG| RGB TG | RGB RMD| RGB MD |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
    _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PAST, XXXXXXX, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, BL_DEC,  BL_INC,  RGB_HUD, RGB_HUI,
    _______, KC_P4,   KC_P5,   KC_P6,   KC_NLCK, KC_CALC, XXXXXXX, KC_PWR,  XXXXXXX, RESET,   XXXXXXX, BL_BRTG, BL_STEP, RGB_SAD, RGB_SAI,
    _______, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, KC_PSLS, XXXXXXX, KC_LWIN, KC_MPLY, KC_MPRV, KC_MNXT, BL_OFF,  BL_ON,   RGB_VAD, RGB_VAI,
    _______, KC_P0,   KC_PDOT, KC_PENT, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, BL_TOGG, RGB_TOG, RGB_RMOD,RGB_MOD
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        capslock_led_on();
    } else {
        capslock_led_off();
    }
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = get_highest_layer(state);
    
  gp100_led_off();
  //gp103_led_off();
  
  // turns on gp100 (top left led) for odd layers
  if (layer & (1<<0)) gp100_led_on();
  // turns on gp103 (top mid led) for layers 2, 6, ...
  //if (layer & (1<<1)) gp103_led_on();
  
  return state;
}
