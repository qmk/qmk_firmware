// Copyright 2021 br (@b-)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* physical layout
 * [ ` ]  [ 1 ]  [ 2 ]  [ 3 ]  [ 4 ]  [ 5 ]  [ 6 ]  [ 7 ]  [ 8 ]  [ 9 ]  [ 0 ]  [ - ]  [ = ]  [ bksp ] [ del ]
 * [ tab* ]  [ q ]  [ w ]  [ e ]  [ r ]  [ t ]  [ y ]  [ u ]  [ i ]  [ o ]  [ p ]  [ [ ]  [ ] ]  [ home ]
 * [ ctrl* ]  [ a ]  [ s ]  [ d ]  [ f ]  [ g ]  [ h ]  [ j ]  [ k ]  [ l ]  [ ; ]  [ ' ]  [ enter ]  [ PgUp ]
 * [ lshift* ]  [ z ]  [ x ]  [ c ]  [ v ]  [ b ]  [ n ]  [ m ]  [ , ]  [ . ]  [ / ]  [ rshift* ] ]  [ ↑ ]  [ PgDn ]
 * [ ctrl ]  [ alt ]  [ meta ]  [              spaaaaaaaace             ]  [ meta ]  [ alt ]  [ ← ]  [ ↓ ]  [ → ]
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_65_ansi_blocker( /* normal */
      KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,  /* 15 */
      LT(1,KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, /* 15 */
      LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP, /* 14 */
      LM(2, MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, LM(2, MOD_LSFT), KC_UP, KC_PGDN, /* 14 */
      KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT /* 9 */
      ),
	[1] = LAYOUT_65_ansi_blocker( /* hold tab */
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_MUTE, 
      KC_TRNS, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, BL_UP,  BL_DOWN,BL_BRTG, BL_STEP, KC_PSCR, KC_SCRL, KC_PAUS, KC_TRNS, KC_END, 
      MO(3), RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, 
      KC_TRNS, RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, MO(4), NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_VOLD, 
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END // fn layer. f keys, media keys, backlight control, nkro-toggle, etc.
      ),
	[2] = LAYOUT_65_ansi_blocker( /* lshift + rshift = caps lock */
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS // this feels like a kludge...but it works
      ),
	[3] = LAYOUT_65_ansi_blocker( /* tab+ctrl */
      KC_EXEC, KC_HELP, KC_MENU, KC_SLCT, KC_STOP, KC_AGIN, KC_UNDO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EJCT,
      KC_NO, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_TRNS, BL_TOGG, BL_STEP, BL_BRTG, KC_FIND, BL_DOWN,BL_UP,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BRIU,
      KC_NO, KC_NO, KC_CUT, KC_COPY, KC_PSTE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MSTP, KC_BRID,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MRWD, KC_MPLY, KC_MFFD // miscellaneous silly keys, subject to change
      ),
	[4] = LAYOUT_65_ansi_blocker( /* tab+b */
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, /* backspace */
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS // tab + b + backspace goes to bootloader
      )
};

