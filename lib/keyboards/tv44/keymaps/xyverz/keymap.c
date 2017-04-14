#include "tv44.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _DV 0
#define _QW 1
#define _CM 2
#define _L1 3
#define _L2 4

// Macro name shortcuts
#define DVORAK M(_DV)
#define QWERTY M(_QW)
#define COLEMAK M(_CM)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DV] = { /* 0: Dvorak */
    {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC },
    {MO(_L1), KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT  },
    {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT },
    {KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  KC_SLSH, KC_MINS, XXXXXXX, MO(_L2) }
  },

  [_QW] = { /* 1: Qwerty */
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
    {MO(_L1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT  },
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
    {KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  KC_SLSH, KC_MINS, XXXXXXX, MO(_L2) }
  },

  [_CM] = { /* 2: Colemak */
    {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC },
    {MO(_L1), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT  },
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
    {KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  KC_SLSH, KC_MINS, XXXXXXX, MO(_L2) }
  },

  [_L1] = {/* 1: FN 1 */
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL  },
    {_______, KC_BSLS, KC_QUOT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_DOWN, KC_UP,   KC_LEFT, KC_RGHT, _______ },
    {_______, _______, _______, KC_PSCR, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_RSFT },
    {KC_ESC,  KC_LGUI, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_SLSH, _______, _______ }
  },

  [_L2] = { /* 2: FN 2 */
    {KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_ESC  },
    {_______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_VOLU, KC_ENT  },
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_VOLD, _______ },
    {QWERTY,  DVORAK,  COLEMAK, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______ }
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


