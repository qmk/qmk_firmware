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

#define            __________NONE_3_________                  ___x___, ___x___, ___x___
#define   ___________________NONE_5__________________         ___x___, ___x___, ___x___, ___x___, ___x___

#define       _____________GACS_MODS____________              KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT
#define       _____________SCAG_MODS____________              KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI
#define   __________________UCCPR_L__________________         SC_UNDO, SC_CUT,  SC_COPY, SC_PAST, SC_REDO


#if defined(MOUSELAYER_ENABLED)
#   define         _________BASE_L4_________                  MOUSE,   NUMBER,  KC_LSFT
#else
#   define         _________BASE_L4_________                  ___x___, NUMBER,  KC_LSFT
#endif //MOUSELAYER_ENABLED

//slave side only has two thumb keys
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
*   |   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#define    _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define    _________________QWERTY_L3_________________        FUN_Z,   KC_X,    KC_C,    KC_V,    KC_B

#define    _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define    _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  AD_SLSH

#if defined(HOMEROWMOD_ENABLED)
#   define _________________QWERTY_L2_________________        LGUI_A,  LALT_S,  CTRL_D,  SHFT_F,  KC_G
#   define _________________QWERTY_R2_________________        KC_H,    SHFT_J,  CTRL_K,  LALT_L,  LGUI_QT
#else
#   define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#   define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT
#endif //HOMEROWMOD_ENABLE


/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   |   Q  |   W  |   F  |   P  |   B  |    |   J  |   L  |   U  |   Y  |   '  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |   A  |   R  |   S  |   T  |   G  |    |   M  |   N  |   E  |   I  |   O  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | FUNZ |   X  |   C  |   D  |   V  |    |   K  |   H  |   ,  |   .  |   /  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#define    ________________COLEMAKDH_L1_______________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define    ________________COLEMAKDH_L3_______________        FUN_Z,   KC_X,    KC_C,    KC_D,    KC_V

#define    ________________COLEMAKDH_R1_______________        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT
#define    ________________COLEMAKDH_R3_______________        KC_K,    KC_H,    KC_COMM, KC_DOT,  AD_SLSH

#if defined(HOMEROWMOD_ENABLED)
#   define ________________COLEMAKDH_L2_______________        LGUI_A,  LALT_R,  CTRL_S,  SHFT_T,  KC_G
#   define ________________COLEMAKDH_R2_______________        KC_M,    SHFT_N,  CTRL_E,  LALT_I,  LGUI_O
#else
#   define ________________COLEMAKDH_L2_______________        KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#   define ________________COLEMAKDH_R2_______________        KC_M,    KC_N,    KC_E,    KC_I,    KC_O
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

#define    _________________NUMPAD_L1_________________        KC_ESC,  ___x___, ___x___, KC_TILD, KC_GRV
#define    _________________NUMPAD_L2_________________        _____________GACS_MODS____________, KC_DOT
#define    _________________NUMPAD_L3_________________        __________________UCCPR_L__________________
#define             ________NUMPAD_L4________                 ___x___, _______, ___x___

#define    _________________NUMPAD_R2_________________        KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL
#define    _________________NUMPAD_R3_________________        KC_MINS, KC_1,    KC_2,    KC_3,    KC_BSLS

//ifdef TAP_DANCE_ENABLE
#if defined(TAP_DANCE_ENABLE)
#   define _________________NUMPAD_R1_________________        TD_LBKT, KC_7,    KC_8,    KC_9,    TD_RBKT
#else
#   define _________________NUMPAD_R1_________________        KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC
#endif //TAP_DANCE_ENABLE

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________NUMPAD_R4________                 KC_SPC,  KC_0
#else
#   define          ________NUMPAD_R4________                 KC_SPC,  KC_0,    ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

#define    __________________NUMROW_L_________________        KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define    __________________NUMROW_R_________________        KC_6,    KC_7,    KC_8,    KC_9,    KC_0

/*
*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  | Home | Up   | End  | PgUp |    | Ins  |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Caps | Left | Down | Right| PgDn |    | Del  | Shft | Ctrl | Alt  | GUI  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |      | Spc  | Tab  |      | App  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      | Bpsc | Ent  |    |      |LyrTap|      |
*                 `------+------+------'    `------+------+------'
*/
#   define ___________________NAV_L1__________________        KC_ESC,  KC_HOME, KC_UP,   KC_END,  KC_PGUP
#   define ___________________NAV_L2__________________        KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#   define ___________________NAV_L3__________________        __________________UCCPR_L__________________
#   define          __________NAV_L4_________                 ___x___, KC_BSPC, KC_ENT

#   define ___________________NAV_R1__________________        KC_INS,  ___x___, ___x___, ___x___, ___x___
#   define ___________________NAV_R2__________________        KC_DEL,  _____________SCAG_MODS____________
#   define ___________________NAV_R3__________________        ___x___, KC_SPC,  KC_TAB,  ___x___, KC_APP

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          __________NAV_R4_________                 ___x___, _______
#else
#   define          __________NAV_R4_________                 ___x___, _______, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5




/*
*   ,----------------------------------.    ,----------------------------------.
*   |      |      |      |      |      |    |PrtScr|  F7  |  F8  |  F9  | F10  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GUI  | Alt  | Ctrl | Shft |      |    |ScrLck|  F4  |  F5  |  F6  | F11  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      |      | Vol- | Vol+ | Mute |    |PauBrk|  F1  |  F2  |  F3  | F12  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |LyrTap|      |      |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#   define _________________FUNCPAD_L1________________        ___________________NONE_5__________________
#   define _________________FUNCPAD_L2________________        _____________GACS_MODS____________, ___x___
#   define _________________FUNCPAD_L3________________        ___x___, ___x___, KC_VOLD, KC_VOLU, KC_MUTE
#   define          ________FUNCPAD_L4_______                 _______, ___x___, ___x___

#   define _________________FUNCPAD_R1________________        KC_PSCR, KC_F7,   KC_F8,   KC_F9,   KC_F10
#   define _________________FUNCPAD_R2________________        KC_SCRL, KC_F4,   KC_F5,   KC_F6,   KC_F11
#   define _________________FUNCPAD_R3________________        KC_PAUS, KC_F1,   KC_F2,   KC_F3,   KC_F12

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________FUNCPAD_R4_______                 ___x___, ___x___
#else
#   define          ________FUNCPAD_R4_______                 __________NONE_3_________
#endif //KEYBOARD_bastardkb_charybdis_3x5

#   define _________________FUNCROW_L_________________        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#   define _________________FUNCROW_M_________________        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#   define              ____FUNCROW_R___                      KC_F11,  KC_F12

/*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  |MBtn4 | MouU |MBtn5 | MwU  |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Mute | MouL | MouD | MouR | MwD  |    |      | Shft | Ctrl | Alt  | GUI  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |      |      |      |      |MOUTOG|
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |MS B3 |Ms B2 |Ms B1 |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/

#if defined(MOUSEKEY_ENABLE)
#   define __________________MOUSE_L1_________________        KC_ESC,  KC_BTN4, KC_MS_U, KC_BTN5, KC_WH_U
#   define __________________MOUSE_L2_________________        KC_MUTE, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D
#   define __________________MOUSE_L3_________________        __________________UCCPR_L__________________
#   define          _________MOUSE_L4________                 KC_BTN3, KC_BTN2, KC_BTN1

#   define __________________MOUSE_R1_________________        ___________________NONE_5__________________
#   define __________________MOUSE_R2_________________        ___x___, _____________SCAG_MODS____________
#   define __________________MOUSE_R3_________________        ___x___, ___x___, ___x___, ___x___, MOU_TOG
#   define          _________MOUSE_R4________                 __________NONE_3_________
#endif //MOUSEKEY_ENABLE

/*
*   ,----------------------------------.    ,----------------------------------.
*   |  Esc |SniTog|MBtn3 | DPI  | sDPI |    | sDPI | DPI  |      |SniTog| Mute |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |MBtn5 |MBtn4 |DrgTog|MBtn1 |MBtn2 |    |      | Shft | Ctrl | Alt  | GUI  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |MBtn2 |MBtn1 |DrgTog|MBtn4 |MBtn5 |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |LyrTap|      |      |    |MOUTOG|MBtn3 |      |
*                 `------+------+------'    `------+------+------'
*/

//this is designed for the cnano (R4)
//two hands for productive, but able to use one hand for causal internet surfing (won't be able to select text one handed)
#if defined(POINTING_DEVICE_ENABLE_OFF)
#   define __________________MOUSE_L1_________________        KC_ESC,  SNP_TOG, KC_BTN3, DPI_MOD, S_D_MOD
#   define __________________MOUSE_L2_________________        ___x___, KC_BTN5, DRGSCRL, KC_BTN4, ___x___
#   define __________________MOUSE_L3_________________        __________________UCCPR_L__________________
#   define          _________MOUSE_L4________                 MOU_TOG, KC_BTN1, KC_BTN2

#   define __________________MOUSE_R1_________________        S_D_MOD, DPI_MOD, ___x___, SNP_TOG, KC_MUTE
#   define __________________MOUSE_R2_________________        ___x___, _____________SCAG_MODS____________
#   define __________________MOUSE_R3_________________        KC_BTN3, KC_BTN1, DRG_TOG, KC_BTN4, KC_BTN5
#   define          _________MOUSE_R4________                 MOU_TOG, KC_BTN2
#endif //POINTING_DEVICE_ENABLE

#if defined(POINTING_DEVICE_ENABLE)
#   define __________________MOUSE_L1_________________        KC_ESC,  SNP_TOG, KC_BTN3, DPI_MOD, S_D_MOD
#   define __________________MOUSE_L2_________________        KC_BTN5, KC_BTN4, DRG_TOG, KC_BTN1, KC_BTN2
#   define __________________MOUSE_L3_________________        __________________UCCPR_L__________________
#   define          _________MOUSE_L4________                 _______, ___x___, ___x___

#   define __________________MOUSE_R1_________________        S_D_MOD, DPI_MOD, ___x___, SNP_TOG, KC_MUTE
#   define __________________MOUSE_R2_________________        ___x___, _____________SCAG_MODS____________
#   define __________________MOUSE_R3_________________        KC_BTN2, KC_BTN1, DRG_TOG, KC_BTN4, KC_BTN5
#   define          _________MOUSE_R4________                 MOU_TOG, KC_BTN3
#endif //POINTING_DEVICE_ENABLE

/*
*   ,----------------------------------.    ,----------------------------------.
*   | Hue+ | Hue- | Spd+ | Spd- |      |    |QWERTY|ClmkDH|      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Sat+ | Sat- | Vib+ | Vib- |      |    |AudTog|MusTog|ClkTog|ClkUp |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |RGBTog|RGBMod|RGBRMd|      |      |    |Reset |Debug |ClkDn |ClkDn |LyrTap|
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |RecStp|DMRec1|DMPly1|    |DMPly2|DMRec2|RecStp|
*                 `------+------+------'    `------+------+------'
*/

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#   define _________________ADJUST_L1_________________        RGB_HUI, RGB_HUD, RGB_SPI, RGB_SPD, ___x___
#   define _________________ADJUST_L2_________________        RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ___x___
#   define _________________ADJUST_L3_________________        RGB_TOG, RGB_MOD, RGB_RMOD, ___x___, ___x___
#else
#   define _________________ADJUST_L1_________________        ___________________NONE_5__________________
#   define _________________ADJUST_L2_________________        ___________________NONE_5__________________
#   define _________________ADJUST_L3_________________        __________NONE_3_________, QK_BOOT, QK_RBT
#endif //RGB_MATRIX_ENABLE || RGBLIGHT_ENABLE

#if defined(DYNAMIC_MACRO_ENABLE)
#   define          ________ADJUST_L4________                 DM_RSTP, DM_REC1, DM_PLY1
#else
#   define          ________ADJUST_L4________                 __________NONE_3_________
#endif //DYNAMIC_MACRO_ENABLE




#if defined(AUDIO_ENABLE)
#   define _________________ADJUST_R1_________________        QWERTY,  CLMAKDH, __________NONE_3_________
#   define _________________ADJUST_R2_________________        AU_TOGG, MU_TOGG, CK_TOGG, CK_UP,   ___x___
#   define _________________ADJUST_R3_________________        QK_RBT,  QK_BOOT, CK_DOWN, CK_DOWN, _______
#else
#   define _________________ADJUST_R1_________________        QWERTY,  CLMAKDH, __________NONE_3_________
#   define _________________ADJUST_R2_________________        ___________________NONE_5__________________
#   define _________________ADJUST_R3_________________        QK_RBT,  QK_BOOT, ___x___, ___x___, _______
#endif //AUDIO_ENABLE


#if (defined(KEYBOARD_bastardkb_charybdis_3x5) && defined(DYNAMIC_MACRO_ENABLE))
#   define          ________ADJUST_R4________                 ___x___, ___x___
#elif defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________ADJUST_R4________                 ___x___, ___x___
#elif defined(DYNAMIC_MACRO_ENABLE)
#   define          ________ADJUST_R4________                 DM_PLY2, DM_REC2, DM_RSTP
#else
#   define          ________ADJUST_R4________                 __________NONE_3_________
#endif