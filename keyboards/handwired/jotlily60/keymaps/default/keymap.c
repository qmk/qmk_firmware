// This is the default layout for the handwired/jotanck keyboard

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY   0
#define _FN       1

#define SPC_FN  LT(_FN, KC_SPC)
#define EN_LSFT LSFT_T(KC_ENT)
#define EN_RSFT RSFT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |   =   |   1   |   2   |   3   |   4   |   5   |               |   6   |   7   |   8   |   9   |   0   |   -   |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  esc  |   Q   |   W   |   E   |   R   |   T   |               |   Y   |   U   |   I   |   O   |   P   |  bksp |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  tab  |   A   |   S   |   D   |   F   |   G   |               |   H   |   J   |   K   |   L   |   ;   |   '   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 * |lsh_ent|   Z   |   X   |   C   |   V   |   B   |   [   |   ]   |   N   |   M   |   ,   |   .   |   /   |rsh_ent|
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 *                 | lctrl | lsuper| lalt  |  del  | fn_spc| fn_spc|  del  |  ralt |  rgui | rctl  |
 *                 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 */
[_QWERTY] = LAYOUT (
    KC_EQL, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    EN_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LBRC,KC_RBRC,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,EN_RSFT,
                    KC_LCTL,KC_LGUI,KC_LALT,KC_DEL ,SPC_FN, SPC_FN, KC_DEL, KC_RALT,KC_RGUI,KC_RCTL
),

/* FN
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  F12  |   F1  |   F2  |   F3  |   F4  |   F5  |               |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |       | Btn1  |MouseUp| Btn2  | WhUp  | WhLeft|               |  Ins  |  Caps | PScr  |  Slck | Pause |       |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |       |MouseL |MouseDn|MouseR | WhDown| WhRght|               |  Left |  Down |   Up  | Right |   |   |   `   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 * |       | Acc0  | Acc1  | Acc2  | Vol-  | Mute  | Vol+  |   ~   |  Home |  End  | PgUp  | PgDn  |   \   |       |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 *                 |       |       |       |       |       |       |       |       | Menu  |       |
 *                 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 */
[_FN] = LAYOUT (
    KC_F12, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
    _______,KC_BTN1,KC_MS_U,KC_BTN2,KC_WH_U,AS_TOG,                _______,_______,KC_PSCR,KC_SCRL,KC_PAUS,_______,
    _______,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_D,KC_WH_R,                KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_PIPE,KC_GRV,
    _______,KC_ACL0,KC_ACL1,KC_ACL2,KC_VOLD,KC_MUTE,KC_VOLU,KC_TILD,KC_HOME,KC_END, KC_PGUP,KC_PGDN,KC_BSLS,_______,
                    _______,_______,_______,_______,_______,_______,_______,_______,KC_APP,_______
)
};

