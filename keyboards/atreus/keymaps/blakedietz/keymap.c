// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "atreus.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW    0
#define _RS    1
#define _LW    2
#define _DEV   3
#define _MOUSE 4
#define _MEDIA 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = {
  { KC_Q,          KC_W,            KC_E,        KC_R,    KC_T,                     KC_TRNS, KC_Y,               KC_U,             KC_I,              KC_O,             KC_P                },
  { KC_A,          KC_S,            KC_D,        KC_F,    KC_G,                     KC_TRNS, KC_H,               KC_J,             KC_K,              KC_L,             LT(_MEDIA, KC_SCLN) },
  { CTL_T(KC_Z),   ALT_T(KC_X),     GUI_T(KC_C), KC_V,    KC_B,                     KC_BSPC, KC_N,               KC_M,             GUI_T(KC_COMM),    ALT_T(KC_DOT),    CTL_T(KC_SLSH)      },
  { ALL_T(KC_ESC), KC_LSFT,         TG(_LW),     LT(_LW, KC_GRV), LT(_DEV, KC_SPC), KC_TAB,  LT(_MOUSE, KC_ENT), LT(_RS,KC_QUOT),  TG(_RS),  KC_RSFT,          ALL_T(KC_ESC)       }
},
[_LW] = {
  { KC_EXLM,        KC_AT,        KC_HASH,      KC_DLR,  KC_PERC, _______, KC_CIRC, KC_AMPR,  KC_ASTR,       KC_LPRN,        KC_RPRN        },
  { KC_F1,          KC_F2,        KC_F3,        KC_F4,   KC_F5,   _______, KC_F6,   KC_UNDS,  KC_PLUS,       KC_LCBR,        KC_RCBR        },
  { ALT_T(KC_F7),   CTL_T(KC_F8), GUI_T(KC_F9), _______, RESET,   _______, _______, KC_MINS,  GUI_T(KC_EQL), ALT_T(KC_LBRC), CTL_T(KC_RBRC) },
  { _______,        _______,      _______,      _______, _______, _______, _______, _______,  _______,       _______,        _______        }
},
[_RS] = {
  { KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, KC_6,    KC_7,    KC_8,        KC_9,        KC_0           },
  { KC_4,    KC_5,    KC_6,    KC_DOT,  KC_PLUS, _______, KC_DOT,  KC_4,    KC_5,        KC_6,        KC_ASTR        },
  { KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, _______, KC_DOT,  KC_1,    GUI_T(KC_2), ALT_T(KC_3), CTL_T(KC_BSLS) },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,      _______       }
},
[_DEV] = {
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______ },
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______ }
},
[_MOUSE] = {
  { _______, _______, KC_MS_U, _______, _______, _______, _______, KC_WH_D, KC_WH_U, _______, _______ },
  { _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_ACL2, KC_ACL1, KC_ACL0 },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
},
[_MEDIA] = {
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, _______ },
  { _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
}
//[_RS] = { /* [> RAISE <] */
//  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
//  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
//  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
//  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
//}
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
