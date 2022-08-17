#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _FN,
    _ADJ
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  FN,
  ADJ,
  RGBRST
};

#define FN_CAPS  LT(_FN, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*  / QWERTY \
   * /-----------------------------------------\  /-----------------------------------------\
   * | GESC |  1   |  2   |  3   |  4   |  5   |  |  6   |  7   |  8   |  9   |  0   | BkSp |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |FNCAPS|   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space|  | Space|  FN  | Left | Down | Up   |Right |
   * \------+------+------+------+------+------/  \------+------+------+------+------+------/
   */
  [_QWERTY] = LAYOUT_ortho_5x12(
    KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
    FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
    KC_LCTL, KC_LGUI, KC_LALT, RGB_TOG,     ADJ,  KC_SPC, KC_SPC,      FN, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT
  ),

  /*  / Colemak \
   * /-----------------------------------------\  /-----------------------------------------\
   * | GESC |  1   |  2   |  3   |  4   |  5   |  |  6   |  7   |  8   |  9   |  0   | BkSp |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   B  |  |   J  |   L  |   U  |   Y  |   ;  |   \  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |FNCAPS|   A  |   R  |   S  |   T  |   G  |  |   K  |   N  |   E  |   I  |   O  |   '  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   D  |   V  |  |   M  |   H  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space|  | Space|  FN  | Left | Down | Up   |Right |
   * \------+------+------+------+------+------/  \------+------+------+------+------+------/
   */
  [_COLEMAK] = LAYOUT_ortho_5x12(
    KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
     KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,   KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSLS,
    FN_CAPS,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,   KC_K,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,   KC_M,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
    KC_LCTL, KC_LGUI, KC_LALT, RGB_TOG,     ADJ,  KC_SPC, KC_SPC,      FN, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT
  ),

  /*  / FN \
   * /-----------------------------------------\  /-----------------------------------------\
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      | PGDN |  UP  | PGUP |      |      |  |      | PGDN |  UP  | PGUP | PRINT| HOME |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|      |      |  |      | LEFT | DOWN | RIGHT|INSERT| END  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |  |      |      |      |      |      |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |      |      |RGBMOD|      |      |  |      | PLAY | NEXT | MUTE | VOL- | VOL+ |
   * \------+------+------+------+------+------/  \------+------+------+------+------+------/
   */
  [_FN] = LAYOUT_ortho_5x12(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
    _______, KC_PGDN, KC_UP,   KC_PGUP, _______, _______, _______, KC_PGDN, KC_UP,   KC_PGUP, KC_PSCR, KC_HOME,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,   KC_END,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, RGB_MOD, _______, _______, _______, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU
  ),

  /*  / ADJ \
   * /-----------------------------------------\  /-----------------------------------------\
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      | SAD  | VAI  | SAI  | QK_BOOT|      |  |      |      |      |      |      |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      | HUD  | VAD  | HUI  |RGBRST|      |  |      |QWERTY|COLEMK|      |      |      |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |  |      |      |RGBTOG|  HUI |  SAI | VAI  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |      |      |      |RGBNXT|      |      |  |      |      |RGBPRV|  HUD |  SAD | VAD  |
   * \------+------+------+------+------+------/  \------+------+------+------+------+------/
   */
  [_ADJ] =  LAYOUT_ortho_5x12(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
    _______, RGB_SAD, RGB_VAI, RGB_SAI, QK_BOOT,   _______, _______, _______, _______, _______, _______, _______,
    _______, RGB_HUD, RGB_VAD, RGB_HUI, RGBRST,  _______, _______, QWERTY,  COLEMAK, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
    _______, _______, _______, RGB_MOD, _______, _______, _______, _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD
  )
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if(record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
      } else {
        layer_off(_FN);
      }
      return false;
    case ADJ:
      if (record->event.pressed) {
        layer_on(_ADJ);
      } else {
        layer_off(_ADJ);
      }
      return false;
    case RGBRST:
#ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
#endif
      break;
  }
  return true;
}
