/* Copyright 2020 William Lindvall
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

enum custom_keycodes {
    LIQUOT = SAFE_RANGE,
    RIQUOT,
    LQUOT,
    RQUOT,
    LTITLE,
    RTITLE,
    TBULLET,
    FBULLET,
    FN_ARROW,
    MAIL,
    GITHUB,
    HEART,
    E_LCRY,
    E_FLOWER,
    E_SHEART,
    E_KISS,
    E_PHEART,
    E_NOGOOD,
    E_PARTY,
    E_ROCKET,
    E_SHRUG,
    E_WIZARD,
    E_OKBUST,
    E_OKHAND,
    E_SLEEP,
    E_HUNNED,
    E_2HEART
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LIQUOT:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("300a"));
        }
        return false;
        case RIQUOT:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("300b"));
        }
        return false;
        case LQUOT:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("300c"));
        }
        return false;
        case RQUOT:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("300d"));
        }
        return false;
        case LTITLE:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("3010"));
        }
        return false;
        case RTITLE:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("3011"));
        }
        return false;
        case TBULLET:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("2023"));
        }
        return false;
        case FBULLET:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("2055"));
        }
        return false;
        case MAIL:
        if (record->event.pressed) {
            SEND_STRING("w-lindvall@outlook.com");
        }
        return false;
        case GITHUB:
        if (record->event.pressed) {
            SEND_STRING("https://github.com/shwilliam");
        }
        return false;
        case FN_ARROW:
        if (record->event.pressed) {
            SEND_STRING("=>");
        }
        return false;
        case HEART:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("2661"));
        }
        return false;
        case E_LCRY:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DE02"));
        }
        return false;
        case E_FLOWER:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83C+DF38"));
        }
        return false;
        case E_SHEART:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DC96"));
        }
        return false;
        case E_KISS:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DE18"));
        }
        return false;
        case E_PHEART:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DC9C"));
        }
        return false;
        case E_NOGOOD:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DE45"));
        }
        return false;
        case E_PARTY:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83C+DF8A"));
        }
        return false;
        case E_ROCKET:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DE80"));
        }
        return false;
        case E_SHRUG:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83E+DD37"));
        }
        return false;
        case E_WIZARD:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83E+DDD9"));
        }
        return false;
        case E_OKBUST:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DE46"));
        }
        return false;
        case E_OKHAND:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DC4C"));
        }
        return false;
        case E_SLEEP:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DE34"));
        }
        return false;
        case E_HUNNED:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DCAF"));
        }
        return false;
        case E_2HEART:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("D83D+DC95"));
        }
        return false;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* qwerty
    * ,-----------------------------------------------------------------------------------.
    * | `    |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   | Del  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Tab  |  q   |  w   |  e   |  r   |  t   |  y   |  u   |  i   |  o   |  p   | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | H/Esc|  a   |  s   |  d   |  f   |  g   |  h   |  j   |  k   |  l   |  '   | Enter|
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Shift|  z   |  x   |  c   |  v   |  b   |  n   |  m   |  ,   |  .   |  /   |  ;   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | PDown| PUp  | Alt  |  OS  | Opt  | Raise| Space| Lower| Left | Down |  Up  | Right|
    * `-----------------------------------------------------------------------------------'
    */

    [0] = LAYOUT_preonic_grid(
        KC_GRV       ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_DEL,
        KC_TAB       ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC,
        C_S_T(KC_ESC),KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_QUOT ,KC_ENT,
        KC_LSFT      ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_SCLN,
        KC_PGDN      ,KC_PGUP ,KC_LALT ,KC_LGUI ,KC_LCTL ,MO(1)   ,KC_SPC  ,MO(2)   ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    ),

    /* raise
    * ,-----------------------------------------------------------------------------------.
    * | ~    |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |  )   |SRight|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | SLeft|
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  "   |  \   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Emoji|  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  <   |  >   |  ?   |  :   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | End  | Home | ShAlt| ShOS | ShOpt|~~~~~~| Space|      |      | BDown| BUp  |      |
    * `-----------------------------------------------------------------------------------'
    */

    [1] = LAYOUT_preonic_grid(
        KC_TILD ,KC_EXLM   ,KC_AT        ,KC_HASH      ,KC_DLR       ,KC_PERC   ,KC_CIRC   ,KC_AMPR   ,KC_ASTR   ,KC_LPRN   ,KC_RPRN   ,SGUI(KC_RGHT),
        KC_NO   ,LSFT(KC_Q),LSFT(KC_W)   ,LSFT(KC_E)   ,LSFT(KC_R)   ,LSFT(KC_T),LSFT(KC_Y),LSFT(KC_U),LSFT(KC_I),LSFT(KC_O),LSFT(KC_P),SGUI(KC_LEFT),
        KC_NO   ,LSFT(KC_A),LSFT(KC_S)   ,LSFT(KC_D)   ,LSFT(KC_F)   ,LSFT(KC_G),LSFT(KC_H),LSFT(KC_J),LSFT(KC_K),LSFT(KC_L),KC_DQUO   ,KC_BSLS,
        OSL(3)  ,LSFT(KC_Z),LSFT(KC_X)   ,LSFT(KC_C)   ,LSFT(KC_V)   ,LSFT(KC_B),LSFT(KC_N),LSFT(KC_M),KC_LT     ,KC_GT     ,KC_QUES   ,KC_COLN,
        KC_END  ,KC_HOME   ,LSFT(KC_LALT),LSFT(KC_LGUI),LSFT(KC_LCTL),KC_TRNS   ,KC_SPC    ,KC_TRNS   ,KC_NO     ,KC_BRID   ,KC_BRIU   ,KC_NO
    ),

    /* lower
    * ,-----------------------------------------------------------------------------------.
    * |  ♡   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  ‣   | CLeft| MUp  |CRight|MWDown| 【   |  -   |  _   |  |   |  =   |  +   | DLeft|
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      | MLeft| MDown|MRight| MWUp |  】  | Left | Down |  Up  | Right|  (   |  )   |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      | 《   |  》  | 「   |  」  |  ⁕   |      |  {   |  }   |  [   |  ]   |  =>  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Mail |GitHub|      |      |      |      | Space|~~~~~~| VMute| VDown| VUp  |      |
    * `-----------------------------------------------------------------------------------'
    */

    [2] = LAYOUT_preonic_grid(
        HEART   ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_NO,
        TBULLET ,KC_BTN1 ,KC_MS_U ,KC_BTN2 ,KC_WH_D ,LTITLE  ,KC_MINS ,KC_UNDS ,KC_PIPE ,KC_EQL  ,KC_PLUS ,LGUI(KC_BSPC),
        KC_NO   ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_U ,RTITLE  ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,KC_LPRN ,KC_RPRN,
        KC_NO   ,LIQUOT  ,RIQUOT  ,LQUOT   ,RQUOT   ,FBULLET ,KC_NO   ,KC_LCBR ,KC_RCBR ,KC_LBRC ,KC_RBRC ,FN_ARROW,
        MAIL    ,GITHUB  ,KC_NO   ,KC_NO   ,KC_NO   ,KC_TRNS ,KC_BSPC ,KC_TRNS ,KC_MUTE ,KC_VOLD ,KC_VOLU ,KC_NO
    ),

    /* emoji
    * ,-----------------------------------------------------------------------------------.
    * |      |  1   |  2   |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |  w   |      |  r   |      |  y   |      |      |  o   |  p   |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |  s   |      |  f   |      |  h   |      |  k   |  l   |      |      |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      |  z   |      |  c   |      |      |  n   |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    *
    * mnemonics:
    *
    * 100       -  💯
    * 2 hearts  -  💕
    * cry       -  😂
    * flower    -  🌸
    * heart     -  💖
    * kiss      -  😘
    * love      -  💜
    * no        -  🙅
    * ok        -  🙆
    * party     -  🎊
    * rocket    -  🚀
    * shrug     -  🤷
    * wizard    -  🧙
    * yes       -  👌
    * zzz       -  😴
    *
    */

    [3] = LAYOUT_preonic_grid(
        KC_NO   ,E_HUNNED,E_2HEART,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO,
        KC_NO   ,KC_NO   ,E_WIZARD,KC_NO   ,E_ROCKET,KC_NO   ,E_OKHAND,KC_NO   ,KC_NO   ,E_OKBUST,E_PARTY ,KC_NO,
        KC_NO   ,KC_NO   ,E_SHRUG ,KC_NO   ,E_FLOWER,KC_NO   ,E_SHEART,KC_NO   ,E_KISS  ,E_PHEART,KC_NO   ,KC_NO,
        KC_NO   ,E_SLEEP ,KC_NO   ,E_LCRY  ,KC_NO   ,KC_NO   ,E_NOGOOD,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO,
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
    )

};
