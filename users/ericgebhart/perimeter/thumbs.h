/*
  Copyright 2018-2023 Erica Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.
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
#define ___6_THUMBS_2_CB___  KC_LSFT,    KC_BKTAB, KC_END,  KC_PGDN, KC_TAB, KC_RSFT

#define ___6_THUMBS_2a___ BSPC_SYMB, ESC_TOPR, ESC_TOPR, ENT_NAV, ENT_NAV, SPC_TOPR
#define ___6_THUMBS_2a_CB___ BSPC_SYMB, ESC_TOPR, ESC_TOPR, ENT_NAV, ENT_NAV, SPC_TOPR

// for the kyria these are the 4 upper thumb keys.
#define ___4_THUMBS_def___       OS_LALT, OS_LCTL, SML_NAV, OS_LSFT

// frankenkyria
// top row of u.
// define something as the top two thumb keys on each side.
//
#define ___4_THUMBS_fkyria_def___   BSPC_SYMB, GUI_ESC, ACCENTS_RALT, ENT_NAV
// bottom row of u.  ie. middle. Plus the first key 4th row.
// 6_urgo  Has arrows for the franken kyria.
#define ___6_ERGO_THUMBS_fkyria___                              \
  KC_RIGHT, BSPC_SYMB, GUI_ESC, ENT_NAV, SPC_TOPR, KC_UP
#define ___6_ERGO_THUMBS_fkyria_ltr___                          \
  KC_RIGHT, TH_LTR_SYM, GUI_ESC, ENT_NAV, SPC_TOPR, KC_UP

// This ends up in 10_ergo_thumbs below. Cause thats what we need.
// We need the left arrow and the down arrow on the inside, then whatever
// on the outer 2 bottom corner keys. Smart lock Nav and keypad ?
// Outer franken kyria thumbs.
// SML_NAV KC_LEFT   6-ergo thumbs   KC_DOWN SML_KEYPAD.


#define ___6_ERGO_THUMBS_layers___                                      \
   SML_NAV, BSPC_SYMB, ESC_TOPR, ENT_NAV, SPC_TOPR, ACCCENTS_RALT

 // Transparent.
#define ___6_ERGO_THUMBS_trns___ ___6___

// A place to test stuff.
#define ___6_ERGO_THUMBS_tst___                                 \
  TT_KEYPAD, BSPC_SYMB, ESC_TOPR, ENT_NAV, SPC_TOPR, KC_XM_PORD

#define ___6_ERGO_THUMBS_mods___                                \
  ALT_DEL, CTL_BSPC, GUI_ESC,  ALT_ENT, CTL_SPC, XC_XM_PORD

#define ___6_ERGO_THUMBS_mod_layers___                          \
  ALT_DEL, BSPC_SYMB, GUI_ESC,  CTL_ENT, SPC_TOPR, ACCENTS_RALT

#define ___6_ERGO_THUMBS_mod_layers_nav___                      \
  ALT_DEL, BSPC_SYMB, GUI_ESC,  ENT_NAV, SPC_TOPR, ACCENTS_RALT

// kinesis has the big keys closer, not further
// move enter and space -> so they are on the big easy keys.
#define ___6_ERGO_THUMBS_mod_layers_nav_kinesis___                      \
  BSPC_SYMB, SML_KEYPAD, GUI_ESC,  ACCENTS_RALT, ENT_NAV, SPC_TOPR

#define ___6_ERGO_THUMBS_mod_layers_nav_kinesis_ltr___                  \
  BSPC_SYMB, TH_LTR_SYM, GUI_ESC,  ACCENTS_RALT, ENT_NAV, SPC_TOPR


// for keymaps that need a letter on the thumb.
#define ___6_ERGO_THUMBS_left_letter___                                 \
  BSPC_ALT, TH_LTR_SYM, GUI_ESC,  ENT_NAV, SPC_TOPR, KC_TAB

// an attempt at an approximation of the HD thumbs as they are on the site.
// really should be expected to be a starting point that doesnt strand you.
#define ___6_ERGO_THUMBS_hd___                                  \
  BSPC_ALT, TH_LTR_SYM, GUI_ESC, ENT_NAV, SPC_TOPR, ACCENTS_CTL
#define ___6_ERGO_THUMBS_hd_a___                                        \
  OS_LSHIFT, TH_LTR_SYM, GUI_ESC, BSPC_ALT, SPC_TOPR, ACCENTS_CTL
#define ___6_ERGO_THUMBS_hd_simple___                   \
  MO_SYMB, THUMB_LETTER, KC_ENT, KC_BSPC, KC_SPC, MO_TOPROWS
/* HD dash has thumbs of ,; and .:        */
#define ___6_ERGO_THUMBS_hd_dash___                                     \
  LANG_KC(TL_COMM), TL_DOT_SYMB, GUI_ESC, ENT_NAV, SPC_TOPR, BSPC_NUM

// miryoku thumbs, either its toprows or keypad for numbers.
#define ___6_ERGO_THUMBS_miryoku_tr___                          \
  ESC_MEDIA, SPACE_NAV, TAB_NAVM,  ENT_SYM, BSPC_TOPR, DEL_FUN
#define ___6_ERGO_THUMBS_miryoku___                             \
  ESC_MEDIA, SPACE_NAV, TAB_NAVM,  ENT_SYM, BSPC_NUM, DEL_FUN
// lose the tab key, put a letter where space was.
// move space to the right side, put backspace where tab was.
#define ___6_ERGO_THUMBS_miryoku_ltr___                         \
  ESC_MEDIA, TH_LTR_NAV, BSPC_NAVm,  ENT_SYM, SPC_NUM, DEL_FUN
#define ___6_ERGO_THUMBS_miryoku_tr_ltr___                      \
  ESC_MEDIA, TH_LTR_NAV, BSPC_NAVm,  ENT_SYM, SPC_TOPR, DEL_FUN

#define ___6_ERGO_THUMBS_miryoku_ltr_tab___                      \
  BSPC_MEDIA, TH_LTR_NAV, TAB_NAVM,    ENT_SYM, SPC_NUM, DEL_FUN

#define ___6_ERGO_THUMBS_miryoku_tr_ltr_tab___                   \
  BSPC_MEDIA, TH_LTR_NAV, TAB_NAVM,    ENT_SYM, SPC_TOPR, DEL_FUN

#define ___6_ERGO_THUMBS_media___ ___3___, ___STOP_PLAY_MUTE___
#define ___6_ERGO_THUMBS_mouse___ ___3___, ___3MOUSE_BTNS_R___
#define ___6_ERGO_THUMBS_keypad___ \
  LANG_KC(_DOT), LANG_KC(_0), LANG_KC(_MINS), ___3___
#define ___6_ERGO_THUMBS_symb___                                \
  LANG_KC(_OCPRN), LANG_KC(_RPRN), LANG_KC(_UNDS), ___3___

// So here's the beakl wi thumbs adapted to this combined layer system.
//
#define ___6_ERGO_THUMBS_WI___                                  \
  ESC_TOPR, I_SYMB, TAB_NUM,  ENT_NAV, SPC_SYMB, BSPC_NAV

// Like my other thumb rows. With an I.
#define ___6_ERGO_THUMBS_WIa___                                 \
  BSPC_NAV, I_SYMB, ESC_TOPR, ENT_NAV, SPC_TOPR, TAB_NUM

#define ___6_ERGO_THUMBS_COMBO___ CB_TH1, CB_TH2, CB_TH3, CB_TH4, CB_TH5, CB_TH6
#define ___6_ERGO_THUMBS_COMBO2___ CB2_TH1, CB2_TH2, CB2_TH3, CB2_TH4, CB2_TH5, CB2_TH6

// Give the right symbol suffix by the value of THUMBS_ARE
// Basically we choose the right cluster here, so the layout
// level doesn't know or care.
//
// ___foo  --> ___foo_WI___, or ___foo_WIa___, or ___foo_def___.
// THUMBS_ARE = WI, or WIa, or DEFAULT, TEST, TRNS, MOD_LAYERS, etc.
// the value of THUMB_LETTER is the key used when needed.
#define THUMB_EXT CAT(THUMBS_ARE, _EXT)
#define WI_EXT _WI___
#define WIa_EXT _WIa___
#define DEFAULT_EXT _mod_layers_nav___  //change this to change the default.
#define TEST_EXT _tst___
#define TRNS_EXT _trns___
#define MODS_EXT _mods___
#define LAYERS_EXT _layers___
#define MODS_LAYERS_EXT _mod_layers___
#define MODS_LAYERS_NAV_EXT _mod_layers_nav___
#define MIRYOKU_EXT _miryoku___
#define MIRYOKU_TR_EXT _miryoku_tr___
#define MIRYOKU_LTR_EXT _miryoku_ltr___  // miryoku versions with a letter
#define MIRYOKU_LTR_TAB_EXT _miryoku_ltr_tab___
#define MIRYOKU_TR_LTR_EXT _miryoku_tr_ltr___
#define MIRYOKU_TR_LTR_TAB_EXT _miryoku_tr_ltr_tab___
#define TH_LTR_EXT _left_letter___ // takes a letter for the left thumb.
#define HD_DASH_EXT _hd_dash___
#define HD_EXT _hd___  // takes a letter for the left thumb.
#define HDA_EXT _hd_a___  // relocate backspace
#define HD_SIMPLE_EXT _hd_simple___  // no LTs or MT´s.
#define FKYRIA_EXT _fkyria___
#define FKYRIA_LTR_EXT _fkyria_ltr___
#define KINESIS_EXT _mod_layers_nav_kinesis___
#define KINESIS_LTR_EXT _mod_layers_nav_kinesis_ltr___
// for the function layers
#define COMBO_EXT _COMBO___
#define COMBO2_EXT _COMBO2___
#define MEDIA_THUMBS_EXT _media___
#define MOUSE_THUMBS_EXT _mouse___
#define KEYPAD_THUMBS_EXT _keypad___
#define SYMB_THUMBS_EXT _symb___

#define ___6_ERGO_THUMBS___ CAT2(___6_ERGO_THUMBS, THUMB_EXT)

/* // consolidated for kinesis, ergodox, and dactyl */
/* //for the ergodox and kinesis. */
//___12___

#define ___12_DOX_ALL_THUMBS___ \
          ___THUMBS_1___,       \
          ___THUMBS_2___,       \
          ___6_ERGO_THUMBS___

#define ___12_DOX_ALL_THUMBS_EN___ ___12_DOX_ALL_THUMBS___
#define ___12_DOX_ALL_THUMBS_BP___ ___12_DOX_ALL_THUMBS___

#define ___10_ERGO_THUMBS_def___ _X_, _X_, ___6_ERGO_THUMBS___, _X_, _X_
#define ___10_ERGO_THUMBS_fkyria_def___ OSL_ACCENTS, KC_LEFT,  \
    ___6_ERGO_THUMBS___, KC_RIGHT, SML_KEYPAD

#define ___4_THUMBS_fkyria_EN___ ___4_THUMBS_fkyria_def___
#define ___4_THUMBS_fkyria_BP___ ___4_THUMBS_fkyria_def___

#define ___4_THUMBS_EN___ ___4_THUMBS_fkyria_def___
#define ___4_THUMBS_BP___ ___4_THUMBS_fkyria_def___
#define ___10_ERGO_THUMBS_EN___ ___10_ERGO_THUMBS_fkyria_def___
#define ___10_ERGO_THUMBS_BP___ ___10_ERGO_THUMBS_fkyria_def___

#define ___16_ALL_THUMBS___                     \
  ___4_THUMBS_1___,                             \
    ___6_THUMBS_2___,                           \
    ___6_ERGO_THUMBS___

#define ___16_ALL_THUMBS_EN___ ___16_ALL_THUMBS___
#define ___16_ALL_THUMBS_BP___ ___16_ALL_THUMBS___
#define ___16_ALL_THUMBSa___                    \
  ___4_THUMBS_1___,                             \
    ___6_THUMBS_2a___,                          \
    ___6_ERGO_THUMBS___

#define ___16_ALL_THUMBSa_EN___ ___16_ALL_THUMBSa___
#define ___16_ALL_THUMBSa_BP___ ___16_ALL_THUMBSa___

// combo reference layer thumbs for the kyria.
// for the kyria, note the odd numbering...a 0 row, and a,b,c,d for the extras
// on either side of the central 6 thumbs.
#define ___2_THUMBS_CB___       CB_1TH1,   CB_1TH2
#define ___4_THUMBS_CB___       CB_0TH1,   CB_0TH2, CB_0TH3, CB_0TH4
#define ___6_THUMBS_CB___       CB_1TH1,   CB_1TH2, CB_1TH3, CB_1TH4, CB_1TH5, CB_1TH6

#define ___10_ERGO_THUMBS_CB___ CB_THA,    CB_THB,      \
    ___6_ERGO_THUMBS___, CB_THC, CB_THD
#define ___12_ERGO_THUMBS_CB___ ___2_THUMBS_CB___,              \
    CB_THA,    CB_THB,  ___6_ERGO_THUMBS___, CB_THC, CB_THD
#define ___12_DOX_ALL_THUMBS_CB___ ___4_THUMBS_CB___, ___2_THUMBS_CB___, ___6_ERGO_THUMBS___
#define ___16_DOX_ALL_THUMBS_CB___ ___4_THUMBS_CB___, ___6_THUMBS_2_CB___, ___6_ERGO_THUMBS___
#define ___16_DOX_ALL_THUMBSa_CB___ ___4_THUMBS_CB___, ___6_THUMBS_2a_CB___, ___6_ERGO_THUMBS___

#define ___2_THUMBS_CB2___       CB2_1TH1, CB2_1TH2
#define ___4_THUMBS_CB2___       CB2_0TH1, CB2_0TH2, CB2_0TH3, CB2_0TH4
#define ___6_THUMBS_CB2___       CB2_1TH1, CB2_1TH2, CB2_1TH3, CB2_1TH4, CB2_1TH5, CB2_1TH6
#define ___10_ERGO_THUMBS_CB2___ CB2_THA,  CB2_THB,     \
    ___6_ERGO_THUMBS___, CB2_THC, CB2_THD
#define ___12_ERGO_THUMBS_CB2___ ___2_THUMBS_CB2___,      \
    CB2_THA,  CB2_THB, ___6_ERGO_THUMBS___, CB2_THC, CB2_THD
#define ___12_DOX_ALL_THUMBS_CB2___ ___4_THUMBS_CB2___, ___2_THUMBS_CB2___, ___6_ERGO_THUMBS___
#define ___16_DOX_ALL_THUMBS_CB2___ ___4_THUMBS_CB2___, ___6_THUMBS_2_CB2___, ___6_ERGO_THUMBS___
#define ___16_DOX_ALL_THUMBSa_CB2___ ___4_THUMBS_CB2___, ___6_THUMBS_2a_CB2___, ___6_ERGO_THUMBS___

// for the kyria, mostly for the combo reference layers.
// #define ___10_ERGO_THUMBS___ CATR(___10_ERGO_THUMBS, EXP_THUMB_EXT)
// #define ___4_THUMBS___ CAT2(___4_THUMBS, EXP_THUMB_EXT)

// Basically give the same 4 top thumbs and bottom outer 4 thumbs for everyone.
// Could be different for every one, but the core 6 is enough for now I think.
// Everyone is the same except the combo reference layers.
// Let 6 ERGO_THUMBS do it´s thing inside.
#define EXP_THUMB_EXT CAT(THUMBS_ARE, _EXP_EXT)
#define WI_EXP_EXT _def___
#define WIa_EXP_EXT _def___
#define DEFAULT_EXP_EXT _def___
#define TEST_EXP_EXT _def___
#define TRNS_EXP_EXT _def___
#define MODS_EXP_EXT _def___
#define LAYERS_EXP_EXT _def___
#define MODS_LAYERS_EXP_EXT _def___
#define MODS_LAYERS_NAV_EXP_EXT _def___
#define MIRYOKU_EXP_EXT _def___
#define MIRYOKU_TR_EXP_EXT _def___
#define MIRYOKU_LTR_EXP_EXT _def___
#define MIRYOKU_TR_LTR_EXP_EXT _def___
#define TH_LTR_EXP_EXT _def___
#define HD_DASH_EXP_EXT _def___
#define HD_EXP_EXT _def___
#define HDA_EXP_EXT _def___
#define HD_SIMPLE_EXP_EXT _def___
// for the function layers
#define COMBO_EXP_EXT _COMBO___
#define COMBO2_EXT _COMBO2___
#define MEDIA_THUMBS_EXP_EXT _def___
#define MOUSE_THUMBS_EXP_EXT _def___
#define KEYPAD_THUMBS_EXP_EXT _def___
#define SYMB_THUMBS_EXP_EXT _def___
