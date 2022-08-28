/* Copyright 2022 bojiguard (@bojiguard)
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


enum layer_names {
		SAM1,
		SAM2,
		SAM3,
		SAM4,
		BASE,
		F3LAY,
		F4LAY,
};





#define SFCTLNO MT(MOD_LCTL|MOD_LSFT,KC_NO) 

#define SFCT_S  MT(MOD_LCTL|MOD_LSFT,KC_S)
#define CT_D    MT(MOD_LCTL,KC_D)
#define SF_F    MT(MOD_LSFT,KC_F)

#define SF_J    MT(MOD_RSFT,KC_J)
#define CT_K    MT(MOD_RCTL,KC_K)

#define MTC_F7   MT(MOD_LCTL|MOD_LSFT, KC_F7)
#define MTC_F8   MT(MOD_LCTL, KC_F8)      
#define MTC_F9   MT(MOD_LSFT, KC_F9)

#define MTC_K   MT(MOD_RCTL, KC_K)      
#define MTC_J   MT(MOD_RSFT, KC_J)

#define MTC_8   MT(MOD_RCTL, KC_8)      
#define MTC_7   MT(MOD_RSFT, KC_7)

//#define MTLC_8   MT(MOD_LCTL, KC_8)      
#define MTLC_9   MT(MOD_LSFT, KC_9)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE
   * ,------------------------------------------------.                                ,------------------------------------------------.
   * |   ~  |   1  |   2  |   3  |   4  |   5  | ESC  |                                |  BS  |   6  |   7  |   8  |   9  |   [  |   \  |
   * |------+------+------+------+------+------+------|                                |-------------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  `   |                                |   \  |   Y  |   U  |   I  |   O  |   P  | Tab  |
   * |------+------+------+------+------+------+------|                                |-------------+------+------+------+------+------|
   * | ctrl |   A  |   S  |   D  |   F  |   G  |  [   |                                |  ]   |   H  |   J  |   K  |   L  |   ;  | ctrl |
   * |------+------+------+------+------+------+------|                                |------|------+------+------+------+------+------|
   * | shift|   Z  |   X  |   C  |   V  |  B   |  3   |  -     | 7     ||  1   |   2   |  =   |  4   |   N  |   M  |   ,  |   .  |shift |
   * |------+------+------+------+------+------+------|                                |------+------+------+------+------+------+------|
   * |  1   |  2   |   3  |  4   |     alt     | spc  |  MO(1) |enter  ||enter | MO(0) |  spc |     alt     |  1   |   2  |   3  |  4   |
   * `------------------------------------------------'                                ------------------------------------------------'
   */

  [BASE] = LAYOUT_fungo_split_num(
    KC_GRV,     KC_1,     KC_2,    KC_3,    KC_4,     KC_5,    KC_ESC,                                                              KC_BSPC,  KC_6,  KC_7,   KC_8,    KC_9,    KC_0,    KC_NO,
    KC_TAB,     KC_Q,     KC_W,    KC_E,    KC_R,     KC_T,    KC_MINS,                                                             KC_EQL,   KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,    KC_TAB,
    KC_NO,      KC_A,     SFCT_S,  CT_D,    SF_F,     KC_G,    KC_LBRC,                                                             KC_RBRC,  KC_H,  MTC_J,  MTC_K,   KC_L,    KC_SCLN, KC_NO,
    KC_LCTL,    KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,    KC_BSLS,  LM(F3LAY, MOD_LSFT), KC_NO,   KC_NO,  LM(F3LAY, MOD_RSFT), KC_QUOT,  KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
    KC_NO,      TT(SAM1), KC_NO,   KC_LALT,    KC_LSHIFT,      KC_SPC,   MO(F3LAY),           KC_ENT,  KC_ENT, TT(F3LAY),           KC_SPC,     KC_RSHIFT,   KC_RALT, KC_NO,   TT(SAM1),TG(F4LAY)
  ),

  /* BASE
   * ,------------------------------------------------.                                ,------------------------------------------------.
   * |   ~  |   1  |   2  |   3  |   4  |   5  | ESC  |                                |  BS  |   6  |   7  |   8  |   9  |   [  |   \  |
   * |------+------+------+------+------+------+------|                                |-------------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  `   |                                | DEL  | HOME |  UP  | END  |   O  |   P  | Tab  |
   * |------+------+------+------+------+------+------|                                |-------------+------+------+------+------+------|
   * | ctrl |   A  |   S  |   D  |   F  |   G  |  [   |                                | INS  | LEFT | DOWN | RIGHT|   L  |   ;  | ctrl |
   * |------+------+------+------+------+------+------|                                |------|------+------+------+------+------+------|
   * | shift|   Z  |   X  | ctr+C|ctr+V |  B   |  3   |  -     | 7     ||  1   |   2   |  NO  | PGUP |  NO  | PGDN |   ,  |   .  |shift |
   * |------+------+------+------+------+------+------|                                |------+------+------+------+------+------+------|
   * |  1   |  2   |   3  |  4   |     alt     | spc  |  MO(1) |enter  ||enter | MO(0) |  spc |     alt     |  1   |   2  |   3  |  4   |
   * `------------------------------------------------'                                ------------------------------------------------'
   */

  [F3LAY] = LAYOUT_fungo_split_num(
    KC_F11,     KC_F1,      KC_F2,       KC_F3,        KC_F4,        KC_F5,   KC_ESC,                                                              KC_BSPC, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F12,
    KC_TAB,     KC_1,       KC_2,        KC_3,         KC_4,         KC_5,    KC_CAPS,                                                             KC_CAPS, KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_TAB,
    KC_NO,      KC_NO,      SFCTLNO,     KC_LCTL,      KC_LSFT,      KC_PAUS, KC_PSCR,                                                             KC_BSPC, KC_DEL,  KC_HOME, KC_UP,   KC_END,   KC_PGUP, KC_NO,
    KC_LCTL,    LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C),   LCTL(KC_V),   KC_NO,   KC_NO,    LM(F3LAY, MOD_LSFT), KC_NO,   KC_NO,  LM(F3LAY, MOD_RSFT), KC_NO,   KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_RCTL,
    KC_NO,      KC_NO,      KC_NO,       KC_LALT,           KC_LSHIFT,        KC_SPC,   MO(F3LAY),           KC_ENT,  KC_ENT, TT(F3LAY),           KC_SPC,     KC_RSHIFT,     KC_RALT, KC_NO,    KC_NO,   TG(F4LAY)
  ),


  [F4LAY] = LAYOUT_fungo_split_num(
    KC_F11,     KC_F1,      KC_F2,       KC_F3,        KC_F4,        KC_F5,   KC_ESC,                                                              KC_BSPC, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F12,
    KC_TAB,     KC_NO,      KC_NO,       KC_NO,        KC_NO,        KC_NO,   KC_CAPS,                                                             KC_CAPS, KC_DEL,  KC_HOME, KC_UP,   KC_END,   KC_NO,   KC_TAB,
    KC_NO,      KC_NO,      SFCTLNO,     KC_LCTL,      KC_LSFT,      KC_PAUS, KC_PSCR,                                                             KC_BSPC, KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,   KC_NO,
    KC_LCTL,    LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C),   LCTL(KC_V),   KC_NO,   KC_NO,    LM(F3LAY, MOD_LSFT), KC_NO,   KC_NO,  LM(F3LAY, MOD_RSFT), KC_NO,   KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_RCTL,
    KC_NO,      KC_NO,      KC_NO,       KC_LALT,           KC_LSHIFT,        KC_SPC,   MO(F3LAY),           KC_ENT,  KC_ENT, TT(F3LAY),           KC_SPC,     KC_RSHIFT,     KC_RALT, KC_NO,    KC_NO,   TG(F4LAY)
  ),
  
  /*
    [TEST] = LAYOUT_fungo_split_num(
    KC_GRV,     KC_1,   KC_2,    KC_3,    KC_4,     KC_5,    KC_ESC,                                                KC_BSPC,  KC_6,    KC_7,    KC_8,      KC_9,   KC_0,    KC_NO,
    KC_TAB,     KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,    KC_MINS,                                               KC_EQL,   KC_Y,    KC_U,    KC_I,      KC_O,   KC_P,    KC_TAB,
    KC_LSFT,    KC_A,   KC_S,    KC_D,    KC_F,     KC_G,    KC_LBRC,                                               KC_RBRC,  KC_H,    KC_J,    KC_K,      KC_L,   KC_SCLN, KC_RSFT,
    KC_LCTL,    KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    KC_BSLS,  KC_LCTL,        KC_NO,   KC_NO,  TG(F4LAY),  KC_QUOT,  KC_N,    KC_M,    KC_COMM,   KC_DOT, KC_SLSH, KC_RCTL,
    KC_NO,      KC_NO,  KC_NO,   KC_LALT,    KC_LSHIFT,      KC_SPC,   MO(F3LAY),      KC_ENT,  KC_ENT, TT(F3LAY),  KC_SPC,      KC_RSHIFT,     KC_RALT,   KC_NO,  KC_NO,   KC_NO
  ),
  */
  
  //--------------------------------------------------------NEW-----------------------------------------------
  //SAM1을 기반으로 새로운 모드
    [SAM1] = LAYOUT_fungo_split_num(
    KC_NO,      KC_1,     KC_2,    KC_3,    KC_4,     KC_5,    KC_ESC,                                            KC_ESC,   KC_6,  KC_7,   KC_8,    KC_9,    KC_0,     KC_NO,
    KC_NO,      KC_Q,     KC_W,    KC_E,    KC_R,     KC_T,    KC_BSPC,                                           KC_BSPC,  KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,     KC_NO,
    KC_TAB,     KC_A,     SFCT_S,  CT_D,    SF_F,     KC_G,    KC_CAPS,                                           KC_CAPS,  KC_H,  MTC_J,  MTC_K,   KC_L,    KC_SCLN,  KC_TAB,
    KC_LCTL,    KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,    KC_NO,     TT(SAM3),   KC_NO,    KC_NO, TT(SAM2),  KC_NO,    KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RCTL,
    KC_NO,      TT(SAM1), KC_NO,   KC_LALT,    KC_SPC,         TT(SAM2),  KC_ENT,     MO(SAM4), KC_NO, KC_ENT,    TT(SAM3),     KC_SPC,    KC_RALT, KC_NO,   TT(SAM1), KC_NO
  ),
  
    [SAM3] = LAYOUT_fungo_split_num(
    KC_NO,      KC_NO,      KC_NO,       KC_NO,        KC_NO,        KC_NO,   KC_ESC,                                       KC_ESC,  KC_NO,   KC_NO,     KC_NO,   KC_NO,    KC_NO,    KC_NO,
    KC_NO,      KC_1,       KC_2,        KC_3,         KC_4,         KC_5,    KC_BSPC,                                      KC_BSPC, KC_1,    KC_2,      KC_3,    KC_4,     KC_5,     KC_NO,
    KC_TAB,     KC_6,       KC_7,        KC_8,         MTLC_9,       KC_0,    KC_CAPS,                                      KC_CAPS, KC_6,    MTC_7,     MTC_8,   KC_9,     KC_0,     KC_TAB,
    KC_LCTL,    KC_PSLS,    KC_PAST,     KC_MINS,      KC_PPLS,      KC_EQL,  KC_DOT,   TT(SAM3),  KC_NO,  KC_NO, TT(SAM2), KC_DOT,  KC_EQL,  KC_PPLS,   KC_PMNS, KC_PAST,  KC_PSLS,  KC_RCTL,
    KC_NO,      TT(SAM1),   KC_NO,       KC_LALT,             KC_SPC,         TT(SAM2), KC_ENT,    MO(SAM4),  KC_NO, KC_ENT,   TT(SAM3),    KC_SPC,         KC_RALT, KC_NO,    TT(SAM1), KC_NO
  ),
  
    [SAM2] = LAYOUT_fungo_split_num(
    KC_NO,      KC_NO,      KC_NO,       KC_NO,        KC_NO,        KC_NO,   KC_ESC,                                       KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,
    KC_NO,      KC_F1,      KC_F2,       KC_F3,        KC_F4,        KC_F5,   KC_F11,                                       KC_BSPC, KC_DEL,  KC_HOME, KC_UP,   KC_END,   KC_PGUP, KC_NO,
    KC_TAB,     KC_F6,      MTC_F7,      MTC_F8,       MTC_F9,       KC_F10,  KC_F12,                                       KC_CAPS, KC_INS,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_TAB,
    KC_LCTL,    LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C),   LCTL(KC_V),   KC_NO,   KC_NO,    TT(SAM3),  KC_NO,  KC_NO, TT(SAM2), KC_NO,   KC_BSLS, KC_QUOT, KC_LBRC, KC_RBRC,  KC_GRV,  KC_RCTL,
    KC_NO,      TT(SAM1),   KC_NO,       KC_LALT,             KC_SPC,         TT(SAM2), KC_ENT,    MO(SAM4),  KC_NO, KC_ENT,   TT(SAM3),    KC_SPC,       KC_RALT, KC_NO,   TT(SAM1), KC_NO
  ),  
    [SAM4] = LAYOUT_fungo_split_num(
    KC_NO,      KC_NO,      KC_NO,       KC_NO,        KC_NO,        KC_NO,   KC_ESC,                                       KC_ESC,   KC_NO,     KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,
    KC_NO,      KC_F1,      KC_F2,       KC_F3,        KC_F4,        KC_F5,   KC_F11,                                       KC_BSPC,  KC_ACL0,   KC_BTN1, KC_MS_U, KC_BTN2,  KC_NO,    KC_NO,
    KC_TAB,     KC_F6,      MTC_F7,      MTC_F8,       MTC_F9,       KC_F10,  KC_F12,                                       KC_CAPS,  KC_ACL1,   KC_MS_L, KC_MS_D, KC_MS_R,  KC_NO,    KC_TAB,
    KC_NO,      KC_NO,      KC_ACL0,     KC_ACL1,      KC_ACL2,      KC_NO,   KC_NO,    TT(SAM3),  KC_NO,  KC_NO, TT(SAM2), KC_NO,    KC_ACL2,   KC_WH_L, KC_WH_U, KC_WH_D,  KC_WH_R,  KC_RCTL,
    KC_NO,      TT(SAM1),   KC_NO,       KC_LALT,             KC_SPC,         TT(SAM2), KC_ENT,    MO(SAM4),  KC_NO, KC_ENT,   TT(SAM3),       KC_SPC,       KC_RALT, KC_NO,    TT(SAM1), KC_NO
  ),  
};



