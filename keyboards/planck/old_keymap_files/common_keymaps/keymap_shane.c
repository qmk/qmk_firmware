#include "keymap.h"
#include "action_layer.h"
#include "action.h"
#include "action_util.h"

#define KC_MO6 MO(6)
#define KC_MO8 MO(8)

/*
  Shane's Planck Layout
  http://www.keyboard-layout-editor.com/#/layouts/015d9011102619d7695c86ffe57cf441
*/
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = KEYMAP_AND_SWAP( /* Base */
    TAB,  Q,  W,  E,  R,  T,  Y,  U,  I,  O,  P,  MINS,
    LCTL, A,  S,  D,  F,  G,  H,  J,  K,  L,  SCLN, BSPC,
    LSFT, Z,  X,  C,  V,  B,  N,  M,  COMM, DOT,  SLSH, FN5,
    /*ALPHA*/FN3, /*HYPER*/ /*SUPER*/LGUI, /*META*/LALT, LCTL,  MO8,  FN6,  MO6,  LEFT, DOWN, UP, RGHT),
  [2] = KEYMAP_AND_SWAP( /* More modifiers */
    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, RCTL, RALT, RGUI, TRNS),
  [4] = KEYMAP_AND_SWAP( /* WASD */
    TRNS, TRNS, UP, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
    TRNS, LEFT, DOWN, RIGHT,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),
  [6] = KEYMAP_AND_SWAP( /* Raise/FN1 */
    FN23, 1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  EQL,
    TRNS, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,  ENT,
    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, BSLS, TRNS,
    PAUS, TRNS, TRNS, TRNS, TRNS, BSPC, TRNS, MUTE, PGUP, PGDN, MNXT),
  [8] = KEYMAP_AND_SWAP( /* Lower/FN2 */
    ESC,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN19, FN20, TRNS,
    TRNS, TRNS, TRNS, TRNS, CAPS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, QUOT,
    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, FN24, FN25, LBRC, RBRC, TRNS, TRNS,
    FN4,  TRNS, TRNS, TRNS, TRNS, ENT,  TRNS, MPLY, VOLD, VOLU, MPRV),
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
  [3] = ACTION_LAYER_TOGGLE(2), // toggle more modifiers
  [4] = ACTION_LAYER_TOGGLE(4), // toggle wasd
  [5] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),
  [6] = ACTION_FUNCTION_TAP(SPACE_FN),

  [11] = ACTION_MODS_KEY(MOD_LSFT, KC_1),
  [12] = ACTION_MODS_KEY(MOD_LSFT, KC_2),
  [13] = ACTION_MODS_KEY(MOD_LSFT, KC_3),
  [14] = ACTION_MODS_KEY(MOD_LSFT, KC_4),
  [15] = ACTION_MODS_KEY(MOD_LSFT, KC_5),
  [16] = ACTION_MODS_KEY(MOD_LSFT, KC_6),
  [17] = ACTION_MODS_KEY(MOD_LSFT, KC_7),
  [18] = ACTION_MODS_KEY(MOD_LSFT, KC_8),
  [19] = ACTION_MODS_KEY(MOD_LSFT, KC_9),
  [20] = ACTION_MODS_KEY(MOD_LSFT, KC_0),
  [21] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),
  [22] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),
  [23] = ACTION_MODS_KEY(MOD_LSFT, KC_GRV),
  [24] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC),
  [25] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC),
  [26] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),
};
