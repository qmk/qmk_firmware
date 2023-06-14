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
/********************************************************************************/
/* NAVIGATION  - MOUSE, Scroll, Buttons, Arrows, Tab, Home, page up/down, End   */
/* Navigation layers:                                                           */
/*    3 row Layer                                                               */
/*    4 Row Layer with repeated and swapped VI arrows, and Scroll wheel.        */
/********************************************************************************/
/*                                                                              */
/* Navigation layer with optional 4th Row....                                   */
/*                                                                              */
/* M = Mouse                                                                    */
/* B = Button                                                                   */
/* W = Wheel                                                                    */
/* AC   = Acceleration                                                          */
/* CCCV = Tap -> Ctrl-C, hold for double tap duration -> Ctrl-V                 */
/* CTCN = Tap -> Ctrl-T, hold for double tap duration -> Ctrl-N                 */
/* CWCQ = Tap -> Ctrl-W, hold for double tap duration -> Ctrl-Q                 */
/* HOME = TAB & PGDN                                                            */
/* END =  BKTAB & PGUP -- See combos.                                           */
/*                                                                              */
/* MB5  MB4    MB3    MB2  MB1     MAC0  |  CTCN  MB1    MB2    MB3  MB4   MB5 */
/* TAB  MLeft  MDown  MUp  MRight  MAC1  |  CCCV  Left   Down   UP   Right TAB */
/*      WLeft  WDown  WUp  WRight  MAC2  |  CWCQ  TAB    PGDN   PGUP BKTAB       */
/*                                                                              */
/*      Left   Down   Up   Right   CCCV  |  CCCV   MLeft  MDown  MUp  MRight    */
/*                                                                              */
/********************************************************************************/

#ifdef MOUSEKEY_ENABLE
#define ___MOUSE_LDUR___      KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R
#define ___MWHEEL_LDUR___     KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R
//  really BTN 1, 2, 3, 8, 9 - according to xev.
#define ___MOUSE_BTNS_R___    KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_BTN4,  KC_BTN5
#define ___4MOUSE_BTNS_R___   KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_BTN4
#define ___3MOUSE_BTNS_R___   KC_BTN1,  KC_BTN3,  KC_BTN2
//  really BTN 9, 8, 3, 2, 1 - according to xev
#define ___4MOUSE_BTNS_L___   KC_BTN4,  KC_BTN2,  KC_BTN3,  KC_BTN1
#define ___MOUSE_BTNS_L___    KC_BTN5,  KC_BTN4,  KC_BTN2,  KC_BTN3,  KC_BTN1
#define ___MOUSE_ACCL_012___  KC_ACL0,  KC_ACL1,  KC_ACL2
#define ___MACCL___ ___MOUSE_ACCL_012___
#endif

#define ___VI_ARROWS___           KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
#define ___HOME_PGDN_PGUP_END___  KC_HOME,  KC_PGDN, KC_PGUP, KC_END
#define ___TAB_PGDN_PGUP_BKTAB___ KC_TAB,  KC_PGDN, KC_PGUP, KC_BKTAB
// home and end are combos.  tab/pgdn = home, bktab/pgup = end.

#define ___REDO_CUT_COPY_PASTE_UNDO___ S_REDO, S_CUT, S_COPY, S_PASTE, S_UNDO

#ifdef MOUSEKEY_ENABLE
#define ___NAV_La_1___ ___SML_MODS_L___, KC_ACL0
#define ___NAV_L_1___ ___4MOUSE_BTNS_L___, KC_ACL0
#define ___NAV_L_2___ ___MOUSE_LDUR___,  KC_ACL1
#define ___NAV_L_3___ ___MWHEEL_LDUR___, KC_ACL2
#define ___NAV_L_4___ ___VI_ARROWS___,   KC_CCCV

#define ___NAV_R_1___  KC_CTCN, ___4MOUSE_BTNS_R___
#define ___NAV_R_4___  KC_CCCV, ___MOUSE_LDUR___

#else

#define ___NAV_La_1___ ___NAV_L_1___
#define ___NAV_L_1___  ___OS_MODS_L___
#define ___NAV_L_2___  ___SML_MODS_L___, ___
#define ___NAV_L_3___  ___5___
#define ___NAV_L_4___  ___VI_ARROWS___,   KC_CCCV

#define ___NAV_R_1___  KC_CTCN, ___SML_MODS_R___
#define ___NAV_R_4___  KC_CCCV, ___4___

#endif // end mousekey

#define ___NAV_R_2___  KC_CCCV, ___VI_ARROWS___
#define ___NAV_R_3___  KC_CWCQ, ___HOME_PGDN_PGUP_END___
#define ___NAV_Ra_3___ KC_CWCQ, ___TAB_PGDN_PGUP_BKTAB___

#ifdef MOUSEKEY_ENABLE

#define ___6NAV_L_1___ ___MOUSE_BTNS_L___,           KC_ACL0
#define ___6NAV_L_2___ TAB_BKTAB, ___MOUSE_LDUR___,  KC_ACL1
#define ___6NAV_L_3___ ___,       ___MWHEEL_LDUR___, KC_ACL2
#define ___6NAV_L_4___ ___,       ___VI_ARROWS___,   KC_CCCV

#define ___6NAV_R_1___ KC_CTCN, ___MOUSE_BTNS_R___
#define ___6NAV_R_4___ KC_CCCV, ___MOUSE_LDUR___, ___

#else

#define ___6NAV_L_1___ ___6___
#define ___6NAV_L_2___ TAB_BKTAB, ___SML_MODS_L___, ___

#define ___6NAV_L_3___ ___,       ___5___
#define ___6NAV_L_4___ ___,       ___VI_ARROWS___,   KC_CCCV

#define ___6NAV_R_1___ KC_CTCN, ___SML_MODS_R___
#define ___6NAV_R_4___ KC_CCCV, ___4___, ___

#endif // end mousekey

#define ___6NAV_R_2___ KC_CCCV, ___VI_ARROWS___,          TAB_BKTAB
#define ___6NAV_R_3___ KC_CWCQ, ___HOME_PGDN_PGUP_END___, ___

// compact. 3x10 per layer.
#define ___10_NAV_1a___ ___NAV_La_1___, ___NAV_R_1___
#define ___10_NAV_1___ ___NAV_L_1___, ___NAV_R_1___
#define ___10_NAV_2___ ___NAV_L_2___, ___NAV_R_2___
#define ___10_NAV_3___ ___NAV_L_3___, ___NAV_Ra_3___

// designed without mouse, mods on left.
#define ___NAVnm_La_1___ ___NAV_L_1___
#define ___NAVnm_L_1___  ___SML_MODS_L___
#define ___NAVnm_L_2___  ___OS_MODS_L___, ___
#ifdef MOUSEKEY_ENABLE
#define ___NAVnm_L_3___  ___2___, SML_NAVm, ___2___  // get to mouse layer if enabled.
#else
#define ___NAVnm_L_3___  ___5___
#endif

#define ___10_NAVnm_1___ ___SML_MODS_L___, ___, ___NAV_R_1___
#define ___10_NAVnm_2___ ___OS_MODS_L___, ___NAV_R_2___
#define ___10_NAVnm_3___ ___NAVnm_L_3___, ___NAV_R_3___

#ifdef MOUSEKEY_ENABLE
// Mouse layer only. mods on right.
#define ___10_NAVm_1___ ___NAV_L_1___, ___NAV_R_1___
#define ___10_NAVm_2___ ___NAV_L_2___, ___NAV_R_2___
#define ___10_NAVm_3___ ___NAV_L_3___, ___NAV_R_3___
#endif

/********************************************************************************/
/* The Navigation LAYER Chunks                                                  */
/********************************************************************************/
// A Navigation Layer
#define CARTE_NAV                               \
  carte_de_map("54321 0  ctn 12345",            \
               " ldur 1  ccv ldur",             \
               " ldur 2  cwq tdubt")

#define CARTE_NAVA                              \
  carte_de_map(" gacs 0  ctn 12345",             \
               " ldur 1  ccv ldur",              \
               " ldur 2  cwq tdubt")

#define CARTE_NAVnm                             \
  carte_de_map(" gacsc2 ctn cscag ",            \
               " gacs   ccv ldur",              \
               " __M_   cwq tdubt")

// currently the same as NAVA
#define CARTE_NAVm                                 \
  carte_de_map(" gacs 0  ctn 12345",               \
               " ldur 1  ccv ldur",                \
               " ldur 2  cwq tdubt")

#define CARTE_NAV_miryoku                       \
  carte_de_map("  rdo  ccp undo",               \
               "  Caps ldur",                   \
               "  Ins  HDUE")

#define CARTE_NAVm_miryoku                      \
  carte_de_map("  rdo ccp undo",               \
               "      ldur",                   \
               "      ldur")


#ifdef MOUSEKEY_ENABLE
#define ___NAVm_3x10___ ___10_NAVm_1___, ___10_NAVm_2___, ___10_NAVm_3___
#endif

#define ___NAVnm_3x10___ ___10_NAVnm_1___, ___10_NAVnm_2___, ___10_NAVnm_3___
#define ___NAVA_3x10___ ___10_NAV_1a___, ___10_NAV_2___, ___10_NAV_3___
#define ___NAV_3x10___ ___10_NAV_1___, ___10_NAV_2___, ___10_NAV_3___
#define ___NAV_3x12___ ___12_NAV_1___, ___12_NAV_2___, ___12_NAV_3___
#define ___NAV_miryoku___ \
  ___5___, ___redo_cut_copy_paste_undo___,                              \
    ___5___, KC_CAPS, ___VI_ARROWS___,                                  \
    ___5___, KC_INSERT, ___HOME_PGDN_PGUP_END___

#ifdef MOUSEKEY_ENABLE
#define ___NAVm_miryoku___                                              \
  ___5___, ___redo_cut_copy_paste_undo___,                              \
    ___5___, ___, ___MOUSE_LDUR___,                                     \
    ___5___, ___, ___MWHEEL_LDUR___,
#endif
