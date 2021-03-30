#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Level 0: Default Layer
     * ,---------------------------------------------------------------------------------------.
     * |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |  BSP  |
     * |---------------------------------------------------------------------------------------|
     * |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |  ENT  |LT(1|,)|
     * |---------------------------------------------------------------------------------------|
     * |LT(3|Z)|   X   |   C   |   V   |      SPC      |   B   |   N   |   M   |  RSFT |LT(2|.)|
     * |---------------------------------------------------------------------------------------|
     */
  [0] = LAYOUT(
    KC_Q,        KC_W, KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I, KC_O, KC_P,    KC_BSPC,
    KC_A,        KC_S, KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K, KC_L, KC_ENT,  LT(1, KC_COMMA),
    LT(3, KC_Z), KC_X, KC_C, KC_V,       KC_SPC, KC_B, KC_N, KC_M, KC_RSFT, LT(2, KC_DOT)
  ),
  /* Level 1: Numbers Layer
     * ,---------------------------------------------------------------------------------------.
     * |  ESC  |   7   |   8   |   9   |   /   |   *   |   .   |   ,   |   (   |   )   |  DEL  |
     * |---------------------------------------------------------------------------------------|
     * |  TAB  |   4   |   5   |   6   |   -   |   +   |  HOME |   UP  |  END  |  PGUP |  TRNS |
     * |---------------------------------------------------------------------------------------|
     * |  LATL |   1   |   2   |   3   |   0           |  LEFT |  DOWN |  RGHT |  PGDN | RSHFT |
     * |---------------------------------------------------------------------------------------|
     */
  [1] = LAYOUT(
    KC_ESC,  KC_7, KC_8, KC_9, KC_SLSH, KC_ASTR, KC_DOT,  KC_COMM, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TAB,  KC_4, KC_5, KC_6, KC_MINS, KC_PLUS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
    KC_LALT, KC_1, KC_2, KC_3, KC_0,             KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_RSFT
  ),
  /* Level 2: Symbols Layer
     * ,---------------------------------------------------------------------------------------.
     * |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   -   |   +   |   =   |
     * |---------------------------------------------------------------------------------------|
     * |   {   |   }   |   [   |   ]   |  TRNS |  TRNS |   \   |   ;   |   :   |   `   |   ?   |
     * |---------------------------------------------------------------------------------------|
     * |  LSFT |  LCTL |   L   |   T   |      TAB      |   N   |  TRNS |  TRNS |  RCTL |  TRNS |
     * |---------------------------------------------------------------------------------------|
     */
  [2] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS, KC_EQL,
    KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, _______, KC_BSLS, KC_SCLN, KC_COLN, KC_GRV,  KC_QUES,
    KC_LSFT, KC_LCTL, KC_L,    KC_T,             KC_TAB,  KC_N,    _______, _______, KC_RCTL, _______
  ),
  /* Level 3: RGB Layer
     * ,---------------------------------------------------------------------------------------.
     * | RESET |  TRNS |  TRNS |  TRNS |  TRNS |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |
     * |---------------------------------------------------------------------------------------|
     * |RGB_TOG|RGB_MOD|RGB_HUI|RGB_HUD|   NO  |RGB_SAI|RGB_SAD|RGB_VAI|RGB_VAD|  TRNS |  TRNS |
     * |---------------------------------------------------------------------------------------|
     * |  TRNS |  TRNS |  TRNS |  TRNS |       F7      |   F8  |   F9  |  F10  |  F11  |  F12  |
     * |---------------------------------------------------------------------------------------|
     */
  [3] = LAYOUT(
    RESET,   _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, KC_NO,   RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______,
    _______, _______, _______, _______,          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12
  )
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_KANA)) {

  } else {

  }

}
