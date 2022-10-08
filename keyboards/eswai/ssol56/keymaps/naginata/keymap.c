/* Copyright 2018-2019 eswai <@eswai>
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
#include "action_layer.h"
#include "eeconfig.h"

#include "keymap_japanese.h"

extern keymap_config_t keymap_config;

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  EUCALYN,
  WORKMAN,
  QGMLWY,
  RAISE,
  LOWER,
  NUMBER,
  ADJUST,
  RGBRST,
  EISU,
  KANA2,
  EURO,
  SSCLN,
  SEQL,
  DELA,
  DELE,
  ALPH,
  SALPH,
};

// Layers
enum kepmap_layers {
  _EUCALYN,
  _QGMLWY,
  _WORKMAN,
  _SHIFT,
// 薙刀式
  _NAGINATA,
// 薙刀式
  _EDIT1R,
  _EDIT1L,
  _EDIT2R,
  _EDIT2L,
  _NUMBER,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define _____   KC_TRNS
#define XXXXX   KC_NO
#define KFUNC   TD(FUNC)
#define SFTSPC  SFT_T(KC_SPC)
#define ALTENT  ALT_T(KC_ENT)
#define ALTSPC  ALT_T(KC_SPC)
#define ALTBS   ALT_T(KC_BSPC)
#define CMDSPC  CMD_T(KC_SPC)
#define CMDBSP  CMD_T(KC_BSPC)
#define CTLENT  CTL_T(KC_ENT)
#define CTLSPC  CTL_T(KC_SPC)
#define CTLBSP  CTL_T(KC_BSPC)
#define CMDENT  CMD_T(KC_ENT)
#define CTLBS   CTL_T(KC_BSPC)
#define LSHFT LM(_SHIFT,MOD_LSFT)
// 薙刀式
// 編集モードを追加する場合
#define KC(A) C(KC_##A)
#define KS(A) S(KC_##A)
#define KG(A) G(KC_##A)
#define KA(B) A(KC_##B)
// 薙刀式

// 薙刀式
enum combo_events {
  NAGINATA_ON_CMB,
  NAGINATA_OFF_CMB,
  LOGIN_CMB,
  EDITR1_CMB,
  EDITL1_CMB,
  EDITR2_CMB,
  EDITL2_CMB,
  ENTER_CMB,
};

#if defined(DEUCALYN)
const uint16_t PROGMEM ngon_combo[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_I, KC_U, COMBO_END};
const uint16_t PROGMEM editr1_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM editl1_combo[] = {KC_T, KC_K, COMBO_END};
const uint16_t PROGMEM editr2_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM editl2_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_V, KC_H, COMBO_END};
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_W, KC_M, COMBO_END};
#endif
#if defined(DWORKMAN)
const uint16_t PROGMEM ngon_combo[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM editr1_combo[] = {KC_H, KC_T, COMBO_END};
const uint16_t PROGMEM editl1_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM editr2_combo[] = {KC_M, KC_C, COMBO_END};
const uint16_t PROGMEM editl2_combo[] = {KC_L, KC_COMM, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_C, KC_L, COMBO_END};
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_D, KC_R, COMBO_END};
#endif
#if defined(DQGMLWY)
const uint16_t PROGMEM ngon_combo[] = {KC_I, KC_A, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_N, KC_R, COMBO_END};
const uint16_t PROGMEM editr1_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM editl1_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM editr2_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM editl2_combo[] = {KC_H, KC_P, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_V, KC_H, COMBO_END};
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_G, KC_M, COMBO_END};
#endif

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB] = COMBO_ACTION(ngon_combo),
  [NAGINATA_OFF_CMB] = COMBO_ACTION(ngoff_combo),
  [LOGIN_CMB] = COMBO_ACTION(login_combo),
  [EDITR1_CMB] = COMBO_ACTION(editr1_combo),
  [EDITL1_CMB] = COMBO_ACTION(editl1_combo),
  [EDITR2_CMB] = COMBO_ACTION(editr2_combo),
  [EDITL2_CMB] = COMBO_ACTION(editl2_combo),
  [ENTER_CMB] = COMBO(enter_combo, KC_ENT),
};
// 薙刀式

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* _WORKMAN
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  D   |  R   |  W   |  B   |      |      |  J   |  F   |  U   |  P   |  ;   | BSPC |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  A   |  S   |  H   |  T   |  G   |      |      |  Y   |  N   |  E   |  O   |  I   | ENT  |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ALPH |  Z   |  X   |  M   |  C   |  V   |      |      |  K   |  L   |  ,   |  .   |  /   |SALPH |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | LCTL |      |      |      |LOWER |SFTSPC| LCTL |CMDENT|SFTSPC|RAISE |      |      |      | RALT |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_WORKMAN] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_D   ,KC_R   ,KC_W   ,KC_B   ,XXXXXXX,XXXXXXX,KC_J   ,KC_F   ,KC_U   ,KC_P   ,JP_SCLN,KC_BSPC, \
    KC_TAB ,KC_A   ,KC_S   ,KC_H   ,KC_T   ,KC_G   ,XXXXXXX,XXXXXXX,KC_Y   ,KC_N   ,KC_E   ,KC_O   ,KC_I   ,KC_ENT , \
    ALPH   ,KC_Z   ,KC_X   ,KC_M   ,KC_C   ,KC_V   ,XXXXXXX,XXXXXXX,KC_K   ,KC_L   ,JP_COMM,JP_DOT ,JP_SLSH,SALPH  , \
    KC_LCTL,XXXXXXX,XXXXXXX,XXXXXXX,LOWER  ,SFTSPC ,KC_LCTL,CMDENT ,SFTSPC ,RAISE  ,XXXXXXX,XXXXXXX,XXXXXXX,KC_RALT
  ),

/* _EDIT1L
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Q) |G(W) |G(N) | F2  |     |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Y) |G(S) |PGDN |PGUP |     |     |     | __  | __  |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Z) |G(X) |G(C) |G(V) |     |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT1L] = LAYOUT(
    XXXXXXX,G(KC_Q),G(KC_W),G(KC_N),KC_F2  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,G(KC_Y),G(KC_S),KC_PGDN,KC_PGUP,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,G(KC_Z),G(KC_X),G(KC_C),G(KC_V),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EDIT1R
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |       | DELE  |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |  __   |  __   |       |       |G(LEFT)| LEFT  |S(LEFT)|  UP   |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |G(RGHT)| RGHT  |S(RGHT)| DOWN  |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_EDIT1R] = LAYOUT(
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,DELE      ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   ,_______   ,XXXXXXX   ,XXXXXXX   ,G(KC_LEFT),KC_LEFT   ,S(KC_LEFT),KC_UP     ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,G(KC_RGHT),KC_RGHT   ,S(KC_RGHT),KC_DOWN   ,XXXXXXX   ,XXXXXXX   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _EDIT2L
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |  ~  |  @  |  #  |  $  |  %  |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |  ^  |  &  |  !  |  ?  |  ¥  |     |     | __  | __  |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |  |  |  `  |  '  |  "  |  _  |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT2L] = LAYOUT(
    XXXXXXX,JP_TILD,JP_AT  ,JP_HASH,JP_DLR ,JP_PERC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,JP_CIRC,JP_AMPR,JP_EXLM,JP_QUES,JP_YEN ,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,JP_PIPE,JP_GRV ,JP_QUOT,JP_DQUO ,JP_UNDS,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EDIT2R
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |     |DELA |  +  |  -  |  =  |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     | __  | __  |     |     |  :  |  (  |  [  |  {  |  <  |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |  ;  |  )  |  ]  |  }  |  >  |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT2R] = LAYOUT(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,DELA   ,JP_PLUS,JP_MINS,JP_EQL ,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,JP_COLN,JP_LPRN,JP_LBRC,JP_LCBR,KC_LT  ,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,JP_SCLN,JP_RPRN,JP_RBRC,JP_RCBR,KC_GT  ,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _LOWER
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     | UP  |     |     |     |     |  /  |  7  |  8  |  9  |  -  |BSPC |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |LEFT |DOWN |RGHT |     |     |     |  *  |  4  |  5  |  6  |  +  |  .  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |  0  |  1  |  2  |  3  |  =  |  ,  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  |KANA2| __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_LOWER] = LAYOUT(
    XXXXXXX,XXXXXXX,XXXXXXX,KC_UP  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,JP_SLSH,KC_7   ,KC_8   ,KC_9   ,JP_MINS,KC_BSPC, \
    XXXXXXX,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT,XXXXXXX,XXXXXXX,XXXXXXX,JP_ASTR,KC_4   ,KC_5   ,KC_6   ,JP_PLUS,JP_DOT , \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_0   ,KC_1   ,KC_2   ,KC_3   ,JP_EQL ,JP_COMM, \
    _______,_______,_______,_______,_______,_______,_______,_______,KANA2  ,_______,_______,_______,_______,_______
  ),

/* _RAISE
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |   ~   |   @   |   #   |   $   |   %   |       |       |       |       |  UP   |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |   ^   |   &   |   !   |   ?   |   ¥   |       |       | HOME  | LEFT  | DOWN  | RGHT  | PGUP  |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |   |   |   `   |   '   |   "   |   _   |       |       |  END  |S(LEFT)|       |S(RGHT)| PGDN  |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   | EISU  |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_RAISE] = LAYOUT(
    XXXXXXX   ,JP_TILD   ,JP_AT     ,JP_HASH   ,JP_DLR    ,JP_PERC   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,KC_UP     ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,JP_CIRC   ,JP_AMPR   ,JP_EXLM   ,JP_QUES   ,JP_YEN    ,XXXXXXX   ,XXXXXXX   ,KC_HOME   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,KC_PGUP   ,XXXXXXX   , \
    XXXXXXX   ,JP_PIPE   ,JP_GRV    ,JP_QUOT   ,JP_DQUO    ,JP_UNDS   ,XXXXXXX   ,XXXXXXX   ,KC_END    ,S(KC_LEFT),XXXXXXX   ,S(KC_RGHT),KC_PGDN   ,XXXXXXX   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,EISU      ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _ADJUST
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |EEP_RST|       |       |       |       | WAKE  |       |       |       |       |       |       |       |EUCALYN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       | SLEP  |       |       | RESET |       |       |       |       |       |       |       |WORKMAN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  XX   |       |       |       |       |       |       |       |       |       |  PWR  |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |QGMLWY |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_ADJUST] = LAYOUT(
    EEP_RST,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_WAKE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,EUCALYN, \
    XXXXXXX,XXXXXXX,KC_SLEP,XXXXXXX,XXXXXXX,RESET  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,WORKMAN, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_PWR ,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,QGMLWY
  ),

/* _EUCALYN
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  W   |  ,   |  .   |  ;   |      |      |  M   |  R   |  D   |  Y   |  P   |  `   |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  A   |  O   |  E   |  I   |  U   |      |      |  G   |  T   |  K   |  S   |  N   |  '   |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ALPH |  Z   |  X   |  C   |  V   |  F   |      |      |  B   |  H   |  J   |  L   |  /   |SALPH |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | LCTL |      |      |      |LOWER |SFTSPC|CMDBSP|CMDENT|SFTSPC|RAISE |      |      |      | RALT |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_EUCALYN] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_W   ,JP_COMM,JP_DOT ,JP_SCLN,XXXXXXX,XXXXXXX,KC_M   ,KC_R   ,KC_D   ,KC_Y   ,KC_P   ,JP_GRV , \
    KC_TAB ,KC_A   ,KC_O   ,KC_E   ,KC_I   ,KC_U   ,XXXXXXX,XXXXXXX,KC_G   ,KC_T   ,KC_K   ,KC_S   ,KC_N   ,JP_QUOT, \
    ALPH   ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_F   ,XXXXXXX,XXXXXXX,KC_B   ,KC_H   ,KC_J   ,KC_L   ,JP_SLSH,SALPH  , \
    KC_LCTL,XXXXXXX,XXXXXXX,XXXXXXX,LOWER  ,SFTSPC ,CMDBSP ,CMDENT ,SFTSPC ,RAISE  ,XXXXXXX,XXXXXXX,XXXXXXX,KC_RALT
  ),

/* _NAGINATA
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_Q  | NG_W  | NG_E  | NG_R  | NG_T  |       |       | NG_Y  | NG_U  | NG_I  | NG_O  | NG_P  |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_A  | NG_S  | NG_D  | NG_F  | NG_G  |       |       | NG_H  | NG_J  | NG_K  | NG_L  |NG_SCLN|  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  | ALPH  | NG_Z  | NG_X  | NG_C  | NG_V  | NG_B  |       |       | NG_N  | NG_M  |NG_COMM|NG_DOT |NG_SLSH| SALPH |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |NG_SHFT|  __   |  __   |NG_SHFT|  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_NAGINATA] = LAYOUT(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,XXXXXXX,XXXXXXX,NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,XXXXXXX,XXXXXXX,NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    ALPH   ,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,XXXXXXX,XXXXXXX,NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,SALPH  , \
    _______,_______,_______,_______,_______,NG_SHFT,_______,_______,NG_SHFT,_______,_______,_______,_______,_______
  ),

/* _QGMLWY
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
  |       ESC       |        Q        |        G        |        M        |        L        |        W        |                 |                 |        Y        |        F        |        U        |        B        |        ,        |      BSPC       |
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
  |       TAB       |        D        |        S        |        T        |        N        |        R        |                 |                 |        I        |        A        |        E        |        O        |        '        |       ENT       |
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
  |      ALPH       |        Z        |        X        |        C        |        V        |        J        |                 |                 |        K        |        H        |        P        |        .        |        ?        |      SALPH      |
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
  |      LCTL       |                 |                 |                 |      LOWER      |LT(_SHIFT,KC_SPC)|      LCTL       |     CMDENT      |LT(_SHIFT,KC_SPC)|      RAISE      |                 |                 |                 |      RALT       |
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
*/
  [_QGMLWY] = LAYOUT(
    KC_ESC           ,KC_Q             ,KC_G             ,KC_M             ,KC_L             ,KC_W             ,XXXXXXX          ,XXXXXXX          ,KC_Y             ,KC_F             ,KC_U             ,KC_B             ,JP_COMM          ,KC_BSPC          , \
    KC_TAB           ,KC_D             ,KC_S             ,KC_T             ,KC_N             ,KC_R             ,XXXXXXX          ,XXXXXXX          ,KC_I             ,KC_A             ,KC_E             ,KC_O             ,JP_QUOT          ,KC_ENT           , \
    ALPH             ,KC_Z             ,KC_X             ,KC_C             ,KC_V             ,KC_J             ,XXXXXXX          ,XXXXXXX          ,KC_K             ,KC_H             ,KC_P             ,JP_DOT           ,JP_QUES          ,SALPH            , \
    KC_LCTL          ,XXXXXXX          ,XXXXXXX          ,XXXXXXX          ,LOWER            ,LT(_SHIFT,KC_SPC),KC_LCTL          ,CMDENT           ,LT(_SHIFT,KC_SPC),RAISE            ,XXXXXXX          ,XXXXXXX          ,XXXXXXX          ,KC_RALT
  ),

/* _SHIFT
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  |S(Q) |S(G) |S(M) |S(L) |S(W) |     |     |S(Y) |S(F) |S(U) |S(B) |  %  | DEL |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  |S(D) |S(S) |S(T) |S(N) |S(R) |     |     |S(I) |S(A) |S(E) |S(O) |  "  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  |S(Z) |S(X) |S(C) |S(V) |S(J) |     |     |S(K) |S(H) |S(P) |  &  |  !  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  |     |     |     | __  | __  | __  | __  | __  | __  |     |     |     | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_SHIFT] = LAYOUT(
    _______,S(KC_Q),S(KC_G),S(KC_M),S(KC_L),S(KC_W),XXXXXXX,XXXXXXX,S(KC_Y),S(KC_F),S(KC_U),S(KC_B),JP_PERC,KC_DEL , \
    _______,S(KC_D),S(KC_S),S(KC_T),S(KC_N),S(KC_R),XXXXXXX,XXXXXXX,S(KC_I),S(KC_A),S(KC_E),S(KC_O),JP_DQUO ,_______, \
    _______,S(KC_Z),S(KC_X),S(KC_C),S(KC_V),S(KC_J),XXXXXXX,XXXXXXX,S(KC_K),S(KC_H),S(KC_P),JP_AMPR,JP_EXLM,_______, \
    _______,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,_______,_______,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,_______
  ),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

static bool num_toggle = false;
static bool nstate = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // tap=toggle layer, hold=momentally layer on
  if (keycode == NUMBER) {
    if (record->event.pressed) {
      num_toggle = true;
      layer_invert(_NUMBER);
    } else {
      if (layer_state_is(_NUMBER) && num_toggle == false) {
        layer_invert(_NUMBER);
      }
    }
    return false;
  } else {
    num_toggle = false;
  }

  switch (keycode) {
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        naginata_on();
      }
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        naginata_off();
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYN);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case QGMLWY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QGMLWY);
      }
      return false;
      break;
    case EURO:
      if (record->event.pressed) {
        send_string("(e)");
        return false;
      }
      break;
    case SSCLN:
      if (record->event.pressed) {
        unregister_code(KC_LSFT);
        tap_code(KC_SCLN);
        return false;
      }
      break;
    case SEQL:
      if (record->event.pressed) {
        unregister_code(KC_LSFT);
        tap_code(KC_EQL);
        return false;
      }
      break;
    case DELA:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        tap_code(KC_HOME);
        unregister_code(KC_LSFT);
        register_code(KC_LCTRL);
        tap_code(KC_X);
        unregister_code(KC_LCTRL);
        return false;
      }
      break;
    case DELE:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        register_code(KC_LCTRL);
        tap_code(KC_X);
        unregister_code(KC_LCTRL);
      }
      break;
    case ALPH:
      if (record->event.pressed) {
        nstate = naginata_state();
        if (nstate) naginata_off();
      } else {
        if (nstate) naginata_on();
      }
      break;
    case SALPH:
      if (record->event.pressed) {
        nstate = naginata_state();
        if (nstate) naginata_off();
        register_code(KC_LSFT);
      } else {
        unregister_code(KC_LSFT);
        if (nstate) naginata_on();
      }
      break;
    }

  // 薙刀式
  bool a = true;
  if (naginata_state()) {
    naginata_mode(keycode, record);
    a = process_naginata(keycode, record);
    if (a == false) return false;
  }
  // 薙刀式

  return true;
}

// 薙刀式
// IME ONのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NAGINATA_ON_CMB:
      if (pressed) {
        naginata_on();
      }
      break;
    case NAGINATA_OFF_CMB:
      if (pressed) {
        naginata_off();
      }
      break;
    case LOGIN_CMB:
      if (pressed && !naginata_state()) {
        register_code (KC_LCTRL);
        register_code (KC_LALT);
        register_code (KC_DEL);
        unregister_code (KC_DEL);
        unregister_code (KC_LALT);
        unregister_code (KC_LCTRL);
      }
      break;
    case EDITR1_CMB:
      if (pressed) {
        layer_on(_EDIT1R);
      } else {
        layer_off(_EDIT1R);
      }
      break;
    case EDITL1_CMB:
      if (pressed) {
        layer_on(_EDIT1L);
      } else {
        layer_off(_EDIT1L);
      }
      break;
    case EDITR2_CMB:
      if (pressed) {
        layer_on(_EDIT2R);
      } else {
        layer_off(_EDIT2R);
      }
      break;
    case EDITL2_CMB:
      if (pressed) {
        layer_on(_EDIT2L);
      } else {
        layer_off(_EDIT2L);
      }
      break;

  }
}
// 薙刀式

void matrix_init_user(void) {
  // 薙刀式
  set_naginata(_NAGINATA);
  set_unicode_input_mode(UC_OSX);
  // set_unicode_input_mode(UC_WINC);
  // 薙刀式
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
