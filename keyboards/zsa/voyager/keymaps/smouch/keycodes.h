#pragma once

#include QMK_KEYBOARD_H

enum layer_names {
    _DEF,
    _NUM,
    _SYM,
    _NAV,
    _SNTH,
};

enum custom_keycodes {
    SS_Qu,
    SS_Th,
    SS_Ch,
    SS_Sh,
    SS_Gh,
    SS_Wh,
    SS_Ph,
};

/*  KEY POSITION Names
    LN5 LN4 LN3 LN2 LN1 LN0     RN0 RN1 RN2 RN3 RN4 RN5
    LT5 LT4 LT3 LT2 LT1 LT0     RT0 RT1 RT2 RT3 RT4 RT5
    LM5 LM4 LM3 LM2 LM1 LM0     RM0 RM1 RM2 RM3 RM4 RM5
    LB5 LB4 LB3 LB2 LB1 LB0     RB0 RB1 RB2 RB3 RB4 RB5
                    LH1 LH0     RH0 RH1
*/

/*  Base (alpha) Layer Hands Down Vibranuim-F
            Building for ZSA Voyager
    ⎋           ⇥        tg          tg  (   ⌦    )   vol↓↑
    `   x   w   m⌃   g   j           +=  .:  /⌃   "!  '? \
    z   s   c⌥  n⌘   t⇧  k           ,;  a⇧  e⌘   i⌥  h  q
        f   p   l    d   v      	 -   u   o    y   b
                         r   ⌫   ⏎   ␣
*/

// Num row
#define LN5 KC_ESC
#define LN4 KC_NO
#define LN3 KC_NO
#define LN2 KC_TAB
#define LN1 KC_NO
#define LN0 TO(_SNTH)

#define RN0 TG(_NUM)
#define RN1 KC_LPRN
#define RN2 KC_DEL
#define RN3 KC_RPRN
#define RN4 KC_VOLD
#define RN5 KC_VOLU

// top row
#define LT5 KC_GRV
#define LT4 KC_X
#define LT3 KC_W
#define LT2 LCTL_T(KC_M)
#define LT1 KC_G
#define LT0 KC_J

#define RT0 KC_PLUS
#define RT1 KC_DOT
#define RT2 RCTL_T(KC_SLSH)
#define RT3 KC_DQUO
#define RT4 KC_QUOT
#define RT5 KC_BSLS

// middle row
#define LM5 KC_Z
#define LM4 LT(_SYM, KC_S)
#define LM3 LALT_T(KC_C)
#define LM2 LGUI_T(KC_N)
#define LM1 LSFT_T(KC_T)
#define LM0 KC_K

#define RM0 KC_COMM
#define RM1 RSFT_T(KC_A)
#define RM2 RGUI_T(KC_E)
#define RM3 RALT_T(KC_I)
#define RM4 LT(_SYM, KC_H)
#define RM5 KC_Q

// bottom row
#define LB5 KC_NO
#define LB4 KC_F
#define LB3 KC_P
#define LB2 KC_L
#define LB1 KC_D
#define LB0 KC_V

#define RB0 KC_MINS
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 KC_B
#define RB5 KC_NO

// thumb row
#define LH1 LT(_NAV, KC_R)
#define LH0 KC_BSPC

#define RH0 KC_ENT
#define RH1 LT(_NUM, KC_SPC)

#define ___x___ KC_NO  // visual aid to null keys

// layer momentaries
// #define OS_SYM OSL(_SYM)

// layer tap
// #define SPC_NUM LT(_NUM, KC_SPC)
// #define R_NAV LT(_NAV, KC_R)
// #define ENT_SYM LT(_SYM, KC_ENT)
// #define MY_PRNS LT(0, KC_1)

// One Shots
// #define OSMSFT OSM(MOD_LSFT)
// #define OSMCMD OSM(MOD_LGUI)
// #define OSMOPT OSM(MOD_LALT)
// #define OSMCTL OSM(MOD_LCTL)
