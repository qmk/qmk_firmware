/*
Copyright 2021 Tyler Tolley <thattolleyguy@gmail.com>

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

#include QMK_KEYBOARD_H

enum dactyl_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define KC_CBP LCTL(KC_F11) //Clipboard previous
#define KC_CBN LCTL(KC_F12) //Clipboard previous
#define KC_DSKD LCA(KC_DOWN)
#define KC_DSKU LCA(KC_UP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(


  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ┌────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┼────────┼────────┼────────┼────────┘                          └────────┴────────┼────────┼────────┼────────┼────────┘
                       KC_DSKU, KC_DSKD,                                                                KC_PGUP, KC_PGDN,
  //                  └────────┴────────┘        ┌────────┬────────┐        ┌────────┬────────┐        └────────┴────────┘
                                                  LOWER,   KC_ENT,           KC_SPC,  RAISE,
  //                                             ├────────┼────────┤        ├────────┼────────┤
                                                  KC_LGUI, KC_GRV,           KC_DEL,  KC_RALT,
  //                                             ├────────┼────────┤        ├────────┼────────┤
                                                  KC_CBP,  KC_CBN,           KC_APP,  KC_RCTL
  //                                             └────────┴────────┘        └────────┴────────┘
  ),

  [_LOWER] = LAYOUT_5x6(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, KC_VOLU, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT,                            XXXXXXX, XXXXXXX, KC_PSLS, KC_PAST, KC_PMNS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_VOLD, RGB_M_SW,RGB_TOG, XXXXXXX, XXXXXXX,                            XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, XXXXXXX,                            XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_EQL,  KC_PSCR,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ┌────────┼────────┼────────┼────────┼────────┼────────┤
     _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,XXXXXXX,                            XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PDOT, _______,
  //└────────┴────────┼────────┼────────┼────────┼────────┘                          └────────┴────────┼────────┼────────┼────────┼────────┘
                       KC_PGUP, KC_PGDN,                                                                KC_P0,   Debug,
  //                  └────────┴────────┘        ┌────────┬────────┐        ┌────────┬────────┐        └────────┴────────┘
                                                  _______, _______,          _______,  _______,
  //                                             ├────────┼────────┤        ├────────┼────────┤
                                                  _______, _______,          _______,  _______,
  //                                             ├────────┼────────┤        ├────────┼────────┤
                                                  _______, QK_BOOT,          _______, _______
  //                                             └────────┴────────┘        └────────┴────────┘

  ),

  [_RAISE] = LAYOUT_5x6(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, _______, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX,                            XXXXXXX, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_UNDS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP,                            KC_INS,  KC_HOME, KC_PPLS, KC_MINS, KC_TILD, KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ┌────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN,                            KC_DEL,  KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //└────────┴────────┼────────┼────────┼────────┼────────┘                          └────────┴────────┼────────┼────────┼────────┼────────┘
                       DM_REC1, DM_REC2,                                                                DM_PLY1, DM_PLY2,
  //                  └────────┴────────┘        ┌────────┬────────┐        ┌────────┬────────┐        └────────┴────────┘
                                                  LOWER,   KC_ENT,           KC_SPC,  RAISE,
  //                                             ├────────┼────────┤        ├────────┼────────┤
                                                  KC_LGUI, KC_GRV,           KC_DEL,  KC_RALT,
  //                                             ├────────┼────────┤        ├────────┼────────┤
                                                  XXXXXXX, XXXXXXX,          QK_BOOT, XXXXXXX
  //                                             └────────┴────────┘        └────────┴────────┘
  ),
};


#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  // Left
  // 0  1  2  3  4  5
  //                   ROWS
  // 25 24 19 18 11 10   0
  //    03    02    01
  // 26 23 20 17 12 09   1
  //    04    05    06
  // 27 22 21 16 13 08   2
  //
  //          15 14 07   3
  //
  // Right
  // 0  1  2  3  4  5
  //                    ROWS
  // 25 24 19 18 11 10   4
  //    03    02    01
  // 26 23 20 17 12 09   5
  //    04    05    06
  // 27 22 21 16 13 08   6
  //
  //          15 14 07   7
  //
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 25 24 19 18 11 10       10 11 18 19 24 25  0
  //    03    02    01       01    02    03
  // 26 23 20 17 12 09       09 12 17 20 23 26  1
  //    04                               04
  // 27 22 21 16 13 08       08 13 16 21 22 27  2
  //          05    06       06    05
  //           15 14 07     07 14 15              3

led_config_t g_led_config = { {
    {      0,      1,  2,  3,      4,      5 },
    {     11,     10,  9,  8,      7,      6 },
    {     12,     13, 14, 15,     16,     17 },
    {     23,     22, 21, 20,     19,     18 },
    { NO_LED, NO_LED, 24, 25,     26,     27 },
    { NO_LED, NO_LED, 30, 31,     28,     29 },
    {     37,     36, 35, 34,     33,     32 },
    {     43,     42, 41, 40,     39,     38 },
    {     49,     48, 47, 46,     45,     44 },
    {     55,     54, 53, 52,     51,     50 },
    // {     NO_LED,     NO_LED, 57, 56, NO_LED, NO_LED},
    // {     NO_LED,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    {     59,     58, 57, 56, NO_LED, NO_LED},
    {     61,     60, 62, 63, NO_LED, NO_LED }

}, {
    {  0,  0 }, {  17,  0 }, {  34,  0 }, {  52,  0 }, {  69,  0 }, {  86,  0 }, {  86,  9 }, {  69,  9 },
    {  52,  9 }, {  34,   9 }, {  17,   9 }, {  0,  9 }, {  0,  18 }, {  17,  18 }, {  34,  18 }, {  52,  18 },
     {  60,  18 }, {  86,   18 }, {  86,   27 }, {  69,  27 }, {  52,  27 }, {  34,  27 }, {  17,  27 }, {  0,   27 },
      {  34,   37 }, {   52,  37 }, {   69,  45 }, { 86,  45 }, { 103,  55 }, { 103,  64 }, { 86,  55 }, { 86,  64 },


    { 224,  0 }, { 207,  0 }, { 190,  0 }, { 172,  0 }, { 155,   0 }, { 138,   0 }, { 224,  9 }, { 207,  9 },
    { 190,  9 }, { 172,  9 }, { 155,  9 }, { 138,  9 }, { 224,  18 }, { 207,  18 }, { 190,  18 },{ 172,  18 },
    { 155,   18 }, { 138,   18 }, { 224,  27 }, { 207,  27 }, { 190,  27}, { 172,  27 },{ 155,  27 }, { 138,  27 },
    { 190,  37 }, { 172,  37 }, { 155,  45}, { 138,  45 }, { 121,  55 }, { 121,  64 },  { 138,  64 }, { 138,  55 }
}, {
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2
} };

#endif

