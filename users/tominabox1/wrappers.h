#pragma once
#include "tominabox1.h"
/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_arrow_wrapper(...) 	         LAYOUT_arrow(__VA_ARGS__)

/*
  _____  _                 _
 |  __ \(_)               | |
 | |  | |_ _ __ ___  _ __ | | ___
 | |  | | | '_ ` _ \| '_ \| |/ _ \
 | |__| | | | | | | | |_) | |  __/
 |_____/|_|_| |_| |_| .__/|_|\___|
                    | |
                    |_|
*/
// Dimple Base layer
#define __________________DIMPLE1__________________       QK_GESC, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC
#define __________________DIMPLE2__________________       LCTL_T(KC_TAB), KC_A,    KC_R,    KC_S,    KC_T,    KC_D, KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT
#define __________________DIMPLE3L_________________       KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#define __________________DIMPLE3R_________________       KC_K,    KC_M,    KC_COMM, KC_UP,  LT(_FKEY,KC_DOT)
#define __________________DIMPLE4__________________       KC_LCTL, KC_LGUI, KC_LALT, KC_ENT_LOW,  KC_SPC_RSE,  KC_LEFT, KC_DOWN, KC_RGHT

// Dimple Symbol Layer
#define _________________LOWER_1___________________       KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC
#define _________________LOWER_2___________________       KC_DEL,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE
#define _________________LOWER_3___________________       KC_CAPS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_PGUP, KC_QUES
#define _________________LOWER_4___________________       LCA(KC_DEL),   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_END

// Dimple Number layer
#define ___________________RAISE1__________________       KC_TILD, KC_EXLM, TD(KC_EMAIL),   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL
#define ___________________RAISE2__________________       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS
#define ___________________RAISE3__________________       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_DOT,   KC_SLSH
#define ___________________RAISE4__________________       KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS,   KC_NO,   KC_NO

// Dimple F-key layer
#define ___________________FKEY1___________________       KC_PASTA, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_NO
#define ___________________FKEY2___________________       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F11,   KC_F12,   KC_NO
#define ___________________FKEY3___________________       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________FKEY4___________________       KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_TRNS,   KC_NO, KC_NO

// Dimple Adjust layer
#define ___________________ADJST1__________________       RESET,RGBRST,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________ADJST2__________________       RGB_M_P,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________ADJST3__________________       RGB_MOD,   RGB_HUI,   RGB_HUD,   RGB_M_SN,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________ADJST4__________________       RGB_VAD, RGB_TOG, RGB_VAI, KC_NO,   KC_NO,   KC_TRNS,   KC_NO,   KC_NO

/*
__  __ _       _
|  \/  (_)     (_)
| \  / |_ _ __  ___   ____ _ _ __
| |\/| | | '_ \| \ \ / / _` | '_ \
| |  | | | | | | |\ V / (_| | | | |
|_|  |_|_|_| |_|_| \_/ \__,_|_| |_|
*/


// Minivan Base Layer
#define __________________MINIVAN1_________________       __________________DIMPLE1__________________
#define __________________MINIVAN2_________________       __________________DIMPLE2__________________
#define __________________MINIVAN3_________________       __________________DIMPLE3L_________________, __________________DIMPLE3R_________________, KC_RSFT
#define __________________MINIVAN4_________________       KC_LCTL, KC_LGUI, KC_LALT, KC_ENT_LOW,  KC_SPC_RSE,  KC_LEFT, KC_DOWN, KC_RGHT, MO(_FKEY)

/* Minivan Symbol Layer
#define _________________LOWER_1___________________
#define _________________LOWER_2___________________        */
#define __________________MININUM3_________________       _________________LOWER_3___________________, KC_SLSH
#define __________________MININUM4_________________       _________________LOWER_4___________________, KC_END

/* Minvian Number Layer
#define ___________________RAISE1__________________
#define ___________________RAISE2__________________       */
#define ___________________RVAN_3__________________       ___________________RAISE3__________________, KC_NO
#define ___________________RVAN_4__________________       ___________________RAISE4__________________, KC_NO

/* Minvian F-key layer
#define ___________________FKEY1___________________
#define ___________________FKEY2___________________       */
#define ___________________FVAN_3__________________       ___________________FKEY3___________________, KC_NO
#define ___________________FVAN_4__________________       ___________________FKEY4___________________, KC_TRNS

/* Minivan Adjust Layer
#define ___________________ADJST1__________________
#define ___________________ADJST2__________________       */
#define ___________________ADJVAN3_________________       ___________________ADJST3__________________, KC_NO
#define ___________________ADJVAN4_________________       ___________________ADJST4__________________, KC_TRNS

/*
  _____ _____  _  ______  _____
 / ____|  __ \| |/ /  _ \|  __ \
| |    | |__) | ' /| |_) | |  | |
| |    |  _  /|  < |  _ <| |  | |
| |____| | \ \| . \| |_) | |__| |
 \_____|_|  \_\_|\_\____/|_____/
*/

// CRKBD Base Layer
#define ___________________CRKBD1__________________       __________________DIMPLE1__________________
#define ___________________CRKBD2__________________       __________________DIMPLE2__________________
#define ___________________CRKBD3__________________       __________________DIMPLE3L_________________, KC_K, KC_M,KC_COMM,   KC_DOT,  KC_SLSH,  KC_BBB
#define ___________________CRKBD4__________________       KC_LGUI, KC_LALT,KC_ENT_LOW,  KC_SPC_RSE, KC_ARROW, KC_FKEY

/* CRKBD Number layer
#define ___________________RAISE1__________________
#define ___________________RAISE1__________________        */
#define ___________________CRKBD_RAISE3____________       ___________________RVAN_3__________________
#define ___________________CRKBD_RAISE4____________       ___________________CRKBD4__________________

/* CRKBD Symbol Layer
#define _________________LOWER_1___________________
#define _________________LOWER_2___________________       */
#define ___________________CRKBD_LOW3______________       __________________MININUM3_________________
#define ___________________CRKBD_LOW4______________       ___________________CRKBD4__________________

/* CRKBD F-key layer
#define ___________________FKEY1___________________
#define ___________________FKEY2___________________       */
#define ___________________CRKBD_FKEY3_____________       ___________________FVAN_3__________________
#define ___________________CRKBD_FKEY4_____________       ___________________CRKBD4__________________

/* CRKBD adjust layer
#define ___________________ADJST1__________________      */
#define ___________________CRKBD_ADJST2____________       KC_LTOG,KC_LHUI,KC_LSAI,KC_LVAI,KC_NO,KC_NO,KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
#define ___________________CRKBD_ADJST3____________       KC_LMOD,  KC_LHUD,  KC_LSAD,  KC_LVAD, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
#define ___________________CRKBD_ADJST4____________       ___________________CRKBD4__________________

// CRKBD arrow layer
#define ___________________ARROW1__________________       KC_NO, KC_NO,    KC_UP, KC_NO, KC_NO, KC_NO, KC_NO,  KC_PGDN,    KC_UP,  KC_PGUP, KC_NO, KC_NO
#define ___________________ARROW2__________________       KC_NO,  KC_LEFT,  KC_DOWN, KC_RIGHT, KC_NO, KC_NO,KC_NO,  KC_LEFT,  KC_DOWN,  KC_RGHT, KC_NO, KC_NO
#define ___________________ARROW3__________________       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
#define ___________________ARROW4__________________       ___________________CRKBD4__________________

// clang-format on
