#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  DLOWER,
  DRAISE,
  ADJUST,
  TS_CTL_1,
  TS_CTL_2,
  TS_CTL_3,
  TS_CTL_4,
  TS_CTL_5,
  TS_CMD_1,
  TS_CMD_2,
  TS_CMD_3,
  TS_CMD_4,
  TS_CMD_5,
  TS_CMD_6,
  TS_CMD_7,
  TS_CMD_8,
  TS_CMD_9,
  TS_CMD_0,
  TS_CMD_TAB,
  TS_CMD_SPC,
  TS_CMD_ENTER,
  TS_AC_3,
  TS_AC_4,
  TS_AC_5,
  TS_AC_6,

  // DVOLIKE
  TS_AU, TS_OU, TS_EU,
  TS_ANN, TS_ONN, TS_ENN, TS_UNN, TS_INN,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |BSpace|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Alt  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ;:  |  '"  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |Space |   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |  ,<  |  .>  |  /?  |  \|  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      | Cmd  | Ctrl |Lower |             |Raise |Enter |Shift |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_QWERTY] = LAYOUT_ortho_4x12(
   KC_ESC, KC_Q ,KC_W,  KC_E,  KC_R,  KC_T,              KC_Y,  KC_U,  KC_I, KC_O,   KC_P, KC_BSPACE, \
   KC_LALT, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,             KC_H,  KC_J,  KC_K, KC_L,   KC_SCLN, KC_QUOT, \
   KC_SPC, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,             KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, \
   _______, _______, _______, KC_LGUI, KC_LCTL, LOWER,   RAISE, KC_ENT, KC_RSFT, _______, _______, _______ \
   ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |  ^   |  &   |  *   |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |   (  |   )  |   `  |             |  -   |  {   |  }   |   [  |   ]  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |RESET |             |  _   |  +   |  =   |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |------|             |ADJUST|      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_LOWER] =  LAYOUT_ortho_4x12( \
      KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______,\
      KC_TAB, _______, _______, KC_LPRN, KC_RPRN, KC_GRV,    KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, \
      _______, _______, _______, _______, _______, _______,  KC_UNDS, KC_PLUS, KC_EQUAL, _______, _______, _______,\
      _______, _______, _______, _______, _______, _______,  ADJUST, _______, _______, _______, _______, _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   1  |   2  |   3  |  4   |   5  |             |   6  |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |CTL_1 |CTL_2 |CTL_3 |CTL_4 |CTL_5 |             | Left | Down | Up   |Right |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |CMD_1 |CMD_2 |CMD_3 |CMD_4 |CMD_5 |             |CMD_6 |CMD_7 |CMD_8 |CMD_9 |CMD_0 |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |ADJUST|             |------|Shift |      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_RAISE] = LAYOUT_ortho_4x12( \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  _______, \
  _______, TS_CTL_1, TS_CTL_2, TS_CTL_3, TS_CTL_4, TS_CTL_5,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, \
  _______, TS_CMD_1, TS_CMD_2, TS_CMD_3, TS_CMD_4, TS_CMD_5,   TS_CMD_6, TS_CMD_7, TS_CMD_8, TS_CMD_9, TS_CMD_0, _______, \
  _______, _______, _______, _______, _______, ADJUST,        _______, KC_LSFT, _______, _______, _______, _______ \
  ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |  ^   |  &   |  *   |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |   (  |   )  |   `  |             |  -   |  {   |  }   |   [  |   ]  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |RESET |             |  _   |  +   |  =   |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |------|             |------|      |      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_ADJUST] =  LAYOUT_ortho_4x12( \
      KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______,\
      _______, _______, _______, KC_LPRN, KC_RPRN, KC_GRV,   KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, \
      _______, _______, _______, _______, _______, RESET,    KC_UNDS, KC_PLUS, KC_EQUAL, _______, _______, _______,\
      _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______ \
      ),

};

// define variables for reactive RGB
bool TOG_STATUS = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TS_CTL_1:
      // Ctrl + 1
      if (record->event.pressed) { SEND_STRING(SS_LCTRL("1")); return false; }; break;
    case TS_CTL_2:
      // Ctrl + 2
      if (record->event.pressed) { SEND_STRING(SS_LCTRL("2")); return false; }; break;
    case TS_CTL_3:
      // Ctrl + 3
      if (record->event.pressed) { SEND_STRING(SS_LCTRL("3")); return false; }; break;
    case TS_CTL_4:
      // Ctrl + 4
      if (record->event.pressed) { SEND_STRING(SS_LCTRL("4")); return false; }; break;
    case TS_CTL_5:
      // Ctrl + 5
      if (record->event.pressed) { SEND_STRING(SS_LCTRL("5")); return false; }; break;
    case TS_CMD_1:
      // Cmd + 1
      if (record->event.pressed) { SEND_STRING(SS_LGUI("1")); return false; }; break;
    case TS_CMD_2:
      // Cmd + 2
      if (record->event.pressed) { SEND_STRING(SS_LGUI("2")); return false; }; break;
    case TS_CMD_3:
      // Cmd + 3
      if (record->event.pressed) { SEND_STRING(SS_LGUI("3")); return false; }; break;
    case TS_CMD_4:
      // Cmd + 4
      if (record->event.pressed) { SEND_STRING(SS_LGUI("4")); return false; }; break;
    case TS_CMD_5:
      // Cmd + 5
      if (record->event.pressed) { SEND_STRING(SS_LGUI("5")); return false; }; break;
    case TS_CMD_6:
      // Cmd + 6
      if (record->event.pressed) { SEND_STRING(SS_LGUI("6")); return false; }; break;
    case TS_CMD_7:
      // Cmd + 7
      if (record->event.pressed) { SEND_STRING(SS_LGUI("7")); return false; }; break;
    case TS_CMD_8:
      // Cmd + 8
      if (record->event.pressed) { SEND_STRING(SS_LGUI("8")); return false; }; break;
    case TS_CMD_9:
      // Cmd + 9
      if (record->event.pressed) { SEND_STRING(SS_LGUI("9")); return false; }; break;
    case TS_CMD_0:
      // Cmd + 0
      if (record->event.pressed) { SEND_STRING(SS_LGUI("0")); return false; }; break;
    case TS_AC_3:
      // Control + Alt + 3
      if (record->event.pressed) { SEND_STRING(SS_LCTRL(SS_LALT("3"))); return false; }; break;
    case TS_AC_4:
      // Control + Alt + 4
      if (record->event.pressed) { SEND_STRING(SS_LCTRL(SS_LALT("4"))); return false; }; break;
    case TS_AC_5:
      // Control + Alt + 5
      if (record->event.pressed) { SEND_STRING(SS_LCTRL(SS_LALT("5"))); return false; }; break;
    case TS_AC_6:
      // Control + Alt + 6
      if (record->event.pressed) { SEND_STRING(SS_LCTRL(SS_LALT("6"))); return false; }; break;
    case TS_AU:
      // au
      SEND_STRING("au"); return false; break;
    case TS_OU:
      // ou
      SEND_STRING("ou"); return false; break;
    case TS_EU:
      // eu
      SEND_STRING("eu"); return false; break;
    case TS_ANN:
      // ann
      SEND_STRING("ann"); return false; break;
    case TS_ONN:
      // onn
      SEND_STRING("onn"); return false; break;
    case TS_ENN:
      // enn
      SEND_STRING("enn"); return false; break;
    case TS_UNN:
      // unn
      SEND_STRING("unn"); return false; break;
    case TS_INN:
      // inn
      SEND_STRING("inn"); return false; break;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
        }
        layer_on(_LOWER);
      } else {
        TOG_STATUS = false;
        layer_off(_LOWER);
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
        }
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
        TOG_STATUS = false;
      }
      return false;
      break;

    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;

  }
  return true;
}
