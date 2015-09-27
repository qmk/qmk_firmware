#include "keymap_common.h"
#include "action_layer.h"
#include "action.h"
#include "action_util.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP_AND_REVERSE( /* Charlie querty */
  TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    BSPC,
  LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, ENT,
  LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, RSFT,
  FN3,  LCTL, LALT, LGUI, FN1,    FN16,     FN2,  RGUI, RALT, RCTL, FN3),
[2] = KEYMAP_AND_REVERSE( /* Charlie workman */
  TAB,   Q,    D,    R,    W,    B,    J,    F,    U,    P,    SCLN, BSPC,
  LCTL,  A,    S,    H,    T,    G,    Y,    N,    E,    O,    I,    ENT,
  LSFT,  Z,    X,    M,    C,    V,    K,    L,    COMM, DOT,  SLSH, RSFT,
  FN3,   LCTL, LALT, LGUI, FN1,     FN16,    FN2,  RGUI, RALT, RCTL,  FN3),
[4] = KEYMAP_AND_REVERSE( /* Charlie RAISE */
  ESC,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    TRNS,
  TRNS, FN4,  FN5,  FN6,  FN7,  FN8,  FN9,  FN10, FN11, FN12, FN13, TRNS,
  TRNS, F11,  F12,  F13,  F14,  F15,  F16,  F17,  TRNS,  TRNS,  TRNS,  TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,    TRNS,  TRNS,  MNXT, VOLD, VOLU, MPLY),
[6] = KEYMAP_AND_REVERSE( /* Charlie LOWER */
  GRV, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, BSLS,
  TRNS, FN14, FN15, TRNS, TRNS, TRNS, TRNS, MINS, EQL, LBRC, RBRC, QUOT,
  TRNS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS,    TRNS,    TRNS, MNXT, VOLD, VOLU, MPLY),
};


enum function_id {
  SPACE_FN,
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id) {
  case SPACE_FN:
    if (record->event.pressed) {
      // Change the keyboard maps.
      // Whatever even layer's are on, turn on the odd one's too.
      for (uint8_t i = 0; i < 9; i += 2) {
        if (layer_state & (1UL << i))
          layer_on(i + 1);
      }
      layer_on(1);
    } else {
      // turn off all the even layers.
      for (uint8_t i = 0; i < 9; i += 2)
        layer_off(i + 1);

      if (record->tap.count != 0) {
        // Space was tapped rather than used like a modifier.
        // So send a space up and down event.
        add_key(KC_SPC);
        send_keyboard_report();
        del_key(KC_SPC);
        send_keyboard_report();
      }
    }
    break;
  }
}

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(4),  // to Fn overlay
    [2] = ACTION_LAYER_MOMENTARY(6),  // to Fn overlay
    [3] = ACTION_MODS_KEY(MOD_LGUI, KC_TAB), // switch windows
    [4] = ACTION_MODS_KEY(MOD_LSFT, KC_1), // !
    [5] = ACTION_MODS_KEY(MOD_LSFT, KC_2), // @
    [6] = ACTION_MODS_KEY(MOD_LSFT, KC_3), // #
    [7] = ACTION_MODS_KEY(MOD_LSFT, KC_4), // $
    [8] = ACTION_MODS_KEY(MOD_LSFT, KC_5), // %
    [9] = ACTION_MODS_KEY(MOD_LSFT, KC_6), // ^
    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_7), // &
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_8), // *
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_9), // (
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_0), // )
    [14] = ACTION_DEFAULT_LAYER_SET(1), // change to qwerty
    [15] = ACTION_DEFAULT_LAYER_SET(0), // change to workman
    [16] = ACTION_FUNCTION_TAP(SPACE_FN), // space reverse
};
