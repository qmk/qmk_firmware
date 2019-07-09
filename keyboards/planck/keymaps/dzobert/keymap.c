#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = { /* Qwerty */
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_TAB},
  {KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_BSPC},
  {KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {KC_FN4, KC_RSFT, KC_LGUI, KC_LSFT, MO(3),      KC_SPC,   KC_SPC,    MO(2),     KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
                                                // Space is repeated to accommadate for both spacebar wiring positions
},
[1] = { /* Colemak */
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_TAB},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_BSPC},
  {KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {KC_FN3, KC_RSFT, KC_LGUI, KC_LSFT, MO(3),      KC_SPC,   KC_SPC,    MO(2),     KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
},
[2] = { /* RAISE */
  {KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12},
  {KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,     KC_7,    KC_8,          KC_9,  KC_DEL},
  {KC_TRNS, KC_GRV,  KC_MINS,  KC_EQL,  KC_QUOT,  S(KC_QUOT),  S(KC_LBRC),  S(KC_RBRC),  KC_LBRC,  KC_RBRC,  KC_BSLS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,  MO(2),     KC_HOME, KC_PGUP, KC_PGDN, KC_END}
},
[3] = { /* LOWER */
  {KC_POWER,KC_PSCR, KC_SLCK, KC_PAUSE, KC_NLCK, KC_EXECUTE, KC_MENU,   KC_APP,  KC_7,  KC_8, KC_9, KC_KP_SLASH},
  {KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_CAPS, KC_CANCEL, KC_UNDO, KC_AGAIN, KC_4,  KC_5, KC_6, KC_KP_ASTERISK},
  {KC_TRNS, KC_INSERT,KC_CUT,   KC_COPY,   KC_PASTE,   KC_BSLS,   KC_9,   KC_0,   KC_1,   KC_2,   KC_3,  KC_KP_MINUS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3),     KC_TRNS,   KC_TRNS,   KC_TRNS, KC_0, KC_KP_DOT, KC_KP_ENTER, KC_KP_PLUS}
}
};

const uint16_t PROGMEM fn_actions[] = {
    [3] = ACTION_DEFAULT_LAYER_SET(0),
    [4] = ACTION_DEFAULT_LAYER_SET(1),

};
