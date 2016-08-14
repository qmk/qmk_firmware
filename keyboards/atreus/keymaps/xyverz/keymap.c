// This is the personal keymap of Ian Sterling (@xyverz). It is based on the keymap by
// Chris Gerber (@gerbercj), with the addition of persistent layers like the Planck and
// Preonic keyboards by Jack Humbert.

#include "atreus.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DV 0
#define _QW 1
#define _CM 2
#define _L1 3
#define _L2 4

// Macro name shortcuts
#define DVORAK M(_DV)
#define QWERTY M(_QW)
#define COLEMAK M(_CM)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DV] = { /* Dvorak */
    {KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_NO,   KC_F,    KC_G,    KC_C,    KC_R,    KC_L   },
    {KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_NO,   KC_D,    KC_H,    KC_T,    KC_N,    KC_S   },
    {SFT_T(KC_SCLN), KC_Q, KC_J, KC_K, KC_X, CTL_T(KC_DEL),  KC_B,  KC_M,  KC_W,  KC_V,   SFT_T(KC_Z) },
    {KC_ESC, KC_TAB, KC_LGUI, MO(_L2), KC_BSPC, ALT_T(KC_ENT), KC_SPC, MO(_L1), KC_MINS, KC_SLSH, KC_EQL}
  },
  [_QW] = { /* Qwerty */
    {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P   },
    {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN},
    {SFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, CTL_T(KC_DEL), KC_N, KC_M, KC_COMM, KC_DOT, SFT_T(KC_SLSH)  },
    {KC_ESC, KC_TAB, KC_LGUI, MO(_L2), KC_BSPC, ALT_T(KC_ENT), KC_SPC, MO(_L1), KC_MINS, KC_QUOT, KC_ENT}
  },
  [_CM] = { /* Colemak */
    {KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_NO,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN},
    {KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_NO,   KC_H,    KC_N,    KC_E,    KC_I,    KC_O   },
    {SFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, CTL_T(KC_DEL), KC_K, KC_M, KC_COMM, KC_DOT, SFT_T(KC_SLSH)  },
    {KC_ESC, KC_TAB, KC_LGUI, MO(_L2), KC_BSPC, ALT_T(KC_ENT), KC_SPC, MO(_L1), KC_MINS, KC_QUOT, KC_ENT}
  },
  [_L1] = { /* LAYER 1 */
    {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0   },
    {KC_TAB,  KC_INS,  KC_UP,   KC_DEL,  KC_HOME, KC_NO,   KC_PGUP, KC_MUTE, KC_VOLD, KC_VOLU, KC_EQL },
    {KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_LCTL, KC_PGDN, KC_MPRV, KC_MPLY, KC_MNXT, KC_BSLS},
    {KC_TRNS, KC_GRV,  KC_LGUI, KC_TRNS, KC_DEL,  KC_LALT, KC_SPC,  KC_TRNS, KC_LBRC, KC_RBRC, KC_ENT }
  },
  [_L2] = { /* LAYER 2 */
    {KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN},
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,   KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_PLUS},
    {KC_TRNS, KC_TRNS, DVORAK,  QWERTY,  COLEMAK, KC_LCTL, KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12 },
    {KC_TRNS, KC_TRNS, KC_LGUI, KC_TRNS, KC_BSPC, KC_LALT, KC_SPC,  KC_TRNS, LSFT(KC_LBRC), LSFT(KC_RBRC), RESET}
  }
};

const uint16_t PROGMEM fn_actions[] = {

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _DV:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_DV);
          }
          break;
        case _QW:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_QW);
          }
          break;
        case _CM:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_CM);
          }
          break;
      }
    return MACRO_NONE;
};
