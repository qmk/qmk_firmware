#pragma once
#include QMK_KEYBOARD_H

#if defined(OLED_ENABLE)
#   include "features/oled.h"
#endif

//#include "wrappers.h"

enum layers {
  _QWERTY = 0,
  FIRST_DEFAULT_LAYER = 0,  
  _COLEMAK_DH,
  _GAMING,
  _NUMBER,
  _NAVIGATION,
  _FUNCTION,
  _MOUSE,
  _GAMENUMBER,
  _ADJUST
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  CLMAKDH,
  GAMING
};

#define _DEFAULT_LAYER_1 FIRST_DEFAULT_LAYER
#define _DEFAULT_LAYER_2 (FIRST_DEFAULT_LAYER + 1)
#define _DEFAULT_LAYER_3 (FIRST_DEFAULT_LAYER + 2)

#define ___x___ KC_NO

//tap toggle layer
#define NAVGTIN    TT(_NAVIGATION)
#define NUMBERS    TT(_NUMBER)
#define GAMENUM    TT(_GAMENUMBER)
#define ADJUST     TT(_ADJUST)


//pinky layer taps
#define AD_SLSH    LT(_ADJUST, KC_SLSH)
#define FUNC_Z     LT(_FUNCTION, KC_SLSH)

//Windows Shortcuts
#define SC_COPY    LCTL(KC_C)
#define SC_CUT     LCTL(KC_X)
#define SC_UNDO    LCTL(KC_Z)
#define SC_PAST    LCTL(KC_V)
#define SC_REDO    LCTL(KC_Y)
#define W_SNIP     LSG(KC_S)
#define W_FILE     LGUI(KC_E)


/*
We will move all as many preprocessor directives here so the wrapper is easier to follow
- Any keycodes with prefix TR has behavior dependent on if the feature is enabled.
- We will only define things that are used across different layers. Entire layers are turned off in the keymap
*/

#if defined(ONESHOT_ENABLE)
#   define TR_OSTG OS_TOGG
#   define TR_LSFT OSM(MOD_LSFT)
#   define TR_LCTL OSM(MOD_LCTL)
#   define TR_LALT OSM(MOD_LALT)
#   define TR_LGUI OSM(MOD_LGUI)
#else
#   define TR_OSTG ___x___
#   define TR_LSFT KC_LSFT
#   define TR_LCTL KC_LCTL
#   define TR_LALT KC_LALT
#   define TR_LGUI KC_LGUI
#endif //ONESHOT_ENABLE



#if defined(MOUSELAYER_ENABLE)
#   define TR_MOUC LT(_MOUSE, KC_C)
#   define TR_BTN1 KC_BTN1
#   define TR_MOUS TG(_MOUSE)
#else
#   define TR_MOUC KC_C
#   define TR_BTN1 ___x___
#   define TR_MOUS ___x___
#endif //MOUSELAYER_ENABLE



#if defined(MOUSEKEY_ENABLE)
#   define TR_MOUU KC_MS_U
#   define TR_MOUD KC_MS_D
#   define TR_MOUL KC_MS_L
#   define TR_MOUR KC_MS_R
#   define TR_MWHU KC_WH_U
#   define TR_MWHD KC_WH_D
#else
#   define TR_MOUU ___x___
#   define TR_MOUD ___x___
#   define TR_MOUL ___x___
#   define TR_MOUR ___x___
#   define TR_MWHU ___x___
#   define TR_MWHD ___x___
#endif //MOUSEKEY_ENABLE



//these keycodes come from the cnano
#if defined(POINTING_DEVICE_ENABLE)
#   define TR_SNIP SNIPING
#   define TR_SNIT SNP_TOG
#   define TR_DRGS DRGSCRL
#   define TR_DRGT DRG_TOG
#   define TR_SDPI S_D_MOD
#   define TR_PDPI DPI_MOD
#else
#   define TR_SNIP ___x___
#   define TR_SNIT ___x___
#   define TR_DRGS ___x___
#   define TR_DRGT ___x___
#   define TR_SDPI ___x___
#   define TR_PDPI ___x___
#endif //POINTING_DEVICE_ENABLE



#if defined(GAMELAYER_ENABLE) 
#   define TR_GAME GAMING
#else
#   define TR_GAME ___x___
#endif //GAMELAYER_ENABLE



#if defined(HOMEROWMOD_ENABLE)
//Home Row Mods QWERTY
#   define TR_A  LGUI_T(KC_A)
#   define TR_S  LALT_T(KC_S)
#   define TR_D  LCTL_T(KC_D)
#   define TR_F  LSFT_T(KC_F)

#   define TR_J  LSFT_T(KC_J)
#   define TR_K  LCTL_T(KC_K)
#   define TR_L  LALT_T(KC_L)
#   define TR_QT LGUI_T(KC_QUOT)
//Home Row Mods COLEMAKDH
#   define TR_R  LALT_T(KC_R)
#   define TR_S  LCTL_T(KC_S)
#   define TR_T  LSFT_T(KC_T)

#   define TR_N  LSFT_T(KC_N)
#   define TR_E  LCTL_T(KC_E)
#   define TR_I  LALT_T(KC_I)
#   define TR_O  LGUI_T(KC_O)
#else
//Home Row Mods QWERTY
#   define TR_A  KC_A
#   define TR_S  KC_S
#   define TR_D  KC_D
#   define TR_F  KC_F

#   define TR_J  KC_J
#   define TR_K  KC_K
#   define TR_L  KC_L
#   define TR_QT KC_QUOT
//Home Row Mods COLEMAKDH
#   define TR_R  KC_R
#   define TR_S  KC_S
#   define TR_T  KC_T

#   define TR_N  KC_N
#   define TR_E  KC_E
#   define TR_I  KC_I
#   define TR_O  KC_O
#endif //HOMEROWMOD_ENABLE



#if defined(TAP_DANCE_ENABLE)
#   define TR_LBRC TD_LBKT
#   define TR_RBRC TD_RBKT
#else
#   define TR_LBRC KC_LBRC
#   define TR_RBRC KC_RBRC
#endif //TAP_DANCE_ENABLE



#if defined(DYNAMIC_MACRO_ENABLE)
#   define TR_DMR1 DM_REC1
#   define TR_DMP1 DM_PLY1
#   define TR_DMR2 DM_REC2
#   define TR_DMP2 DM_PLY2
#else
#   define TR_DMR1 ___x___
#   define TR_DMP1 ___x___
#   define TR_DMR2 ___x___
#   define TR_DMP2 ___x___
#endif //DYNAMIC_MACRO_ENABLE



#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#   define TR_RHUI RGB_HUI
#   define TR_RSAI RGB_SAI
#   define TR_RVAI RGB_VAI
#   define TR_RSPI RGB_SPI
#   define TR_RTOG RGB_TOG
#   define TR_RMOD RGB_MOD
#else
#   define TR_RHUI ___x___
#   define TR_RSAI ___x___
#   define TR_RVAI ___x___
#   define TR_RSPI ___x___
#   define TR_RTOG ___x___
#   define TR_RMOD ___x___
#endif //RGB_MATRIX_ENABLE or RGBLIGHT_ENABLE



#if defined(AUDIO_ENABLE)
#   define TR_ATOG AU_TOGG
#   define TR_MTOG MU_TOGG
#   define TR_CTOG CK_TOGG
#   define TR_CKUP CK_UP
#   define TR_CKDN CK_DOWN
#else
#   define TR_ATOG ___x___
#   define TR_MTOG ___x___
#   define TR_CTOG ___x___
#   define TR_CKUP ___x___
#   define TR_CKDN ___x___
#endif //AUDIO_ENABLE





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

#   define         __________NONE_3_________                  ___x___, ___x___, ___x___
#   define __________________NONE_5___________________        ___x___, ___x___, ___x___, ___x___, ___x___

#   define    _____________GACS_MODS____________              TR_LGUI, TR_LALT, TR_LCTL, TR_LSFT
#   define    _____________SCAG_MODS____________              TR_LSFT, TR_LCTL, TR_LALT, TR_LGUI

#   define _________________UCCPR_L___________________        SC_UNDO, SC_CUT,  SC_COPY, SC_PAST, SC_REDO

#   define         _________BASE_L4_________                  TR_BTN1, NUMBERS, TR_LSFT

//right side only has two thumb keys
#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define         _________BASE_R4_________                  KC_SPC,  NAVGTIN
#else
#   define         _________BASE_R4_________                  KC_SPC,  NAVGTIN, ___x___
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
#   define _________________QWERTY_L3_________________        FUNC_Z,  KC_X,    TR_MOUC, KC_V,    KC_B

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
#   define ________________COLEMAKDH_L3_______________        FUNC_Z,  KC_X,    TR_MOUC, KC_D,    KC_V

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
*   |  Z   |   X  |   C  |   V  |   B  |    |      |      |      |      | ADJ  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Ctrl | Spc  | Shift|    |      | Nav  |      |
*                 `------+------+------'    `------+------+------'
*/
#   define _______________GAMING_BASE_L1______________        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R
#   define _______________GAMING_BASE_L2______________        GAMENUM, KC_A,    KC_S,    KC_D,    KC_F
#   define _______________GAMING_BASE_L3______________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#   define          ______GAMING_BASE_L4_____                 KC_LCTL, KC_SPC,  KC_LSFT

#   define _______________GAMING_BASE_R1______________        __________________NONE_5___________________
#   define _______________GAMING_BASE_R2______________        __________________NONE_5___________________
#   define _______________GAMING_BASE_R3______________        ___x___, ___x___, ___x___, ___x___, ADJUST

# if defined(KEYBOARD_bastardkb_charybdis_3x5) 
#   define          ______GAMING_BASE_R4_____                 ___x___, NAVGTIN
# else
#   define          ______GAMING_BASE_R4_____                 ___x___, NAVGTIN, ___x___
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
*   | Esc  | Snip | File | Bpsc |   `  |    |   [  |   7  |   8  |   9  |   ]  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Gui  | Alt  | Ctrl | Shft |   .  |    |   -  |   4  |   5  |   6  |   =  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |   ;  |   1  |   2  |   3  |   \  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | MB1  |LyrTap| Ent  |    | Spc  |   0  |      |
*                 `------+------+------'    `------+------+------'
*/
#   define _________________NUMPAD_L1_________________        KC_ESC,  W_SNIP,  W_FILE,  KC_BSPC, KC_GRV
#   define _________________NUMPAD_L2_________________        _____________GACS_MODS____________, KC_DOT
#   define _________________NUMPAD_L3_________________        _________________UCCPR_L___________________
#   define          ________NUMPAD_L4________                 TR_BTN1, _______, KC_ENT

#   define _________________NUMPAD_R1_________________        TR_LBRC, KC_7,    KC_8,    KC_9,    TR_RBRC
#   define _________________NUMPAD_R2_________________        KC_MINS, KC_4,    KC_5,    KC_6,    KC_EQL
#   define _________________NUMPAD_R3_________________        KC_SCLN, KC_1,    KC_2,    KC_3,    KC_BSLS

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
*   | Esc  | Home | Up   | End  | PgUp |    | Ins  |      | App  |      | MOU  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      | Left | Down | Right| PgDn |    | Del  | Shft | Ctrl | Alt  | Gui  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    |      |      |      |      |      |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Tab  | Bpsc | Ent  |    | Spc  | NAV  |      |
*                 `------+------+------'    `------+------+------'
*/
#   define ___________________NAV_L1__________________        KC_ESC,  KC_HOME, KC_UP,   KC_END,  KC_PGUP
#   define ___________________NAV_L2__________________        ___x___, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#   define ___________________NAV_L3__________________        _________________UCCPR_L___________________
#   define          __________NAV_L4_________                 KC_TAB,  KC_BSPC, KC_ENT

#   define ___________________NAV_R1__________________        KC_INS,  ___x___, KC_APP,  ___x___, TR_MOUS
#   define ___________________NAV_R2__________________        KC_DEL,  _____________SCAG_MODS____________
#   define ___________________NAV_R3__________________        __________________NONE_5___________________ 

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          __________NAV_R4_________                 KC_SPC,  _______
#else
#   define          __________NAV_R4_________                 KC_SPC,  _______, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5


/*
*   ,----------------------------------.    ,----------------------------------.
*   |      |      |      |      |      |    |ScrLck|  F7  |  F8  |  F9  | F10  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GUI  | Alt  | Ctrl | Shft |PrnScr|    |CapLck|  F4  |  F5  |  F6  | F11  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |LyrTap|      | Vol- | Vol+ | Mute |    |PauBrk|  F1  |  F2  |  F3  | F12  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | MB1  |DMRec1|DMPly1|    |DMPly2|DMRec2|      |
*                 `------+------+------'    `------+------+------'
*/
#   define _________________FUNCPAD_L1________________        __________________NONE_5___________________
#   define _________________FUNCPAD_L2________________        _____________GACS_MODS____________, KC_PSCR
#   define _________________FUNCPAD_L3________________        _______, ___x___, KC_VOLD, KC_VOLU, KC_MUTE
#   define          ________FUNCPAD_L4_______                 TR_BTN1, TR_DMR1, TR_DMP1

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
*   |      |      | MouU |      | MwU  |    | sDPI | DPI  |      |      | MOU  |
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

#   define __________________MOUSE_R1_________________        TR_SDPI, TR_PDPI, ___x___, ___x___, TR_MOUS
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

#   define _________________ADJUST_L1_________________        __________________NONE_5___________________
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