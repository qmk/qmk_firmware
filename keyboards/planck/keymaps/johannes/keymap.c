#include "planck.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | super|shift | Space|Raise | lower|  alt | altgr|      |fn    |
 * `-----------------------------------------------------------------------------------'
 */
[0] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LCTRL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, KC_LSHIFT,    KC_SPC,  M(2),   M(1),   KC_LALT, KC_RALT, XXXXXXX,   M(3)}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  {   |  }   |  +   |      |      | Å    |  Ä   |  Ö   |   _  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |   \  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[1] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {_______, _______,   KC_LCBR,   KC_RCBR,   KC_PLUS,   _______,   _______,   M(4), M(5), M(6), KC_UNDS, _______},
  {_______, _______,   _______,   _______,   _______,  _______,  _______,_______, _______,_______, KC_BSLS, _______},
  {_______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  [   |  ]   |  =   |      |  left|  down|  up  | right|   -  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |   |  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[2] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
  {_______,  _______,   KC_LBRC,   KC_RBRC,   KC_EQL,   _______,   KC_LEFT,   KC_DOWN, KC_UP,  KC_RIGHT, KC_MINS, _______},
  {_______, _______,   _______,   _______,   _______,  _______,  _______,  _______, _______, _______, KC_PIPE, _______},
  {_______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

// Fn-layer
[3] = {
  {KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12},
  {_______,  _______,   _______,   _______,   _______,   _______,   _______,   _______, _______,  _______, _______, _______},
  {_______, _______,   _______,   _______,   _______,  _______,  _______,  _______, _______, _______, _______, _______},
  {_______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case 1:
      if (record->event.pressed) {
        layer_on(1);
      } else {
        layer_off(1);
      }
      break;
    case 2:
      if (record->event.pressed) {
        layer_on(2);
      } else {
        layer_off(2);
      }
      break;
	  case 3:
      if (record->event.pressed) {
        layer_on(3);
      } else {
        layer_off(3);
      }
      break;
    case 4: // å
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_W);
      } else {
        unregister_code(KC_RALT);
      }
      break;
    case 5: // ä
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_Q);
      } else {
        unregister_code(KC_RALT);
      }
      break;
	  case 6: // ö
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_P);
      } else {
        unregister_code(KC_RALT);
      }
      break;
  }
  return MACRO_NONE;
};
