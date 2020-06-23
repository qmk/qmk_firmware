/* Copyright 2020 Yoonbae Cho
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

/* 
 * Refereces:
 * https://beta.docs.qmk.fm/using-qmk/guides/keymap
 * https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes
 * https://beta.docs.qmk.fm/using-qmk/software-features/feature_layers
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/keebio/iris/keymaps/dbroqua/keymap.c
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/keebio/iris/keymaps/fluffactually/keymap.c
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/keebio/iris/keymaps/dcompact/keymap.c
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/smittey/keymap.c
 */


#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

#define KC_ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
    /*
     * ,-----+-----+-----+-----+-----+-----+                ,-----+-----+-----+-----+-----+-----+
     * |~ESC~|  1  |  2  |  3  |  4  |  5  |                |  6  |  7  |  8  |  9  |  0  |  `  |
     * |-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * | TAB |  Q  |  W  |  E  |  R  |  T  |                |  Y  |  U  |  I  |  O  |  P  | BSPC|
     * +-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * | LCTL|  A  |  S  |  D  |  F  |  G  |                |  H  |  J  |  K  |  L  |  ;  |  '  |
     * +-----+-----+-----+-----+-----+-----+-----.    ,-----+-----+-----+-----+-----+-----+-----+
     * | LSFT|  Z  |  X  |  C  |  V  |  B  | ??? /    \     |  N  |  M  |  ,  |  .  |  /  | RSFT|
     * +-----+-----+-----+--+--+-----+-----+----/      \ SPC+-----+-----+--+--+-----+-----+-----+
     *                      \ LGUI|LOWER| ENT  /        \      |RAISE| RALT/
     *                      `-----+-----+-----'          `-----+-----+----'
     */
     GESC,  1  ,  2  ,  3  ,  4  ,  5  ,                 6  ,  7  ,  8  ,  9  ,  0  ,  GRV, 
     TAB ,  Q  ,  W  ,  E  ,  R  ,  T  ,                 Y  ,  U  ,  I  ,  O  ,  P  , BSPC, 
     LCTL,  A  ,  S  ,  D  ,  F  ,  G  ,                 H  ,  J  ,  K  ,  L  , SCLN, QUOT, 
     LSFT,  Z  ,  X  ,  C  ,  V  ,  B  , ??? ,        ,  N  ,  M  , COMM, DOT , SLSH, RSFT, 
                          LGUI, LOWER, ENT,          SPC , RAISE, RALT
  ),

  [_LOWER] = LAYOUT_kc(
    /*
     * ,-----+-----+-----+-----+-----+-----+                ,-----+-----+-----+-----+-----+-----+
     * |  ~  |  !  |  @  |  #  |  $  |  %  |                |  ^  |  &  |  *  |  (  |  )  | BSPC|
     * |-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * |RESET|  1  |  2  |  3  |  4  |  5  |                |  6  |  7  |  8  |  9  |  0  |     |
     * +-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * | DEL |     | LEFT| RGHT| UP  |  [  |                |  ]  |  4  |  5  |  6  |  +  |  |  |
     * +-----+-----+-----+-----+-----+-----+-----.    ,-----+-----+-----+-----+-----+-----+-----+
     * |     |     |     |     | DOWN|  {  |     /    \     |  }  |  1  |  2  |  3  |  -  |     |
     * +-----+-----+-----+--+--+-----+-----+----/      \ SPC+-----+-----+--+--+-----+-----+-----+
     *                      \     |     |      /        \      |     | 0   /
     *                      `-----+-----+-----'          `-----+-----+----'
     */
     TILD , EXLM,  AT , HASH, DLR , PERC,                CIRC, AMPR, ASTR, LPRN, RPRN, BSPC, 
     RESET,  1  ,  2  ,  3  ,  4  ,  5  ,                 6  ,  7  ,  8  ,  9  ,  0  ,     , 
     DEL  ,     , LEFT, RGHT,  UP , LBRC,                RBRC,  P4 ,  P5 ,  P6 , PLUS, PIPE, 
          ,     ,     ,     , DOWN, LCBR,     ,        , RCBR,  P1 ,  P2 ,  P3 , MINS,     , 
                            ,     , DEL ,             DEL ,     ,  P0
  ),

  [_RAISE] = LAYOUT_kc(
    /*
     * ,-----+-----+-----+-----+-----+-----+                ,-----+-----+-----+-----+-----+-----+
     * | F12 |  F1 |  F2 |  F3 |  F4 |  F5 |                |  F6 |  F7 |  F8 |  F9 | F10 | F11 |
     * |-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * |     |  !  |  @  |  #  |  $  |  %  |                |  ^  |  &  |  *  |  (  |  )  |     |
     * +-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * |     | Prev| Next| Vol+| PgUp|  _  |                |  =  | Home|     |     |  +  |  \  |
     * +-----+-----+-----+-----+-----+-----+-----.    ,-----+-----+-----+-----+-----+-----+-----+
     * | Mute| Stop| Play| Vol-| PgDn|  -  |     /    \     |  +  | End |     |     |     |Debug|
     * +-----+-----+-----+--+--+-----+-----+    /      \    +-----+-----+--+--+-----+-----+-----+
     *                      \     |     |      /        \      |     | 0   /
     *                      `-----+-----+-----'          `-----+-----+----'
     */
     F12 ,  F1 ,  F2 ,  F3 ,  F4 ,  F5 ,                 F6 ,  F7 ,  F8 ,  F9 , F10 , F11 , 
         , EXLM,  AT , HASH, DLR , PERC,                CIRC, AMPR, ASTR, LPRN, RPRN,     , 
         , MPRV, MNXT, VOLU, PGUP, UNDS,                EQL , HOME,     ,     ,     , BSLS, 
     MUTE, MSTP, MPLY, VOLD, PGDN, MINS,     ,        , PLUS, END ,     ,     ,     ,DEBUG, 
                              ,     ,     ,              ,     , 
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      }
      return false;
      break;
  }
  return true;
}


/*

   // fluffactually
  [0] = LAYOUT(
     KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,LSFT_T(KC_EQL),RCTL_T(KC_MINS),KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                    KC_LGUI, TT(1),   KC_ENT,                    KC_SPC,  TT(2),   KC_RALT
  ),

  [1] = LAYOUT(
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PSCR,
     _______, _______, _______, KC_END,  _______, _______,                            _______, _______, _______, _______, _______, KC_DEL,
     _______, KC_HOME, _______, _______, KC_PGDN, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
     _______, _______, _______, _______, _______, KC_PGUP, KC_LBRC,          KC_RBRC, _______, _______, _______, _______, _______, _______,
                                    _______, _______, _______,                   _______, _______, _______
  ),

  [2] = LAYOUT(
     KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RESET,
     KC_MUTE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    RGB_TOG,
     KC_VOLU, KC_BRIU, KC_MNXT, KC_MPLY, _______, _______,                            _______, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,
     KC_VOLD, KC_BRID, KC_MPRV, KC_MSTP, _______, KC_LBRC, KC_LCBR,          KC_RCBR, KC_RBRC, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,
                                    _______, _______, _______,                   _______, _______, _______
  ),


  [0] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //| GESC   |   1    |        |   KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //| KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //| KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,LSFT_T(KC_EQL),RCTL_T(KC_MINS),KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, TT(1),   KC_ENT,                    KC_SPC,  TT(2),   KC_RALT

                                    

  [_BASE] = LAYOUT(
     KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,LSFT_T(KC_EQL),        KC_SPC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                    KC_LGUI, TT(1),   KC_ENT,                    KC_SPC,  TT(2),   KC_RALT
  ),

  [_LOWER] = LAYOUT(
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
     XXXXXXX, KC_PSCR, KC_MENU, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
     XXXXXXX, KC_CAPS, KC_LNUM, KC_INS,  XXXXXXX, XXXXXXX,                            XXXXXXX, WKSP_L,  WKSP_D,  WKSP_U,  WKSP_R,  XXXXXXX,
     _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX,          XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    _______, _______, _______,                   XXXXXXX, _______, XXXXXXX
  ),

  [_RAISE] = LAYOUT(
     QUAKE,   KC_GRV,  KC_TILD, KC_BSLS, KC_PIPE, KC_LPRN,                            KC_RPRN, KC_7,    KC_8,    KC_9,    KC_SLSH, KC_EQL,
     XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_LCBR,                            KC_RCBR, KC_4,    KC_5,    KC_6,    KC_ASTR, KC_PLUS,
     XXXXXXX, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC,                            KC_RBRC, KC_1,    KC_2,    KC_3,    KC_MINS, KC_BSPC,
     _______, XXXXXXX, _______, _______, _______, KC_LABK, XXXXXXX,          XXXXXXX, KC_RABK, _______, KC_0,    KC_DOT,  KC_COMM, XXXXXXX,
                                    _______, _______, KC_LABK,                   KC_RABK, _______, KC_0
  ),

  [_FUNC] = LAYOUT(
     XXXXXXX, KC_SLEP, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                            XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,
     XXXXXXX, KC_WAKE, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,                            XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,
     XXXXXXX, KC_PWR,  KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX,                            XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,
     _______, _______, _______, _______, _______, _______, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,
                                    XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_LNUM] = LAYOUT(
     _______, KC_1,    KC_2,    KC_3,    KC_4,    XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, KC_5,    KC_6,    KC_7,    KC_8,    XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, KC_9,    KC_0,    KC_COMM, KC_DOT,  XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    _______, _______, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_LFUN] = LAYOUT(
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    _______, _______, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX
  ),

};
*/
