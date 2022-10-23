/* Copyright 2020 elagil 
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

enum layers {
    BASE,
    _F1,
    _F2,
    _F3
};

#define ALT_BSL MT(MOD_RALT, KC_BSLS)

#define PRE_WRD LCTL(KC_LEFT)  // jump to next word
#define NXT_WRD LCTL(KC_RGHT)  // jump to previous word

#define NXT_WDL LCTL(KC_DEL)   // delete next word
#define PRE_WDL LCTL(KC_BSPC)  // delete previous word

#define MF1 MO(_F1) // F1 layer access
#define MF2 MO(_F2) // F2 layer access

/*
 * This default keymap is aimed at users of the US or US international layout
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* BASE
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |  =+  |  1!  |  2@  |  3#  |  4$  |  5%  |                        |  6^  |  7&  |  8*  |  9(  |  0)  |  -_  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       | Tab  |  Q   |  W   |  E   |  R   |  T   |                        |   Y  |   U  |   I  |   O  |   P  |  \|  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       | Del  |  A   |  S   |  D   |  F   |  G   |                        |   H  |   J  |   K  |   L  |  ;:  |  '"  |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       | Sft  |  Z   |  X   |  C   |  V   |  B   | Esc  |          | Ent  |   N  |   M  |  ,<  |  .>  |  /?  |  Sft |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  | LAlt | LGUI |  SYM | Back | Ctrl |                | RAlt |Space | NAV  | RWIN | Caps | 
   *                  `----------------------------------'                `----------------------------------'
   */
  [BASE] = LAYOUT( /* qwerty */
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_LBRC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GESC, KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
             KC_LALT, KC_LGUI, MF1,     KC_BSPC, KC_LCTL,                   ALT_BSL, KC_SPC,  MF2,     KC_RWIN, KC_CAPS
  ),

  /* F2
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |      |  F1  |  F2  |  F3  |  F4  |  F5  |                        |   F6 |   F7 |   F8 |   F9 |   F10|   F11|
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |      |      | Volu |      |      |                        |      |PRE W |  UP  |NXT W | PGUP |   F12|
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       | Del  |      | Prev | Play | Next |      |                        | HOME | LEFT | DOWN |RIGHT | END  |      |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      |      |      | Vold |      |      |      |          |      |      |DEL PW| Ins  |DEL NW| PGDN |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |      |      |      |                |      |      |      |      |      |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_F2] = LAYOUT(
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX,                   XXXXXXX, PRE_WRD, KC_UP,   NXT_WRD, KC_PGUP, KC_F12,
    KC_DEL,  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX,  
    _______, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, PRE_WDL, KC_INS,  NXT_WDL, KC_PGDN, _______,
             _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
  ),

  /* F1
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |      |  F1  |  F2  |  F3  |  F4  |  F5  |                        |   F6 |   F7 |   F8 |   F9 |   F10|   F11|
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      | PGUP |PRE W |  UP  |NXT W |      |                        |      |   7  |   8  |   9  |      |   F12|
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       | Del  | HOME | LEFT | DOWN |RIGHT | END  |                        |   +  |   4  |   5  |   6  |   -  |      |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      | PGDN |DEL PW| Ins  |DEL NW|      |      |          | NEnt |   *  |   1  |   2  |   3  |   /  |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |      |      |      |                |      |   0  |      |      | NLck |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_F1] = LAYOUT(
    XXXXXXX,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    XXXXXXX, KC_PGUP, PRE_WRD, KC_UP,   NXT_WRD, XXXXXXX,                   XXXXXXX, KC_P7,   KC_P8,   KC_P9,   XXXXXXX, KC_F12,
    KC_DEL,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                    KC_PPLS, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, XXXXXXX,  
    _______, KC_PGDN, PRE_WDL, KC_INS,  NXT_WDL, XXXXXXX, _______, KC_PENT, KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PSLS, _______,
             _______, _______, _______, _______, _______,                   _______, KC_P0,   _______, _______, KC_NLCK
  ),
  
  /* F3
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |      |      |      |      |      |      |                        |      |      |      |      |      |      |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |      |      |      |      |      |                        |      |      |      |      |      |      |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |      |      |      |      |      |                        |      |      |      |      |      |      |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      |      |      |      |      |      |      |          |      |      |      |      |      |      |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |      |      |      |                |      |      |      |      |      |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_F3] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};
