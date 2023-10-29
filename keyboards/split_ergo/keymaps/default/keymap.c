#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,--------------------------------------------------------------------------------------.
 * |    | Esc |  Q  |   W  |   E  |   R  |  T  |   Y  |   U  |   I  |   O  |  P | [ | ]   |
 * |----+-----+-----+------+------+------+-----|------+------+------+------+----+---+-----|
 * |    | Tab |  A  |   S  |   D  |   F  |  G  |   H  |   J  |   K  |   L  |  ; | ' |Enter|
 * |----+-----+-----+------+------+------+-----|------+------+------+------+----+---+-----|
 * |GUI |Shift|  Z  |   X  |   C  |   V  |  B  |   N  |   M  |   ,  |   .  |  / |   |Shift|
 * |----+-----+-----+------+------+------+-----|------+------+------+------+----+---+-----|
 * |GUI | Ctrl| Up  | Down | Alt  | Bksp |Lower|Raise | space|Left  | Right|    |   |Shift|
 * `--------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x14(
   _______, KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
   _______, KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
   KC_LGUI, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, _______,
   KC_RGUI, KC_LCTL, KC_UP,   KC_DOWN, KC_LALT, LOWER,  KC_BSPC,  KC_SPC,  RAISE,   KC_RCTL, KC_LEFT, KC_RGHT, KC_RALT, _______
),

/* Dvorak  TODO!  Defaults to QWERTY now.
 */
[_DVORAK] = LAYOUT_ortho_4x14(
   _______, KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
   _______, KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
   KC_LGUI, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, _______,
   KC_RGUI, KC_LCTL, KC_UP,   KC_DOWN, KC_LALT, LOWER,  KC_BSPC,  KC_SPC,  RAISE,   KC_RCTL, KC_LEFT, KC_RGHT, KC_RALT, _______
),

/* Lower
 * ,--------------------------------------------------------------------------------------.
 * |    |     | F1  |  F2  |  F3  |  F4  |  F5 |  F6  |  F7  |  F8  |  F9  | F10|F11| F12 |
 * |----+-----+-----+------+------+------------+------+------+------+------+----+---+-----|
 * |    |     |     |      |      |      |     |      |      |      |      |    |   |     |
 * |----+-----+-----+------+------+------|-----+------+------+------+------+----+---+-----|
 * |    |     |     |      |      |      |     |      |      |      |      |    |   |     |
 * |----+-----+-----+------+------+------+-----+------+------+------+------+----+---+-----|
 * |    |     |     |      |      |      | DEL |      |      |      |      |    |   |     |
 * `--------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x14(
  _______, _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, KC_F12,
  _______, _______, _______, _______, _______, _______, _______, KC_WH_U, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_WH_D, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,  KC_DEL, _______, _______, _______, _______, _______, _______, _______
),

/* Raise
 * ,--------------------------------------------------------------------------------------.
 * |    |  `  | 1   |  2   |  3   |  4   |  5  |  6   |  7   |  8   |  9   | 0  | - |  =  |
 * |----+-----+-----+------+------+------------+------+------+------+------+----+---+-----|
 * |    |     | Prev| play | Next |      |     |      |      |      |      |    |   |     |
 * |----+-----+-----+------+------+------|-----+------+------+------+------+----+---+-----|
 * |    |     |     |      |      |      |     |      |      |      |      |    |   |     |
 * |----+-----+-----+------+------+------+-----+------+------+------+------+----+---+-----|
 * |    |     |     |      |      |      | DEL |      |      |      |      |    |   |     |
 * `--------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x14(
  _______,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,  KC_DEL, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,--------------------------------------------------------------------------------------.
 * |    | Boot| 1   |  2   |  3   |  4   |  5  |  6   |  7   |  8   |  9   | 0  |   |     |
 * |----+-----+-----+------+------+------------+------+------+------+------+----+---+-----|
 * |    |     |     |      |      |      |     |      |      |      |      |    |   |     |
 * |----+-----+-----+------+------+------|-----+------+------+------+------+----+---+-----|
 * |    |     |     |      |      |      |     |      |      |      |      |    |   |     |
 * |----+-----+-----+------+------+------+-----+------+------+------+------+----+---+-----|
 * |    |     |     |      |      |      |     |      |      |      |      |    |   |     |
 * `--------------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x14(
  _______, QK_BOOT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_PGUP, KC_HOME,   KC_UP,  KC_END,    KC_0, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
  }
  return true;
}
