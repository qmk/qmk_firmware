/* This is the Atreus62 keyboard layout by Xyverz aka u/Zrevyx on r/mk
   I've blatantly stolen what works for me from the Planck and Preonic
   layouts and modified this file to fit me. Initial credet goes to
   u/profet23 for the doing all the work and adding this keyboard to
   QMK in the first place.

   I've got Dvorak, Qwerty, and Colemak layouts at this time, with the
   possibility of adding more in the future.

   The bottom row is fairly Kinesis-ish since the Contour and Advantage
   keyboards have been my daily drivers for the last 17 years. I hope
   You can get some enjoyment out of this layout should you chose it!

CHANGELOG:

 0.1 - Initial commit. Based off of Profet's default keymap.
 0.2 - Converted to a more Planck/Preonic keymap style file with 
       persistent layers enabled. Renamed layers to reflect OLKB maps.
       Added a TODO list.
 0.3 - Moved location of media & volume keys. Added Print Screen, 
       Scroll Lock and Pause keys. Added a WOW gaming layer that
       changes the location of Ctrl & Alt to the thumb keys. Added
       readme.
 0.4 - After more useage, I realized that the ESC key was in the way 
       of my muscle memory (gee, thanks, Planck!) so I moved it to
       the normal Caps Lock position, and moved Caps Lock to the same
       position on the RAISE and LOWER layers. Added code to turn off
       the Pro Micro LEDs after flashing.
 0.5 - Converted keymap to LAYOUT standard.

TODO:

 * Make the layout more efficient, even if it means changing the RAISE
   and LOWER functionality.
 * Add legends in comments for each layer. Maybe.

*/

// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _COLEMAK 2
#define _WOW 3
#define _LOWER 4
#define _RAISE 5
#define _ADJUST 16

enum atreus52_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  WOW,
  LOWER,
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Aliases to make the keymap clearer.
#define CTL_ENT CTL_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT ( /* dvorak */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_QWERTY] = LAYOUT ( /* qwerty */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_COLEMAK] = LAYOUT ( /* colemak */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_WOW] = LAYOUT ( /* Dvorak with minor modifications for playing World of Warcraft */
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LALT, CTL_ENT, KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT
  ),

  [_LOWER] = LAYOUT (
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    KC_TILD, KC_GRV,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_PIPE,
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, _______, KC_PLUS, KC_LCBR, KC_RCBR, _______,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
    _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______
  ),
  [_RAISE] = LAYOUT (
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    KC_TILD, KC_GRV,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_BSLS,
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, _______, KC_EQL,  KC_LBRC, KC_RBRC, _______,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
    _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______
  ),
  [_ADJUST] = LAYOUT (
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, QWERTY,  COLEMAK, DVORAK,  _______, WOW,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

};

const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DVORAK);
          }
          return false;
          break;
        case WOW:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_WOW);
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
