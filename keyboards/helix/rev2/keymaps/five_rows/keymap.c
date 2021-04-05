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

// clang-format off

#define LAYOUT_wrapper(...)    LAYOUT(__VA_ARGS__)

//Macros
#define KC_LOWER  MO(_LOWER)
#define XXXX      XXXXXXX
#define ____      _______
#define KC_ADJ    MO(_ADJUST)

#define _1_____2_____3_____4_____5   KC_1, KC_2, KC_3, KC_4, KC_5
#define _6_____7_____8_____9_____0   KC_6, KC_7, KC_8, KC_9, KC_0
#define LOWER__LOWER__CAPS__LALT__LGUI__SPC__RABS \
    KC_LOWER, KC_LOWER, KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, LT(_RAISE,KC_BSPC)
#define RAEN___SPC___RGUI__RALT__APP___LOWER__LOWER  \
    LT(_RAISE,KC_ENT), KC_SPC, KC_RGUI, KC_RALT,  KC_APP, KC_LOWER, KC_LOWER
#define GRV__QUOT  KC_GRV, KC_QUOT

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty */
#define Q_____W_____E_____R_____T     KC_Q, KC_W, KC_E, KC_R, KC_T
#define Y_____U_____I_____O_____P     KC_Y, KC_U, KC_I, KC_O, KC_P
#define A_____S_____D_____F_____G     KC_A, KC_S, KC_D, KC_F, KC_G
#define H_____J_____K_____L____SCLN   KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define Z_____X_____C_____V_____B     KC_Z, KC_X, KC_C, KC_V, KC_B
#define N_____M____COMM__DOT___SLSH   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
  /* ,-----------------------------------.           ,-----------------------------------.
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
  [_QWERTY] = LAYOUT_wrapper(
    KC_ESC,  _1_____2_____3_____4_____5,               _6_____7_____8_____9_____0,   KC_BSPC,
    KC_TAB,   Q_____W_____E_____R_____T,                Y_____U_____I_____O_____P,   KC_BSLS,
    KC_LCTL,  A_____S_____D_____F_____G,                H_____J_____K_____L____SCLN, KC_RCTL,
    KC_LSFT,  Z_____X_____C_____V_____B,   GRV__QUOT,   N_____M____COMM__DOT___SLSH, KC_RSFT,
     LOWER__LOWER__CAPS__LALT__LGUI__SPC__RABS, RAEN___SPC___RGUI__RALT__APP___LOWER__LOWER
   ),

  /* Colemak */
#define Q_____W_____F_____P_____G     KC_Q, KC_W, KC_F, KC_P, KC_G
#define J_____L_____U_____Y____SCLN   KC_J, KC_L, KC_U, KC_Y, KC_SCLN
#define A_____R_____S_____T_____D     KC_A, KC_R, KC_S, KC_T, KC_D
#define H_____N_____E_____I_____O     KC_H, KC_N, KC_E, KC_I, KC_O
#define Z_____X_____C_____V_____B     KC_Z, KC_X, KC_C, KC_V, KC_B
#define K_____M____COMM__DOT___SLSH   KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH
  /* ,-----------------------------------.           ,-----------------------------------.
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
  [_COLEMAK] = LAYOUT_wrapper(
    KC_ESC,  _1_____2_____3_____4_____5,               _6_____7_____8_____9_____0,   KC_BSPC,
    KC_TAB,   Q_____W_____F_____P_____G,                J_____L_____U_____Y____SCLN, KC_BSLS,
    KC_LCTL,  A_____R_____S_____T_____D,                H_____N_____E_____I_____O,   KC_RCTL,
    KC_LSFT,  Z_____X_____C_____V_____B,   GRV__QUOT,   K_____M____COMM__DOT___SLSH, KC_RSFT,
     LOWER__LOWER__CAPS__LALT__LGUI__SPC__RABS, RAEN___SPC___RGUI__RALT__APP___LOWER__LOWER
   ),

  /* Dvorak */
#define QUOT_COMM___DOT____P_____Y   KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y
#define  F_____G_____C_____R_____L   KC_F, KC_G, KC_C, KC_R, KC_L
#define  A_____O_____E_____U_____I   KC_A, KC_O, KC_E, KC_U, KC_I
#define  D_____H_____T_____N_____S   KC_D, KC_H, KC_T, KC_N, KC_S
#define SCLN___Q_____J_____K_____X   KC_SCLN, KC_Q, KC_J, KC_K, KC_X
#define  B_____M_____W_____V_____Z   KC_B, KC_M, KC_W, KC_V, KC_Z
#define GRV__SLSH KC_GRV,  KC_SLSH
  /* ,-----------------------------------.           ,-----------------------------------.
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
  [_DVORAK] = LAYOUT_wrapper(
    KC_ESC,  _1_____2_____3_____4_____5,               _6_____7_____8_____9_____0,   KC_BSPC,
    KC_TAB,  QUOT_COMM___DOT____P_____Y,                F_____G_____C_____R_____L,   KC_BSLS,
    KC_LCTL,  A_____O_____E_____U_____I,                D_____H_____T_____N_____S,   KC_RCTL,
    KC_LSFT, SCLN___Q_____J_____K_____X,   GRV__SLSH,   B_____M_____W_____V_____Z,   KC_RSFT,
     LOWER__LOWER__CAPS__LALT__LGUI__SPC__RABS, RAEN___SPC___RGUI__RALT__APP___LOWER__LOWER
   ),

  /* Eucalyn (http://eucalyn.hatenadiary.jp/entry/about-eucalyn-layout) */
#define Q_____W___COMM___DOT__SCLN   KC_Q, KC_W, KC_COMM, KC_DOT, KC_SCLN
#define M_____R_____D_____Y_____P    KC_M, KC_R, KC_D, KC_Y, KC_P
#define A_____O_____E_____I_____U    KC_A, KC_O, KC_E, KC_I, KC_U
#define G_____T_____K_____S_____N    KC_G, KC_T, KC_K, KC_S, KC_N
#define Z_____X_____C_____V_____F    KC_Z, KC_X, KC_C, KC_V, KC_F
#define B_____H_____J_____L____SLSH  KC_B, KC_H, KC_J, KC_L, KC_SLSH
  /* ,-----------------------------------.           ,-----------------------------------.
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
  [_EUCALYN] = LAYOUT_wrapper(
    KC_ESC,  _1_____2_____3_____4_____5,               _6_____7_____8_____9_____0,   KC_BSPC,
    KC_TAB,   Q_____W___COMM___DOT__SCLN,               M_____R_____D_____Y_____P,   KC_BSLS,
    KC_LCTL,  A_____O_____E_____I_____U,                G_____T_____K_____S_____N,   KC_RCTL,
    KC_LSFT,  Z_____X_____C_____V_____F,   GRV__QUOT,   B_____H_____J_____L____SLSH, KC_RSFT,
     LOWER__LOWER__CAPS__LALT__LGUI__SPC__RABS, RAEN___SPC___RGUI__RALT__APP___LOWER__LOWER
   ),

  /* Keypad */
#define KP_TAB__PSLS_PAST  KC_TAB,  KC_PSLS, KC_PAST
#define KP__7_____8_____9  KC_KP_7, KC_KP_8, KC_KP_9
#define KP__4_____5_____6  KC_KP_4, KC_KP_5, KC_KP_6
#define KP__1_____2_____3  KC_KP_1, KC_KP_2, KC_KP_3
#define KP__0___COMM_PDOT  KC_KP_0, KC_COMM, KC_PDOT
#define F1___F6  KC_F1, KC_F6
#define F2___F7  KC_F2, KC_F7
#define F3___F8  KC_F3, KC_F8
#define F4___F9  KC_F4, KC_F9
#define F5__F10  KC_F5, KC_F10
#define FF12   LT(_PADFUNC,KC_F12)
  /* ,-----------------------------------.           ,-----------------------------------.
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
  [_KEYPAD] = LAYOUT_wrapper(
    KP_TAB__PSLS_PAST, KC_DEL,  F1___F6,                F1___F6, KC_DEL,  KP_TAB__PSLS_PAST,
    KP__7_____8_____9, KC_BSPC, F2___F7,                F2___F7, KC_BSPC, KP__7_____8_____9,
    KP__4_____5_____6, KC_PMNS, F3___F8,                F3___F8, KC_PMNS, KP__4_____5_____6,
    KP__1_____2_____3, KC_PPLS, F4___F9, KC_F11,KC_F11, F4___F9, KC_PPLS, KP__1_____2_____3,
    KP__0___COMM_PDOT, KC_PENT, F5__F10,   FF12,  FF12, F5__F10, KC_PENT, KP__0___COMM_PDOT
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
  [_KAUX] = LAYOUT(
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____,
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____,
      ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____,
      ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
      ____,ZERO2, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,ZERO2, ____
   ),

  /*  Keypad function layer */
#define PAUS__SLCK__PSCR              KC_PAUS, KC_SLCK, KC_PSCR
#define PSCR__SLCK__PAUS              KC_PSCR, KC_SLCK, KC_PAUS
#define HOME___UP___PGUP              KC_HOME, KC_UP,   KC_PGUP
#define PGUP___UP___HOME              KC_PGUP, KC_UP,   KC_HOME
#define DEL____INS__LEFT__DOWN__RGHT  KC_DEL,  KC_INS,  KC_LEFT, KC_DOWN, KC_RGHT
#define LEFT__DOWN__RGHT___INS___DEL  KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,  KC_DEL
#define PGDN___ADJ___ADJ__PGDN        KC_PGDN, KC_ADJ,  KC_ADJ,  KC_PGDN
  /* ,-----------------------------------------.             ,-----------------------------------------.
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
  [_PADFUNC] = LAYOUT_wrapper(
    XXXX, XXXX, XXXX, PAUS__SLCK__PSCR,             PSCR__SLCK__PAUS, XXXX, XXXX, XXXX,
    XXXX, XXXX, XXXX, HOME___UP___PGUP,             PGUP___UP___HOME, XXXX, XXXX, XXXX,
    XXXX, DEL____INS__LEFT__DOWN__RGHT,             LEFT__DOWN__RGHT___INS___DEL, XXXX,
    XXXX, XXXX, XXXX,KC_END,XXXX, PGDN___ADJ___ADJ__PGDN, XXXX,KC_END,XXXX, XXXX, XXXX,
    XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, ____, ____, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX
   ),

  /* Lower */
#define F1____F2____F3____F4____F5     KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define F6____F7____F8____F9____F10    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define XXXX__PAUS__SLCK___INS         XXXX, KC_PAUS, KC_SLCK, KC_INS
#define XXXX___INS__SLCK__PAUS__XXXX   XXXX, KC_INS,  KC_SLCK, KC_PAUS, XXXX
#define ADJ___ADJ                      KC_ADJ,  KC_ADJ
#define HOME__XXXX___UP____DEL__PGUP   KC_HOME, XXXX, KC_UP, KC_DEL, KC_PGUP
#define PGUP___DEL___UP___XXXX__HOME   KC_PGUP, KC_DEL,  KC_UP, XXXX, KC_HOME
#define END__LEFT__DOWN__RGHT__PGDN    KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#define PGDN__LEFT__DOWN__RGHT___END   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |Pause | ScrLk| Ins  |      |             |      | Ins  | ScrLk|Pause |      | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Home |      | Up   |Delete| PgUp |             | PgUp |Delete| Up   |      | Home |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | End  | Left | Down | Right| PgDn |Adjust|Adjust| PgDn | Left | Down | Right| End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | PrtSc|      |      |      |      |      |      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_wrapper(
    XXXX,  F1____F2____F3____F4____F5,               F6____F7____F8____F9____F10, KC_F11,
    XXXX, XXXX__PAUS__SLCK___INS, XXXX,             XXXX___INS__SLCK__PAUS__XXXX, KC_F12,
    ____, HOME__XXXX___UP____DEL__PGUP,             PGUP___DEL___UP___XXXX__HOME,  ____,
    ____,  END__LEFT__DOWN__RGHT__PGDN, XXXX, XXXX, PGDN__LEFT__DOWN__RGHT___END,  ____,
    ____, ____,KC_PSCR,____, ____, ____, ADJ___ADJ, ____, ____, ____,KC_PSCR,____, ____
   ),

  /* Raise */
#define UNDS__MINS             KC_UNDS, KC_MINS
#define EQL___PLUS             KC_EQL,  KC_PLUS
#define LCBR__LBRC             KC_LCBR, KC_LBRC
#define RBRC__RCBR             KC_RBRC, KC_RCBR
#define MNXT__VOLD__VOLU__MPLY KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
#define EISU__EISU             xEISU, xEISU
#define KANA__KANA             xKANA, xKANA
  /* ,-----------------------------------------.             ,-----------------------------------------.
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
  [_RAISE] = LAYOUT_wrapper(
    XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,             XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,
    XXXX, XXXX, XXXX, XXXX, UNDS__MINS,             EQL___PLUS, XXXX, XXXX, XXXX, XXXX,
    ____, XXXX, XXXX, XXXX, LCBR__LBRC,             RBRC__RCBR, XXXX, XXXX, XXXX, ____,
    ____, XXXX, XXXX, XXXX, XXXX, EISU__EISU, KANA__KANA, MNXT__VOLD__VOLU__MPLY, ____,
     ADJ___ADJ, XXXX, ____, ____, XXXX, ____, ____, XXXX, ____, ____, XXXX,  ADJ___ADJ
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
  [_ADJUST] =  LAYOUT(
      XXXXXXX, KEYPAD,  DVORAK,  COLEMAK, EUCALYN,  QWERTY,          QWERTY,  EUCALYN, COLEMAK,  DVORAK,  KEYPAD, XXXXXXX,
      XXXXXXX, RESET,   RGBRST,  RGB_TOG,   AU_ON, AG_SWAP,          AG_SWAP,   AU_ON, RGB_TOG,  RGBRST, XXXXXXX, XXXXXXX,
      RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  AU_OFF, AG_NORM,          AG_NORM,  AU_OFF, RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI,
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,____,____,XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD,
      _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,____,____,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______
   ),

  /*  AUX modifier key layer */
#define BSPC__RAEN KC_BSPC, LT(_RAISE,KC_ENT)
  /* ,-----------------------------------------.             ,-----------------------------------------.
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
  [_AUX] = LAYOUT_wrapper(
    ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, BSPC__RAEN, ____, ____, ____, ____, ____, ____, ____
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
