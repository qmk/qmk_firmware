// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "atreus62.h"
#include "action_layer.h"
#include "eeconfig.h"

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
    [_DV] = { /* dvorak */
        { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL  },
        { KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_TRNS, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH },
        { KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_TRNS, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS },
        { KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_LGUI, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT },
        { KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, MO(_L1), KC_BSPC, KC_ENT,  KC_SPC,  MO(_L2), KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL }
    },
    
    [_QW] = { /* qwerty */
        { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS },
        { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_TRNS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL  },
        { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_TRNS, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
        { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
        { KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, MO(_L1), KC_BSPC, KC_ENT,  KC_SPC,  MO(_L2), KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL }
    },
    
    [_CM] = { /* colemak */
        { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS },
        { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_TRNS, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL  },
        { KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_TRNS, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT },
        { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
        { KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, MO(_L1), KC_BSPC, KC_ENT,  KC_SPC,  MO(_L2), KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL }
    },
    [_L1] = {
        { KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC },
        { KC_TRNS, KC_F11,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,  KC_BSLS },
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS },
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS },
        { KC_TRNS, KC_TRNS, KC_HOME, KC_END,  KC_TRNS, KC_DEL,  KC_TRNS, KC_INS,  KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS }
    },
    [_L2] = {
        { KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC },
        { KC_TRNS, KC_F11,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,  KC_PIPE },
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS },
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS },
        { KC_TRNS, KC_TRNS, KC_HOME, KC_END,  KC_TRNS, KC_DEL,  KC_TRNS, KC_INS,  KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS }
    },

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
