#include "keymap_common.h"
#include "beeps.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = { /* Qwerty */
  {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_BSPC,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC},
  {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_ENT,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT},
  {KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ESC,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {M(10), KC_LCTL, KC_LALT, KC_LGUI, FUNC(2),    KC_SPC,   KC_SPC,    FUNC(1),   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
                                                // Space is repeated to accommadate for both spacebar wiring positions
},
[1] = { /* Colemak */
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {KC_FN3, KC_LCTL, KC_LALT, KC_LGUI, FUNC(2),    KC_SPC,   KC_SPC,    FUNC(1),   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
},
[2] = { /* RAISE */
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TRNS, FUNC(3), FUNC(4), RESET, M(0), M(1), M(2), KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_F11,  KC_F12,  M(0),   M(1),   M(2),   M(3),   M(4),   M(5),   M(6),   M(7), KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,  FUNC(1),   KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[3] = { /* LOWER */
  {S(KC_GRV),  S(KC_1),    S(KC_2),    S(KC_3),    S(KC_4),    S(KC_5),    S(KC_6),    S(KC_7),    S(KC_8),    S(KC_9),    S(KC_0), KC_BSPC},
  {KC_TRNS, FUNC(3), FUNC(4), RESET, M(0), M(1), M(2), S(KC_MINS), S(KC_EQL),  S(KC_LBRC), S(KC_RBRC), S(KC_BSLS)},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, FUNC(2),   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
}
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(2),  // to RAISE
    [2] = ACTION_LAYER_MOMENTARY(3),  // to LOWER

    [3] = ACTION_DEFAULT_LAYER_SET(0),
    [4] = ACTION_DEFAULT_LAYER_SET(1),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) 
{
  // MACRODOWN only works in this function
    if (record->event.pressed) {
      switch(id) {
        case 0:
            true_note(12, 12, 20);
        break;
        case 1:
            true_note(14, 14, 20);
        break;
        case 2:
            true_note(16, 16, 20);
        break;
        case 3:
            true_note(17, 17, 20);
        break;
        case 4:
            true_note(19, 19, 20);
        break;
        case 5:
            true_note(21, 21, 20);
        break;
        case 6:
            true_note(23, 23, 20);
        break;
        case 7:
            true_note(24, 24, 20);
        break;
        case 10:

        break;
      } 
    }
    return MACRO_NONE;
};
