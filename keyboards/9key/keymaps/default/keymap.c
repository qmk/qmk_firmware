#include "9key.h"

// Tap Dance Declarations
enum {
  ENT_5 = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER 0
 * ,-----------------.
 * |  1  |  2  |  3  |
 * |-----+-----+-----|
 * |  4  |5/ENT|  6  | Dbl Tap 5 for Enter
 * |-----+-----+-----|
 * |  7  |  8  | FN  | 
 * `-----------------'
 */
[0] = KEYMAP( \
  KC_1, KC_2, KC_3, \
  KC_4, TD(ENT_5), KC_6, \
  KC_7, KC_8, MO(1) \
),

/* LAYER 1
 * ,-----------------.
 * |  9  |  0  |  -  |
 * |-----+-----+-----|
 * |  +  |  *  |  /  |
 * |-----+-----+-----|
 * | F1  | F2  |     |
 * `-----------------'
 */
[1] = KEYMAP( \
  KC_9,    KC_0,    KC_MINS, \
  KC_PLUS, KC_ASTR, KC_SLSH, \
  KC_F1,   KC_F2,   KC_TRNS  \
)

};

qk_tap_dance_action_t tap_dance_actions[] = {
  [ENT_5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_ENT)
};

void matrix_init_user(void) {
}