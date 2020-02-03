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
#define LAYOUT_arrow_wrapper(...) 	         LAYOUT_arrow_command(__VA_ARGS__)
#define LAYOUT_catalyst(...)                 LAYOUT_arrow(__VA_ARGS__)

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
#define __________________BASE1____________________       KC_ESC, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC
#define __________________BASE2____________________       LCTL_T(KC_TAB), KC_A,    KC_R,    KC_S,    KC_T,    KC_D, KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT
#define __________________BASE3L___________________       KC_LSFT, LT(_FKEY,KC_Z),    KC_X,    KC_C,    KC_V,    KC_B
#define __________________BASE3R___________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  RSFT_T(KC_QUES)
#define __________________BASE4____________________       KC_LCTL, KC_LGUI, KC_LALT, LT(_LOWER, KC_SPC),  LT(_LOWER, KC_SPC),  MO(_RAISE), MO(_FKEY), KC_NO

// Dimple Num/Symbol Layer
#define _________________LOWER_1___________________       KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC
#define _________________LOWER_2___________________       KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_MINS, KC_PIPE
#define _________________LOWER_3___________________       KC_DEL,KC_NO, KC_LCBR, KC_LBRC, KC_LPRN, KC_UNDS, KC_RPRN, KC_RBRC, KC_RCBR, KC_DOT, KC_SLSH
#define _________________LOWER_4___________________       LCA(KC_DEL),   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_ENT, KC_PGDN, KC_END

// Dimple Nav layer
#define ___________________NAV1____________________       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_PGDN,   KC_UP,     KC_PGUP,    KC_NO, KC_NO
#define ___________________NAV2____________________       KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_DOWN,  KC_RIGHT, KC_RBRC, KC_BSLS
#define ___________________NAV3____________________       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_DOT,   KC_SLSH
#define ___________________NAV4____________________       SPONGEBOB, AESTHETIC, KC_VOLU, KC_ENT, KC_TRNS, KC_TRNS,   KC_NO,   KC_NO

// Dimple F-key layer
#define ___________________FKEY1___________________       KC_PASTA, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_NO
#define ___________________FKEY2___________________       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F11,   KC_F12,   KC_TRNS
#define ___________________FKEY3___________________       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________FKEY4___________________       KC_NO, KC_NO, KC_NO, KC_NO,   KC_TRNS,   KC_TRNS,   KC_NO, KC_NO

// Dimple Adjust layer
#define ___________________ADJST1__________________       RESET,MAGIC_UNSWAP_LALT_LGUI,   MAGIC_SWAP_LALT_LGUI,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TG(_GAMER)
#define ___________________ADJST2__________________       RGB_M_P,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________ADJST3__________________       RGB_MOD,   RGB_HUI,   RGB_HUD,   RGB_M_SN,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________ADJST4__________________       RGB_VAD, RGB_TOG, RGB_VAI, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NO,   KC_NO

 // Dimple gaming Layer
#define ___________________GAMER1__________________       TD(TD_TAB_ESC), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, TO(_BASE)
#define ___________________GAMER2__________________       KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_NO, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO
#define ___________________GAMER3__________________       KC_LSFT, KC_1,    KC_2,    KC_4,    KC_5,    KC_5, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
#define ___________________GAMER4__________________       KC_GRV, KC_ESC, KC_3, KC_SPC,  KC_SPC_RSE,  KC_LEFT, KC_DOWN, KC_LGUI

/*
__  __ _       _
|  \/  (_)     (_)
| \  / |_ _ __  ___   ____ _ _ __
| |\/| | | '_ \| \ \ / / _` | '_ \
| |  | | | | | | |\ V / (_| | | | |
|_|  |_|_|_| |_|_| \_/ \__,_|_| |_|
*/


// Minivan Base Layer
#define __________________MINIVAN1_________________       __________________BASE1____________________
#define __________________MINIVAN2_________________       __________________BASE2____________________
#define __________________MINIVAN3_________________       __________________BASE3L___________________, __________________BASE3R___________________, KC_RSFT
#define __________________MINIVAN4_________________       KC_DEL, KC_LCTL, KC_LGUI, KC_LALT, LT(_LOWER, KC_SPC),  LT(_LOWER, KC_SPC),  LT(_RAISE, KC_ENT), MO(_FKEY), KC_NO, MO(_FKEY)

/* Minivan Num/Symbol Layer
#define _________________LOWER_1___________________
#define _________________LOWER_2___________________        */
#define __________________MININUM3_________________       _________________LOWER_3___________________, KC_SLSH
#define __________________MININUM4_________________       KC_DEL, _________________LOWER_4___________________, KC_END

/* Minvian Nav Layer
#define ___________________NAV1____________________
#define ___________________NAV2____________________       */
#define ___________________RVAN_3__________________       ___________________NAV3____________________, KC_NO
#define ___________________RVAN_4__________________       KC_NO, ___________________NAV4____________________, KC_NO

/* Minvian F-key layer
#define ___________________FKEY1___________________
#define ___________________FKEY2___________________       */
#define ___________________FVAN_3__________________       ___________________FKEY3___________________, KC_NO
#define ___________________FVAN_4__________________       KC_DEL, ___________________FKEY4___________________, KC_TRNS

/* Minivan Adjust Layer
#define ___________________ADJST1__________________
#define ___________________ADJST2__________________       */
#define ___________________ADJVAN3_________________       ___________________ADJST3__________________, KC_NO
#define ___________________ADJVAN4_________________       KC_DEL, ___________________ADJST4__________________, KC_TRNS

/*
  _____ _____  _  ______  _____
 / ____|  __ \| |/ /  _ \|  __ \
| |    | |__) | ' /| |_) | |  | |
| |    |  _  /|  < |  _ <| |  | |
| |____| | \ \| . \| |_) | |__| |
 \_____|_|  \_\_|\_\____/|_____/
*/

// CRKBD Base Layer
#define ___________________CRKBD1__________________       __________________BASE1____________________
#define ___________________CRKBD2__________________       __________________BASE2____________________
#define ___________________CRKBD3__________________       __________________BASE3L___________________, KC_K, KC_M,KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT
#define ___________________CRKBD4__________________       KC_LGUI, KC_LALT,LT(_LOWER, KC_SPC),  LT(_LOWER, KC_SPC), MO(_ARROW), KC_FKEY

/* CRKBD Nav layer
#define ___________________NAV1____________________
#define ___________________NAV2____________________        */
#define ___________________CRKBD_RAISE3____________       ___________________RVAN_3__________________
#define ___________________CRKBD_RAISE4____________       SPONGEBOB, KC_LALT,LT(_LOWER, KC_SPC),  LT(_LOWER, KC_SPC), MO(_ARROW), KC_FKEY

/* CRKBD Number/Symbol Layer
#define _________________LOWER_1___________________
#define _________________LOWER_2___________________       */
#define ___________________CRKBD_LOW3______________       __________________MININUM3_________________
#define ___________________CRKBD_LOW4______________       SPONGEBOB, AESTHETIC,LT(_RAISE, KC_SPC),  LT(_LOWER, KC_SPC), MO(_ARROW), KC_FKEY

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
