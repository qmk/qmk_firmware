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
#include "keymap_japanese.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  EUCALYN,
  WORKMAN,
  QGMLWB,
  QGMLWY,
  RAISE, LOWER, ADJUST,
  RGBRST,
  NUMLOC,
  EISU,
  KANA2,
  SSCLN,
  DELA,
  DELE,
  ALPH,
  SALPH,
};

// Layers
enum kepmap_layers {
  _WORKMAN,
  _QGMLWY,
  _QGMLWB,
  _EUCALYN,
  _SHIFT,
// 薙刀式
  _NAGINATA,
// 薙刀式
  _EDIT1R,
  _EDIT1L,
  _EDIT2R,
  _EDIT2L,
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
#define CTLBSP  CTL_T(KC_BSPC)
#define CMDENT  CMD_T(KC_ENT)
#define CTLBS   CTL_T(KC_BSPC)
#define LSHFT LM(_SHIFT,MOD_LSFT)
// 薙刀式
// 編集モードを追加する場合
#define KC(A) C(KC_##A)
#define KS(A) S(KC_##A)
#define KG(A) G(KC_##A)
// 薙刀式

#define DEG   UC(0x00B0)
#define DELTA UC(0x0394)
#define NTEQ  UC(0x2260)
#define NREQ  UC(0x2260)
#define MICRO UC(0x00B5)
#define EURO  UC(0x20AC)
#define LTE   UC(0x2264)
#define GTE   UC(0x2265)

// 薙刀式
enum combo_events {
  NAGINATA_ON_CMB,
  NAGINATA_OFF_CMB,
  LOGIN_CMB,
  EDIT1R_CMB,
  EDIT1L_CMB,
  EDIT2R_CMB,
  EDIT2L_CMB,
  ENTER_CMB,
};

#if defined(DEUCALYN)
const uint16_t PROGMEM ngon_combo[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_I, KC_U, COMBO_END};
const uint16_t PROGMEM edit1r_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM edit1l_combo[] = {KC_T, KC_K, COMBO_END};
const uint16_t PROGMEM edit2r_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM edit2l_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_V, KC_H, COMBO_END};
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_W, KC_M, COMBO_END};
#endif
#if defined(DWORKMAN)
const uint16_t PROGMEM ngon_combo[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM edit1r_combo[] = {KC_H, KC_T, COMBO_END};
const uint16_t PROGMEM edit1l_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM edit2r_combo[] = {KC_M, KC_C, COMBO_END};
const uint16_t PROGMEM edit2l_combo[] = {KC_L, KC_COMM, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_C, KC_L, COMBO_END};
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_D, KC_R, COMBO_END};
#endif
#if defined(DQGMLWB)
const uint16_t PROGMEM ngon_combo[] = {KC_I, KC_A, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_N, KC_R, COMBO_END};
const uint16_t PROGMEM edit1r_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM edit1l_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM edit2r_combo[] = {KC_C, KC_F, COMBO_END};
const uint16_t PROGMEM edit2l_combo[] = {KC_P, KC_COMM, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_G, KC_M, COMBO_END};
#endif
#if defined(DQGMLWY)
const uint16_t PROGMEM ngon_combo[] = {KC_I, KC_A, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_N, KC_R, COMBO_END};
const uint16_t PROGMEM edit1r_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM edit1l_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM edit2r_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM edit2l_combo[] = {KC_H, KC_P, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_V, KC_H, COMBO_END};
const uint16_t PROGMEM login_combo[] = {KC_Q, KC_G, KC_M, COMBO_END};
#endif

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB] = COMBO_ACTION(ngon_combo),
  [NAGINATA_OFF_CMB] = COMBO_ACTION(ngoff_combo),
  [LOGIN_CMB] = COMBO_ACTION(login_combo),
  [EDIT1R_CMB] = COMBO_ACTION(edit1r_combo),
  [EDIT1L_CMB] = COMBO_ACTION(edit1l_combo),
  [EDIT2R_CMB] = COMBO_ACTION(edit2r_combo),
  [EDIT2L_CMB] = COMBO_ACTION(edit2l_combo),
  [ENTER_CMB] = COMBO(enter_combo, KC_ENT),
};
// 薙刀式

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* _QGMLWY
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
  |       ESC       |        Q        |        G        |        M        |        L        |        W        |      C(S)       |       DEL       |        Y        |        F        |        U        |        B        |        ,        |      BSPC       |
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
  |       TAB       |        D        |        S        |        T        |        N        |        R        |        (        |        )        |        I        |        A        |        E        |        O        |        '        |       ENT       |
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
  |      ALPH       |        Z        |        X        |        C        |        V        |        J        |        -        |        +        |        K        |        H        |        P        |        .        |        ?        |      SALPH      |
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
  |      LCTL       |     NUMLOC      |       F2        |      LSHFT      |      LOWER      |LT(_SHIFT,KC_SPC)|      LCTL       |       ENT       |LT(_SHIFT,KC_SPC)|      RAISE      |        0        |        .        |      LALT       |      RCTL       |
  +-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
*/
  [_QGMLWY] = LAYOUT(
    KC_ESC           ,KC_Q             ,KC_G             ,KC_M             ,KC_L             ,KC_W             ,C(KC_S)          ,KC_DEL           ,KC_Y             ,KC_F             ,KC_U             ,KC_B             ,JP_COMM          ,KC_BSPC          , \
    KC_TAB           ,KC_D             ,KC_S             ,KC_T             ,KC_N             ,KC_R             ,JP_LPRN          ,JP_RPRN          ,KC_I             ,KC_A             ,KC_E             ,KC_O             ,JP_QUOT          ,KC_ENT           , \
    ALPH             ,KC_Z             ,KC_X             ,KC_C             ,KC_V             ,KC_J             ,JP_MINS          ,JP_PLUS          ,KC_K             ,KC_H             ,KC_P             ,JP_DOT           ,JP_QUES          ,SALPH            , \
    KC_LCTL          ,NUMLOC           ,KC_F2            ,LSHFT            ,LOWER            ,LT(_SHIFT,KC_SPC),KC_LCTL          ,KC_ENT           ,LT(_SHIFT,KC_SPC),RAISE            ,KC_0             ,JP_DOT           ,KC_LALT          ,KC_RCTL
  ),

/* _SHIFT
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  |S(Q) |S(G) |S(M) |S(L) |S(W) | __  | __  |S(Y) |S(F) |S(U) |S(B) |  %  | DEL |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  |S(D) |S(S) |S(T) |S(N) |S(R) |  <  |  >  |S(I) |S(A) |S(E) |S(O) |  "  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  |S(Z) |S(X) |S(C) |S(V) |S(J) |  /  |  *  |S(K) |S(H) |S(P) |  &  |  /  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_SHIFT] = LAYOUT(
    _______,S(KC_Q),S(KC_G),S(KC_M),S(KC_L),S(KC_W),_______,_______,S(KC_Y),S(KC_F),S(KC_U),S(KC_B),JP_PERC,KC_DEL , \
    _______,S(KC_D),S(KC_S),S(KC_T),S(KC_N),S(KC_R),KC_LT  ,KC_GT  ,S(KC_I),S(KC_A),S(KC_E),S(KC_O),JP_DQUO ,_______, \
    _______,S(KC_Z),S(KC_X),S(KC_C),S(KC_V),S(KC_J),JP_SLSH,JP_ASTR,S(KC_K),S(KC_H),S(KC_P),JP_AMPR,JP_SLSH,_______, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _LOWER
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |  /  |  7  |  8  |  9  |  -  |BSPC |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |DELTA|  <  |  {  |  [  |  (  |  :  |  [  |  ]  |  *  |  4  |  5  |  6  |  +  |  .  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |NTEQ |  >  |  }  |  ]  |  )  |  ;  |  -  |  +  |  0  |  1  |  2  |  3  |  =  |  ,  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  |KANA2| __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_LOWER] = LAYOUT(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,JP_SLSH,KC_7   ,KC_8   ,KC_9   ,JP_MINS,KC_BSPC, \
    DELTA  ,KC_LT  ,JP_LCBR,JP_LBRC,JP_LPRN,JP_COLN,JP_LBRC,JP_RBRC,JP_ASTR,KC_4   ,KC_5   ,KC_6   ,JP_PLUS,JP_DOT , \
    NTEQ   ,KC_GT  ,JP_RCBR,JP_RBRC,JP_RPRN,JP_SCLN,JP_MINS,JP_PLUS,KC_0   ,KC_1   ,KC_2   ,KC_3   ,JP_EQL ,JP_COMM, \
    _______,_______,_______,_______,_______,_______,_______,_______,KANA2  ,_______,_______,_______,_______,_______
  ),

/* _RAISE
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  | MICRO |   ~   |   @   |   #   |   $   |   %   |       |       | HOME  | S(UP) |  UP   |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  DEG  |   ^   |   &   |   !   |   ?   |   ¥   |   {   |   }   |  END  | LEFT  | DOWN  | RGHT  | PGUP  |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  | EURO  |   |   |   `   |   '   |   "   |   _   |       |       |       |S(LEFT)|S(DOWN)|S(RGHT)| PGDN  |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   | EISU  |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_RAISE] = LAYOUT(
    MICRO     ,JP_TILD   ,JP_AT     ,JP_HASH   ,JP_DLR    ,JP_PERC   ,XXXXXXX   ,XXXXXXX   ,KC_HOME   ,S(KC_UP)  ,KC_UP     ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   , \
    DEG       ,JP_CIRC   ,JP_AMPR   ,JP_EXLM   ,JP_QUES   ,JP_YEN    ,JP_LCBR   ,JP_RCBR   ,KC_END    ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,KC_PGUP   ,XXXXXXX   , \
    EURO      ,JP_PIPE   ,JP_GRV    ,JP_QUOT   ,JP_DQUO    ,JP_UNDS   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,S(KC_LEFT),S(KC_DOWN),S(KC_RGHT),KC_PGDN   ,XXXXXXX   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,EISU      ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _ADJUST
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |EEP_RST|       |       | MAIL  |       | WAKE  |       |       |       |       |       |       |       |EUCALYN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       | SLEP  |       |       | RESET |       |       |       |       | MYCM  |       |       |WORKMAN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       | CALC  |       |       |       |       |       |  PWR  |       |       |       |QGMLWB|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |QGMLWY|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_ADJUST] = LAYOUT(
    EEP_RST,XXXXXXX,XXXXXXX,KC_MAIL,XXXXXXX,KC_WAKE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,EUCALYN, \
    XXXXXXX,XXXXXXX,KC_SLEP,XXXXXXX,XXXXXXX,RESET  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_MYCM,XXXXXXX,XXXXXXX,WORKMAN, \
    XXXXXXX,XXXXXXX,XXXXXXX,KC_CALC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_PWR ,XXXXXXX,XXXXXXX,XXXXXXX,QGMLWB, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,QGMLWY
  ),

/* _EDIT1L
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |C(Q) |C(W) |C(N) | F2  |     |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |C(Y) |C(S) |PGDN |PGUP |     |     |     | __  | __  |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |C(Z) |C(X) |C(C) |C(V) |     |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT1L] = LAYOUT(
    XXXXXXX,C(KC_Q),C(KC_W),C(KC_N),KC_F2  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,C(KC_Y),C(KC_S),KC_PGDN,KC_PGUP,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,C(KC_Z),C(KC_X),C(KC_C),C(KC_V),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EDIT1R
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |       |  DEL  |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |  __   |  __   |       |       | HOME  | LEFT  |S(LEFT)|  UP   |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |       |       |       |       |  END  | RGHT  |S(RGHT)| DOWN  |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_EDIT1R] = LAYOUT(
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,KC_DEL    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   ,_______   ,XXXXXXX   ,XXXXXXX   ,KC_HOME   ,KC_LEFT   ,S(KC_LEFT),KC_UP     ,XXXXXXX   ,XXXXXXX   , \
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,KC_END    ,KC_RGHT   ,S(KC_RGHT),KC_DOWN   ,XXXXXXX   ,XXXXXXX   , \
    _______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _EDIT2L
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |MICRO|  ~  |  @  |  #  |  $  |  %  |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | DEG |  ^  |  &  |  !  |  ?  |  ¥  |     |     | __  | __  |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |EURO |  |  |  `  |  '  |  "  |  _  |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | DEL | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT2L] = LAYOUT(
    MICRO  ,JP_TILD,JP_AT  ,JP_HASH,JP_DLR ,JP_PERC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    DEG    ,JP_CIRC,JP_AMPR,JP_EXLM,JP_QUES,JP_YEN ,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    EURO   ,JP_PIPE,JP_GRV ,JP_QUOT,JP_DQUO ,JP_UNDS,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    _______,_______,_______,_______,_______,_______,KC_DEL ,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EDIT2R
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |     |DELA |  +  |  -  |  =  |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     | __  | __  |     |     |  :  |  (  |  [  |  {  |  <  |DELTA|
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     |     |     |     |     |  ;  |  )  |  ]  |  }  |  >  |NTEQ |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  | __  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_EDIT2R] = LAYOUT(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,DELA   ,JP_PLUS,JP_MINS,JP_EQL ,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,XXXXXXX,XXXXXXX,JP_COLN,JP_LPRN,JP_LBRC,JP_LCBR,KC_LT  ,DELTA  , \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,JP_SCLN,JP_RPRN,JP_RBRC,JP_RCBR,KC_GT  ,NTEQ   , \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* _EUCALYN
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  W   |  ,   |  .   |  ;   | C(S) | DEL  |  M   |  R   |  D   |  Y   |  P   | BSPC |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  A   |  O   |  E   |  I   |  U   |  (   |  )   |  G   |  T   |  K   |  S   |  N   | ENT  |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ALPH |  Z   |  X   |  C   |  V   |  F   |  -   |  +   |  B   |  H   |  J   |  L   |  /   |SALPH |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | LSFT |NUMLOC|  F2  | APP  |LOWER |SFTSPC| LCTL | ENT  |SFTSPC|RAISE |  0   |  .   | LALT | RCTL |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_EUCALYN] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_W   ,JP_COMM,JP_DOT ,JP_SCLN,C(KC_S),KC_DEL ,KC_M   ,KC_R   ,KC_D   ,KC_Y   ,KC_P   ,KC_BSPC, \
    KC_TAB ,KC_A   ,KC_O   ,KC_E   ,KC_I   ,KC_U   ,JP_LPRN,JP_RPRN,KC_G   ,KC_T   ,KC_K   ,KC_S   ,KC_N   ,KC_ENT , \
    ALPH   ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_F   ,JP_MINS,JP_PLUS,KC_B   ,KC_H   ,KC_J   ,KC_L   ,JP_SLSH,SALPH  , \
    KC_LSFT,NUMLOC ,KC_F2  ,KC_APP ,LOWER  ,SFTSPC ,KC_LCTL,KC_ENT ,SFTSPC ,RAISE  ,KC_0   ,JP_DOT ,KC_LALT,KC_RCTL
  ),

/* _QGMLWB
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  G   |  M   |  L   |  W   | C(S) | DEL  |  B   |  Y   |  U   |  V   |  H   | BSPC |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  D   |  S   |  T   |  N   |  R   |  (   |  )   |  I   |  A   |  E   |  O   |  :   | ENT  |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ALPH |  Z   |  X   |  C   |  F   |  J   |  -   |  +   |  K   |  P   |  ,   |  .   |  /   |SALPH |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | LSFT |NUMLOC|  F2  | APP  |LOWER |SFTSPC| LCTL | ENT  |SFTSPC|RAISE |  0   |  .   | LALT | RCTL |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_QGMLWB] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_G   ,KC_M   ,KC_L   ,KC_W   ,C(KC_S),KC_DEL ,KC_B   ,KC_Y   ,KC_U   ,KC_V   ,KC_H   ,KC_BSPC, \
    KC_TAB ,KC_D   ,KC_S   ,KC_T   ,KC_N   ,KC_R   ,JP_LPRN,JP_RPRN,KC_I   ,KC_A   ,KC_E   ,KC_O   ,JP_COLN,KC_ENT , \
    ALPH   ,KC_Z   ,KC_X   ,KC_C   ,KC_F   ,KC_J   ,JP_MINS,JP_PLUS,KC_K   ,KC_P   ,JP_COMM,JP_DOT ,JP_SLSH,SALPH  , \
    KC_LSFT,NUMLOC ,KC_F2  ,KC_APP ,LOWER  ,SFTSPC ,KC_LCTL,KC_ENT ,SFTSPC ,RAISE  ,KC_0   ,JP_DOT ,KC_LALT,KC_RCTL
  ),

/* _NAGINATA
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_Q  | NG_W  | NG_E  | NG_R  | NG_T  |  __   |  __   | NG_Y  | NG_U  | NG_I  | NG_O  | NG_P  |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_A  | NG_S  | NG_D  | NG_F  | NG_G  |  __   |  __   | NG_H  | NG_J  | NG_K  | NG_L  |NG_SCLN|  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  | ALPH  | NG_Z  | NG_X  | NG_C  | NG_V  | NG_B  |  __   |  __   | NG_N  | NG_M  |NG_COMM|NG_DOT |NG_SLSH| SALPH |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   |  __   |  __   |  __   |  __   |NG_SHFT|  __   |  __   |NG_SHFT|  __   |  __   |  __   |  __   |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_NAGINATA] = LAYOUT(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,_______,_______,NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,_______,_______,NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    ALPH   ,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,_______,_______,NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,SALPH  , \
    _______,_______,_______,_______,_______,NG_SHFT,_______,_______,NG_SHFT,_______,_______,_______,_______,_______
  ),

/* _WORKMAN
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  D   |  R   |  W   |  B   | C(S) | DEL  |  J   |  F   |  U   |  P   |  :   | BSPC |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  A   |  S   |  H   |  T   |  G   |  (   |  )   |  Y   |  N   |  E   |  O   |  I   | ENT  |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ALPH |  Z   |  X   |  M   |  C   |  V   |  -   |  +   |  K   |  L   |  ,   |  .   |  /   |SALPH |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | LSFT |NUMLOC|  F2  | APP  |LOWER |SFTSPC| LCTL | ENT  |SFTSPC|RAISE |  0   |  .   | LALT | RCTL |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_WORKMAN] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_D   ,KC_R   ,KC_W   ,KC_B   ,C(KC_S),KC_DEL ,KC_J   ,KC_F   ,KC_U   ,KC_P   ,JP_COLN,KC_BSPC, \
    KC_TAB ,KC_A   ,KC_S   ,KC_H   ,KC_T   ,KC_G   ,JP_LPRN,JP_RPRN,KC_Y   ,KC_N   ,KC_E   ,KC_O   ,KC_I   ,KC_ENT , \
    ALPH   ,KC_Z   ,KC_X   ,KC_M   ,KC_C   ,KC_V   ,JP_MINS,JP_PLUS,KC_K   ,KC_L   ,JP_COMM,JP_DOT ,JP_SLSH,SALPH  , \
    KC_LSFT,NUMLOC ,KC_F2  ,KC_APP ,LOWER  ,SFTSPC ,KC_LCTL,KC_ENT ,SFTSPC ,RAISE  ,KC_0   ,JP_DOT ,KC_LALT,KC_RCTL
  ),

};

void update_led(void);

void update_led() {
  rgblight_set_effect_range(56, 15);

  if (!layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
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
  if (layer_state_is(_LOWER)) {
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
uint16_t timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
    uint16_t nowt = timer_read();
    if (nowt - timer > 5000) {
      makesure_mode();
    }
    timer = nowt;
  }

  // tap=toggle layer, hold=momentally layer on
  if (keycode == NUMLOC) {
    if (record->event.pressed) {
      num_toggle = true;
      layer_invert(_LOWER);
    } else {
      if (layer_state_is(_LOWER) && num_toggle == false) {
        layer_invert(_LOWER);
      }
    }
    update_led();
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
    case QGMLWB:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QGMLWB);
      }
      return false;
      break;
    case QGMLWY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QGMLWY);
      }
      return false;
      break;
    case SSCLN:
      if (record->event.pressed) {
        unregister_code(KC_LSFT);
        tap_code(KC_SCLN);
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
    update_led();
  }
  return a;
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
        update_led();
      }
      break;
    case NAGINATA_OFF_CMB:
      if (pressed) {
        naginata_off();
        update_led();
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
    case EDIT1R_CMB:
      if (pressed) {
        layer_on(_EDIT1R);
      } else {
        layer_off(_EDIT1R);
      }
      break;
    case EDIT1L_CMB:
      if (pressed) {
        layer_on(_EDIT1L);
      } else {
        layer_off(_EDIT1L);
      }
      break;
    case EDIT2R_CMB:
      if (pressed) {
        layer_on(_EDIT2R);
      } else {
        layer_off(_EDIT2R);
      }
      break;
    case EDIT2L_CMB:
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
  set_unicode_input_mode(UC_WINC);
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
