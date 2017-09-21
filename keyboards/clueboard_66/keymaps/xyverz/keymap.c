// Xyverz' keymap.
// It's based on the default keymap, but Dvorak!

#include "clueboard_66.h"

// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _RS 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,--------------------------------------------------------------------------.  ,----.
   * |Esc~|   1|   2|   3|   4|   5|   6|   7|   8|   9|   0|   [|   ]|   \|  BS|  |PGUP|
   * |--------------------------------------------------------------------------|  |----|
   * |   Tab|   '|   ,|   .|   P|   Y|   F|   G|   C|   R|   L|   /|   =|      \|  |PGDN|
   * |--------------------------------------------------------------------------|  `----'
   * |_FL/Caps|   A|   O|   E|   U|   I|   H|   D|   H|   T|   N|   S|  - |  Ent|
   * |-----------------------------------------------------------------------------.
   * |Shift|  BS|   ;|   Q|   J|   K|   X|   B|   M|   W|   V|   Z|   BS|Shift|  UP|
   * |------------------------------------------------------------------------|----|----.
   * | Ctrl|  Gui|  Alt| MHen|    Space|    Space|  Hen|  Alt| Ctrl|  _FL|LEFT|DOWN|RGHT|
   * `----------------------------------------------------------------------------------'
   */
[_BL] = KEYMAP(
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_GRV,  KC_BSPC,          KC_PGUP, \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS,                   KC_PGDN, \
  LT(_FL, KC_CAPS), KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_NUHS, KC_ENT,                    \
  KC_LSFT, KC_RO,   KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_SLSH, KC_RSFT,          KC_UP,            \
  KC_LCTL, KC_LALT, KC_LGUI, KC_MHEN,          KC_SPC,  KC_SPC,                             KC_HENK, KC_RGUI, KC_RCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,--------------------------------------------------------------------------.  ,----.
   * |   `|  F1|  F2|  F3|  F4|  F5|  F6|  F7|  F8|  F9| F10| F11| F12|    | Del|  |BLIN|
   * |--------------------------------------------------------------------------|  |----|
   * |      |    |    |    |    |    |    |    |PScr|SLck|Paus|    |    |       |  |BLDE|
   * |--------------------------------------------------------------------------|  `----'
   * |       |    | _RS|    |    |    |    |    |    |    |    |    |     |     |
   * |-----------------------------------------------------------------------------.
   * |     |    |    |    |    |    |    |    |    |    |    |    |     |     |PGUP|
   * |------------------------------------------------------------------------|----|----.
   * |     |     |     |     |         |         |     |     |     |  _FL|HOME|PGDN| END|
   * `----------------------------------------------------------------------------------'
   */
[_FL] = KEYMAP(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_DEL,           BL_STEP, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, \
  KC_TRNS, KC_TRNS, MO(_RS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_PGUP,          \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, MO(_FL), KC_HOME, KC_PGDN, KC_END),

  /* Keymap _RS: Reset layer
   * ,--------------------------------------------------------------------------.  ,----.
   * |    |    |    |    |    |    |    |    |    |    |    |    |    |    | RGB|  |VAL+|
   * |--------------------------------------------------------------------------|  |----|
   * |      |    |    |    |RESET|   |    |    |    |    |    |    |    |       |  |VAL-|
   * |--------------------------------------------------------------------------|  `----'
   * |       |    | _RS|    |    |    |    |    |    |    |    |    |     |     |
   * |-----------------------------------------------------------------------------.
   * |     |    |    |    |    |    |    |    |    |    |    |    |     |     |SAT+|
   * |------------------------------------------------------------------------|----|----.
   * |     |     |     |     |         |         |     |     |     |  _FL|HUE-|SAT-|HUE+|
   * `----------------------------------------------------------------------------------'
   */
[_RS] = KEYMAP(
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG,          RGB_VAI, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   RGB_VAD, \
  KC_TRNS, KC_TRNS, MO(_RS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            \
  MO(_FL), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FL),          RGB_SAI,          \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_MOD, RGB_MOD,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUD, RGB_SAD, RGB_HUI),
};

