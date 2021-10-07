/* Copyright 2021 @waffle#0007
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "waffle.h"
#define LAYOUT_waffle(...)       LAYOUT(__VA_ARGS__)
#define LAYOUT_waffle_3x6(...)   LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_waffle_3x5(...)   LAYOUT_split_3x5_3(__VA_ARGS__)
#define LAYOUT_waffle_all(...)   LAYOUT_all(__VA_ARGS__)
#define LAYOUT_waffle_yoink(...) LAYOUT_split_bar(__VA_ARGS__)
#define LAYOUT_waffle_qaz(...)   LAYOUT_split_space(__VA_ARGS__)
#define LAYOUT_waffle_rev34(...) LAYOUT_reviung34(__VA_ARGS__)

/*
 ________  ________  ___  __    ________  ________     
|\   ____\|\   __  \|\  \|\  \ |\   __  \|\   ___ \    
\ \  \___|\ \  \|\  \ \  \/  /|\ \  \|\ /\ \  \_|\ \   
 \ \  \    \ \   _  _\ \   ___  \ \   __  \ \  \ \\ \  
  \ \  \____\ \  \\  \\ \  \\ \  \ \  \|\  \ \  \_\\ \ 
   \ \_______\ \__\\ _\\ \__\\ \__\ \_______\ \_______\
    \|_______|\|__|\|__|\|__| \|__|\|_______|\|_______|
*/

#define ________________CRKBDQWERTY1_______________ STARX,   ALTQ, KC_W, KC_E, KC_R, KC_T,          KC_Y, KC_U, KC_I,    KC_O,   ALTP,   ROFL,
#define ________________CRKBDQWERTY2_______________ QMKTD,   SFA,  KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K,    KC_L,   SFCLN,  RWORD,
#define ________________CRKBDQWERTY3_______________ CP_PSTE, CTLZ, KC_X, KC_C, KC_V, KC_B,          KC_N, KC_M, KC_COMM, KC_DOT, CTLSLH, ADJUST,
#define ________________CRKBDQWERTY4_______________                     MSLGTD, LOWER, KC_SPC, KC_BSPC, RSEBSP, GCPTD

#define ________________CRKBDLOWER1________________ HAP,    ALT1,   KC_2,   KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    ALT0,    MAKE,
#define ________________CRKBDLOWER2________________ DOCSTD, SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,   TABLE1,
#define ________________CRKBDLOWER3________________ LOCK,   CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL, TABLE2,
#define ________________CRKBDLOWER4________________                              KC_LGUI, KC_TRNS, KC_SPC, KC_VOLU, KC_MS_U, KC_PGUP

#define ________________CRKBDRAISE1________________ KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
#define ________________CRKBDRAISE2________________ KC_TRNS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
#define ________________CRKBDRAISE3________________ KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
#define ________________CRKBDRAISE4________________                              KC_PGDN, KC_MS_D, KC_VOLD, KC_BSPC, KC_TRNS, KC_RALT

#define _______________CRKBDADJUST1________________ RGB_TOG,  RGB_M_P, RGB_M_G,  RGB_HUD, RGB_HUI, RGB_SPI,         CK_TOGG, CK_RST,  BALL_WHT, BALL_DEC, BALL_HUI, RESET,
#define _______________CRKBDADJUST2________________ RGB_MOD,  RGB_M_B, RGB_M_TW, RGB_SAD, RGB_SAI, RGB_SPD,         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
#define _______________CRKBDADJUST3________________ RGB_RMOD, RGB_M_R, RGB_M_SW, RGB_VAD, RGB_VAI, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
#define _______________CRKBDADJUST4________________                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

/*
███╗   ███╗██╗ ██████╗██████╗  ██████╗ ██████╗  ██████╗ ██╗  ██╗
████╗ ████║██║██╔════╝██╔══██╗██╔═══██╗██╔══██╗██╔═══██╗╚██╗██╔╝
██╔████╔██║██║██║     ██████╔╝██║   ██║██║  ██║██║   ██║ ╚███╔╝
██║╚██╔╝██║██║██║     ██╔══██╗██║   ██║██║  ██║██║   ██║ ██╔██╗
██║ ╚═╝ ██║██║╚██████╗██║  ██║╚██████╔╝██████╔╝╚██████╔╝██╔╝ ██╗
╚═╝     ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝
*/

#define ________________MDOXQWERTY1________________ ALTQ, KC_W, KC_E, KC_R, KC_T,       KC_Y, KC_U, KC_I,    KC_O,   ALTP,
#define ________________MDOXQWERTY2________________ SFA,  KC_S, KC_D, KC_F, KC_G,       KC_H, KC_J, KC_K,    KC_L,   SFCLN,
#define ________________MDOXQWERTY3________________ CTLZ, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, CTLSLH,
#define ________________MDOXQWERTY4________________          LOWER, KC_SPC, KC_MS_L, KC_MS_R, KC_BSPC, RAISE

#define ________________MDOXLOWER1________________ ALT1,   KC_2,   KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    ALT0,
#define ________________MDOXLOWER2________________ SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,
#define ________________MDOXLOWER3________________ CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL,
#define ________________MDOXLOWER4________________                     KC_TRNS, KC_SPC, KC_LGUI, KC_PGUP, KC_VOLU, KC_MS_U

#define ________________MDOXRAISE1________________ KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,         RGB_HUI, RGB_M_G,  RGB_M_P, RGB_MOD, RGB_TOG,
#define ________________MDOXRAISE2________________ KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,         RGB_HUD, RGB_M_SW, RGB_M_R, RGB_SAD, RGB_SAI,
#define ________________MDOXRAISE3________________ QMKTD,   DOCSTD,  ROFL,    KC_TRNS, ALT_TAB,         KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,
#define ________________MDOXRAISE4________________                       KC_MS_D, KC_VOLD, KC_PGDN, KC_RALT, KC_BSPC, KC_TRNS

/*
              _       _
  _   _  ___ (_)_ __ | | __
 | | | |/ _ \| | '_ \| |/ /
 | |_| | (_) | | | | |   <
  \__, |\___/|_|_| |_|_|\_\
  |___/
*/

#define ______________YOINKQWERTY1________________ QMKTD, ALTQ, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, ALTP, ROFL,        KC_MPLY
#define ______________YOINKQWERTY2________________ ALT_TAB, SFA, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,  KC_K,  KC_L, SFCLN,          KC_MNXT
#define ______________YOINKQWERTY3________________ CP_PSTE,  CTLZ, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, CTLDOT,   KC_UP,   KC_MPRV
#define ______________YOINKQWERTY4________________ KC_LCTL, KC_LALT, KC_LGUI, LWRSPC, RSEBSP, CLIPST, KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT

#define _______________YOINKLOWER1________________ DOCSTD, ALT1, KC_2,   KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    ALT0, STARX,       KC_NO
#define _______________YOINKLOWER2________________ LOCK,    SFEXM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,            KC_NO
#define _______________YOINKLOWER3________________ KC_TRNS,  CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV, KC_LEFT, KC_DOWN, KC_UP, CTLRGHT,        RGB_M_P,  KC_NO
#define _______________YOINKLOWER4________________ KC_LCTL, KC_LALT, KC_LGUI,   KC_TRNS,          KC_SLSH,          CLIPST, KC_RCTL,  RGB_RMOD, RGB_M_SN, RGB_MOD

#define _______________YOINKRAISE1________________ UC_M_LN, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, ARWUP,       RESET
#define _______________YOINKRAISE2________________ UC_M_MA,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            MAKE
#define _______________YOINKRAISE3________________ KC_F1,       KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_F7, KC_F8, KC_F9, KC_F10,        RGB_VAI, EEP_RST
#define _______________YOINKRAISE4________________ KC_LCTL, KC_LALT, KC_LGUI,   KC_SCLN,            KC_TRNS,                 CLIPST, KC_RCTL,   KC_TRNS, RGB_VAD, KC_TRNS

/*
8888888b.
888   Y88b
888    888
888   d88P  .d88b.  88888b.d88b.   .d88b.   .d88b.
8888888P"  d88""88b 888 "888 "88b d8P  Y8b d88""88b
888 T88b   888  888 888  888  888 88888888 888  888
888  T88b  Y88..88P 888  888  888 Y8b.     Y88..88P
888   T88b  "Y88P"  888  888  888  "Y8888   "Y88P"
*/

#define ______________ROMEOQWERTY1________________ KC_TRNS,      ALTQ,  KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, ALTP, KC_VOLU,
#define ______________ROMEOQWERTY2________________ QMKTD,          SFA,  KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    SFCLN,
#define ______________ROMEOQWERTY3________________ CP_PSTE, KC_MPLY, CTLZ, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, CTLDOT, KC_RCTL,
#define ______________ROMEOQWERTY4________________ KC_LALT,  KC_TRNS,  KC_LGUI,  LWRSPC,  KC_LGUI,  RSEBSP,  CLIPST,  KC_TRNS,  KC_VOLD

#define ______________ROMEOLOWER1_________________ DOCSTD,       ALT1, KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    ALT0, KC_TRNS ,
#define ______________ROMEOLOWER2_________________ KC_TRNS,       SFEXM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,
#define ______________ROMEOLOWER3_________________ LOCK, KC_TRNS,  CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV, KC_LEFT, KC_DOWN, KC_UP, CTLRGHT, KC_LCTL,
#define ______________ROMEOLOWER4_________________ KC_LALT, KC_TRNS, KC_LGUI, KC_TRNS, KC_LGUI, KC_SLSH, KC_RGUI, KC_TRNS, KC_RALT

#define ______________ROMEORAISE1_________________ KC_MNXT,        KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,  KC_BSLS,  SHRUG,  TABLE1, TABLE2,   ARWUP, STARX, ROFL,
#define ______________ROMEORAISE2_________________ KC_MPRV, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    RESET,
#define ______________ROMEORAISE3_________________ KC_TRNS, KC_TRNS,   KC_F1,  KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F9, KC_F10,
#define ______________ROMEORAISE4_________________ KC_LALT,    KC_TRNS,    KC_LGUI,    KC_SCLN,    KC_SPC,    KC_TRNS,    KC_RGUI,    KC_TRNS,    KC_RALT

/*
         _             _             _
        /\ \          / /\         /\ \
       /  \ \        / /  \       /  \ \
      / /\ \ \      / / /\ \   __/ /\ \ \
     / / /\ \ \    / / /\ \ \ /___/ /\ \ \
    / / /  \ \_\  / / /  \ \ \\___\/ / / /
   / / / _ / / / / / /___/ /\ \     / / /
  / / / /\ \/ / / / /_____/ /\ \   / / /    _
 / / /__\ \ \/ / /_________/\ \ \  \ \ \__/\_\
/ / /____\ \ \/ / /_       __\ \_\  \ \___\/ /
\/________\_\/\_\___\     /____/_/   \/___/_/
*/

#define _______________QAZQWERTY1_________________ ALTQ, KC_W,  KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,  KC_O, ALTP,
#define _______________QAZQWERTY2_________________ SFA,   KC_S,  KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,   KC_L, SFCLN,
#define _______________QAZQWERTY3_________________ CTLZ,   KC_X,  KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,  CTLDOT,
#define _______________QAZQWERTY4_________________ KC_VOLU, KC_TRNS, KC_LGUI, LWRSPC, RSEBSP, CLIPST, KC_TRNS, KC_VOLD

#define ________________QAZLOWER1_________________ ALT1, KC_2,  KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     ALT0,
#define ________________QAZLOWER2_________________ SFEXM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,
#define ________________QAZLOWER3_________________ CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV, KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT,
#define ________________QAZLOWER4_________________ KC_MPRV,   KC_TRNS,   KC_LGUI,   KC_TRNS,   KC_SLSH,   CLIPST,   KC_TRNS,   KC_MNXT

#define ________________QAZRAISE1_________________ KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI,  RGB_TOG,
#define ________________QAZRAISE2_________________ KC_UNDS,  KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, RGB_M_SW, RGB_VAD, RGB_VAI, RGB_RMOD, RGB_RMOD,
#define ________________QAZRAISE3_________________ QMKTD,      DOCSTD, ROFL,    KC_F1,  KC_F2,   KC_F3,    KC_F4,    KC_F5,  KC_F6,
#define ________________QAZRAISE4_________________ KC_TRNS,    KC_TRNS,    KC_LGUI,    KC_SCLN,    KC_TRNS,    CLIPST,    KC_TRNS,    KC_TRNS

/*
 ______     ______     __   __   __     __  __     __   __     ______    
/\  == \   /\  ___\   /\ \ / /  /\ \   /\ \/\ \   /\ "-.\ \   /\  ___\   
\ \  __<   \ \  __\   \ \ \'/   \ \ \  \ \ \_\ \  \ \ \-.  \  \ \ \__ \  
 \ \_\ \_\  \ \_____\  \ \__|    \ \_\  \ \_____\  \ \_\\"\_\  \ \_____\ 
  \/_/ /_/   \/_____/   \/_/      \/_/   \/_____/   \/_/ \/_/   \/_____/ 
*/

#define _______________REV34QWERTY1_______________ ALTQ, KC_W, KC_E, KC_R, KC_T,     KC_Y, KC_U, KC_I,    KC_O,   KC_P,
#define _______________REV34QWERTY2_______________ SFA,  KC_S, KC_D, KC_F, KC_G,     KC_H, KC_J, KC_K,    KC_L,   SFCLN,
#define _______________REV34QWERTY3_______________ CTLZ, KC_X, KC_C, KC_V, KC_B,     KC_N, KC_M, KC_COMM, KC_DOT, CTLSLH,
#define _______________REV34QWERTY4_______________                KC_LGUI, LWRSPC, RSEBSP, CLIPST

#define _______________REV34LOWER1________________ ALT1,   KC_2,   KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    ALT0, 
#define _______________REV34LOWER2________________ SFEXM,  KC_AT,  KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN, 
#define _______________REV34LOWER3________________ CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL,
#define _______________REV34LOWER4________________                            KC_LGUI, KC_TRNS, KC_VOLU, CLIPST

#define _______________REV34RAISE1________________ KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,      RGB_HUI, RGB_M_G,  RGB_M_P,  RGB_MOD, RGB_TOG,
#define _______________REV34RAISE2________________ KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,      RGB_HUD, RGB_M_SW, RGB_M_TW, RGB_SAD, RGB_SAI,
#define _______________REV34RAISE3________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,
#define _______________REV34RAISE4________________                             KC_LGUI, KC_VOLD, KC_TRNS, CLIPST

/*
 ____  ____  ___  _   _  _  _  ____  _  _ 
(_  _)( ___)/ __)( )_( )( \( )(_  _)( )/ )
  )(   )__)( (__  ) _ (  )  (  _)(_  )  ( 
 (__) (____)\___)(_) (_)(_)\_)(____)(_)\_)
*/

#define ______________TECHNIKQWERTY1______________ KC_TRNS,  ALTQ,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    ALTP,    KC_TRNS,
#define ______________TECHNIKQWERTY2______________ KC_TRNS,    SFA,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
#define ______________TECHNIKQWERTY3______________ KC_TRNS, KC_TRNS, CTLZ,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  CTLDOT, KC_SLSH,
#define ______________TECHNIKQWERTY4______________ KC_VOLD, KC_TRNS, KC_TRNS,   KC_LGUI,   LWRSPC,   RSEBSP, CLIPST,  KC_TRNS,   KC_TRNS, KC_VOLU

#define ______________TECHNIKLOWER1_______________ KC_TRNS, ALT1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, ALT0, KC_TRNS, KC_TRNS,
#define ______________TECHNIKLOWER2_______________ KC_TRNS, SFEXM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SFPRN,
#define ______________TECHNIKLOWER3_______________ KC_TRNS, CTLESC, KC_TAB, KC_CAPS, KC_TILD, KC_GRV, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,
#define ______________TECHNIKLOWER4_______________ KC_TRNS, KC_TRNS, KC_TRNS, KC_LGUI, KC_TRNS, KC_VOLU, CLIPST, KC_TRNS, KC_TRNS, KC_TRNS

#define ______________TECHNIKRAISE1_______________ KC_TRNS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, RGB_HUI, RGB_M_G, RGB_M_P, RGB_MOD, RGB_TOG, KC_TRNS, 
#define ______________TECHNIKRAISE2_______________ KC_TRNS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, RGB_HUD, RGB_M_SW, RGB_M_TW, RGB_SAD, RGB_SAI,
#define ______________TECHNIKRAISE3_______________ KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
#define ______________TECHNIKRAISE4_______________ KC_TRNS, KC_TRNS, KC_TRNS, KC_LGUI, KC_VOLD, KC_TRNS, CLIPST, KC_TRNS, KC_TRNS, KC_TRNS

//extra
#define ___________CRKBDQWERTY2NO_RWORD___________ QMKTD,   SFA,  KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K,    KC_L,   SFCLN,  KC_TRNS,
#define ___________CRKBDADJUST1NO_BALL____________ RGB_TOG,  RGB_M_P, RGB_M_G,  RGB_HUD, RGB_HUI, RGB_SPI,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,

