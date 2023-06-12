#pragma once
#include "T4CORUN.h"

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts

NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.

Modeled code after Drashna's Wrappers.
Definitions inspired by Miryoku (https://github.com/manna-harbour/miryoku). 

I added comment maps to better visualize the map. I intended to only 
show the definition once so its less comments to change when I change
a mapping

I prefer to use KC_NO over KC_TRNS so I don't have accidental presses
*/

#   define          __________NONE_3_________                 ___x___, ___x___, ___x___
#   define ___________________NONE_5__________________        ___x___, ___x___, ___x___, ___x___, ___x___

#   define    _____________GACS_MODS____________              TR_LGUI, TR_LALT, TR_LCTL, TR_LSFT
#   define    _____________SCAG_MODS____________              TR_LSFT, TR_LCTL, TR_LALT, TR_LGUI

#   define __________________UCCPR_L__________________        SC_UNDO, SC_CUT,  SC_COPY, SC_PAST, SC_REDO


#   define         _________BASE_L4_________                  TR_BTN1, NUMBER,  KC_LSFT

//right side only has two thumb keys
#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define         _________BASE_R4_________                  KC_SPC,  NAV
#else
#   define         _________BASE_R4_________                  KC_SPC,  NAV,     ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |   '  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | FUNZ |   X  | MOUC |   V  |   B  |    |   N  |   M  |   ,  |   .  | ADJ/ |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#   define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#   define _________________QWERTY_L2_________________        TR_A,    TR_S,    TR_D,    TR_F,    KC_G
#   define _________________QWERTY_L3_________________        FUN_Z,   KC_X,    TR_MOUC, KC_V,    KC_B

#   define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#   define _________________QWERTY_R2_________________        KC_H,    TR_J,    TR_K,    TR_L,    TR_QT
#   define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  AD_SLSH

/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   |   Q  |   W  |   F  |   P  |   B  |    |   J  |   L  |   U  |   Y  |   '  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |   A  |   R  |   S  |   T  |   G  |    |   M  |   N  |   E  |   I  |   O  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | FUNZ |   X  | MOUC |   D  |   V  |    |   K  |   H  |   ,  |   .  | ADJ/ |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#   define ________________COLEMAKDH_L1_______________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#   define ________________COLEMAKDH_L2_______________        TR_A,    TR_R,    TR_S,    TR_T,    KC_G
#   define ________________COLEMAKDH_L3_______________        FUN_Z,   KC_X,    TR_MOUC, KC_D,    KC_V

#   define ________________COLEMAKDH_R1_______________        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT
#   define ________________COLEMAKDH_R2_______________        KC_M,    TR_N,    TR_E,    TR_I,    TR_O
#   define ________________COLEMAKDH_R3_______________        KC_K,    KC_H,    KC_COMM, KC_DOT,  AD_SLSH

/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   | Tab  |   Q  |   W  |   E  |   R  |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Num  |   A  |   S  |   D  |   F  |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |  Z   |   X  |   C  |   V  |   B  |    |      |      |      |      | Adj  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Ctrl | Spc  | Shift|    |      | Nav  |      |
*                 `------+------+------'    `------+------+------'
*/

#   define _______________GAMING_BASE_L1______________        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R
#   define _______________GAMING_BASE_L2______________        GAMENO,  KC_A,    KC_S,    KC_D,    KC_F
#   define _______________GAMING_BASE_L3______________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#   define          ______GAMING_BASE_L4_____                 KC_LCTL, KC_SPC,  KC_LSFT

#   define _______________GAMING_BASE_R1______________        ___________________NONE_5__________________
#   define _______________GAMING_BASE_R2______________        ___________________NONE_5__________________
#   define _______________GAMING_BASE_R3______________        ___x___, ___x___, ___x___, ___x___, ADJUST

# if defined(KEYBOARD_bastardkb_charybdis_3x5) 
#   define          ______GAMING_BASE_R4_____                 ___x___, NAV
# else
#   define          ______GAMING_BASE_R4_____                 ___x___, NAV,     ___x___
# endif //KEYBOARD_bastardkb_charybdis_3x5


/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   |      | Esc  |  ~   |   G  |   T  |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |LyrTap|   1  |   2  |   3  |   4  |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      |   5  |   6  |   7  |   8  |    |      |      |      |      |      |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Alt  |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#   define _______________GAMING_NUM_L1_______________        ___x___, KC_ESC,  KC_TILD, KC_G,    KC_T
#   define _______________GAMING_NUM_L2_______________        _______, KC_1,    KC_2,    KC_3,    KC_4
#   define _______________GAMING_NUM_L3_______________        ___x___, KC_5,    KC_6,    KC_7,    KC_8
#   define          ______GAMING_NUM_L4______                 KC_LALT, ___x___, ___x___



/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  |      | Snip | Ent  |   `  |    |   [  |   7  |   8  |   9  |   ]  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GUI  | Alt  | Ctrl | Shft |   .  |    |   -  |   4  |   5  |   6  |   =  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |   ;  |   1  |   2  |   3  |   \  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |LyrTap|      |    | spc  |   0  |      |
*                 `------+------+------'    `------+------+------'
*/

#   define _________________NUMPAD_L1_________________        KC_ESC,  ___x___, W_SNIP,  KC_ENT,  KC_GRV
#   define _________________NUMPAD_L2_________________        _____________GACS_MODS____________, KC_DOT
#   define _________________NUMPAD_L3_________________        __________________UCCPR_L__________________
#   define          ________NUMPAD_L4________                 ___x___, _______, ___x___

#   define _________________NUMPAD_R1_________________        TR_LBRC, KC_7,    KC_8,    KC_9,    TR_RBRC
#   define _________________NUMPAD_R2_________________        KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL
#   define _________________NUMPAD_R3_________________        KC_MINS, KC_1,    KC_2,    KC_3,    KC_BSLS

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________NUMPAD_R4________                 KC_SPC,  KC_0
#else
#   define          ________NUMPAD_R4________                 KC_SPC,  KC_0,    ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

#   define __________________NUMROW_L_________________        KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#   define __________________NUMROW_R_________________        KC_6,    KC_7,    KC_8,    KC_9,    KC_0

/*
*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  | Home | Up   | End  | PgUp |    | Ins  |      | App  |      |MOUTOG|
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      | Left | Down | Right| PgDn |    | Del  | Shft | Ctrl | Alt  | GUI  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |      |      |      |      |      |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Tab  | Bpsc | Ent  |    |      |LyrTap|      |
*                 `------+------+------'    `------+------+------'
*/
#   define ___________________NAV_L1__________________        KC_ESC,  KC_HOME, KC_UP,   KC_END,  KC_PGUP
#   define ___________________NAV_L2__________________        ___x___, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#   define ___________________NAV_L3__________________        __________________UCCPR_L__________________
#   define          __________NAV_L4_________                 KC_TAB,  KC_BSPC, KC_ENT

#   define ___________________NAV_R1__________________        KC_INS,  ___x___, KC_APP,  ___x___, TR_MOUT
#   define ___________________NAV_R2__________________        KC_DEL,  _____________SCAG_MODS____________
#   define ___________________NAV_R3__________________        ___________________NONE_5__________________

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          __________NAV_R4_________                 ___x___, _______
#else
#   define          __________NAV_R4_________                 ___x___, _______, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

/*
*   ,----------------------------------.    ,----------------------------------.
*   |      |      |      |      |      |    |ScrLck|  F7  |  F8  |  F9  | F10  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GUI  | Alt  | Ctrl | Shft |PrnScr|    |CapLck|  F4  |  F5  |  F6  | F11  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |LyrTap|      | Vol- | Vol+ | Mute |    |PauBrk|  F1  |  F2  |  F3  | F12  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |DMRec1|DMPly1|    |DMPly2|DMRec2|      |
*                 `------+------+------'    `------+------+------'
*/


#   define _________________FUNCPAD_L1________________        ___________________NONE_5__________________
#   define _________________FUNCPAD_L2________________        _____________GACS_MODS____________, KC_PSCR
#   define _________________FUNCPAD_L3________________        _______, ___x___, KC_VOLD, KC_VOLU, KC_MUTE
#   define          ________FUNCPAD_L4_______                 ___x___, TR_DMR1, TR_DMP1

#   define _________________FUNCPAD_R1________________        KC_SCRL, KC_F7,   KC_F8,   KC_F9,   KC_F10
#   define _________________FUNCPAD_R2________________        KC_CAPS, KC_F4,   KC_F5,   KC_F6,   KC_F11
#   define _________________FUNCPAD_R3________________        KC_PAUS, KC_F1,   KC_F2,   KC_F3,   KC_F12

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________FUNCPAD_R4_______                 TR_DMP2, TR_DMR2
#else
#   define          ________FUNCPAD_R4_______                 TR_DMP2, TR_DMR2, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

#   define _________________FUNCROW_L_________________        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#   define _________________FUNCROW_M_________________        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#   define              ____FUNCROW_R___                      KC_F11,  KC_F12

/*
*   ,----------------------------------.    ,----------------------------------.
*   |      |      | MouU |      | MwU  |    | sDPI | DPI  |      |      |MOUTOG|
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      | MouL | MouD | MouR | MwD  |    |      | Shft | Ctrl | Alt  | Gui  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |Sniper|      |LyrTap|DrgScr|      |    |DrgTog| MB1  | MB2  | MB3  |SniTog|
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | MB1  | MB2  | MB3  |    | MB5  | MB4  |      |
*                 `------+------+------'    `------+------+------'
*/

#   define __________________MOUSE_L1_________________        ___x___, ___x___, TR_MOUU, ___x___, TR_MWHU
#   define __________________MOUSE_L2_________________        ___x___, TR_MOUL, TR_MOUD, TR_MOUR, TR_MWHD
#   define __________________MOUSE_L3_________________        TR_SNIP, ___x___, _______, TR_DRGS, ___x___
#   define          _________MOUSE_L4________                 KC_BTN1, KC_BTN2, KC_BTN3

#   define __________________MOUSE_R1_________________        TR_SDPI, TR_PDPI, ___x___, _______, TR_MOUT
#   define __________________MOUSE_R2_________________        ___x___, _____________SCAG_MODS____________
#   define __________________MOUSE_R3_________________        TR_DRGT, KC_BTN1, KC_BTN2, KC_BTN3, TR_SNIT

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          _________MOUSE_R4________                 KC_BTN5, KC_BTN4
#else
#   define          _________MOUSE_R4________                 KC_BTN5, KC_BTN4, ___x___
#endif


/*
*   ,----------------------------------.    ,----------------------------------.
*   |      |      |      |      |      |    |QWERTY|ClmkDH|Gaming|      | 1STog|
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Hue+ | Sat+ | Vib+ | Spd+ |      |    |      | Shft |      |ClkUp |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |RGBTog|RGBMod|      |      |      |    |AudTog|MusTog|ClkTog|ClkDn |LyrTap|
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      | Boot | Rbt  |    | Rbt  | Boot |      |
*                 `------+------+------'    `------+------+------'
*/

#   define _________________ADJUST_L1_________________        ___________________NONE_5__________________
#   define _________________ADJUST_L2_________________        TR_RHUI, TR_RSAI, TR_RVAI, TR_RSPI, ___x___
#   define _________________ADJUST_L3_________________        TR_RTOG, TR_RMOD, __________NONE_3_________
#   define          ________ADJUST_L4________                 ___x___, QK_BOOT, QK_RBT

#   define _________________ADJUST_R1_________________        QWERTY,  CLMAKDH, TR_GAME, ___x___, TR_OSTG
#   define _________________ADJUST_R2_________________        ___x___, KC_LSFT, ___x___, TR_CKUP, ___x___
#   define _________________ADJUST_R3_________________        TR_ATOG, TR_MTOG, TR_CTOG, TR_CKDN, _______

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________ADJUST_R4________                 QK_RBT,  QK_BOOT
#else
#   define          ________ADJUST_R4________                 QK_RBT,  QK_BOOT, ___x___
#endif

/*
*   ,----------------------------------.    ,----------------------------------.
*   |      |      |      |      |      |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      |      |      |      |      |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      |      |      |      |      |    |      |      |      |      |      |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/