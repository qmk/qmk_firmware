#include QMK_KEYBOARD_H
//Tap Dance Declarations
enum {
  TD_WINW = 0
  //,TD_F5
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_WINW]  = ACTION_TAP_DANCE_DOUBLE(KC_W, KC_LGUI)
  //,[TD_F5]  = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_F5)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Level 0: Default Layer
     * ,---------------------------------------------------------------------------------------.
     * |LCTL/Q |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | BKSP  |
     * |---------------------------------------------------------------------------------------|
     * |LSFT/A |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |  ENT  |LT(1|,)|
     * |---------------------------------------------------------------------------------------|
     * |LT(3|Z)|   X   |   C   |   V   |   B   |  SPC  |   B   |   N   |   M   |  RSFT |LT(2|.)|
     * |---------------------------------------------------------------------------------------|
     */
  [0] = LAYOUT_ortho_3x11(
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K, KC_L, KC_SCLN,  RSFT_T(KC_ENT),
    LCTL_T(KC_Z), LALT_T(KC_X), LT(3,KC_C), LT(2,KC_V), KC_B, KC_SPC, LT(1,KC_N), KC_M, KC_COMM, RALT_T(KC_DOT), RCTL_T(KC_QUES)
  ),
  /* Level 1: Numbers Layer
     * ,---------------------------------------------------------------------------------------.
     * |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |  DEL  |
     * |---------------------------------------------------------------------------------------|
     * |   F1  |  F2   |  F3   |  F4   |  F5   |  F6   |   _   |   +   |   /   |   \   |  TRNS |
     * |---------------------------------------------------------------------------------------|
     * |   F7 |   F8   |   F9  | F10   | F11   |  F12  |   -   |   =   |  RGHT |  PGDN | RSHFT |
     * |---------------------------------------------------------------------------------------|
     */
  [1] = LAYOUT_ortho_3x11(
    KC_1,  KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,  KC_8, KC_9, KC_0, KC_DEL,
    KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
    KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  KC_SLASH,KC_LEFT,KC_RIGHT,KC_DOWN, KC_UP
  ),
  /* Level 2: Symbols Layer
     * ,---------------------------------------------------------------------------------------.
     * |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   (   |   )   |  ESC  |
     * |---------------------------------------------------------------------------------------|
     * |   {   |   }   |   [   |   ]   |  TRNS |  TRNS |   \   |   ;   |   :   |   `   |   ?   |
     * |---------------------------------------------------------------------------------------|
     * |  LSFT |  LCTL |   L   |   T   |      TAB      |   N   |  TRNS |  TRNS |  RCTL |  TRNS |
     * |---------------------------------------------------------------------------------------|
     */
  [2] = LAYOUT_ortho_3x11(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_ESC,
    _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______,  KC_QUES,
    KC_CAPS, KC_LCTL, _______, _______,   _______, _______,  _______, KC_LEFT,KC_RIGHT,KC_DOWN, KC_UP
  ),
  /* Level 3: RGB Layer
     * ,---------------v------------------------------------------------------------------------.
     * | RESET |  TRNS |  TRNS |  TRNS |  TRNS |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |
     * |---------------------------------------------------------------------------------------|
     * |RGB_TOG|RGB_MOD|RGB_HUI|RGB_HUD|   NO  |RGB_SAI|RGB_SAD|RGB_VAI|RGB_VAD|  TRNS |  TRNS |
     * |---------------------------------------------------------------------------------------|
     * |  TRNS |  TRNS |  TRNS |  TRNS |       F7      |   F8  |   F9  |  F10  |  F11  |  F12  |
    ------------|
     */
  [3] = LAYOUT_ortho_3x11(
    RESET,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,_______,RESET,
    KC_TAB, _______, _______, _______, _______,  _______,  KC_MINS, KC_EQL,KC_GRV, _______, KC_SCLN,
    _______, KC_LGUI, _______, _______, _______,  _______,  _______, KC_HOME,KC_END,KC_PGDN, KC_PGUP
  )
};



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
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
