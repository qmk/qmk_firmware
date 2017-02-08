// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "atreus50.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _COLEMAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = { /* dvorak */
        { KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    _______, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH },
        { KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    _______, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS },
        { KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_ENT,  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT },
        { KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL }
    },
    
    [_QWERTY] = { /* qwerty */
        { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL  },
        { KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
        { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
        { KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL }
    },
    
    [_COLEMAK] = { /* colemak */
        { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    _______, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL  },
        { KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    _______, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT },
        { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ENT,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
        { KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL}
    },
    
    [_LOWER] = {
        { KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ },
        { KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE },
        { _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, KC_F12,  KC_MUTE, KC_VOLD, KC_VOLU, _______, _______ },
        { _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______ }
    },
    [_RAISE] = {
        { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ },
        { KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS },
        { _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, KC_F12,  KC_MPRV, KC_MPLY, KC_MNXT, _______, _______ },
        { _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______ }
    },
    [_ADJUST] = {
        { KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12  },
        { _______, RESET,   _______, _______, _______, _______, _______, _______, QWERTY,  COLEMAK, DVORAK,  _______, _______ },
        { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
        { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
    },

};

const uint16_t PROGMEM fn_actions[] = {

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_DVORAK);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};