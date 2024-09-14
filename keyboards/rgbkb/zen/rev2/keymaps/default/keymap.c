#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _NAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.              .-----------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |              |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * |CAPS(NAV)|A  |   S  |   D  |   F  |   G  |              |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+------..------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |RGBPrv||RGBNxt|   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  |RGBTOG| NAV  |Space |Delete||Enter |Space |  NAV |   -  |   =  | PGUP | PGDN |
   * `----------------------------------+-------------''------------------------------------------------'
   *                                    |Space |Delete||Enter |Space |
   *                                    '-------------''-------------'
   */
  [_QWERTY] = LAYOUT(
    QK_GESC,          KC_1,    KC_2,    KC_3,    KC_4,     KC_5,                       KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                       KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSLS,
    LT(_NAV, KC_CAPS),KC_A,    KC_S,    KC_D,    KC_F,     KC_G,                       KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    UG_PREV, UG_NEXT,  KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL,          KC_LGUI, KC_LALT, UG_TOGG, MO(_NAV), KC_SPC,  KC_DEL,  KC_ENT,   KC_SPACE, MO(_NAV), KC_MINS, KC_EQL,  KC_PGUP, KC_PGDN,
                                                           KC_SPC,  KC_DEL,  KC_ENT,   KC_SPACE
  ),

  /* NAV
   * ,-----------------------------------------.              .-----------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |              |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * |CAPS(NAV)|A  |   S  |   D  |   F  |   G  |              |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+------..------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      ||      |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  |RGBTOG| NAV  |Space |Delete||Enter |Space |  NAV |   -  |   =  | PGUP | PGDN |
   * `----------------------------------+-------------''------------------------------------------------'
   *                                    |Space |Delete||Enter |Space |
   *                                    '-------------''-------------'
   */
  [_NAV] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, UG_SATU, UG_VALU, UG_SATD, QK_BOOT, KC_LBRC,                   KC_RBRC, KC_PGUP,  KC_UP,   KC_PGDN, KC_INS,  KC_HOME,
    _______, UG_HUED, UG_VALD, UG_HUEU, _______, _______,                   _______, KC_LEFT,  KC_DOWN, KC_RGHT, KC_DEL,  KC_END,
    KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_MPLY, KC_MPRV, KC_MNXT,
    KC_LCTL, KC_LGUI, KC_LALT, UG_NEXT, _______, _______, _______, _______, _______, _______,  _______, KC_MUTE, KC_VOLU, KC_VOLD,
                                                 _______, _______, _______, _______
  ),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
  } else if (index == 1) { /* Second encoder from slave */
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
    return true;
}

#if OLED_ENABLE
const char* layer_name_user(uint32_t layer) {
  switch (layer) {
    case _QWERTY:
      return PSTR("QWRTY");
    case _NAV:
      return PSTR("NAV\n");
    default:
      return PSTR("UNDEF");
  }
}
#endif
