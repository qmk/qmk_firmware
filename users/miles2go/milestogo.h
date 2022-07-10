/* Modified from
Copyright 2017 Christopher Courtney <drashna@live.com> @drashna

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

#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif

#define USERSPACE_ACTIVE

/* Define layer names */
enum userspace_layers { _QWERTY = 0, _CDH, _SYM, _MOV, _DMOV, _NUM };

/*
define modifiers here, since MOD_* doesn't seem to work for these
 */
#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))
#define MODS_GUI_MASK (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))

#if defined(BABBLE_END_RANGE)
#    define USER_START BABBLE_END_RANGE
#else
#    if defined(KEYMAP_SAFE_RANGE)
#        define USER_START KEYMAP_SAFE_RANGE
#    else
#        define USER_START SAFE_RANGE
#    endif
#endif

enum userspace_custom_keycodes {
    EPRM = BABBLE_END_RANGE,  // Resets EEPROM do defaults (as in eeconfig_init)
    VRSN,                     // Prints QMK Firmware and board info
    KC_QWERTY,                // Sets default layer to QWERTY
    KC_CDH,                   // Sets default layer to COLEMAK DH
    KC_MAKE,
    VIBRK,    // escape :
    DHPASTE,  // allow pasting via qwerty V,not colemak V
    TMUX,     // TMUX Ctrl-b
    ALTSYM,   // Alt when held, toggle MOV when tapped
    GUISYM,
    SPCMOV,
    SAVE,           // placeholder for CTRL-S while I get babble working again.
    NEW_SAFE_RANGE  // Keymap specific codes come AFTER this
};

#define QWERTY KC_QWERTY
#define COLEMAK KC_CDH
#define KC_RESET RESET

#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define _________________QWERTY_L1_________________ KC_Q, KC_W, KC_E, KC_R, KC_T
#define _________________QWERTY_L2_________________ KC_A, KC_S, KC_D, KC_F, KC_G
#define _________________QWERTY_L3_________________ KC_Z, KC_X, KC_C, KC_V, KC_B

#define _________________QWERTY_R1_________________ KC_Y, KC_U, KC_I, KC_O, KC_P
#define _________________QWERTY_R2_________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define _________________QWERTY_R3_________________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH

#define ______________COLEMAK_MOD_DH_L1____________ KC_Q, KC_W, KC_F, KC_P, KC_B
#define ______________COLEMAK_MOD_DH_L2____________ KC_A, KC_R, KC_S, KC_T, KC_G
#define ______________COLEMAK_MOD_DH_L3____________ KC_Z, KC_X, KC_C, KC_D, KC_V

#define ______________COLEMAK_MOD_DH_R1____________ KC_J, KC_L, KC_U, KC_Y, KC_SCLN
#define ______________COLEMAK_MOD_DH_R2____________ KC_M, KC_N, KC_E, KC_I, KC_O
#define ______________COLEMAK_MOD_DH_R3____________ KC_K, KC_H, KC_COMM, KC_DOT, KC_SLASH

#define ________________NUMBER_LEFT________________ KC_1, KC_2, KC_3, KC_4, KC_5
#define ________________NUMBER_RIGHT_______________ KC_6, KC_7, KC_8, KC_9, KC_0

#define ________________FKEYS__LEFT________________ KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define ________________FKEYS__RIGHT_______________ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define ________________FKEYS__FAR_RIGHT___________ KC_F11, KC_F12, KC_PSCR, KC_HOME, KC_END

#define ________________NAV_NUMBER_LEFT____________ KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX

#define ___________________BLANK___________________ _______, _______, _______, _______, _______
#define ___________________BLOCK___________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

// BabblePaste
#define ____________BABBLE_SWITCH_L________________ B_MAC, B_READ, B_LINUX, B_VI, _______
#define ____________BABBLE_SWITCH_R________________ B_CROM, B_LINUX, B_WIN, QWERTY, COLEMAK

/////////MOVE  - Full size  keyboard version

/*    ,--------------------------------------------.  ,--------------------------------------------.
 * N  |Lock    |PrevApp |NextApp |PasteVal|        |  |        |        |SwitchKB|Devtools| Lock   |
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 01 | ESC    |FindPrev|  Find  |FindNext| \n cell|  |ParStart|LineStrt|   Up   |  EOL   | ParEnd |
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 02 | SelA   | Do_DEL | Shift  |   Undo |Hsplit+ |  | WrdLft | Left   | Down   | Right  | WrdRght|
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 03 |Vspli+  | Cut    | Copy   | Paste  | Paste  |  | WinPrv | Tab--  | NewTab | Tab++  | WinNxt |
 *    `--------------------------------------------'  `--------------------------------------------'
 */
/* Movement layer  similar to Extend, but fully enriched with babblepaste */
#define ____________BABBLE_MOV_LNUM________________ B_LOCK, B_PAPP, B_NAPP, B_PASTV, XXXX

#define ____________BABBLE_MOV_L1__________________ KC_ESC, B_FINDP, B_FIND, B_FINDN, B_NCEL
#define ____________BABBLE_MOV_L2__________________ B_SELA, MO(_DMOV), KC_LSFT, B_UNDO, B_HSPLIT
#define ____________BABBLE_MOV_L3__________________ B_VSPLIT, B_CUT, B_COPY, B_PASTE, B_PASTE

#define ____________BABBLE_MOV_RNUM________________ XXXX, XXXX, B_KEYB, B_BDEV, B_LOCK
#define ____________BABBLE_MOV_R1__________________ B_PTOP, B_GSOL, B_UP, B_GEOL, B_PEND
#define ____________BABBLE_MOV_R2__________________ B_L1W, B_L1C, B_DOWN, B_R1C, B_R1W
#define ____________BABBLE_MOV_R3__________________ B_PWIN, B_PTAB, B_NTAB, B_NXTB, B_NWIN

// Move in a direction, deleting as we go, or do opposite of Mov layer action */
/*    ,--------------------------------------------.  ,--------------------------------------------.
 * 01 |  Esc   |        |Replace |MultiSel|PasteVal|  |     .  |LineStrt|   .    |  EOL   |    .   |
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 02 |        | Do_Mov | Shift  | Redo   |Hsplit- |  | WrdLft | Left   |   .    | Right  | WrdRght|
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 03 |Vsplit- | Cut    | Copy   | Paste  |Paste   |  |  App-- | ZoomOut| NewWin | ZoomIn | App+   |
 *    `--------------------------------------------'  `--------------------------------------------'
 */
#define _________BABBLE_DELMOV_L1__________________ KC_ESC, _______, B_RPLACE, B_MSEL, B_PASTV
#define _________BABBLE_DELMOV_L2__________________ XXXXXXX, _______, _______, B_REDO, B_HUNSPT
#define _________BABBLE_DELMOV_L3__________________ B_VUNSPT, B_CUT, B_COPY, B_PASTE, B_PRVFM

#define _________BABBLE_DELMOV_R1__________________ XXXXXXX, B_DSOL, _______, B_DEOL, XXXXXXX
#define _________BABBLE_DELMOV_R2__________________ B_DLW, KC_BSPC, _______, B_DEL, B_DRW
#define _________BABBLE_DELMOV_R3__________________ B_NAPP, B_ZOUT, B_WINN, B_ZIN, B_PAPP

/* SYM  / excel / programming logic +=1 optimization*/
/*    ,----------------------------------.  ,----------------------------------.
 * 01 |      |   [  |  ]   |  {   |  }   |  |  {   |  }   | (    | )    |      |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 |  ^   |   !  |  =   |   0  | $    |  |   #  |  1   | -    |  +   |  `   |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 |  \   |   %  |   @  |  |   |  _   |  |   *  |  &   |  ~   |  .   |  /   |
 *    `----------------------------------'  `----------------------------------'
 Memnonics
 ^begining end$ .   &&/|| on strong finger.  #at start of line.
 * (multiply) opposite /
 Minus is left of plus as normal.
 ` is a shifted ''
 ~/ is an outwards roll. / .* is a roll. !=0 is a roll , ++1 --1 roll.
 _ is hard to get to.
 */
#define ___________________SYM_L1__________________ XXXXXXX, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR
#define ___________________SYM_L2__________________ KC_CIRC, KC_EXLM, KC_EQL, KC_0, KC_DLR
#define ___________________SYM_L3__________________ KC_BSLS, KC_PERC, KC_AT, KC_PIPE, KC_UNDS

#define ___________________SYM_R1__________________ KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, XXXXXXX
#define ___________________SYM_R2__________________ KC_HASH, KC_1, KC_MINS, KC_PLUS, KC_GRAVE
#define ___________________SYM_R3__________________ KC_ASTR, KC_AMPR, KC_TILDE, KC_DOT, KC_SLASH

// Move and brackets - 40% optimization.
/*    ,--------------------------------------------.  ,--------------------------------------------.
 * 01 |  ESC   |   (    |  )     |  {     |  }     |  | PgDn   |LineStrt|   Up   |  EOL   |  PGUp  |
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 02 |   [    |DelMove |  Shift | Undo   |   ]    |  | WrdLft | Left   | Down   | Right  | WrdRght|
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 03 |  CDH   | Cut    | Copy   | Paste  | Paste  |  | Babl-- | Tab--  | NewTab | Tab++  | Babl++ |
 *    `--------------------------------------------'  `--------------------------------------------'
 */

#define __________40_______MOV_L1__________________ KC_ESC, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR
#define __________40_______MOV_L2__________________ KC_LBRC, MO(_DMOV), KC_LSFT, KC_UNDO, KC_RBRC
#define __________40_______MOV_L3__________________ KC_CDH, B_CUT, B_COPY, B_PASTE, B_PASTE

#define __________40_______MOV_R1__________________ B_PGDN, B_GSOL, B_UP, B_GEOL, B_PGUP
#define __________40_______MOV_R2__________________ B_L1W, B_L1C, B_DOWN, B_R1C, B_R1W
#define __________40_______MOV_R3__________________ B_DEC, B_PTAB, B_NTAB, B_NXTB, B_INC

// Move in a direction, deleting as we go, or do opposite of Mov layer action
/*    ,--------------------------------------------.  ,--------------------------------------------.
 * 01 |  Esc   |        | B_print|        |        |  | Zoom-- |LineStrt|   .    |  EOL   |  Zoom++|
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 02 |        | Do_DEL | Shift  | Redo   |        |  | WrdLft | Left   |   .    | Right  | WrdRght|
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 03 | Qwerty | Cut    | Copy   | Paste  |Paste   |  | WIN--  |PrvFrame| Split  |nxtFrame| Win++  |
 *    `--------------------------------------------'  `--------------------------------------------'
 */
#define ____________40__DELMOV_L1__________________ KC_ESC, XXXXXXX, B_MODE, XXXXXXX, XXXXXXX
#define ____________40__DELMOV_L2__________________ XXXXXXX, _______, _______, B_REDO, XXXXXXX
#define ____________40__DELMOV_L3__________________ KC_QWERTY, _______, _______, _______, _______

#define ____________40__DELMOV_R1__________________ B_ZOUT, B_DSOL, _______, B_DEOL, B_ZIN
#define ____________40__DELMOV_R2__________________ B_DLW, KC_BSPC, _______, B_DEL, B_DRW
#define ____________40__DELMOV_R3__________________ B_PWIN, B_PRVFM, B_VSPLIT, B_NXTFM, B_NWIN

/* NUM  +  symbol / programming logic +=1 optimization*/
/*    ,----------------------------------.  ,----------------------------------.
 * 01 |   1  |   2  |  3   |  4   |  5   |  | 6    | 7    | 8    | 9    | 0    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 |  ^   |   !  |  =   |   0  | $    |  |   #  |  1   | -    |  +   |  `   |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 |  \   |   %  |   @  |  |   |  _   |  |   *  |  &   |  ~   |  .   |  /   |
 *    `----------------------------------'  `----------------------------------'
 Memnonics
 ^begining end$ .   &&/|| on strong finger.  #at start of line.
 Minus is left of plus as normal. ` is a shifted ''
 ~/ and is an outwards roll. / * is a roll.
 _ is hard to get to.
 */

#define __________40_______NUM_L1__________________ ________________NUMBER_LEFT________________
#define __________40_______NUM_L2__________________ KC_CIRC, KC_EXLM, KC_EQL, KC_0, KC_DLR
#define __________40_______NUM_L3__________________ KC_BSLS, KC_PERC, KC_AT, KC_PIPE, KC_UNDS

#define __________40_______NUM_R1__________________ ________________NUMBER_RIGHT_______________
#define __________40_______NUM_R2__________________ KC_HASH, KC_1, KC_MINS, KC_PLUS, KC_GRAVE
#define __________40_______NUM_R3__________________ KC_ASTR, KC_AMPR, KC_TILDE, KC_DOT, KC_SLASH

// NUM
/*    ,----------------------------------.  ,----------------------------------.
 * 01 |   1  |   2  |  3   |  4   |  5   |  |   6  |  7   |  8   |   9  |  0   |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 |  F1  |  F2  |  F3  |  F4  |  F5  |  |   +  |  4   |  5   |  6   |  -   |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 |  F11 |  F12 |      |   CDH| QWERT|  |  0   |  1   |  2   |  3   |  .   |
 *    `----------------------------------'  `----------------------------------'
 */

#define ___________________NUM_L1__________________ ________________NUMBER_LEFT________________
#define ___________________NUM_L2__________________ ________________FKEYS__LEFT________________
#define ___________________NUM_L3__________________ KC_F11, KC_F11, XXXXXXX, XXXXXXX, QWERTY

#define ___________________NUM_R1__________________ ________________NUMBER_RIGHT_______________
#define ___________________NUM_R2__________________ KC_PLUS, KC_4, KC_5, KC_6, KC_MINS
#define ___________________NUM_R3__________________ KC_0, KC_1, KC_2, KC_3, KC_DOT

// Standard Sym
/*    ,----------------------------------.  ,----------------------------------.
 * 01 |   !  |   @  |  #   |  $   |  %   |  |   ^  |  &   |  *   |  (   |  )   |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 */
#define __________________SSYM_L1__________________ KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC
#define __________________SSYM_R1__________________ KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN

#define _________________ADJUST_L1_________________ RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define _________________ADJUST_L2_________________ MU_TOG, CK_TOGG, AU_ON, AU_OFF, AG_NORM
#define _________________ADJUST_L3_________________ RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_RGB_T

#define _________________ADJUST_R1_________________ KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5
#define _________________ADJUST_R2_________________ AG_SWAP, QWERTY, COLEMAK, DVORAK, WORKMAN
#define _________________ADJUST_R3_________________ MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT

/* excel centric symbol layer*/
/*    ,--------------------------------------------.  ,--------------------------------------------.
* 01 |  DelRow|InsCol  | SelCol |PasteVal|        |  |     .  |   1    |  2     |   3    |        |
*    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
* 02 |   -    |InsRow  | SelRow | Undo   | +      |  |    *   |   4    |  5     |   6    |   -    |
*    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
* 03 | Undo   |  Cut   | Copy   | Paste  |Paste   |  |    /   |   7    |  8     |   9    | Paste  |
*    `--------------------------------------------'  `--------------------------------------------'

*/
#define _________________EXCEL_L1__________________ B_DROW, B_ICOL, B_SELC, B_PASTV, XXXX
#define _________________EXCEL_L2__________________ KC_MINS, B_ICOL, B_SELC, B_UNDO, KC_PLUS
#define _________________EXCEL_L3__________________ B_UNDO, B_CUT, B_COPY, B_PASTE, B_PASTE

#define _________________EXCEL_R1__________________ XXXXXXX, KC_1, KC_2, KC_3, XXXXXXX
#define _________________EXCEL_R2__________________ KC_ASTR, KC_4, KC_5, KC_6, KC_MINS
#define _________________EXCEL_R3__________________ KC_SLASH, KC_7, KC_8, KC_8, B_PASTE

/* Based on BEKL 15 punctuation
 *     ,----------------------------------.  ,----------------------------------.
 * 01 |      |   <  |  $   |  >   |      |  |      |  [   |  _   |  ]   |      |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 |  \   |   (  |  ""  |  )   |  #   |  |   %  |  {   |  =   |  }   |  "|" |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 |      |   :  |   *  |  +   |      |  |      |  &   |  ^   |  ~   |      |
 *    `----------------------------------'  `----------------------------------'
 */
#define ______________BEKL_SYM_L1__________________ XXXXXXX, KC_LBRC, KC_RBRC, KC_LCBR, XXXXXXX
#define ______________BEKL_SYM_L2__________________ KC_CIRC, KC_EXLM, KC_EQL, KC_0, KC_DLR
#define ______________BEKL_SYM_L3__________________ KC_BSLS, KC_PERC, KC_AT, KC_PIPE, KC_UNDS

#define ______________BEKL_SYM_R1__________________ XXXXXXX, KC_RCBR, KC_LPRN, KC_RPRN, XXXXXXX
#define ______________BEKL_SYM_R2__________________ KC_HASH, KC_KP_1, KC_MINS, KC_PLUS, KC_GRAVE
#define ______________BEKL_SYM_R3__________________ KC_PERC, KC_TILDE, KC_AMPR, KC_DOT, KC_SLASH
