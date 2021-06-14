#include QMK_KEYBOARD_H
#include "kageurufu.h"

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

#define FN_CAPS  LT(_FN, KC_CAPS)

// Define your non-alpha grouping in this define's LAYOUT, and all your BASE_LAYERS will share the same mod/macro columns
  /*  / Base Layout \
   * /-----------------------------------------\  /-----------------------------------------\
   * | GESC |  1   |  2   |  3   |  4   |  5   |  |  6   |  7   |  8   |  9   |  0   | BkSp |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Tab  |      |      |      |      |      |  |      |      |      |      |      |   \  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |FNCAPS|      |      |      |      |      |  |      |      |      |      |      |   '  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |Shift |      |      |      |      |      |  |      |      |      |      |      |Shift |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space|  | Space|  FN  | Left | Down | Up   |Right |
   * \------+------+------+------+------+------/  \------+------+------+------+------+------/
   */
#define EXPAND_LAYOUT(...) LAYOUT_ortho_5x12(__VA_ARGS__)
#define _BASE_LAYOUT( \
  _00, _01, _02, _03, _04,  _05, _06, _07, _08, _09, \
  _10, _11, _12, _13, _14,  _15, _16, _17, _18, _19, \
  _20, _21, _22, _23, _24,  _25, _26, _27, _28, _29 \
) \
EXPAND_LAYOUT( \
      KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
      KC_TAB,  _00,     _01,     _02,     _03,     _04,    _05,     _06,     _07,     _08,     _09,     KC_BSLS, \
      FN_CAPS, _10,     _11,     _12,     _13,     _14,    _15,     _16,     _17,     _18,     _19,     KC_QUOT, \
      KC_LSFT, _20,     _21,     _22,     _23,     _24,    _25,     _26,     _27,     _28,     _29,     KC_ENT, \
      KC_LCTL, KC_LGUI, KC_LALT, RGB_TOG,  ADJ,    KC_SPC, KC_SPC,  FN,      KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT \
)
#define BASE_LAYOUT(...) _BASE_LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = BASE_LAYOUT( \
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, \
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, \
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________ \
  ),

  [_COLEMAK] = BASE_LAYOUT( \
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, \
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, \
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________ \
  ),

  [_FN] = EXPAND_LAYOUT( \
    ________________FUNCTION_L1________________, ________________FUNCTION_R1________________, \
    ________________FUNCTION_L2________________, ________________FUNCTION_R2________________, \
    ________________FUNCTION_L3________________, ________________FUNCTION_R3________________, \
    ________________FUNCTION_L4________________, ________________FUNCTION_R4________________, \
    ________________FUNCTION_L5________________, ________________FUNCTION_R5________________ \
  ),

  [_ADJ] =  EXPAND_LAYOUT( \
    _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, \
    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, \
    _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, \
    _________________ADJUST_L4_________________, _________________ADJUST_R4_________________, \
    _________________ADJUST_L5_________________, _________________ADJUST_R5_________________ \
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
