/* Copyright 2019 eswai
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
//#include"keymap_jp.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  EUCALYN,
  WORKMAN,
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
#define CTLENT  CTL_T(KC_ENT)
#define CTLSPC  CTL_T(KC_SPC)
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
#endif
#if defined(DWORKMAN)
const uint16_t PROGMEM ngon_combo[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM editr1_combo[] = {KC_H, KC_T, COMBO_END};
const uint16_t PROGMEM editl1_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM editr2_combo[] = {KC_M, KC_C, COMBO_END};
const uint16_t PROGMEM editl2_combo[] = {KC_L, KC_COMM, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_C, KC_L, COMBO_END};
#endif
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_D, KC_R, COMBO_END};

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
/* _EUCALYN
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |ESC   |Q     |W     |M     |R     |,     |      |      |.     |BSPC  |D     |Y     |P     |      |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |TAB   |A     |O     |E     |I     |U     |      |      |G     |T     |K     |S     |N     |;     |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |ALPH  |Z     |X     |C     |V     |F     |      |      |B     |H     |J     |L     |/     |SALPH |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |LCMD  |      |      |      |LOWER |LSFT  |CTLSPC|ALTENT|RSFT  |RAISE |      |      |      |RCMD  |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_EUCALYN] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_W   ,KC_M   ,KC_R   ,KC_COMM,XXXXXXX,XXXXXXX,KC_DOT ,KC_BSPC,KC_D   ,KC_Y   ,KC_P   ,XXXXXXX, \
    KC_TAB ,KC_A   ,KC_O   ,KC_E   ,KC_I   ,KC_U   ,XXXXXXX,XXXXXXX,KC_G   ,KC_T   ,KC_K   ,KC_S   ,KC_N   ,KC_SCLN, \
    ALPH   ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_F   ,XXXXXXX,XXXXXXX,KC_B   ,KC_H   ,KC_J   ,KC_L   ,KC_SLSH,SALPH  , \
    KC_LCMD,XXXXXXX,XXXXXXX,XXXXXXX,LOWER  ,KC_LSFT,CTLSPC ,ALTENT ,KC_RSFT,RAISE  ,XXXXXXX,XXXXXXX,XXXXXXX,KC_RCMD
  ),

/* _WORKMAN
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |ESC   |Q     |D     |R     |W     |B     |      |      |J     |BSPC  |U     |P     |F     |      |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |TAB   |A     |S     |H     |T     |G     |      |      |Y     |N     |E     |O     |I     |;     |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |ALPH  |Z     |X     |M     |C     |V     |      |      |K     |L     |,     |.     |/     |SALPH |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |LCMD  |      |      |      |LOWER |LSFT  |CTLSPC|ALTENT|RSFT  |RAISE |      |      |      |RCMD  |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_WORKMAN] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_D   ,KC_R   ,KC_W   ,KC_B   ,XXXXXXX,XXXXXXX,KC_J   ,KC_BSPC,KC_U   ,KC_P   ,KC_F   ,XXXXXXX, \
    KC_TAB ,KC_A   ,KC_S   ,KC_H   ,KC_T   ,KC_G   ,XXXXXXX,XXXXXXX,KC_Y   ,KC_N   ,KC_E   ,KC_O   ,KC_I   ,KC_SCLN, \
    ALPH   ,KC_Z   ,KC_X   ,KC_M   ,KC_C   ,KC_V   ,XXXXXXX,XXXXXXX,KC_K   ,KC_L   ,KC_COMM,KC_DOT ,KC_SLSH,SALPH  , \
    KC_LCMD,XXXXXXX,XXXXXXX,XXXXXXX,LOWER  ,KC_LSFT,CTLSPC ,ALTENT ,KC_RSFT,RAISE  ,XXXXXXX,XXXXXXX,XXXXXXX,KC_RCMD
  ),

/* _NAGINATA
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |__     |NG_Q   |NG_W   |NG_E   |NG_R   |NG_T   |       |       |NG_Y   |NG_U   |NG_I   |NG_O   |NG_P   |__     |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |__     |NG_A   |NG_S   |NG_D   |NG_F   |NG_G   |       |       |NG_H   |NG_J   |NG_K   |NG_L   |NG_SCLN|__     |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |ALPH   |NG_Z   |NG_X   |NG_C   |NG_V   |NG_B   |       |       |NG_N   |NG_M   |NG_COMM|NG_DOT |NG_SLSH|SALPH  |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |__     |__     |__     |__     |__     |NG_SHFT|__     |__     |NG_SHFT|__     |__     |__     |__     |__     |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_NAGINATA] = LAYOUT(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,XXXXXXX,XXXXXXX,NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,XXXXXXX,XXXXXXX,NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    ALPH   ,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,XXXXXXX,XXXXXXX,NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,SALPH  , \
    _______,_______,_______,_______,_______,NG_SHFT,_______,_______,NG_SHFT,_______,_______,_______,_______,_______
  ),

/* _EDIT1L
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Q) |G(W) |G(N) |     |     |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Y) |G(S) |PGDN |PGUP |     |     |     |__   |__   |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |G(Z) |G(X) |G(C) |G(V) |     |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT1L] = LAYOUT(
    XXXXXXX,G(KC_Q),G(KC_W),G(KC_N),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,G(KC_Y),G(KC_S),KC_PGDN,KC_PGUP,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,G(KC_Z),G(KC_X),G(KC_C),G(KC_V),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EDIT1R
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |       |DELE   |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |__     |__     |       |       |G(LEFT)|LEFT   |S(LEFT)|LEFT   |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |G(RGHT)|RGHT   |S(RGHT)|RGHT   |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_EDIT1R] = LAYOUT(
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,DELE      ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   ,_______   ,XXXXXXX   ,XXXXXXX   ,G(KC_LEFT),KC_LEFT   ,S(KC_LEFT),KC_LEFT   ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,G(KC_RGHT),KC_RGHT   ,S(KC_RGHT),KC_RGHT   ,XXXXXXX   ,XXXXXXX   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _EDIT2L
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |!    |@    |#    |$    |%    |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |\    |^    |&    |!    |?    |~    |     |     |__   |__   |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     ||    |`    |'    |"    |_    |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT2L] = LAYOUT(
    XXXXXXX,KC_EXLM,KC_AT  ,KC_HASH,KC_DLR ,KC_PERC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    KC_BSLS,KC_CIRC,KC_AMPR,KC_EXLM,KC_QUES,KC_TILD,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,KC_PIPE,KC_GRV ,KC_QUOT,KC_DQT ,KC_UNDS,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EDIT2R
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |     |DELA |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |__   |__   |     |     |     |(    |[    |{    |<    |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |     |)    |]    |}    |>    |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |__   |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT2R] = LAYOUT(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,DELA   ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,KC_LPRN,KC_LBRC,KC_LCBR,KC_LT  ,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_RPRN,KC_RBRC,KC_RCBR,KC_GT  ,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _LOWERWER
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |UP   |     |     |     |/    |7    |8    |9    |-    |:    |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |LEFT |DOWN |RGHT |     |     |*    |4    |5    |6    |+    |.    |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |0    |1    |2    |3    |=    |,    |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |__   |__   |__   |__   |__   |EISU |__   |__   |__   |__   |__   |__   |__   |__   |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_LOWER] = LAYOUT(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_UP  ,XXXXXXX,XXXXXXX,XXXXXXX,KC_SLSH,KC_7   ,KC_8   ,KC_9   ,KC_MINS,KC_COLN, \
    XXXXXXX,XXXXXXX,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT,XXXXXXX,XXXXXXX,KC_ASTR,KC_4   ,KC_5   ,KC_6   ,KC_PLUS,KC_DOT , \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_0   ,KC_1   ,KC_2   ,KC_3   ,KC_EQL ,KC_COMM, \
    _______,_______,_______,_______,_______,EISU   ,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _RAISE
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |       |       |UP     |       |       |PGUP   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |       |LEFT   |DOWN   |RGHT   |       |PGDN   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |       |S(LEFT)|       |S(RGHT)|       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |__     |__     |__     |__     |__     |__     |__     |__     |KANA   |__     |__     |__     |__     |__     |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_RAISE] = LAYOUT(
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,KC_UP     ,XXXXXXX   ,XXXXXXX   ,KC_PGUP   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,XXXXXXX   ,KC_PGDN   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,S(KC_LEFT),XXXXXXX   ,S(KC_RGHT),XXXXXXX   ,XXXXXXX   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,KC_KANA   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _ADJUST
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |KC_WAKE|       |RESET  |       |       |       |       |       |       |       |KC_PWR |EUCALYN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |EEP_RST|       |       |       |       |       |       |       |       |WORKMAN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |KC_SLEP|KC_CALC|       |       |       |       |       |       |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |__     |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_ADJUST] = LAYOUT(
    XXXXXXX,XXXXXXX,KC_WAKE,XXXXXXX,RESET  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_PWR ,EUCALYN, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,EEP_RST,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,WORKMAN, \
    XXXXXXX,XXXXXXX,KC_SLEP,KC_CALC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

};

void update_led(void);

void update_led() {
  rgblight_set_effect_range(56, 15);

  if (!layer_state_is(_NUMBER) && !layer_state_is(_LOWER) && !layer_state_is(_RAISE) && !layer_state_is(_NUMBER)) {
    rgblight_sethsv_range(0, 0, 0, 0, 56);
  }
  if (naginata_state()) {
    rgblight_sethsv_at(150, 200, 255, 0);
    rgblight_sethsv_at(150, 200, 200, 17);
    rgblight_sethsv_at(150, 200, 200, 38);
    rgblight_sethsv_at(150, 200, 200, 20);
    rgblight_sethsv_at(150, 200, 200, 35);
    // rgblight_setrgb_range(10, 10, 10, 56, 71);
  } else {
    rgblight_sethsv_at(50, 200, 0, 0);
    rgblight_sethsv_at(150, 200, 0, 17);
    rgblight_sethsv_at(150, 200, 0, 38);
  }
  if (layer_state_is(_NUMBER)) {
    rgblight_sethsv_at(240, 200, 255, 0);
    rgblight_sethsv_at(150, 200, 200, 4);
    rgblight_sethsv_range(150, 200, 200, 40, 43);
    rgblight_sethsv_range(150, 200, 200, 45, 51);
    rgblight_sethsv_at(150, 200, 200, 9);
    rgblight_sethsv_at(150, 200, 200, 14);
    rgblight_sethsv_at(150, 200, 200, 15);
    rgblight_sethsv_at(150, 200, 200, 17);
  }
  if (layer_state_is(_LOWER)) {
    // rgblight_sethsv_at(240, 100, 200, 19);
    rgblight_sethsv_range(240, 200, 200, 40, 43);
    rgblight_sethsv_range(240, 200, 200, 45, 51);
  }
  if (layer_state_is(_RAISE)) {
    // rgblight_sethsv_at(100, 100, 200, 36);
    rgblight_sethsv_at(100, 200, 200, 38);
    rgblight_sethsv_at(100, 200, 200, 40);
    rgblight_sethsv_at(100, 200, 200, 41);
    rgblight_sethsv_at(100, 200, 200, 46);
  }
}


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
    case RGBRST:
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
      }
      update_led();
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      update_led();
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
      update_led();
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
      update_led();
      return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        naginata_on();
      }
      update_led();
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        naginata_off();
      }
      update_led();
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
    update_led();
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
  // 薙刀式
  set_unicode_input_mode(UC_OSX);
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
