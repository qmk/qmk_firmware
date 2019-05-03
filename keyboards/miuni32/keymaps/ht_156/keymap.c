#include QMK_KEYBOARD_H

// Keyboard layer definitions
#define BASE    0
#define NUMBERS 1
#define SYMBOLS 2
#define MEDIA   3

// Keyboard macro defintions
#define GIT_ST  M(0)
#define GIT_PU  M(1)
#define GIT_CM  M(2)
#define HM_DIR  M(3)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Level 0: Default Layer
     * ,---------------------------------------------------------------------------------------.
     * |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |  BSP  |
     * |---------------------------------------------------------------------------------------|
     * |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |  ENT  |  RSFT |
     * |---------------------------------------------------------------------------------------|
     * |LT(2|Z)|LT(3|X)|   C   |   V   |   B   |  SPC  |   N   |   M   |   ,   |LT(1|.)|  RCTL |
     * |---------------------------------------------------------------------------------------|
     */
  [BASE] = LAYOUT_ortho_3x11(
    KC_Q,        KC_W,        KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I, KC_O,     KC_P,          KC_BSPC,
    KC_A,        KC_S,        KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K, KC_L,     KC_ENT,        KC_RSFT,
    LT(2, KC_Z), LT(3, KC_X), KC_C, KC_V, KC_B, KC_SPC, KC_N, KC_M, KC_COMMA, LT(1, KC_DOT), KC_RCTL
  ),
  /* Level 1: Numbers Layer
     * ,---------------------------------------------------------------------------------------.
     * |  ESC  |   7   |   8   |   9   |   /   |   *   |   .   |   ,   |   (   |   )   |  DEL  |
     * |---------------------------------------------------------------------------------------|
     * |  TAB  |   4   |   5   |   6   |   -   |   +   |  HOME |   UP  |  END  |  INS  |  PGUP |
     * |---------------------------------------------------------------------------------------|
     * |  LATL |   1   |   2   |   3   |   0   |  ENT  |  LEFT |  DOWN |  RGHT | !TRNS!|  PGDN |
     * |---------------------------------------------------------------------------------------|
     */
  [NUMBERS] = LAYOUT_ortho_3x11(
    KC_ESC,  KC_7, KC_8, KC_9, KC_SLSH, KC_ASTR, KC_DOT,  KC_COMM, KC_LPRN, KC_RPRN,   KC_DEL,
    KC_TAB,  KC_4, KC_5, KC_6, KC_MINS, KC_PLUS, KC_HOME, KC_UP,   KC_END,  KC_INSERT, KC_PGUP,
    KC_LALT, KC_1, KC_2, KC_3, KC_0,    KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, _______,   KC_PGDN
  ),
  /* Level 2: Symbols Layer
     * ,---------------------------------------------------------------------------------------.
     * |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   _   |   =   |   ?   |
     * |---------------------------------------------------------------------------------------|
     * | RESET |  LSFT |   ~   |   {   |   }   |   \   |   |   |   ;   |   :   |   `   |   "   |
     * |---------------------------------------------------------------------------------------|
     * | !TRNS!|  LCTL |  TRNS |   [   |   ]   |  TAB  |   <   |   >   |  TRNS |  RCTL |  TRNS |
     * |---------------------------------------------------------------------------------------|
     */
  [SYMBOLS] = LAYOUT_ortho_3x11(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_EQL, KC_QUES,
    RESET,   KC_LSFT, KC_TILD, KC_LCBR, KC_RCBR, KC_BSLS, KC_PIPE, KC_SCLN, KC_COLN, KC_GRV, KC_DQUO,
    _______, KC_LCTL, _______, KC_LBRC, KC_RBRC, KC_TAB,  KC_LABK, KC_RABK, _______, KC_RCTL, _______
  ),
  /* Level 3: Media Layer
   * ,---------------------------------------------------------------------------------------.
   * |RGB_TOG|RGB_HUI|RGB_SAI|RGB_VAI| GIT_CM|  CALC |  WREF |  WFAV |  MUTE |  VOLD |  VOLU |
   * |---------------------------------------------------------------------------------------|
   * |RGB_MOD|RGB_HUD|RGB_SAD|RGB_VAD| GIT_ST|  WHOM |  WBAK |  WFWD |  TRNS |  STOP |  PLAY |
   * |---------------------------------------------------------------------------------------|
   * |  TRNS | !TRNS!|  TRNS | HM_DIR| GIT_PU|  MYCM |  WSTP |  WSCH |  MSEL |  MPRV |  MNXT |
   * |---------------------------------------------------------------------------------------|
   */
  [MEDIA] = LAYOUT_ortho_3x11(
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, GIT_CM, KC_CALC, KC_WREF, KC_WFAV, KC_MUTE, KC_VOLD, KC_VOLU,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, GIT_ST, KC_WHOM, KC_WBAK, KC_WFWD, _______, KC_MSTP, KC_MPLY,
    _______, _______, _______, HM_DIR,  GIT_PU, KC_MYCM, KC_WSTP, KC_WSCH, KC_MSEL, KC_MPRV, KC_MNXT
  )
};

void press_and_release_key(uint8_t code)
{
    register_code(code);
    unregister_code(code);
}

void press_and_release_mod_key(uint8_t mod, uint8_t code)
{
    register_code(mod);
    register_code(code);
    unregister_code(code);
    unregister_code(mod);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id)
      {
        case 0:
          if (record->event.pressed)
          {
            return MACRO(T(G), T(I), T(T), T(SPC),
                         T(S), T(T), T(A), T(T), T(U), T(S), END);
          }
        break;
        case 1:
          if (record->event.pressed)
          {
            return MACRO(T(G), T(I), T(T), T(SPC),
                         T(P), T(U), T(L), T(L), END);
          }
        break;
        case 2:
          if (record->event.pressed)
          {
            return MACRO(T(G), T(I), T(T), T(SPC),
                         T(C), T(O), T(M), T(M), T(I), T(T), END);
          }
        break;
        case 3:
          if (record->event.pressed)
          {
            /*press_and_release_key(KC_C);
            press_and_release_key(KC_D);
            press_and_release_key(KC_SPC);
            press_and_release_mod_key(KC_LSFT, KC_GRV);
            press_and_release_key(KC_SLSH);
            press_and_release_key(KC_Q);
            press_and_release_key(KC_M);
            press_and_release_key(KC_K);
            press_and_release_mod_key(KC_LSFT, KC_MINS);*/
            return MACRO(I(0),
                         T(C), T(D), T(SPC),
                         D(LSFT), T(GRV), U(LSFT), T(SLSH),
                         T(Q), T(M), T(K), D(LSFT), T(MINS), U(LSFT),
                         T(F), T(I), T(R), T(M), T(W), T(A), T(R), T(E), T(SLSH),
                         T(K), T(E), T(Y), T(B), T(O), T(A), T(R), T(D), T(S), T(SLSH),
                         T(M), T(I), T(U), T(N), T(I), T(3), T(2), T(SLSH),
                         T(K), T(E), T(Y), T(M), T(A), T(P), T(S), END);
          }
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
