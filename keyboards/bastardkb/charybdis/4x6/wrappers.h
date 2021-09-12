/* Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
// clang-format off

/*  Based on miryoku.
    Those wrapers are meant to help create a custom keymap based on miryoku.
    Typically you would build directly with the miryoku keymap, but the Charybdis
    has a different MBO layer.

    This also enables the user to easily create custom base layers.
*/

#define MS_L KC_MS_LEFT
#define MS_R KC_MS_RIGHT
#define MS_D KC_MS_DOWN
#define MS_U KC_MS_UP

#define WH_L KC_MS_WH_LEFT
#define WH_R KC_MS_WH_RIGHT
#define WH_D KC_MS_WH_DOWN
#define WH_U KC_MS_WH_UP


/*
    Basic layers
*/
#define __________________MBO_L1___________________ RESET,   U_NA,    U_NA,    U_NA,    U_NA
#if defined CHARYBDIS_MR_GASC
#define __________________MBO_L2___________________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, U_NA
#elif defined CHARYBDIS_MR_SCGA
#define __________________MBO_L2___________________ KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, U_NA
#elif defined CHARYBDIS_MR_GACS
#define __________________MBO_L2___________________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA
#elif defined CHARYBDIS_MR_CAGS
#define __________________MBO_L2___________________ KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA
#else
#define __________________MBO_L2___________________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, U_NA
#endif
#define __________________MBO_L3___________________ KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1, U_NA
#define __________________MBO_L4___________________ U_NA,    U_NA,    U_NA

#define __________________MBO_R1___________________ U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND
#define __________________MBO_R2___________________ KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
#define __________________MBO_R3___________________ KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END
#define __________________MBO_R4___________________ KC_ENT,  KC_DEL, KC_DEL

#define __________________MEDIA_L1_________________ RESET,   U_NA,    U_NA,    U_NA,    U_NA
#define __________________MEDIA_L2_________________ __________________MBO_L2___________________
#define __________________MEDIA_L3_________________ U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA
#define __________________MEDIA_L4_________________ U_NA,    U_NA,    U_NA

#define __________________MEDIA_R1_________________ U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND
#define __________________MEDIA_R2_________________ U_NU,    MS_L,    MS_D,    MS_U,    MS_R
#define __________________MEDIA_R3_________________ U_NU,    WH_L,    WH_D,    WH_U,    WH_L
#define __________________MEDIA_R4_________________ KC_BTN1, KC_BTN3, KC_BTN2

#define __________________NAV_L1___________________ RESET,   U_NA,    U_NA,    U_NA,    U_NA
#define __________________NAV_L2___________________ __________________MBO_L2___________________
#define __________________NAV_L3___________________ U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA
#define __________________NAV_L4___________________ U_NA,    U_NA,    U_NA

#define __________________NAV_R1___________________ RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI
#define __________________NAV_R2___________________ U_NU,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
#define __________________NAV_R3___________________ U_NU,    U_NU,    U_NU,    U_NU,    U_NU
#define __________________NAV_R4___________________ KC_MSTP, KC_MPLY, KC_MUTE

#define _________________MOUSE_L1__________________ SNIPER_CONFIG,   U_PST,   U_CPY,   U_CUT,   U_UND
#define _________________MOUSE_L2__________________ DPI_CONFIG, DRAG_SCROLL, KC_LSFT, KC_LCTL, KC_TRNS
#define _________________MOUSE_L3__________________ U_RDO,   U_PST,  U_CPY,   U_CUT,   U_UND
#define _________________MOUSE_L4__________________ KC_BTN2, KC_BTN1, KC_BTN3

#define _________________MOUSE_R1__________________ U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND
#define _________________MOUSE_R2__________________ U_NU,    MS_L,    MS_D,    MS_U,    MS_R
#define _________________MOUSE_R3__________________ U_NU,    WH_L,    WH_D,    WH_U,    WH_L
#define _________________MOUSE_R4__________________ KC_BTN1, KC_BTN3, KC_BTN2

#define _________________SYM_L1____________________ KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC
#define _________________SYM_L2____________________ KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL
#define _________________SYM_L3____________________ KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS
#define _________________SYM_L4____________________ KC_DOT,  KC_0,    KC_MINS

#define _________________SYM_R1____________________ U_NA,    U_NA,    U_NA,    U_NA,    RESET
#define _________________SYM_R2____________________ U_NA,    KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
#define _________________SYM_R3____________________ U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA
#define _________________SYM_R4____________________ U_NA,    U_NA,    U_NA

#define _________________NUM_L1____________________ KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR
#define _________________NUM_L2____________________ KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS
#define _________________NUM_L3____________________ KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE
#define _________________NUM_L4____________________ KC_LPRN, KC_RPRN, KC_UNDS

#define _________________NUM_R1____________________ U_NA,    U_NA,    U_NA,    U_NA,    RESET
#define _________________NUM_R2____________________ U_NA,    KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
#define _________________NUM_R3____________________ U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA
#define _________________NUM_R4____________________ U_NA,    U_NA,    U_NA

#define _________________FUN_L1____________________ KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR
#define _________________FUN_L2____________________ KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK
#define _________________FUN_L3____________________ KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS
#define _________________FUN_L4____________________ KC_APP,  KC_SPC,  KC_TAB

#define _________________FUN_R1____________________ U_NA,    U_NA,    U_NA,    U_NA,    RESET
#define _________________FUN_R2____________________ U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI
#define _________________FUN_R3____________________ U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA
#define _________________FUN_R4____________________ U_NA,    U_NA,    U_NA



/*
    Complete wrappers meant to be directly called in LAYOUT_split_3x5_3
*/
#define _MBO \
	__________________MBO_L1___________________, __________________MBO_R1___________________, \
	__________________MBO_L2___________________, __________________MBO_R2___________________, \
	__________________MBO_L3___________________, __________________MBO_R3___________________, \
	__________________MBO_L4___________________, __________________MBO_R4___________________

#define _MEDIA \
    __________________MEDIA_L1_________________, __________________MEDIA_R1_________________, \
    __________________MEDIA_L2_________________, __________________MEDIA_R2_________________, \
    __________________MEDIA_L3_________________, __________________MEDIA_R3_________________, \
    __________________MEDIA_L4_________________, __________________MEDIA_R4_________________
    
#define _NAV  \
    __________________NAV_L1___________________, __________________NAV_R1___________________, \
    __________________NAV_L2___________________, __________________NAV_R2___________________, \
    __________________NAV_L3___________________, __________________NAV_R3___________________, \
    __________________NAV_L4___________________, __________________NAV_R4___________________

#define _MOUSE \
    _________________MOUSE_L1__________________, _________________MOUSE_R1__________________, \
    _________________MOUSE_L2__________________, _________________MOUSE_R2__________________, \
    _________________MOUSE_L3__________________, _________________MOUSE_R3__________________, \
    _________________MOUSE_L4__________________, _________________MOUSE_R4__________________

#define _SYM \
    _________________SYM_L1____________________, _________________SYM_R1____________________, \
    _________________SYM_L2____________________, _________________SYM_R2____________________, \
    _________________SYM_L3____________________, _________________SYM_R3____________________, \
    _________________SYM_L4____________________, _________________SYM_R4____________________

#define _NUM \
    _________________NUM_L1____________________, _________________NUM_R1____________________, \
    _________________NUM_L2____________________, _________________NUM_R2____________________, \
    _________________NUM_L3____________________, _________________NUM_R3____________________, \
    _________________NUM_L4____________________, _________________NUM_R4____________________

#define _FUN  \
    _________________FUN_L1____________________, _________________FUN_R1____________________, \
    _________________FUN_L2____________________, _________________FUN_R2____________________, \
    _________________FUN_L3____________________, _________________FUN_R3____________________, \
    _________________FUN_L4____________________, _________________FUN_R4____________________


/*
    Homerow wrappers
    Those wrappers enable the user to choose which homerow mods he uses.
    With this, he can define a base layer, and call the desired HRM wrapper which will 
    automatically add the relevant modifiers
*/

/* SACG */
#define HRM_MAC(k) HRM_SACG(k)
#define HRM_SACG( \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10, \
	k13,        k14,        k15,        k16,        k17,        k18,        k19,        k20,        k21,        k22, \
	... \
) \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10,    \
	SFT_T(k13), ALT_T(k14), CTL_T(k15), GUI_T(k16), k17,        k18,        GUI_T(k19), CTL_T(k20), ALT_T(k21), SFT_T(k22), \
	__VA_ARGS__
#define HRM_SACG_wrapper(...)                HRM_SACG(__VA_ARGS__)


/* GCAS */
#define HRM_WIN(k) HRM_GCAS(k)
#define HRM_GCAS( \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10, \
	k13,        k14,        k15,        k16,        k17,        k18,        k19,        k20,        k21,        k22, \
	... \
) \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10,    \
	GUI_T(k13), CTL_T(k14), ALT_T(k15), SFT_T(k16), k17,        k18,        SFT_T(k19), ALT_T(k20), CTL_T(k21), GUI_T(k22), \
	__VA_ARGS__
#define HRM_GCAS_wrapper(...)                HRM_GCAS(__VA_ARGS__)

/* GASC */
#define HRM_GASC( \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10, \
	k13,        k14,        k15,        k16,        k17,        k18,        k19,        k20,        k21,        k22, \
	... \
) \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10,    \
	GUI_T(k13), ALT_T(k14), SFT_T(k15), CTL_T(k16), k17,        k18,        CTL_T(k19), SFT_T(k20), ALT_T(k21), GUI_T(k22), \
	__VA_ARGS__
#define HRM_GASC_wrapper(...)                HRM_GASC(__VA_ARGS__)

/* SCGA */
#define HRM_SCGA( \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10, \
	k13,        k14,        k15,        k16,        k17,        k18,        k19,        k20,        k21,        k22, \
	... \
) \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10,    \
	SFT_T(k13), CTL_T(k14), GUI_T(k15), ALT_T(k16), k17,        k18,        ALT_T(k19), GUI_T(k20), CTL_T(k21), SFT_T(k22), \
	__VA_ARGS__
#define HRM_SCGA_wrapper(...)                HRM_SCGA(__VA_ARGS__)

/* GACS */
#define HRM_GACS( \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10, \
	k13,        k14,        k15,        k16,        k17,        k18,        k19,        k20,        k21,        k22, \
	... \
) \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10,    \
	GUI_T(k13), ALT_T(k14), CTL_T(k15), SFT_T(k16), k17,        k18,        SFT_T(k19), CTL_T(k20), ALT_T(k21), GUI_T(k22), \
	__VA_ARGS__
#define HRM_GACS_wrapper(...)                HRM_GACS(__VA_ARGS__)

/* CAGS */
#define HRM_CAGS( \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10, \
	k13,        k14,        k15,        k16,        k17,        k18,        k19,        k20,        k21,        k22, \
	... \
) \
	k01,        k02,        k03,        k04,        k05,        k06,        k07,        k08,        k09,        k10,    \
	CTL_T(k13), ALT_T(k14), GUI_T(k15), SFT_T(k16), k17,        k18,        SFT_T(k19), GUI_T(k20), ALT_T(k21), CTL_T(k22), \
	__VA_ARGS__
#define HRM_CAGS_wrapper(...)                HRM_CAGS(__VA_ARGS__)
// clang-format on