// This is the default layout for the handwired/jotanck keyboard

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY   0
#define _FN       1
#define _ADJUST   2

#define EN_LSFT LSFT_T(KC_ENT)  // Tap: Enter - Hold: Lesft Shift
#define F13_LCT LCTL_T(KC_F13)  // Tap: F13   - Hold: Left Control
#define F14_LSG LSG_T(KC_F14)   // Tap: F14   - Hold: Left Shift+Super
#define F15_LAL LALT_T(KC_F15)  // Tap: F15   - Hold: Left Alt
#define DEL_LGU LGUI_T(KC_DEL)  // Tap: Del   - Hold: Left Super
#define SPC_FN  LT(_FN, KC_SPC) // Tap: Space - Hold: FN
#define DEL_RGU LGUI_T(KC_DEL)  // Tap: Del   - Hold: Right Super
#define F16_RAL RALT_T(KC_F16)  // Tap: F16   - Hold: Right Alt
#define F17_RSG RSG_T(KC_F17)   // Tap: F17   - Hold: Right Shift+Super
#define F18_RCT RCTL_T(KC_F18)  // Tap: F18   - Hold: Right Control
#define EN_RSFT RSFT_T(KC_ENT)  // Tap: Enter = Hold: Right Shift

#define ADJUST MO(ADJUST)

#define SFT_TAB LSFT(TAB) // Left Shift + Tab

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |   =   |   1   |   2   |   3   |   4   |   5   |               |   6   |   7   |   8   |   9   |   0   |   -   |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  esc  |   Q   |   W   |   E   |   R   |   T   |               |   Y   |   U   |   I   |   O   |   P   |  bksp |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  tab  |   A   |   S   |   D   |   F   |   G   |               |   H   |   J   |   K   |   L   |   ;   |   '   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 * |en_lsft|   Z   |   X   |   C   |   V   |   B   |   [   |   ]   |   N   |   M   |   ,   |   .   |   /   |en_rsft|
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 *                 |f13_lct|f14_lgu|f15_lal|del_lsg| spc_fn| spc_fn|del_rsg|f16_ral|f17_rgu|f18_rct|
 *                 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 */
[_QWERTY] = LAYOUT (
    KC_EQL, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    EN_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LBRC,KC_RBRC,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,EN_RSFT,
                    F13_LCT,F14_LSG,F15_LAL,DEL_LGU,SPC_FN, SPC_FN, DEL_RGU,F16_RAL,F17_RGU,F17_RCT
),

/* FN
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |  F12  |   F1  |   F2  |   F3  |   F4  |   F5  |               |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |adjust | Btn1  |MouseUp| Btn2  | WhUp  | WhLeft|               |  Ins  |  Caps | PScr  |  Slck | Pause |adjust |
 * +-------+-------+-------+-------+-------+-------+               +-------+-------+-------+-------+-------+-------+
 * |lst_tab|MouseL |MouseDn|MouseR | WhDown| WhRght|               |  Left |  Down |   Up  | Right |   |   |   `   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 * | caps  | Acc0  | Acc1  | Acc2  | Vol-  | Mute  | Vol+  |   ~   |  Home |  End  | PgUp  | PgDn  |   \   | caps  |
 * +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 *                 |       |       |       |       |       |       |       |       |       |       |
 *                 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
 */
[_FN] = LAYOUT (
    KC_F12, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
    ADJUST, KC_BTN1,KC_MS_U,KC_BTN2,KC_WH_U,DM_PLY1,                KC_INS, KC_APP, KC_PSCR,KC_SCRL,KC_PAUS,ADJUST,
    LST_TAB,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_D,DM_PLY2,                KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_PIPE,KC_GRV,
    KC_CAPS,KC_ACL0,KC_ACL1,KC_ACL2,KC_VOLD,KC_MUTE,KC_VOLU,KC_TILD,KC_HOME,KC_END, KC_PGUP,KC_PGDN,KC_BSLS,KC_CAPS,
                    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______
),

[_ADJUST] = LAYOUT (
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,QK_BOOT,_______,_______,_______,DM_REC1,                _______,_______,_______,_______,_______,_______,
    _______,_______,_______,DB_TOGG,_______,DM_REC2,                _______,_______,_______,_______,_______,_______,
    AS_TOGG,AS_UP,  AS_DOWN,AS_RPT, _______,DM_RSTP,_______,_______,_______,_______,_______,_______,_______,_______,
                    DT_UP,  DT_DOWN,DT_PRNT,_______,_______,_______,_______,_______,_______,_______
),
};

