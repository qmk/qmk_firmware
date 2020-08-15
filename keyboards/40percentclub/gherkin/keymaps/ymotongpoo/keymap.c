#include QMK_KEYBOARD_H

#define FN1_B       LT(1, KC_B)
#define FN2_N       LT(2, KC_N)
#define FN3_S       LT(3, KC_S)
#define FN4_D       LT(4, KC_D)
#define FN5_P       LT(5, KC_P)
#define CTL_A       CTL_T(KC_A)
#define CTL_SCLN    CTL_T(KC_SCLN)
#define SFT_Z       LSFT_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define CTL_M       RCTL_T(KC_M)
#define SFT_SLSH    RSFT_T(KC_SLSH)
#define SFT_ENT     RSFT_T(KC_ENT)
#define SFTSPC      LSFT(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    FN5_P,
    CTL_A,   FN3_S,   FN4_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    CTL_SCLN,
    SFT_Z,   ALT_X,   KC_C,    KC_V,    FN1_B,   FN2_N,   KC_M,    KC_COMM, KC_DOT,  SFT_SLSH
  ),

  [1] = LAYOUT_ortho_3x10(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_F11,  KC_F12
  ),

  [2] = LAYOUT_ortho_3x10(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_GRV,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [3] = LAYOUT_ortho_3x10(
    _______, _______, KC_LGUI, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    KC_TAB,  _______, SFTSPC,  _______, KC_DEL,  KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    _______, _______, _______, _______, KC_BSPC, KC_SPC,  _______, _______, _______, _______
  ),

  [4] = LAYOUT_ortho_3x10(
    _______, _______, _______, _______, _______, KC_GRV,  KC_TILD, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
    _______, _______, _______, _______, _______, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR
  ),

  [5] = LAYOUT_ortho_3x10(
    KC_CALC, KC_WHOM, KC_MAIL, KC_MYCM, _______, KC_PSCR, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, BL_DEC,  BL_INC,
    _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______
  )

};

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinLow(D5);
  } else {
    writePinHigh(D5);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(B0);
  } else {
    writePinHigh(B0);
  }
}
