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
    _DVOLIKE,
    _DRAISE
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  DVOLIKE,
  DLOWER,
  DRAISE,
  ADJUST,
  TS_NXT_LNG,
  TS_NXT_WNDW,
  TS_PRV_WNDW,
  TS_CMD_V,
  TS_SCMD,
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
  // TS_CS_LEFT,
  // TS_CS_DOWN,
  // TS_CS_UP,
  // TS_CS_RGHT,
  TS_ITERM,
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
   * | Tab  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ;:  |  '"  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |  ,<  |  .>  |  /?  |  \|  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Cmd  | Alt  |iTerm |Shift |Lower |Space |             |Enter |Raise |Shift | Cmd  |      |  =+  |
   * `-----------------------------------------'             `-----------------------------------------'
   */
[_QWERTY] = LAYOUT_ortho_4x12(
   KC_ESC, KC_Q ,KC_W,  KC_E,  KC_R,  KC_T,              KC_Y,  KC_U,  KC_I, KC_O,   KC_P, KC_BSPACE, \
   KC_TAB, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,             KC_H,  KC_J,  KC_K, KC_L,   KC_SCLN, KC_QUOT, \
   KC_LCTL, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,            KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, \
   KC_LGUI, KC_LALT, TS_ITERM, KC_LSFT, LOWER, KC_SPC,  KC_ENT, RAISE, KC_RSFT, KC_LGUI, _______, KC_EQUAL \
   ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |  ^   |  &   |  *   |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |   (  |   )  |   `  |             |  -   |  {   |  }   |   [  |   ]  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |  _   |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |------|      |      |             |      |      |      |      |ADJUST|      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_LOWER] = LAYOUT_ortho_4x12( \
      KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______, \
      _______, _______, _______, KC_LPRN, KC_RPRN, KC_GRV,    KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, \
      _______, _______, _______, _______, _______, _______,   KC_UNDS, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, ADJUST, _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   1  |   2  |   3  |  4   |   5  |             |   6  |   7  |   8  |   9  |   0  |BSpace|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |CTL_1 |CTL_2 |CTL_3 |CTL_4 |CTL_5 |             | Left | Down | Up   |Right |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |CMD_1 |CMD_2 |CMD_3 |CMD_4 |CMD_5 |             |CMD_6 |CMD_7 |CMD_8 |CMD_9 |CMD_0 |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |AlCm3 |AlCm4 |AlCm5 |AlCm6 |      |      |             |      |------|      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_RAISE] = LAYOUT_ortho_4x12( \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPACE, \
  _______, TS_CTL_1, TS_CTL_2, TS_CTL_3, TS_CTL_4, TS_CTL_5,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, \
  _______, TS_CMD_1, TS_CMD_2, TS_CMD_3, TS_CMD_4, TS_CMD_5,   TS_CMD_6, TS_CMD_7, TS_CMD_8, TS_CMD_9, TS_CMD_0, _______, \
  TS_AC_3, TS_AC_4, TS_AC_5, TS_AC_6, _______, _______,    _______, _______, _______, _______, _______, _______ \
  ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |Dvolik|      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |------|      |             |      |------|      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_ADJUST] =  LAYOUT_ortho_4x12( \
      _______, RESET,   _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,\
      _______, _______, _______, _______, _______, _______,   DVOLIKE, _______, _______, _______, _______, _______,\
      _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,\
      _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______ \
      ),

  /* Dvorak-like custom keymap by myself
   *
   * - seealso: https://alpha.mixi.co.jp/entry/2012/10806/
   *
   * - todo: implement DLOWER if needed
   *
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |  au  |  ou  |  eu  |  \|  |   ;  |             |   F  |   G  |   C  |   R  |   T  |BSpace|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   L  |   N  |   S  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl | ann  | onn  | enn  | unn  | inn  |             |   B  |   M  |   W  |   V  |   Z  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Cmd  | Alt  |      |Lower |Shift |Space |             |Enter |Raise |Shift |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_DVOLIKE] = LAYOUT_ortho_4x12(
      KC_ESC,  TS_AU, TS_OU, TS_EU, KC_BSLS, KC_SCLN,       KC_F, KC_G, KC_C, KC_R, KC_T, KC_BSPACE, \
      KC_TAB, KC_A, KC_O, KC_E, KC_U, KC_I,                 KC_D, KC_H, KC_L, KC_N, KC_S, _______, \
      KC_LCTL, TS_ANN, TS_ONN, TS_ENN, TS_UNN, TS_INN,      KC_B, KC_M, KC_W, KC_V, KC_Z, _______, \
      KC_LGUI, KC_LALT, _______, DLOWER, KC_LSFT, KC_SPC,   KC_ENT, DRAISE, KC_RSFT, _______, _______, _______ \
      ),

  /* Dvolike Raised
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |  `~  |  '"  |  <,  |  .>  |             |   P  |   Y  |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  ~   |  !   |   @  |   #  |   $  |   %  |             |   Q  |   J  |   K  |   X  |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |   ^  |   &  |   *  |             | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |------|      |      |      |QWERTY|
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_DRAISE] = LAYOUT_ortho_4x12(
      _______, _______,  KC_GRV, KC_QUOT, KC_COMM, KC_DOT,  KC_P,   KC_Y, _______, _______, _______, _______, \
      KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,   KC_Q,   KC_J,   KC_K,    KC_X, _______, _______, \
      _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QWERTY \
      ),

};

// define variables for reactive RGB
bool TOG_STATUS = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TS_NXT_LNG:
      // Ctl + space
      SEND_STRING(SS_LCTRL(" "));
      return false;
      break;
    case TS_NXT_WNDW:
      // Cmd + ]
      SEND_STRING(SS_LGUI("]"));
      return false;
      break;
    case TS_PRV_WNDW:
      // Cmd + [
      SEND_STRING(SS_LGUI("["));
      return false;
      break;
    case TS_CMD_V:
      // Cmd + V
      SEND_STRING(SS_LGUI("V"));
      return false;
      break;
    case TS_SCMD:
      // Shift + Cmd
      if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSHIFT));
      } else {
          SEND_STRING(SS_UP(X_LGUI) SS_UP(X_LSHIFT));
      }
      return false;
      break;
    case TS_ITERM:
      // ctl shift cmd alt + i
      SEND_STRING(SS_LGUI(SS_LSFT(SS_LALT(SS_LCTRL("i"))))); return false;
      break;
    case TS_CTL_1:
      // Ctrl + 1
      SEND_STRING(SS_LCTRL("1"));
      return false;
      break;
    case TS_CTL_2:
      // Ctrl + 2
      SEND_STRING(SS_LCTRL("2"));
      return false;
      break;
    case TS_CTL_3:
      // Ctrl + 3
      SEND_STRING(SS_LCTRL("3"));
      return false;
      break;
    case TS_CTL_4:
      // Ctrl + 4
      SEND_STRING(SS_LCTRL("4"));
      return false;
      break;
    case TS_CTL_5:
      // Ctrl + 5
      SEND_STRING(SS_LCTRL("5"));
      return false;
      break;
    case TS_CMD_1:
      // Cmd + 1
      SEND_STRING(SS_LGUI("1"));
      return false;
      break;
    case TS_CMD_2:
      // Cmd + 2
      SEND_STRING(SS_LGUI("2"));
      return false;
      break;
    case TS_CMD_3:
      // Cmd + 3
      SEND_STRING(SS_LGUI("3"));
      return false;
      break;
    case TS_CMD_4:
      // Cmd + 4
      SEND_STRING(SS_LGUI("4"));
      return false;
      break;
    case TS_CMD_5:
      // Cmd + 5
      SEND_STRING(SS_LGUI("5")); return false; break;
    case TS_CMD_6:
      // Cmd + 6
      SEND_STRING(SS_LGUI("6")); return false; break;
    case TS_CMD_7:
      // Cmd + 7
      SEND_STRING(SS_LGUI("7")); return false; break;
    case TS_CMD_8:
      // Cmd + 8
      SEND_STRING(SS_LGUI("8")); return false; break;
    case TS_CMD_9:
      // Cmd + 9
      SEND_STRING(SS_LGUI("9")); return false; break;
    case TS_CMD_0:
      // Cmd + 0
      SEND_STRING(SS_LGUI("0")); return false; break;
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
//    case TS_CS_LEFT:
//      // Control + Shift + Left
//      SEND_STRING(SS_LCTRL(SS_LSFT(KC_LEFT)));
//      return false;
//      break;
//    case TS_CS_DOWN:
//      // Control + Shift + Down
//      SEND_STRING(SS_LCTRL(SS_LSFT(KC_DOWN)));
//      return false;
//      break;
//    case TS_CS_UP:
//      // Control + Shift + Up
//      SEND_STRING(SS_LCTRL(SS_LSFT(KC_UP)));
//      return false;
//      break;
//    case TS_CS_RGHT:
//      // Control + Shift + Right
//      SEND_STRING(SS_LCTRL(SS_LSFT(KC_RIGHT)));
//      return false;
//      break;
    case TS_AC_3:
      // Control + Alt + 3
      SEND_STRING(SS_LCTRL(SS_LALT("3")));
      return false;
      break;
    case TS_AC_4:
      // Control + Alt + 4
      SEND_STRING(SS_LCTRL(SS_LALT("4")));
      return false;
      break;
    case TS_AC_5:
      // Control + Alt + 5
      SEND_STRING(SS_LCTRL(SS_LALT("5")));
      return false;
      break;
    case TS_AC_6:
      // Control + Alt + 6
      SEND_STRING(SS_LCTRL(SS_LALT("6")));
      return false;
      break;
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

    case DRAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
        }
        layer_on(_DRAISE);
      } else {
        layer_off(_DRAISE);
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

    case DVOLIKE:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVOLIKE);
      }
      return false;
      break;

  }
  return true;
}
