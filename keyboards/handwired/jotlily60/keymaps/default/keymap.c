// This is the default layout for the handwired/jotanck keyboard

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY   0
#define _FN       1

#define FNLAYER MO(_FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |   =   |   1   |   2   |   3   |   4   |   5   |               |   6   |   7   |   8   |   9   |   0   |   -   |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  esc  |   Q   |   W   |   E   |   R   |   T   |               |   Y   |   U   |   I   |   O   |   P   |  bksp |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  tab  |   A   |   S   |   D   |   F   |   G   |               |   H   |   J   |   K   |   L   |   ;   |   '   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 * |  lsft |   Z   |   X   |   C   |   V   |   B   |   [   |   ]   |   N   |   M   |   ,   |   .   |   /   | enter |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 *                 |  lalt | lsuper| lctrl |   fn  | space | space |   fn  |  home |  end  |  del  |
 *                 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 */
[_QWERTY] = LAYOUT_jotlily60 (
    KC_EQL, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MNS,
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LBRC,KC_RBRC,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_ENT,
                    KC_LALT,KC_LGUI,KC_LCTL,FNLAYER,KC_SPC, KC_SPC, FNLAYER,KC_HOME,KC_END, KC_DEL
),

/* FN
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |   ~   |   F1  |   F2  |   F3  |   F4  |   F5  |               |   F6  |   F7  |   F8  |   F9  |  F10  |       |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |       |  F11  |  F12  |       |       |       |               |       |       | PScr  |  Slck | Pause |       |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |       |  Vol- |  Mute |  Vol+ |       |       |               |  Left |  Down |   Up  | Right |       |   `   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 * |       |  Prev |  Play |  Next |       |       |   \   |   |   |       |       |       |       |       |       |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 *                 |       |       |       |       |       |       |       |  PgDn |  PgUp |       |
 *                 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 */
[_FN] = LAYOUT_jotlily60 (
    KC_EQL, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,  XXXXXXX,XXXXXXX,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MNS,
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,  XXXXXXX,XXXXXXX,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,  XXXXXXX,XXXXXXX,KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  KC_LBRC,KC_RBRC,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_ENT,
    XXXXXXX,XXXXXXX,KC_LCTL,KC_LGUI,KC_LALT,FNLAYER,KC_SPC,KC_SPC, FNLAYER,KC_RALT,KC_DEL, KC_RCTL,XXXXXXX,XXXXXXX
),

