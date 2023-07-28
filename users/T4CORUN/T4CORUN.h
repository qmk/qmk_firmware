#pragma once
#include QMK_KEYBOARD_H

#if defined(TAPHOLD_ENABLE)
#   include "features/taphold.h"
#endif

//#include "wrappers.h"

//bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode);

enum layers {
  _QWERTY = 0,
  FIRST_DEFAULT_LAYER = 0,  
  _COLEMAK_DH,
  _GAMING,
  _NUMBER,
  _NAVIGATION,
  _SYMBOL,
  _MOUSE,
  _GAMENUMBER,
  _CONFIG
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  CLMAKDH,
  GAMING,

  TH_UNDS,
  TH_LABK,
  TH_RABK,
  TH_SLSH,
  TH_BSLS,
  TH_HASH,
  TH_MINS,
  TH_PIPE,
  TH_AMPR,
  TH_EQL,
  TH_GRV,
  TH_EXLM,
  TH_LPRN,
  TH_LCBR,
  TH_LBRC,
  TH_QUOT,
  TH_DQUO,

  TH_COMM,
  TH_DOT,
  TH_SCLN
};

#define _DEFAULT_LAYER_1 FIRST_DEFAULT_LAYER
#define _DEFAULT_LAYER_2 (FIRST_DEFAULT_LAYER + 1)
#define _DEFAULT_LAYER_3 (FIRST_DEFAULT_LAYER + 2)

#define ___x___ KC_NO

//momentary layer
#define NAVGTIN    LT(_NAVIGATION, KC_0)
#define NUMBERS    LT(_NUMBER, KC_BSPC)
#define GAMENUM    MO(_GAMENUMBER)
#define CONFIG     MO(_CONFIG)

//Windows Shortcuts
#define SC_COPY    LCTL(KC_C)
#define SC_CUT     LCTL(KC_X)
#define SC_UNDO    LCTL(KC_Z)
#define SC_PAST    LCTL(KC_V)
#define SC_REDO    LCTL(KC_Y)
#define W_SNIP     LSG(KC_S)
#define W_FILE     LGUI(KC_E)
#define NXT_TAB    LCTL(KC_TAB)

/*
We will move all as many preprocessor directives here so the wrapper is easier to follow
- Any keycodes with prefix TR has behavior dependent on if the feature is enabled.
- We will only define things that are used across different layers. Entire layers are turned off in the keymap
*/

#if defined(ONESHOT_ENABLE)
#   define TR_LSFT OSM(MOD_LSFT)
#   define TR_LCTL OSM(MOD_LCTL)
#   define TR_LALT OSM(MOD_LALT)
#   define TR_LGUI OSM(MOD_LGUI)
#else
#   define TR_LSFT KC_LSFT
#   define TR_LCTL KC_LCTL
#   define TR_LALT KC_LALT
#   define TR_LGUI KC_LGUI
#endif //ONESHOT_ENABLE


//Layer tap key is dependent on if mouse pointer or mouse keys
//c for pointer, z for keys
#if defined(MOUSELAYER_ENABLE) && !defined(MOUSEKEY_ENABLE)
#   define TR_MOUC LT(_MOUSE, KC_C)
#   define TR_MOUZ KC_Z
#elif defined(MOUSELAYER_ENABLE) && defined(MOUSEKEY_ENABLE)
#   define TR_MOUC KC_C
#   define TR_MOUZ LT(_MOUSE, KC_Z)
#else
#   define TR_MOUZ KC_Z
#   define TR_MOUC KC_C
#endif //defined(MOUSELAYER_ENABLE) && !defined(MOUSEKEY_ENABLE)


#if defined(MOUSELAYER_ENABLE)
#   define TR_BTN1 KC_BTN1
#else
#   define TR_BTN1 ___x___
#endif //MOUSELAYER_ENABLE


#if defined(MOUSEKEY_ENABLE)
#   define TR_BTN4 KC_BTN4
#   define TR_BTN5 KC_BTN5
#   define TR_MOUU KC_MS_U
#   define TR_MOUD KC_MS_D
#   define TR_MOUL KC_MS_L
#   define TR_MOUR KC_MS_R
#   define TR_MWHU KC_WH_U
#   define TR_MWHD KC_WH_D

#else
#   define TR_BTN4 ___x___
#   define TR_BTN5 ___x___
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


//There seems to be an issue with the ANSI shifted keys. see if we can do a mod

#if defined(TAPHOLD_ENABLE)
//Double Taps
#   define TR_UNDS  LT(_DEFAULT_LAYER_1, TH_UNDS)
#   define TR_LABK  LT(_DEFAULT_LAYER_1, TH_LABK)
#   define TR_RABK  LT(_DEFAULT_LAYER_1, TH_RABK)
#   define TR_SLSH  LT(_DEFAULT_LAYER_1, TH_SLSH)
#   define TR_BSLS  LT(_DEFAULT_LAYER_1, TH_BSLS)
#   define TR_HASH  LT(_DEFAULT_LAYER_1, TH_HASH)
#   define TR_MINS  LT(_DEFAULT_LAYER_1, TH_MINS)
//Double Taps with Spaces
#   define TR_PIPE  LT(_DEFAULT_LAYER_1, TH_PIPE)
#   define TR_AMPR  LT(_DEFAULT_LAYER_1, TH_AMPR)
#   define TR_EQL   LT(_DEFAULT_LAYER_1, TH_EQL)
//Triple Tap
#   define TR_GRV   LT(_DEFAULT_LAYER_1, TH_GRV)
//Custom
#   define TR_EXLM  LT(_DEFAULT_LAYER_1, TH_EXLM)
#   define TR_LPRN  LT(_DEFAULT_LAYER_1, TH_LPRN)
#   define TR_LCBR  LT(_DEFAULT_LAYER_1, TH_LCBR)
#   define TR_DQUO  LT(_DEFAULT_LAYER_1, TH_DQUO)
#   define TR_COMM  LT(_DEFAULT_LAYER_1, TH_COMM)
#   define TR_DOT   LT(_DEFAULT_LAYER_1, TH_DOT)
#   define TR_SCLN  LT(_DEFAULT_LAYER_1, TH_SCLN)
#else
//Double Taps
#   define TR_UNDS  KC_UNDS
#   define TR_LABK  KC_LABK
#   define TR_RABK  KC_RABK
#   define TR_SLSH  KC_SLSH
#   define TR_BSLS  KC_BSLS
#   define TR_HASH  KC_HASH
#   define TR_MINS  KC_MINS
//Double Taps with Spaces
#   define TR_PIPE  KC_PIPE
#   define TR_AMPR  KC_AMPR
#   define TR_EQL   KC_EQL
//Triple Tap
#   define TR_GRV   KC_GRV
//Custom
#   define TR_EXLM  KC_EXLM
#   define TR_LPRN  KC_LPRN
#   define TR_LCBR  KC_LCBR
#   define TR_DQUO  KC_DQUO
#   define TR_COMM  KC_COMM
#   define TR_DOT   KC_DOT
#   define TR_SCLN  KC_SCLN
#endif //TAPHOLD_ENABLE

//Tap Hold takes precedence over Home Row Mods when we have overlapping keys 
//there should be another key with that mod tap
#if defined(TAPHOLD_ENABLE)
#   define TR_QUOT  LT(_DEFAULT_LAYER_1, TH_QUOT)
#elif defined(HOMEROWMOD_ENABLE)
#   define TR_QUOT  LGUI_T(KC_QUOT)
#else
#   define TR_QUOT  KC_QUOT
#endif

//Tap Hold takes precedence over Tap Dance when we have overlapping keys 
//there should be another key with that mod tap
#if defined(TAPHOLD_ENABLE)
#   define TR_LBRC LT(_DEFAULT_LAYER_1, TH_LBRC)
#   define TR_RBRC KC_RBRC
#elif defined(TAP_DANCE_ENABLE)
#   define TR_LBRC TD_LBKT
#   define TR_RBRC TD_RBKT
#else
#   define TR_LBRC KC_LBRC
#   define TR_RBRC KC_RBRC
#endif //TAP_DANCE_ENABLE

#if defined(HOMEROWMOD_ENABLE)
//QWERTY Home Row Mods
#   define TR_A     LGUI_T(KC_A)
#   define TR_SA    LALT_T(KC_S)
#   define TR_D     LCTL_T(KC_D)
#   define TR_F     LSFT_T(KC_F)
#   define TR_J     LSFT_T(KC_J)
#   define TR_K     LCTL_T(KC_K)
#   define TR_L     LALT_T(KC_L)
//COLEMAKDH Home Row Mods 
#   define TR_R     LALT_T(KC_R)
#   define TR_SC    LCTL_T(KC_S)
#   define TR_T     LSFT_T(KC_T)
#   define TR_N     LSFT_T(KC_N)
#   define TR_E     LCTL_T(KC_E)
#   define TR_I     LALT_T(KC_I)
#   define TR_O     LGUI_T(KC_O)
#else
//QWERTY Home Row Mods
#   define TR_A     KC_A
#   define TR_SA    KC_S
#   define TR_D     KC_D
#   define TR_F     KC_F
#   define TR_J     KC_J
#   define TR_K     KC_K
#   define TR_L     KC_L
//Home Row Mods COLEMAKDH
#   define TR_R     KC_R
#   define TR_SC    KC_S
#   define TR_T     KC_T
#   define TR_N     KC_N
#   define TR_E     KC_E
#   define TR_I     KC_I
#   define TR_O     KC_O
#endif //HOMEROWMOD_ENABLE

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


Modeled code after Drashna's Wrappers.
Definitions inspired by Miryoku (https://github.com/manna-harbour/miryoku). 

I added comment maps to better visualize the map. I intended to only 
show the definition once so its less comments to change when I change
a mapping

I prefer to use KC_NO over KC_TRNS so I don't have accidental presses.
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
*   | Q    | W    | E    | R    | T    |    | Y    | U    | I    | O    | P    |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | A    | S    | D    | F    | G    |    | H    | J    | K    | L    | '    |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | MOUZ | X    | MOUC | V    | B    |    | N    | M    | ,    | .    | -    |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | MB1  |NUMBsp| Lsft |    | Spc  | NAV0 |      |
*                 `------+------+------'    `------+------+------'
*
*/
#   define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#   define _________________QWERTY_L2_________________        TR_A,    TR_SA,   TR_D,    TR_F,    KC_G
#   define _________________QWERTY_L3_________________        TR_MOUZ, KC_X,    TR_MOUC, KC_V,    KC_B
#   define          ________QWERTY_L4________                 _________BASE_L4_________

#   define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#   define _________________QWERTY_R2_________________        KC_H,    TR_J,    TR_K,    TR_L,    TR_QUOT
#   define _________________QWERTY_R3_________________        KC_N,    KC_M,    TR_COMM, TR_DOT,  TR_MINS
#   define          ________QWERTY_R4________                 _________BASE_R4_________

/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   | Q    | W    | F    | P    | B    |    | J    | L    | U    | Y    | '    |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | A    | R    | S    | T    | G    |    | M    | N    | E    | I    | O    |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | MOUZ | X    | MOUC | D    | V    |    | K    | H    | ,    | .    | -    |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | MB1  |NUMBsp| Lsft |    | Spc  | NAV0  |      |
*                 `------+------+------'    `------+------+------'
*/
#   define ________________COLEMAKDH_L1_______________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#   define ________________COLEMAKDH_L2_______________        TR_A,    TR_R,    TR_SC,   TR_T,    KC_G
#   define ________________COLEMAKDH_L3_______________        TR_MOUZ, KC_X,    TR_MOUC, KC_D,    KC_V
#   define          _______COLEMAKDH_L4______                 _________BASE_L4_________

#   define ________________COLEMAKDH_R1_______________        KC_J,    KC_L,    KC_U,    KC_Y,    TR_QUOT
#   define ________________COLEMAKDH_R2_______________        KC_M,    TR_N,    TR_E,    TR_I,    TR_O
#   define ________________COLEMAKDH_R3_______________        KC_K,    KC_H,    TR_COMM, TR_DOT,  TR_MINS
#   define          _______COLEMAKDH_R4______                 _________BASE_R4_________

/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  | Snip | File |      | `    |    | =    | 7    | 8    | 9    | +    |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Gui  | Alt  | Ctrl | Shft | -    |    | ;    | 4    | 5    | 6    | *    |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    | .    | 1    | 2    | 3    | /    |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |NUMBsp|      |    | Spc  | NAV0 |      |
*                 `------+------+------'    `------+------+------'
*
*/
#   define _________________NUMPAD_L1_________________        KC_ESC,  W_SNIP,  W_FILE,  ___x___, TR_GRV
#   define _________________NUMPAD_L2_________________        _____________GACS_MODS____________, KC_MINS
#   define _________________NUMPAD_L3_________________        _________________UCCPR_L___________________
#   define          ________NUMPAD_L4________                 ___x___, _______, ___x___

#   define _________________NUMPAD_R1_________________        KC_EQL,  KC_7,    KC_8,    KC_9,    KC_PLUS
#   define _________________NUMPAD_R2_________________        TR_SCLN, KC_4,    KC_5,    KC_6,    KC_ASTR
#   define _________________NUMPAD_R3_________________        KC_DOT,  KC_1,    KC_2,    KC_3,    KC_BSLS

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________NUMPAD_R4________                 KC_SPC,  _______
#else
#   define          ________NUMPAD_R4________                 KC_SPC,  _______, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

#   define __________________NUMROW_L_________________        KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#   define __________________NUMROW_R_________________        KC_6,    KC_7,    KC_8,    KC_9,    KC_0


/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   | %    | ^    | *    | +    | `    |    | =    | #    | @    | $    | "    |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | |    | {    | }    | !    | -    |    | ;    | ?    | [    | ]    | '    |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | &    | <    | >    | ,    | \    |    | /    | .    | (    | )    | _    |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 |      |NUMBsp|      |    |      | NAV0 |      |              
*                 `------+------+------'    `------+------+------'
*
*
* Need to use One shot shift to hit the following symbols
*   ~ 
*   : (can activate via tap hold as well)
* 
*/
#   define _________________SYMBOL_L1_________________        KC_PERC, KC_CIRC, KC_ASTR, KC_PLUS, TR_GRV
#   define _________________SYMBOL_L2_________________        TR_PIPE, TR_LCBR, KC_RCBR, TR_EXLM, TR_MINS
#   define _________________SYMBOL_L3_________________        TR_AMPR, TR_LABK, TR_RABK, KC_COMM, TR_BSLS
#   define          ________SYMBOL_L4________                 ___x___, _______, ___x___

#   define _________________SYMBOL_R1_________________        TR_EQL,  TR_HASH, KC_AT,   KC_DLR,  TR_DQUO
#   define _________________SYMBOL_R2_________________        TR_SCLN, KC_QUES, TR_LBRC, KC_RBRC, TR_QUOT
#   define _________________SYMBOL_R3_________________        TR_SLSH, KC_DOT,  TR_LPRN, KC_RPRN, TR_UNDS

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________SYMBOL_R4________                 ___x___, _______
#else
#   define          ________SYMBOL_R4________                 ___x___, _______, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5


/*
*
*   ,----------------------------------.    ,----------------------------------.
*   | Esc  | Home | Up   | End  | PgUp |    |DMRec1|DMPly1|NxtTab|DMPly2|DMRec2|
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      | Left | Down | Right| PgDn |    | Del  | Shft | Ctrl | Alt  | Gui  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Undo | Cut  | Copy | Pste | Redo |    | Ins  | Bksp |      |      | App  |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Tab  |NUMBsp| Ent  |    |      | NAV0 |      |
*                 `------+------+------'    `------+------+------'
*/
#   define ___________________NAV_L1__________________        KC_ESC,  KC_HOME, KC_UP,   KC_END,  KC_PGUP
#   define ___________________NAV_L2__________________        ___x___, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#   define ___________________NAV_L3__________________        _________________UCCPR_L___________________
#   define          __________NAV_L4_________                 KC_TAB,  _______, KC_ENT

#   define ___________________NAV_R1__________________        TR_DMR1, TR_DMP1, NXT_TAB, TR_DMP2, TR_DMR2
#   define ___________________NAV_R2__________________        KC_DEL,  _____________SCAG_MODS____________
#   define ___________________NAV_R3__________________        KC_INS,  KC_BSPC, ___x___, ___x___, KC_APP 

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          __________NAV_R4_________                 ___x___, _______
#else
#   define          __________NAV_R4_________                 ___x___, _______, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

/*
*   ,----------------------------------.    ,----------------------------------.
*   |ScrLck|  F7  |  F8  |  F9  | F10  |    |QWERTY|ClmkDH|Gaming|      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |PrnScr|  F4  |  F5  |  F6  | F11  |    | Caps | Shft | Ctrl | Alt  | Gui  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |PauBrk|  F1  |  F2  |  F3  | F12  |    | Hue+ | Sat+ | Vib+ | Spd+ | Boot |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Mute | Vol- | Vol+ |    |RGBTog|RGBMod|      |
*                 `------+------+------'    `------+------+------'
*/
#   define _________________FUNCPAD_L1________________        KC_SCRL, KC_F7,   KC_F8,   KC_F9,   KC_F10
#   define _________________FUNCPAD_L2________________        KC_PSCR, KC_F4,   KC_F5,   KC_F6,   KC_F11
#   define _________________FUNCPAD_L3________________        KC_PAUS, KC_F1,   KC_F2,   KC_F3,   KC_F12
#   define          ________FUNCPAD_L4_______                 KC_MUTE, KC_VOLD, KC_VOLU

#   define _________________CONFIG_R1_________________        QWERTY,  CLMAKDH, TR_GAME, _______, _______
#   define _________________CONFIG_R2_________________        KC_CAPS, _____________SCAG_MODS____________
#   define _________________CONFIG_R3_________________        TR_RHUI, TR_RSAI, TR_RVAI, TR_RSPI, QK_BOOT

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          ________CONFIG_R4________                 TR_RTOG, TR_RMOD
#else
#   define          ________CONFIG_R4________                 TR_RTOG, TR_RMOD, ___x___
#endif //KEYBOARD_bastardkb_charybdis_3x5

#   define _________________FUNCROW_L_________________        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#   define _________________FUNCROW_M_________________        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#   define              ____FUNCROW_R___                      KC_F11,  KC_F12

/*
*   ,----------------------------------.    ,----------------------------------.
*   |      | MB5  | MouU | MB4  | MwU  |    | sDPI | DPI  |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      | MouL | MouD | MouR | MwD  |    |      | Shft | Ctrl | Alt  | Gui  |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | MOU  |      | MOU  |DrgScr|Sniper|    |      | MB1  | MB2  | MB3  |      |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | MB1  | MB2  | MB3  |    | MB5  | MB4  |      |
*                 `------+------+------'    `------+------+------'
*/

#   define __________________MOUSE_L1_________________        ___x___, TR_BTN5, TR_MOUU, TR_BTN4, TR_MWHU
#   define __________________MOUSE_L2_________________        ___x___, TR_MOUL, TR_MOUD, TR_MOUR, TR_MWHD
#   define __________________MOUSE_L3_________________        _______, ___x___, _______, TR_DRGS, TR_SNIP
#   define          _________MOUSE_L4________                 KC_BTN1, KC_BTN2,  KC_BTN3

#   define __________________MOUSE_R1_________________        TR_SDPI, TR_PDPI, ___x___, ___x___, ___x___
#   define __________________MOUSE_R2_________________        ___x___, _____________SCAG_MODS____________
#   define __________________MOUSE_R3_________________        ___x___, KC_BTN1, KC_BTN2, KC_BTN3, ___x___

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#   define          _________MOUSE_R4________                 KC_BTN5, KC_BTN4
#else
#   define          _________MOUSE_R4________                 KC_BTN5, KC_BTN4, ___x___
#endif

/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   | Tab  | Q    | W    | E    | R    |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GNUM | A    | S    | D    | F    |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | Z    | X    | C    | V    | B    |    |      |      |      |      |      |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Ctrl | Spc  | Shft |    |      | Nav  |      |
*                 `------+------+------'    `------+------+------'
*/
#   define _______________GAMING_BASE_L1______________        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R
#   define _______________GAMING_BASE_L2______________        GAMENUM, KC_A,    KC_S,    KC_D,    KC_F
#   define _______________GAMING_BASE_L3______________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#   define          ______GAMING_BASE_L4_____                 KC_LCTL, KC_SPC,  KC_LSFT

#   define _______________GAMING_BASE_R1______________        ___x___, ___x___, ___x___, _______, _______
#   define _______________GAMING_BASE_R2______________        __________________NONE_5___________________
#   define _______________GAMING_BASE_R3______________        __________________NONE_5___________________

# if defined(KEYBOARD_bastardkb_charybdis_3x5) 
#   define          ______GAMING_BASE_R4_____                 ___x___, NAVGTIN
# else
#   define          ______GAMING_BASE_R4_____                 ___x___, NAVGTIN, ___x___
# endif //KEYBOARD_bastardkb_charybdis_3x5


/*
* For 3x5 configuration
*
*   ,----------------------------------.    ,----------------------------------.
*   |      | Esc  | ~    | G    | T    |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   | GNUM | 1    | 2    | 3    | 4    |    |      |      |      |      |      |
*   +------+------+------+------+------|    +------+------+------+------+------+
*   |      | 5    | 6    | 7    | 8    |    |      |      |      |      |      |
*   `------+------+------+------+------+    +------+------+------+------+------'
*                 | Alt  |      | Ent  |    |      |      |      |
*                 `------+------+------'    `------+------+------'
*/
#   define _______________GAMING_NUM_L1_______________        ___x___, KC_ESC,  KC_TILD, KC_G,    KC_T
#   define _______________GAMING_NUM_L2_______________        _______, KC_1,    KC_2,    KC_3,    KC_4
#   define _______________GAMING_NUM_L3_______________        ___x___, KC_5,    KC_6,    KC_7,    KC_8
#   define          ______GAMING_NUM_L4______                 KC_LALT, ___x___, KC_ENT


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