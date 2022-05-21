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
 0.6 - Swapped ESC and GRV in all layers.
 0.7 - Brought code up to current standards.
 0.8 - Added MACLOCK macro.
 0.9 - Updated code to correspond to new setPinInput behaviour
 0.10 - Re-ordered the layers (swapped Destiny & WoW layers in the
       list). Removed duplicated keys from RAISE and LOWER layers.
       Updated readme.md and fixed an aesthetic typo in keymap.c.
 0.11 - Added DEL_GUI macro. Removed WOW layer since I'm no longer
       supporting Blizzard in any way.

TODO:

 * Make the layout more efficient, even if it means changing the RAISE
   and LOWER functionality.
 * Add legends in comments for each layer. Maybe.

*/

// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
#include QMK_KEYBOARD_H

enum layer_names { _DVORAK, _QWERTY, _COLEMAK, _DESTINY, _LOWER, _RAISE, _ADJUST };

enum atreus62_keycodes { DVORAK = SAFE_RANGE, QWERTY, COLEMAK, DESTINY, LOWER, RAISE, ADJUST };

// Aliases to make the keymap clearer.
#define CTL_ENT CTL_T(KC_ENT)
#define DEL_GUI GUI_T(KC_DEL)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define MACLOCK LGUI(LCTL(KC_Q))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT ( /* dvorak */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    KC_GRV,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, DEL_GUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_QWERTY] = LAYOUT ( /* qwerty */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_COLEMAK] = LAYOUT ( /* colemak */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
    KC_GRV,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_DESTINY] = LAYOUT ( /* Dvorak with minor modifications for playing Destiny 2 and other FPS Looters */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    KC_GRV,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_DEL,  KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL
  ),

  [_LOWER] = LAYOUT (
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, _______, KC_PLUS, KC_LCBR, KC_RCBR, _______,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
    _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  MACLOCK, _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______
  ),
  [_RAISE] = LAYOUT (
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, _______, KC_EQL,  KC_LBRC, KC_RBRC, _______,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                   _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
    _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  MACLOCK, _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______
  ),
  [_ADJUST] = LAYOUT (
    _______, _______, _______, KC_F13,  KC_F14,  KC_F15,                    _______, _______, _______, _______, _______, _______,
    _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, QWERTY,  COLEMAK, DVORAK,  DESTINY, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};
//clang-format on

void matrix_init_user(void) {
#ifdef BOOTLOADER_CATERINA
   // This will disable the red LEDs on the ProMicros
   setPinInput(D5);
   setPinInput(B0);
#endif
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
   switch (keycode) {
    case DVORAK:
        set_single_persistent_default_layer(_DVORAK);
      return false;
    case QWERTY:
        set_single_persistent_default_layer(_QWERTY);
      return false;
    case COLEMAK:
        set_single_persistent_default_layer(_COLEMAK);
      return false;
    case DESTINY:
        set_single_persistent_default_layer(_DESTINY);
      return false;
    case WOW:
        set_single_persistent_default_layer(_WOW);
      return false;
   }
  }
  return true;
};
