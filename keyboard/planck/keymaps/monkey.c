#include "keymap_common.h"
#include "backlight.h"
#include "debug.h"

#define COLEMAK_LAYER 0
#define QWERTY_LAYER 1
#define LOWER_LAYER 2
#define UPPER_LAYER 3
#define SPACEFN_LAYER 4
#define TENKEY_LAYER 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[COLEMAK_LAYER] = { /* Colemak */
  {KC_TAB,    UNI(0x1961),     KC_W,    KC_F,    KC_P,    KC_G,     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_BSPC},
  {KC_LCTL,   KC_A,     KC_R,    KC_S,    KC_T,    KC_D,     KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT},
  {KC_LSFT,   KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT},
  {FUNC(5),   KC_ESC,   KC_LGUI, KC_LALT, FUNC(1), FUNC(6),  FUNC(6), FUNC(2), KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT}
},
[QWERTY_LAYER] = { /* Qwerty */
  {KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {FUNC(5), KC_ESC, KC_LGUI, KC_LALT, FUNC(1), FUNC(6), FUNC(6), FUNC(2), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[LOWER_LAYER] = { /* LOWER */
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DELETE},
  {KC_TRNS, FUNC(3), FUNC(4), RESET,   DEBUG,   KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},
[UPPER_LAYER] = { /* RAISE */
  {S(KC_GRV), S(KC_1), S(KC_2), S(KC_3),  S(KC_4),  S(KC_5), S(KC_6), S(KC_7),    S(KC_8),    S(KC_9),    S(KC_0),    KC_DELETE},
  {KC_CALC,   FUNC(3), FUNC(4), RESET,    DEBUG,    KC_TRNS, KC_TRNS, S(KC_MINS), S(KC_EQL),  S(KC_LBRC), S(KC_RBRC), S(KC_BSLS)},
  {KC_TRNS,   KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,   KC_F6,   KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_TRNS},
  {KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_MNXT,    KC_VOLD,    KC_VOLU,    KC_MPLY}
},
[SPACEFN_LAYER] = { /* SpaceFN */
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_UP,   KC_END,   KC_TRNS, KC_TRNS},
  {KC_TRNS, FUNC(3), FUNC(4), KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS}
},
[TENKEY_LAYER] = { /* TENKEY */
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, KC_BSPC},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_NLCK},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3, KC_PDOT, KC_ENT},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,  KC_SPC,  KC_KP_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
}
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_KEY(LOWER_LAYER, KC_BSPC),  // Tap for backspace, hold for LOWER
    [2] = ACTION_LAYER_TAP_KEY(UPPER_LAYER, KC_ENT),  // Tap for enter, hold for RAISE

    [3] = ACTION_DEFAULT_LAYER_SET(COLEMAK_LAYER),
    [4] = ACTION_DEFAULT_LAYER_SET(QWERTY_LAYER),
    [5] = ACTION_LAYER_TOGGLE(TENKEY_LAYER),
    
    [6] = ACTION_LAYER_TAP_KEY(SPACEFN_LAYER, KC_SPC),  // Tap for space, hold for SpaceFN
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) 
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:   
        if (record->event.pressed) {
          register_code(KC_RSFT);
          backlight_step();
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      } 
    return MACRO_NONE;
};