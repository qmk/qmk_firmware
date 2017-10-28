#include "phantom.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;


// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _DV 1
#define _CM 2
#define _FL 3

// Macro name shortcuts
#define QWERTY M(_QW)
#define DVORAK M(_DV)
#define COLEMAK M(_CM)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QW] = { /* Layer 0: Qwerty */
    {KC_ESC,  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS},
    {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, KC_INS,  KC_HOME, KC_PGUP},
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN},
    {KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX},
    {KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, KC_RSFT, XXXXXXX, KC_UP,   XXXXXXX},
    {KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, KC_RGUI, KC_RALT, KC_RCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT}
  },

[_DV] = { /* Layer 1: Dvorak */
    {KC_ESC,  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS},
    {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, XXXXXXX, KC_BSPC, KC_INS,  KC_HOME, KC_PGUP},
    {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, KC_DEL,  KC_END,  KC_PGDN},
    {KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX},
    {KC_LSFT, XXXXXXX, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    XXXXXXX, KC_RSFT, XXXXXXX, KC_UP,   XXXXXXX},
    {KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, KC_RGUI, KC_RALT, KC_RCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT}
  },

[_CM] = { /* Layer 2: Colemak */
    {KC_ESC,  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS},
    {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, KC_INS,  KC_HOME, KC_PGUP},
    {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN},
    {KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX},
    {KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, KC_RSFT, XXXXXXX, KC_UP,   XXXXXXX},
    {KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, KC_RGUI, KC_RALT, KC_RCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT}
  },

[_FL] = { /* Layer 3: Functions */
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, RESET,   KC_MPRV, KC_MPLY, KC_MNXT},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX},
    {_______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX, _______, XXXXXXX},
    {QWERTY,  DVORAK,  COLEMAK, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______},
  },


};

enum function_id {
    SHIFT_ESC,
};


const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _DV:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DV);
          }
          break;
        case _QW:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QW);
          }
          break;
        case _CM:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_CM);
          }
          break;
      }
    return MACRO_NONE;
};
