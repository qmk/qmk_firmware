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

#define              _____BLANK_2____                       _______, _______
#define          _________BLANK_3_________                  _______, _______, _______
#define __________________BLANK_5__________________         _______, _______, _______, _______, _______

#define              _____NONE_2_____                       ___x___, ___x___
#define          _________NONE_3__________                  ___x___, ___x___, ___x___
#define __________________NONE_5___________________         ___x___, ___x___, ___x___, ___x___, ___x___

#define          _________BASE_L4_________                  KC_MPLY, NUMBER,  KC_LSFT

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
# define          _________BASE_R4_________                 KC_SPC,  NAV_TAB
#else
# define          _________BASE_R4_________                 KC_SPC,  NAV_TAB, KC_MUTE
#endif //KEYBOARD_bastardkb_charybdis_3x5

#define          _________MEDIA_R3________                  KC_VOLD, KC_VOLU, KC_MUTE

#define          _________EDIT_L3_________                  CLSETAB, KC_BSPC, KC_ENT

/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  |      |      |   ~  |   `  |    | Ins  |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GUI  | Alt  | Ctrl | Shft |   .  |    | Del  | Shft | Ctrl | Alt  | GUI  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |      | Spc  | Tab  |      | App  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#define _______________MOD_CMDS_L1_________________         KC_ESC,  ___x___, ___x___, KC_TILD, KC_GRV
#define _______________MOD_CMDS_L2_________________         KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_DOT
#define _______________MOD_CMDS_L3_________________         SC_UNDO, SC_CUT,  SC_COPY, SC_PAST, SC_REDO

#define _______________MOD_CMDS_R1_________________         KC_INS,  ___x___, ___x___, ___x___, ___x___
#define _______________MOD_CMDS_R2_________________         KC_DEL,  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI
#define _______________MOD_CMDS_R3_________________         ___x___, KC_SPC,  KC_TAB,  ___x___, KC_APP


/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |   '  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#define _________________QWERTY_L1_________________         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L3_________________         FUN_Z,   KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R3_________________         KC_N,    KC_M,    KC_COMM, KC_DOT,  AD_SLSH

#if defined(HOMEROWMOD_ENABLE)
# define _________________QWERTY_L2_________________         LGUI_A,  LALT_S,  CTRL_D,  SHFT_F,  KC_G
# define _________________QWERTY_R2_________________         KC_H,    SHFT_J,  CTRL_K,  LALT_L,  LGUI_QT
#else
# define _________________QWERTY_L2_________________         KC_A,    KC_S,    KC_D,    KC_F,    KC_G
# define _________________QWERTY_R2_________________         KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT
#endif //HOMEROWMOD_ENABLE


/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   |   Q  |   W  |   F  |   P  |   B  |    |   J  |   L  |   U  |   Y  |   '  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |   A  |   R  |   S  |   T  |   G  |    |   M  |   N  |   E  |   I  |   O  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |   Z  |   X  |   C  |   D  |   V  |    |   K  |   H  |   ,  |   .  |   /  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#define ______________COLEMAK_MOD_DH_L1____________         KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L3____________         FUN_Z,   KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________         KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT
#define ______________COLEMAK_MOD_DH_R3____________         KC_K,    KC_H,    KC_COMM, KC_DOT,  AD_SLSH

#if defined(HOMEROWMOD_ENABLE)
# define ______________COLEMAK_MOD_DH_L2____________         LGUI_A,  LALT_R,  CTRL_S,  SHFT_T,  KC_G
# define ______________COLEMAK_MOD_DH_R2____________         KC_M,    SHFT_N,  CTRL_E,  LALT_I,  LGUI_O
#else
# define ______________COLEMAK_MOD_DH_L2____________         KC_A,    KC_R,    KC_S,    KC_T,    KC_G
# define ______________COLEMAK_MOD_DH_R2____________         KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#endif //HOMEROWMOD_ENABLE



/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  |      |      |   ~  |   `  |    | tLBKT|   7  |   8  |   9  | tRBKT|
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GUI  | Alt  | Ctrl | Shft |   .  |    |   ;  |   4  |   5  |   6  |   =  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |   -  |   1  |   2  |   3  |   \  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |LyrTap|      |    | Spc  |   0  |      |
*                 `------+------+------'    `------+------+------'
*/

#define _______________NUMBER_PAD_L1_______________         _______________MOD_CMDS_L1_________________
#define _______________NUMBER_PAD_L2_______________         _______________MOD_CMDS_L2_________________
#define _______________NUMBER_PAD_L3_______________         _______________MOD_CMDS_L3_________________
#define          ______NUMBER_PAD_L4______                  ___x___, _______, ___x___

//ifdef TAP_DANCE_ENABLE
#if defined(TAP_DANCE_ENABLE)
# define _______________NUMBER_PAD_R1_______________         TD_LBKT, KC_7,    KC_8,    KC_9,    TD_RBKT
#else
# define _______________NUMBER_PAD_R1_______________         KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC
#endif //TAP_DANCE_ENABLE

#define _______________NUMBER_PAD_R2_______________         KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL
#define _______________NUMBER_PAD_R3_______________         KC_MINS, KC_1,    KC_2,    KC_3,    KC_BSLS

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
# define          ______NUMBER_PAD_R4______                 KC_SPC,  KC_0
#else
# define          ______NUMBER_PAD_R4______                 KC_SPC,  KC_0,    ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

#define _______________NUMBER_ROW_L1_______________         KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _______________NUMBER_ROW_R1_______________         KC_6,    KC_7,    KC_8,    KC_9,    KC_0

/*
*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  | Home | Up   | End  | PgUp |    | Ins  |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Caps | Left | Down | Right| PgDn |    | Del  | Shft | Ctrl | Alt  | GUI  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |      | Spc  | Tab  |      | App  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |ClseTb| Bpsc | Ent  |    |      |LyrTap|      |
*                 `------+------+------'    `------+------+------'
*/
#define _______________NAVIGATION_L1_______________         KC_ESC,  KC_HOME, KC_UP,   KC_END,  KC_PGUP
#define _______________NAVIGATION_L2_______________         KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#define _______________NAVIGATION_L3_______________         _______________MOD_CMDS_L3_________________
#define          ______NAVIGATION_L4______                  _________EDIT_L3_________

#define _______________NAVIGATION_R1_______________         _______________MOD_CMDS_R1_________________
#define _______________NAVIGATION_R2_______________         _______________MOD_CMDS_R2_________________
#define _______________NAVIGATION_R3_______________         _______________MOD_CMDS_R3_________________

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
# define          ______NAVIGATION_R4______                 ___x___, _______
#else
# define          ______NAVIGATION_R4______                 ___x___, _______, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5




/*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  |      |      |   ~  |   `  |    |PrtScr|  F7  |  F8  |  F9  | F12  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GUI  | Alt  | Ctrl | Shft |   .  |    |ScrLck|  F4  |  F5  |  F6  | F11  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |LyrTap|      |      |      |      |    |PauBrk|  F1  |  F2  |  F3  | F10  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    | Vol- | Vol+ | Mute |
*                 `------+------+------'    `------+------+------'
*/

#define ______________FUNCTION_PAD_L1______________         _______________MOD_CMDS_L1_________________
#define ______________FUNCTION_PAD_L2______________         _______________MOD_CMDS_L2_________________
#define ______________FUNCTION_PAD_L3______________         _______, ___x___, ___x___, ___x___, ___x___
#define          _____FUNCTION_PAD_L4_____                  _________NONE_3__________

#define ______________FUNCTION_PAD_R1______________         KC_PSCR, KC_F7,   KC_F8,   KC_F9,   KC_F12
#define ______________FUNCTION_PAD_R2______________         KC_SCRL, KC_F4,   KC_F5,   KC_F6,   KC_F11
#define ______________FUNCTION_PAD_R3______________         KC_PAUS, KC_F1,   KC_F2,   KC_F3,   KC_F10

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#define          _____FUNCTION_PAD_R4_____                  ___x___, ___x___
#else
#define          _____FUNCTION_PAD_R4_____                  _________MEDIA_R3________
#endif //KEYBOARD_bastardkb_charybdis_3x5

#define ______________FUNCTION_ROW_L1______________         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ______________FUNCTION_ROW_M1______________         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#define            ___FUNCROW_R1___                         KC_F11,  KC_F12

/*
*   ,----------------------------------.    ,----------------------------------.
*   |      |MS B4 |Ms Up |MS B5 | MsWU |    | Ins  |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      | Ms L |Ms Dn |Ms R  | MsWD |    | Del  | Shft | Ctrl | Alt  | GUI  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      |      |      |      |      |    |      | Spc  | Tab  |      | App  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |MS B3 |Ms B2 |Ms B1 |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/
#define _______________MOUSE_KEYS_L1_______________         ___x___, KC_BTN4, KC_MS_U, KC_BTN5, KC_WH_U
#define _______________MOUSE_KEYS_L2_______________         ___x___, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D
#define _______________MOUSE_KEYS_L3_______________         __________________NONE_5___________________
#define          ______MOUSE_KEYS_L4______                  KC_BTN3, KC_BTN2, KC_BTN1

#define _______________MOUSE_KEYS_R1_______________         _______________MOD_CMDS_R1_________________
#define _______________MOUSE_KEYS_R2_______________         _______________MOD_CMDS_R2_________________
#define _______________MOUSE_KEYS_R3_______________         _______________MOD_CMDS_R3_________________
#define          ______MOUSE_KEYS_R4______                  _________NONE_3__________


/*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  |      |      |   ~  |   `  |    |      |Ms B4 | MsWU |Ms B5 |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GUI  | Alt  | Ctrl | Shft |   .  |    |      |Ms B1 | MsWD |Ms B2 |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |      | MsWL |Ms B3 | MsWR |      |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Del  |      | Ent  |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/
#define _________________MOUSE_L1__________________         _______________MOD_CMDS_L1_________________
#define _________________MOUSE_L2__________________         _______________MOD_CMDS_L2_________________
#define _________________MOUSE_L3__________________         _______________MOD_CMDS_L3_________________
#define          ________MOUSE_L4_________                  KC_DEL,  ___x___, KC_ENT

#define _________________MOUSE_R1__________________         ___x___, KC_BTN4, KC_WH_U, KC_BTN5, ___x___
#define _________________MOUSE_R2__________________         ___x___, KC_BTN1, KC_WH_D, KC_BTN2, ___x___
#define _________________MOUSE_R3__________________         ___x___, KC_WH_L, KC_BTN3, KC_WH_R, ___x___
#define          ________MOUSE_R4_________                  ___x___, ___x___


/*
*   ,----------------------------------.    ,----------------------------------.
*   | Hue+ | Hue- | Spd+ | Spd- |      |    |QWERTY|ClmkDH|      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Sat+ | Sat- | Vib+ | Vib- |      |    |AudTog|MusTog|ClkTog|ClkUp |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |RGBTog|RGBMod|RGBRMd|Debug |Reset |    |Reset |Debug |ClkDn |ClkDn |LyrTap|
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |RecStp|DMRec1|DMPly1|    |DMPly2|DMRec2|RecStp|
*                 `------+------+------'    `------+------+------'
*/

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
# define _________________ADJUST_L1_________________         RGB_HUI, RGB_HUD, RGB_SPI, RGB_SPD, ___x___
# define _________________ADJUST_L2_________________         RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ___x___
# define _________________ADJUST_L3_________________         RGB_TOG, RGB_MOD, RGB_RMOD, QK_BOOT, QK_RBT
#else
# define _________________ADJUST_L1_________________         __________________NONE_5___________________
# define _________________ADJUST_L2_________________         __________________NONE_5___________________
# define _________________ADJUST_L3_________________         _________NONE_3__________, QK_BOOT, QK_RBT
#endif //RGB_MATRIX_ENABLE || RGBLIGHT_ENABLE

#if defined(DYNAMIC_MACRO_ENABLE)
# define          ________ADJUST_L4________                  DM_RSTP, DM_REC1, DM_PLY1
#else
# define          ________ADJUST_L4________                  _________NONE_3__________
#endif //DYNAMIC_MACRO_ENABLE




#if defined(AUDIO_ENABLE)
# define _________________ADJUST_R1_________________         QWERTY,  CLMAKDH, ___x___, ___x___, ___x___
# define _________________ADJUST_R2_________________         AU_TOGG, MU_TOGG, CK_TOGG, CK_UP,   ___x___
# define _________________ADJUST_R3_________________         QK_RBT,  QK_BOOT, CK_DOWN, CK_DOWN, _______
#else
# define _________________ADJUST_R1_________________         QWERTY,  CLMAKDH, ___x___, ___x___, ___x___
# define _________________ADJUST_R2_________________         __________________NONE_5___________________
# define _________________ADJUST_R3_________________         QK_RBT,  QK_BOOT, ___x___, ___x___, _______
#endif //AUDIO_ENABLE


#if (defined(KEYBOARD_bastardkb_charybdis_3x5) && defined(DYNAMIC_MACRO_ENABLE))
# define          ________ADJUST_R4________                  ___x___, ___x___
#elif defined(KEYBOARD_bastardkb_charybdis_3x5)
# define          ________ADJUST_R4________                  ___x___, ___x___
#elif defined(DYNAMIC_MACRO_ENABLE)
# define          ________ADJUST_R4________                  DM_PLY2, DM_REC2, DM_RSTP
#else
# define          ________ADJUST_R4________                  _________NONE_3__________
#endif