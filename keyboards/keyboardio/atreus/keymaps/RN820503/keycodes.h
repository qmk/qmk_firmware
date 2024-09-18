#pragma once
#include QMK_KEYBOARD_H

enum layer_names {
    _DEF,
    _NUM,
    _SYM,
    _NAV,
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

    LT4 LT3 LT2 LT1 LT0           RT0 RT1 RT2 RT3 RT4
    LM4 LM3 LM2 LM1 LM0           RM0 RM1 RM2 RM3 RM4
    LB4 LB3 LB2 LB1 LB0 LB00 RB00 RB0 RB1 RB2 RB3 RB4
    LH4 LH3 LH2 LH1 LH0 LH00 RH00 RH0 RH1 RH2 RH3 RH4
*/

/*  Base (alpha) Layer Hands Down Vibranuim-F
            Building for Atreus44

    x   w   m⌃   g   j           +=  .:  /⌃   "!  '?
    s   c⌥  n⌘   t⇧  k           ,;  a⇧  e⌘   i⌥  h
    f   p   l    d   v	 `   \	 -   u   o    y   b
    ←   →  app   ⇥   r   ⌫   ⏎   ␣   ⎋  num   ↑   ↓
*/

// top row
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

// middle row
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

// bottom row
#define LB4 KC_F
#define LB3 KC_P
#define LB2 KC_L
#define LB1 KC_D
#define LB0 KC_V
#define LB00 KC_GRV

#define RB00 KC_BSLS
#define RB0 KC_MINS
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 KC_B

// thumb row
#define LH4 KC_LEFT
#define LH3 KC_RGHT
#define LH2 G(KC_TAB)
#define LH1 KC_TAB
#define LH0 LT(_NAV, KC_R)
#define LH00 KC_BSPC

#define RH00 KC_ENT
#define RH0 LT(_NUM, KC_SPC)
#define RH1 KC_ESC
#define RH2 TG(_NUM)
#define RH3 KC_UP
#define RH4 KC_DOWN

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
