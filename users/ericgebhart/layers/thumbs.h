/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Split thumbs.

// Split these down the middle to think in left and right hand.
// Top row on kinesis, ergodox, etc.
#define ___THUMBS_1___                                  \
  ___X___  , MO_ADJUST,   MO_LAYERS, OSL(LN_TOPROWS)

// Middle row on kinesis, ergodox, etc.
#define ___THUMBS_2___   HOME_END,   KC_PGUP

#define ___4_THUMBS_1___  ___X___, KC_HOME, KC_PGUP, OSL(LN_TOPROWS)
#define ___6_THUMBS_2___  KC_LSFT,    KC_BKTAB, KC_END,  KC_PGDN, KC_TAB, KC_RSFT

#define ___6_THUMBS_2a___ BSPC_SYMB, ESC_TOPR, ESC_TOPR, ENT_NAV, ENT_NAV, SPC_TOPR


// This has become the default center group of thumbs for all
// So here's the beakl wi thumbs adapted to this combined layer system.
//
#define ___6_ERGO_THUMBS_WI___                                  \
  ESC_TOPR, I_SYMB, TAB_NUM,  ENT_NAV, SPC_SYMB, BSPC_NAV

// Like my other thumb rows. With an I.
#define ___6_ERGO_THUMBS_WIa___                                 \
  BSPC_NAV, I_SYMB, ESC_TOPR, ENT_NAV, SPC_TOPR, TAB_NUM

// The default. Still changing, not happy with it yet.
#define ___6_ERGO_THUMBS_layers___                              \
  TT(_NAV), BSPC_SYMB, ESC_TOPR, ENT_NAV, SPC_TOPR, OS_LSFT
// The default. Still changing, not happy with it yet.

#define ___6_ERGO_THUMBS_COMBO___ CB_TH1, CB_TH2, CB_TH3, CB_TH4, CB_TH5, CB_TH6
#define ___6_ERGO_THUMBS_COMBO2___ CB2_TH1, CB2_TH2, CB2_TH3, CB2_TH4, CB2_TH5, CB2_TH6

// Transparent.
#define ___6_ERGO_THUMBS_trns___ ___6___

// A place to test stuff.
#define ___6_ERGO_THUMBS_tst___                                 \
  TT_KEYPAD, BSPC_SYMB, ESC_TOPR, ENT_NAV, SPC_TOPR, KC_XM_PORD

#define ___6_ERGO_THUMBS_mods___                                \
  ALT_DEL, CTL_BSPC, GUI_ESC,  ALT_ENT, CTL_SPC, XC_XM_PORD

#define ___6_ERGO_THUMBS_mod_layers___                          \
  ALT_DEL, BSPC_SYMB, GUI_ESC,  CTL_ENT, SPC_TOPR, KC_RALT

/* HD dash has thumbs of ,; and .:        */
/* #define ___6_ERGO_THUMBS_hd_dash___                             \ */
TL_COMM, TL_DOT_SYMB, GUI_ESC, ALT_ENT, SPC_TOPR, enter ,

/* esc/media, space/nav, tab/mouse | ent/sym, bspc/num, del/fun */
/* #define ___6_ERGO_THUMBS_miryoku___                             \ */
/*   esc_media, space_navnm, tab_navm,  ENT_SYM, BSPC_TOPR, del_fun */

// Give the right symbol suffix by the value of THUMBS_ARE
// Basically we choose the right cluster here, so the layout
// level doesn't know or care.
//
// ___foo  --> ___foo_WI___, or ___foo_WIa___, or ___foo_def___.
// THUMBS_ARE = WI, or WIa, or DEFAULT, TEST, TRNS, MOD_LAYERS.
#define THUMB_EXT CAT(THUMBS_ARE, _EXT)
#define COMBO_EXT _COMBO___
#define COMBO2_EXT _COMBO2___
#define WI_EXT _WI___
#define WIa_EXT _WIa___
#define DEFAULT_EXT _mod_layers___  //change this to change the default.
#define TEST_EXT _tst___
#define TRNS_EXT _trns___
#define MODS_EXT _mods___
#define LAYERS_EXT _layers___
#define MODS_LAYERS_EXT _mod_layers___

#define ___6_ERGO_THUMBS___ CAT2(___6_ERGO_THUMBS, THUMB_EXT)
/* #define ___6_ERGO_THUMBS___ ___6_ERGO_THUMBS_def___ */

/* #define ___ERGODOX_THUMB_LEFT___                \ */
/*   OSL(SYMB), OSM(KC_LGUI),                      \ */
/*     HOME_END,                                   \ */
/*     CTL_BSPC, ALT_DEL, XMONAD_ESC */

/* #define ___ERGODOX_THUMB_RIGHT___               \ */
/*   XXX, OSL(KEYPAD),                             \ */
/*     KC_PGUP,                                    \ */
/*     KC_PGDN, ALT_ENT, CTL_SPC */

// Translation of LT thumb keys from beakl wi where function layers
// have separate left and right to here, where I'm defining left and right in
// one layer and using it that way. I don't feel that having both halves
// on one layer hurts, if I invoke a layer, I'm not trying to use a non
// layer part of the keyboard. I don't have an edit layer, might be a good idea.
// have most of it on the Navigation layer.
// use the keycodes on that original layer, so It's not defined here.
// The wi keypad has a hexpad instead of a funcpad. All the other keypads
// have a funcpad on the opposite side.

// translation of the original wi layers to those here.
// BSPC_NAV
// SPC_SYMB
// TAB_NUM
// ESC_func ->  ESC_TOPR
// I_regex   -> I_SYMB
// ENT_edit  -> ENT_NAV

// consolidated for kinesis, ergodox, and dactyl
//for the ergodox and kinesis.
#define ___12_DOX_ALL_THUMBS___                 \
  ___THUMBS_1___,                               \
    ___THUMBS_2___,                             \
    ___6_ERGO_THUMBS___

#define ___16_ALL_THUMBS___                     \
  ___4_THUMBS_1___,                             \
    ___6_THUMBS_2___,                           \
    ___6_ERGO_THUMBS___

#define ___16_ALL_THUMBSa___                    \
  ___4_THUMBS_1___,                             \
    ___6_THUMBS_2a___,                          \
    ___6_ERGO_THUMBS___

// For the Kyria
#define ___4_THUMBS___       TG(_LAYERS), SML_KEYPAD, OSL_ACCENTS, OSL(LN_TOPROWS)
#define ___10_ERGO_THUMBS___ KC_LALT, KC_LCTL, ___6_ERGO_THUMBS___, KC_RALT, KC_RCTL
