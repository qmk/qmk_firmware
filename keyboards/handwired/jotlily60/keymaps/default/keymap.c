// This is the default layout for the handwired/jotanck keyboard

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY 0
#define _FN     1
#define _MOUSE  2
#define _ADJUST 3

#define FN MO(_FN)
#define MOUSE MO(_MOUSE)
#define TGMOUSE TG(_MOUSE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |   =   |   1   |   2   |   3   |   4   |   5   |               |   6   |   7   |   8   |   9   |   0   |   -   |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  esc  |   Q   |   W   |   E   |   R   |   T   |               |   Y   |   U   |   I   |   O   |   P   |  tab  |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * | mouse |   A   |   S   |   D   |   F   |   G   |               |   H   |   J   |   K   |   L   |   ;   |   '   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 * | shift |   Z   |   X   |   C   |   V   |   B   |   [   |   ]   |   N   |   M   |   ,   |   .   |   /   | enter |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 *                 | super |  alt  |  ctrl | space |   fn  |   fn  |  del  | bspc  |  ralt |tgmouse| 
 *                 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 */
[_QWERTY] = LAYOUT (
    KC_EQL, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_TAB,
    MOUSE,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LBRC,KC_RBRC,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_ENT,
                    KC_LGUI,KC_LALT,KC_LCTL,KC_SPC, FN,     FN,     KC_DEL, KC_BSPC,KC_RALT,TGMOUSE
),

/* +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |   +   |   F1  |   F2  |   F3  |   F4  |   F5  |               |   F6  |   F7  |   F8  |   F9  |  F10  |   _   |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * | adjust|  F11  |  F12  |  F13  |  F14  |  F15  |               |  F16  |  F17  |  F18  |  F19  |  F20  |adjust |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  caps |  vol- |  mute |  vol+ | macro1| macro2|               |  Left |  Down |   Up  | Right |   |   |  grv  |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 * |       |  prev |  play |  next | mrec1 | mrec2 | rstp  |   ~   |  Home |  End  | PgUp  | PgDn  |   \   |       |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 *                 |       |       |       |       |       |       |       |       |       |       |
 *                 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 */
[_FN] = LAYOUT (
    KC_PLUS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_UNDS,
    ADJUST, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                 KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, ADJUST,  
    KC_CAPS,KC_VOLD,KC_MUTE,KC_VOLU,DM_PLY1,DM_PLY2,                KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_PIPE,KC_GRV,
    _______,KC_ACL0,KC_ACL1,KC_ACL2,DM_REC1,DM_REC2,DM_RSTP,KC_TILD,KC_HOME,KC_END, KC_PGUP,KC_PGDN,KC_BSLS,_______, 
                    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______
),

[_MOUSE] = LAYOUT (
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,                KC_WH_U,KC_WH_L,KC_MS_U,KC_WH_R,_______,_______,
    _______,_______,_______,_______,_______,_______,                KC_WH_D,KC_MS_L,KC_MS_D,KC_MS_R,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_ACL0,KC_ACL1,KC_ACL2,_______,
                    _______,_______,_______,_______,KC_BTN1,KC_BTN2,_______,_______,_______,TGMOUSE
),

[_ADJUST] = LAYOUT (
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,QK_BOOT,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,_______,DB_TOGG,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______
),
};

