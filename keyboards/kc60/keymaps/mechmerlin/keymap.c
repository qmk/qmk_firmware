// This is the 60% layout preferred by u/merlin36 the host of the MechMerlin YouTube channel.
// The layout is highly influenced by the WKL B.Face and KBP V60 standard layouts.
// Layout designed for use on KC60 with no inswitch or underglow lighting. 

#include "kc60.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = KEYMAP( /* Basic QWERTY */
      KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,    KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  \
      KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,    KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  \
      KC_LCTL,  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,     KC_H,     KC_J,    KC_K,  KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,    KC_ENT,   \
      KC_LSFT,  KC_NO,    KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,     KC_N,    KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,    KC_RSFT,  \
      KC_LCTL,  KC_LGUI,  KC_LALT,                     KC_SPC,                             KC_NO,    MO(2),    KC_RALT,  KC_RGUI,  KC_RCTL \
      ),
  [1] = KEYMAP( /* HHKB-ish Base Layout */
      KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,    KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  \
      KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,    KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_DEL,  \
      KC_LCTL,  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,     KC_H,     KC_J,    KC_K,  KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,    KC_ENT,   \
      KC_LSFT,  KC_NO,    KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,     KC_N,    KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,    KC_RSFT,  \
      KC_LCTL,  KC_LGUI,  KC_LALT,                     KC_SPC,                             KC_NO,    MO(3),    KC_RALT,  KC_RGUI,  KC_RCTL \
      ),
  [2] = KEYMAP( /* FN Layer 1 - Basic QWERTY */
      KC_GRV,   KC_F1,     KC_F2,     KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,    KC_F8,    KC_F9,     KC_F10,     KC_F11,   KC_F12,   KC_DEL,  \
      KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,  RESET,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  \
      KC_CAPS,  KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   TO(1),     KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,  KC_NO,    KC_TRNS, \
      KC_TRNS,  KC_NO,     KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_MUTE,  KC_VOLD,   KC_VOLU,    KC_TRNS,  KC_NO,    KC_PGUP,  \
      KC_TRNS,  KC_TRNS,   KC_TRNS,                        TG(4),                          KC_NO,    KC_TRNS,   KC_HOME,    KC_PGDN,  KC_END \
      ),
  [3] = KEYMAP( /* FN Layer 2 - HHKB-ish Base Layout */
      KC_GRV,   KC_F1,     KC_F2,     KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,    KC_F8,    KC_F9,     KC_F10,     KC_F11,   KC_F12,   KC_INS,  \
      KC_CAPS,  KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_UP,    KC_TRNS,  KC_BSPC,  \
      KC_TRNS,  KC_VOLD,   KC_VOLU,   KC_MUTE,  KC_TRNS,   KC_TRNS,   TO(0),     KC_TRNS,  KC_HOME,  KC_PGUP,   KC_LEFT,    KC_RIGHT, KC_NO,    KC_TRNS, \
      KC_TRNS,  KC_NO,     KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_END,    KC_PGDN,    KC_DOWN,  KC_NO,    KC_TRNS,  \
      KC_TRNS,  KC_TRNS,   KC_TRNS,                        KC_TRNS,                        KC_NO,    KC_TRNS,   KC_TRNS,    KC_TRNS,  KC_TRNS \
      ),
  [4] = KEYMAP( /* Arrow Layers - Basic QWERTY ONLY */
      KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  \
      KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  \
      KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_NO,    KC_TRNS,   \
      KC_TRNS,   KC_NO,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_NO,    KC_UP,  \
      KC_TRNS,   KC_TRNS,    KC_TRNS,                              KC_TRNS,                              KC_NO,    KC_TRNS,    KC_LEFT,   KC_DOWN,  KC_RIGHT \
      ),
  [5] = KEYMAP( /* Blank Layer for later usage */
      KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  \
      KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  \
      KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_NO,    KC_TRNS,   \
      KC_TRNS,   KC_NO,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_NO,    KC_TRNS,  \
      KC_TRNS,   KC_TRNS,    KC_TRNS,                              KC_TRNS,                              KC_NO,    KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS \
      ),

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  return MACRO_NONE;
};
