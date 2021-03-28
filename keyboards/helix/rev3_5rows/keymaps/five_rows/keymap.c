/* Copyright 2020 mtei
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

#include QMK_KEYBOARD_H
#include "util.h"
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif
#include "layer_number.h"

extern keymap_config_t keymap_config;

extern uint8_t is_master;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  EUCALYN,
  KEYPAD,
  xEISU,
  xKANA,
  ZERO2,
  RGBRST
};

#define LAYOUT_wrapper(...)    LAYOUT(__VA_ARGS__)

//Macros
#define KC_LOWER  MO(_LOWER)
#define XXXX      XXXXXXX
#define ____      _______
#define KC_ADJ    MO(_ADJUST)
#define KC_LSMI   LSFT(KC_MINS)
#define KC_LSEQ   LSFT(KC_EQL)
#define KC_LSRB   LSFT(KC_RBRC)
#define KC_LSLB   LSFT(KC_LBRC)

#define _1_2_3_4_5           KC_1, KC_2, KC_3, KC_4, KC_5
#define _6_7_8_9_0           KC_6, KC_7, KC_8, KC_9, KC_0
#define L_LOWER2_CAPS_LALT_LGUI_SPC_RABS \
    KC_LOWER, KC_LOWER, KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, LT(_RAISE,KC_BSPC)
#define R_RAEN_SPC_RGUI_RALT_APP_LOWER2 \
    LT(_RAISE,KC_ENT), KC_SPC, KC_RGUI, KC_RALT,  KC_APP, KC_LOWER, KC_LOWER


#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------.           ,-----------------------------------.
   * | ESC |  1  |  2  |  3  |  4  |  5  |           |  6  |  7  |  8  |  9  |  0  | BS  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Tab |  Q  |  W  |  E  |  R  |  T  |           |  Y  |  U  |  I  |  O  |  P  |  \  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Ctrl|  A  |  S  |  D  |  F  |  G  |           |  H  |  J  |  K  |  L  |  ;  |Ctrl |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |Shift|  Z  |  X  |  C  |  V  |  B  |  `  |  '  |  N  |  M  |  ,  |  .  |  /  |Shift|
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |Lower|Lower|Caps | Alt | GUI |Space|  BS |Enter|Space| GUI | Alt |Menu |Lower|Lower|
   * `-----------------------------------------------------------------------------------'
   */
#define _Q_W_E_R_T           KC_Q, KC_W, KC_E, KC_R, KC_T
#define _Y_U_I_O_P           KC_Y, KC_U, KC_I, KC_O, KC_P
#define _A_S_D_F_G           KC_A, KC_S, KC_D, KC_F, KC_G
#define _H_J_K_L_SCLN        KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define _Z_X_C_V_B           KC_Z, KC_X, KC_C, KC_V, KC_B
#define _N_M_COMM_DOT_SLSH   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

  [_QWERTY] = LAYOUT_wrapper( \
    KC_ESC,   _1_2_3_4_5,                       _6_7_8_9_0,         KC_BSPC, \
    KC_TAB,   _Q_W_E_R_T,                       _Y_U_I_O_P,         KC_BSLS, \
    KC_LCTL,  _A_S_D_F_G,                       _H_J_K_L_SCLN,      KC_RCTL, \
    KC_LSFT,  _Z_X_C_V_B,     KC_GRV,  KC_QUOT, _N_M_COMM_DOT_SLSH, KC_RSFT, \
    L_LOWER2_CAPS_LALT_LGUI_SPC_RABS,  R_RAEN_SPC_RGUI_RALT_APP_LOWER2  \
   ),

  /* Colemak
   * ,-----------------------------------.           ,-----------------------------------.
   * | ESC |  1  |  2  |  3  |  4  |  5  |           |  6  |  7  |  8  |  9  |  0  | BS  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Tab |  Q  |  W  |  F  |  P  |  G  |           |  J  |  L  |  U  |  Y  |  ;  |  \  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Ctrl|  A  |  R  |  S  |  T  |  D  |           |  H  |  N  |  E  |  I  |  O  |Ctrl |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |Shift|  Z  |  X  |  C  |  V  |  B  |  `  |  '  |  K  |  M  |  ,  |  .  |  /  |Shift|
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |Lower|Lower|Caps | Alt | GUI |Space|  BS |Enter|Space| GUI | Alt |Menu |Lower|Lower|
   * `-----------------------------------------------------------------------------------'
   */
#define _Q_W_F_P_G           KC_Q, KC_W, KC_F, KC_P, KC_G
#define _J_L_U_Y_SCLN        KC_J, KC_L, KC_U, KC_Y, KC_SCLN
#define _A_R_S_T_D           KC_A, KC_R, KC_S, KC_T, KC_D
#define _H_N_E_I_O           KC_H, KC_N, KC_E, KC_I, KC_O
#define _Z_X_C_V_B           KC_Z, KC_X, KC_C, KC_V, KC_B
#define _K_M_COMM_DOT_SLSH   KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH

  [_COLEMAK] = LAYOUT_wrapper( \
    KC_ESC,   _1_2_3_4_5,                       _6_7_8_9_0,         KC_BSPC, \
    KC_TAB,   _Q_W_F_P_G,                       _J_L_U_Y_SCLN,      KC_BSLS, \
    KC_LCTL,  _A_R_S_T_D,                       _H_N_E_I_O,         KC_RCTL, \
    KC_LSFT,  _Z_X_C_V_B,     KC_GRV,  KC_QUOT, _K_M_COMM_DOT_SLSH, KC_RSFT, \
    L_LOWER2_CAPS_LALT_LGUI_SPC_RABS,  R_RAEN_SPC_RGUI_RALT_APP_LOWER2  \
  ),

  /* Dvorak
   * ,-----------------------------------.           ,-----------------------------------.
   * | ESC |  1  |  2  |  3  |  4  |  5  |           |  6  |  7  |  8  |  9  |  0  | BS  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Tab |  '  |  ,  |  .  |  P  |  Y  |           |  F  |  G  |  C  |  R  |  L  |  \  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Ctrl|  A  |  O  |  E  |  U  |  I  |           |  D  |  H  |  T  |  N  |  S  |Ctrl |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |Shift|  ;  |  Q  |  J  |  K  |  X  |  `  |  /  |  B  |  M  |  W  |  V  |  Z  |Shift|
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |Lower|Lower|Caps | Alt | GUI |Space|  BS |Enter|Space| GUI | Alt |Menu |Lower|Lower|
   * `-----------------------------------------------------------------------------------'
   */
#define _QUOT_COMM_DOT_P_Y   KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y
#define _F_G_C_R_L           KC_F, KC_G, KC_C, KC_R, KC_L
#define _A_O_E_U_I           KC_A, KC_O, KC_E, KC_U, KC_I
#define _D_H_T_N_S           KC_D, KC_H, KC_T, KC_N, KC_S
#define _SCLN_Q_J_K_X        KC_SCLN, KC_Q, KC_J, KC_K, KC_X
#define _B_M_W_V_Z           KC_B, KC_M, KC_W, KC_V, KC_Z

  [_DVORAK] = LAYOUT_wrapper( \
    KC_ESC,   _1_2_3_4_5,                       _6_7_8_9_0,    KC_BSPC, \
    KC_TAB,   _QUOT_COMM_DOT_P_Y,               _F_G_C_R_L,    KC_BSLS, \
    KC_LCTL,  _A_O_E_U_I,                       _D_H_T_N_S,    KC_RCTL, \
    KC_LSFT,  _SCLN_Q_J_K_X,  KC_GRV,  KC_SLSH, _B_M_W_V_Z,    KC_RSFT, \
    L_LOWER2_CAPS_LALT_LGUI_SPC_RABS,  R_RAEN_SPC_RGUI_RALT_APP_LOWER2  \
   ),

  /* Eucalyn (http://eucalyn.hatenadiary.jp/entry/about-eucalyn-layout)
   * ,-----------------------------------.           ,-----------------------------------.
   * | ESC |  1  |  2  |  3  |  4  |  5  |           |  6  |  7  |  8  |  9  |  0  | BS  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Tab |  Q  |  W  |  ,  |  .  |  ;  |           |  M  |  R  |  D  |  Y  |  P  |  \  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * | Ctrl|  A  |  O  |  E  |  I  |  U  |           |  G  |  T  |  K  |  S  |  N  |Ctrl |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |Shift|  Z  |  X  |  C  |  V  |  F  |  `  |  '  |  B  |  H  |  J  |  L  |  /  |Shift|
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |Lower|Lower|Caps | Alt | GUI |Space|  BS |Enter|Space| GUI | Alt |Menu |Lower|Lower|
   * `-----------------------------------------------------------------------------------'
   */
#define _Q_W_COMM_DOT_SCLN   KC_Q, KC_W, KC_COMM, KC_DOT, KC_SCLN
#define _M_R_D_Y_P           KC_M, KC_R, KC_D, KC_Y, KC_P
#define _A_O_E_I_U           KC_A, KC_O, KC_E, KC_I, KC_U
#define _G_T_K_S_N           KC_G, KC_T, KC_K, KC_S, KC_N
#define _Z_X_C_V_F           KC_Z, KC_X, KC_C, KC_V, KC_F
#define _B_H_J_L_SLSH        KC_B, KC_H, KC_J, KC_L, KC_SLSH

  [_EUCALYN] = LAYOUT_wrapper( \
    KC_ESC,   _1_2_3_4_5,                       _6_7_8_9_0,     KC_BSPC, \
    KC_TAB,   _Q_W_COMM_DOT_SCLN,               _M_R_D_Y_P,     KC_BSLS, \
    KC_LCTL,  _A_O_E_I_U,                       _G_T_K_S_N,     KC_RCTL, \
    KC_LSFT,  _Z_X_C_V_F,     KC_GRV,  KC_QUOT, _B_H_J_L_SLSH,  KC_RSFT, \
    L_LOWER2_CAPS_LALT_LGUI_SPC_RABS,  R_RAEN_SPC_RGUI_RALT_APP_LOWER2  \
  ),

  /* Keypad
   * ,-----------------------------------.           ,-----------------------------------.
   * | Tab |  /  |  *  | Del |  F1 |  F6 |           |  F1 |  F6 | Del | Tab |  /  |  *  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |  7  |  8  |  9  | BS  |  F2 |  F7 |           |  F2 |  F7 | BS  |  7  |  8  |  9  |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |  4  |  5  |  6  |  -  |  F3 |  F8 |           |  F3 |  F8 |  -  |  4  |  5  |  6  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |  1  |  2  |  3  |  +  |  F4 |  F9 | F11 | F11 |  F4 |  F9 |  +  |  1  |  2  |  3  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |  0  |  ,  |  .  |Enter|  F5 |  F10| F12 | F12 |  F5 |  F10|Enter|  0  |  ,  |  .  |
   * `-----------------------------------------------------------------------------------'
   */
#define KP_TOP KC_TAB,  KC_PSLS, KC_PAST
#define KP_789 KC_KP_7, KC_KP_8, KC_KP_9
#define KP_456 KC_KP_4, KC_KP_5, KC_KP_6
#define KP_123 KC_KP_1, KC_KP_2, KC_KP_3
#define KP_BTM KC_KP_0, KC_COMM, KC_PDOT
#define F_1_6  KC_F1, KC_F6
#define F_2_7  KC_F2, KC_F7
#define F_3_8  KC_F3, KC_F8
#define F_4_9  KC_F4, KC_F9
#define F_510  KC_F5, KC_F10
#define FF12   LT(_PADFUNC,KC_F12)

  [_KEYPAD] = LAYOUT_wrapper( \
    KP_TOP, KC_DEL,  F_1_6,                     F_1_6,  KC_DEL, KP_TOP, \
    KP_789, KC_BSPC, F_2_7,                     F_2_7, KC_BSPC, KP_789, \
    KP_456, KC_PMNS, F_3_8,                     F_3_8, KC_PMNS, KP_456, \
    KP_123, KC_PPLS, F_4_9,  KC_F11,  KC_F11,  F_4_9, KC_PPLS, KP_123, \
    KP_BTM, KC_PENT, F_510,    FF12,    FF12,  F_510, KC_PENT, KP_BTM  \
  ),

  /*  AUX modifier key layer
   * ,-----------------------------------.           ,-----------------------------------.
   * |     |     |     |     |     |     |           |     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |           |     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----|           |-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |           |     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     | 00  |     |     |     |     |     |     |     |     |     |     | 00  |     |
   * `-----------------------------------------------------------------------------------'
   */
  [_KAUX] = LAYOUT( \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
      ____,ZERO2, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,ZERO2, ____ \
   ),

  /*  Keypad function layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      | Pause| ScrLk| PtrSc|             | PtrSc| ScrLk| Pause|      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      | Home |  Up  | PgUp |             | PgUp |  Up  | Home |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |Delete|Insert| Left | Down | Right|             | Left | Down | Right|Insert|Delete|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      | End  |      | PgDn |Adjust|Adjust| PgDn |      | End  |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
#define _PAUS_SLCK_PSCR           KC_PAUS, KC_SLCK, KC_PSCR
#define _PSCR_SLCK_PAUS           KC_PSCR, KC_SLCK, KC_PAUS
#define _HOME_UP_PGUP             KC_HOME, KC_UP,   KC_PGUP
#define _PGUP_UP_HOME             KC_PGUP, KC_UP,   KC_HOME
#define _DEL_INS_LEFT_DOWN_RGHT   KC_DEL,  KC_INS,  KC_LEFT, KC_DOWN, KC_RGHT
#define _LEFT_DOWN_RGHT_INS_DEL   KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,  KC_DEL
#define _PGDN_ADJ_ADJ_PGDN        KC_PGDN, KC_ADJ,  KC_ADJ,  KC_PGDN

  [_PADFUNC] = LAYOUT_wrapper( \
      XXXX, XXXX, XXXX, _PAUS_SLCK_PSCR,               _PSCR_SLCK_PAUS,       XXXX, XXXX, XXXX, \
      XXXX, XXXX, XXXX,   _HOME_UP_PGUP,               _PGUP_UP_HOME,         XXXX, XXXX, XXXX, \
      XXXX,     _DEL_INS_LEFT_DOWN_RGHT,               _LEFT_DOWN_RGHT_INS_DEL,           XXXX, \
      XXXX, XXXX, XXXX, KC_END, XXXX,   _PGDN_ADJ_ADJ_PGDN,     XXXX, KC_END, XXXX, XXXX, XXXX, \
      XXXX, XXXX, XXXX, XXXX,   XXXX, XXXX, ____, ____,   XXXX, XXXX,   XXXX, XXXX, XXXX, XXXX \
   ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |Pause | ScrLk| Ins  |      |             |      | Ins  | ScrLk|Pause |      | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | PgUp |      | Up   |Delete| Home |             | Home |Delete| Up   |      | PgUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | PgDn | Left | Down | Right| End  |Adjust|Adjust| End  | Left | Down | Right| PgDn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | PrtSc|      |      |      |      |      |      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
#define _F1_F2_F3_F4_F5           KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define _F6_F7_F8_F9_F10_F11      KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11
#define _PAUS_SLCK_INS            KC_PAUS, KC_SLCK, KC_INS
#define _INS_SLCK_PAUS            KC_INS,  KC_SLCK, KC_PAUS
#define _ADJ_ADJ                  KC_ADJ,  KC_ADJ
#define _UP_DEL_PGUP              KC_UP,   KC_DEL,  KC_PGUP
#define _PGUP_DEL_UP              KC_PGUP, KC_DEL,  KC_UP
#define _END_LEFT_DOWN_RGHT_PGDN  KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#define _PGDN_LEFT_DOWN_RGHT_END  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END

  [_LOWER] = LAYOUT_wrapper( \
      XXXX, _F1_F2_F3_F4_F5,                             _F6_F7_F8_F9_F10_F11, \
      XXXX, XXXX,    _PAUS_SLCK_INS,   XXXX,             XXXX,  _INS_SLCK_PAUS,    XXXX, KC_F12, \
      ____, KC_HOME, XXXX, _UP_DEL_PGUP,                 _PGUP_DEL_UP,      XXXX, KC_HOME, ____, \
      ____, _END_LEFT_DOWN_RGHT_PGDN,        XXXX, XXXX, _PGDN_LEFT_DOWN_RGHT_END,         ____, \
      ____, ____, KC_PSCR, ____, ____, ____,  _ADJ_ADJ,  ____, ____, ____, KC_PSCR, ____, ____ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  _   |  -   |             |  =   |  +   |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  {   |  [   |             |  ]   |  }   |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      | EISU | EISU | KANA | KANA | Next | Vol- | Vol+ | Play |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
#define _LSMI_MINS             KC_LSMI, KC_MINS
#define _EQL_LSEQ              KC_EQL,  KC_LSEQ
#define _LSLB_LBRC             KC_LSLB, KC_LBRC
#define _RBRC_LSRB             KC_RBRC, KC_LSRB
#define _MNXT_VOLD_VOLU_MPLY   KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY

  [_RAISE] = LAYOUT_wrapper( \
      XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,             XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, \
      XXXX, XXXX, XXXX, XXXX, _LSMI_MINS,             _EQL_LSEQ,  XXXX, XXXX, XXXX, XXXX, \
      ____, XXXX, XXXX, XXXX, _LSLB_LBRC,             _RBRC_LSRB, XXXX, XXXX, XXXX, ____, \
      ____, XXXX, XXXX, XXXX, XXXX,xEISU,xEISU, xKANA,xKANA, _MNXT_VOLD_VOLU_MPLY,  ____, \
      _ADJ_ADJ,   XXXX, ____, ____, XXXX, ____, ____, XXXX, ____, ____, XXXX,   _ADJ_ADJ \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |Keypad|Dvorak|Colemk|Euclyn|Qwerty|             |Qwerty|Euclyn|Colemk|Dvorak|Keypad|      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|RGB ON|Aud on| Win  |             | Win  |Aud on|RGB ON|RGBRST|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| Mac  |             | Mac  |Audoff|RGB md| VAL+ | SAT+ | HUE+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |      |      |      |      |      |      |      |      | VAL- | SAT- | HUE- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      XXXXXXX, KEYPAD,  DVORAK,  COLEMAK, EUCALYN,  QWERTY,          QWERTY,  EUCALYN, COLEMAK,  DVORAK,  KEYPAD, XXXXXXX, \
      XXXXXXX, RESET,   RGBRST,  RGB_TOG,   AU_ON, AG_SWAP,          AG_SWAP,   AU_ON, RGB_TOG,  RGBRST, XXXXXXX, XXXXXXX, \
      RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  AU_OFF, AG_NORM,          AG_NORM,  AU_OFF, RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI, \
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,____,____,XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD, \
      _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,____,____,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______ \
   ),

  /*  AUX modifier key layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |  BS  | Enter|      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
#define _BSPC_RAEN KC_BSPC, LT(_RAISE,KC_ENT)
  [_AUX] = LAYOUT_wrapper( \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
      ____, ____, ____, ____, ____, _BSPC_RAEN, ____, ____, ____, ____, ____, ____, ____ \
      )
};

#else
#error "undefined keymaps"
#endif


int current_default_layer;

uint32_t default_layer_state_set_user(uint32_t state) {
    current_default_layer = biton32(state);
    return state;
}

void update_base_layer(int base)
{
    if( current_default_layer != base ) {
        eeconfig_update_default_layer(1UL<<base);
        default_layer_set(1UL<<base);
        layer_off(_AUX);
        layer_off(_KAUX);
    } else {
        if( base < _KEYPAD )
            layer_invert(_AUX);
        else
            layer_invert(_KAUX);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        update_base_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        update_base_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        update_base_layer(_DVORAK);
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        update_base_layer(_EUCALYN);
      }
      return false;
      break;
    case KEYPAD:
      if (record->event.pressed) {
        update_base_layer(_KEYPAD);
      }
      return false;
      break;
    case ZERO2:
      if (record->event.pressed) {
          SEND_STRING("00");
      }
      return false;
      break;
    case xEISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case xKANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    INIT_HELIX_OLED(); /* define in layer_number.h */
}
