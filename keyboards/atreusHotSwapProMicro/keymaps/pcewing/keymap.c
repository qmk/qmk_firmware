#include QMK_KEYBOARD_H

#define FN MO(_FN)
#define TODO KC_NO

enum atreus62_layers {
  _DEFAULT,
  _FN,
  _RESET
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default layer
   * ,-----------------------------------------.                ,-----------------------------------------.
   * |  =   |   1  |   2  |   3  |   4  |   5  |                |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |,------.,------.|   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  ||Delete||Enter ||   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * | Ctrl | Win  | Alt  |  `   |  Fn  | Bksp |`------'`------'|Space |  Fn  |      | Alt  | Win  | Ctrl |
   * `-----------------------------------------'                `-----------------------------------------'
   */
  [_DEFAULT] = LAYOUT( /* qwerty */
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_GRV,  FN,      KC_BSPC, KC_DEL,   KC_ENT,   KC_SPC,  FN,      TODO,    KC_RALT, KC_RGUI, KC_RCTL
  ),

  /* Function layer
   * ,-----------------------------------------.                ,-----------------------------------------.
   * |      |      |      |      |      |      |                |      | F10  | F11  | F12  |      |      |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |      | Home | Up   | End  | PgUp |      |                | PrSc |  F7  |  F8  |  F9  |      |      |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * | Caps | Left | Down |Right | PgDn |      |,------.,------.|Pause |  F4  |  F5  |  F6  |      |      |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |      |  {   |  }   |  [   |  ]   |      ||      ||      ||Insert|  F1  |  F2  |  F3  |      |      |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |      |      |      |      |      |      |`------'`------'|      |      |      |      |      |      |
   * `-----------------------------------------'                `-----------------------------------------'
   */
  [_FN] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, KC_F10,  KC_F11,  KC_F12,  _______, TO(_RESET),
    _______, KC_HOME, KC_UP,   KC_END,  KC_PGDN, _______,                   KC_PSCR, KC_F7,   KC_F8,   KC_F9,   _______, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, _______,                   KC_PAUS, KC_F4,   KC_F5,   KC_F6,   _______, _______,
    _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______,                   KC_INS,  KC_F1,   KC_F2,   KC_F3,   _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /*
   * This layer makes it possible to reset the firmware; don't get rid of it and make sure there is a way to activate it.
   */
  [_RESET] = LAYOUT(
    TO(_DEFAULT), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RESET
  )

  /*
  [_TRNS] = LAYOUT(
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  */
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch (id) {
  case 0:
    if (record->event.pressed) {
      register_code(KC_RSFT);
    }
    else {
      unregister_code(KC_RSFT);
    }
    break;
  }
  return MACRO_NONE;
};
