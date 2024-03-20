/*
Copyright 2022 oco9oco <oco9oco@gmail.com>

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

#include "oco9oco.h" //look for users/oco9oco/
//clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, KC_MINS,
    KC_CAPS, __________________QWERTY_SACS_L2___________,                            __________________QWERTY_R2________________, KC_QUOT,
    KC_LSFT, __________________QWERTY_GUIZ_L3___________,                            __________________QWERTY_HOME_R3___________, KC_BSLS,
                                        THUMB_L1, THUMB_L2, THUMB_L3,       THUMB_R3, THUMB_R2, THUMB_R1
    ),
  [_BASE_NOMOD] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, KC_EQL,
    KC_CAPS, __________________QWERTY_L2_SFTA___________,                            __________________QWERTY_R2________________, KC_QUOT,
    KC_LSFT, __________________QWERTY_L3________________,                            __________________QWERTY_R3________________, KC_BSLS,
                                        THUMB_L1, THUMB_L2, THUMB_L3,        THUMB_R3, THUMB_R2, THUMB_R1
),
  [_IPC] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    PDF_HL,  XXXXXXX, XXXXXXX, CLASS_E, CLASS_A, KC_SLSH,                             KC_GRV,  _________NUM_789_________, XXXXXXX, _______,
    _______, IPC(A),  IPC(S),  IPC_MIN, IPC(F), KC_DOT,                               AT_IPC,  _________NUM_456_________, KC_COLN, KC_DQUO,
    KC_LNG1, IPC(Z),  HWP_CITE,IPC(C),  KC_EQL,  KC_BSLS,                             XXXXXXX, _________NUM_123_________, _______, KC_PIPE,
                                        _______, _______, _______,          _______, LT(_NAV,KC_0), _______
    ),
  [_NUM] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL,
    _______, XXXXXXX, KC_L,    KC_K,    KC_J,    KC_H,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COLN, KC_DQUO,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_M,    KC_N,                               KC_B,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE,
                                        _______, _______, _______,          _______, _______, _______
    ),
  [_NAV] = LAYOUT_split_3x6_3(          //Navigations
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  NAV_NS,  LCA(KC_J),LCA(KC_K),LCA(KC_L),KC_F5,                          A(KC_7), A(KC_4), A(S(KC_2)),A(KC_6),A(KC_8), XXXXXXX,
    ALT_TAB, KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT, KC_F6,                          KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    C(KC_F1),NAV(Z),  C(KC_X),  C(KC_C),  C(KC_V),  KC_F7,                          KC_APP,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                                        _______, KC_BSPC, KC_DEL,        _______, _______, _______
    ),
  [_FUNC] = LAYOUT_crkbd_wrapper(       //Functions
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    XXXXXXX, C(KC_F1),KC_F2,   KC_F3,   A(KC_F4),KC_F5,                              _____________FUNC_2789____________, XXXXXXX, KC_BSPC,
    XXXXXXX, KC_LSFT, KC_LALT, KC_LCTL, KC_LSFT, KC_F6,                              _____________FUNC_1456____________, XXXXXXX, KC_DEL,
    XXXXXXX, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            _____________FUNC_0123____________, XXXXXXX, XXXXXXX,
                                        _______, _______, _______,          _______, _______, _______
    ),
  [_MOUSE] = LAYOUT_split_3x6_3(       //Mouse keys
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  C(KC_F1), KC_F2,   KC_F3,  A(KC_F4), XXXXXXX,                           XXXXXXX, KC_ACL0, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
    XXXXXXX, KC_LSFT,  KC_WH_D, KC_MS_U, KC_WH_U, XXXXXXX,                           KC_ACL0, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX, QK_MAKE,
    XXXXXXX, XXXXXXX,  KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,                           XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
                                        _______, _______, _______,          _______, _______, _______
    ),
  [_ONEHAND] = LAYOUT_split_3x6_3( //Trackball Manipulation
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  C(KC_F1), KC_F2,   KC_F3,  ALT_F4,  XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO_HOME,
    KC_TAB,  KC_WH_U, KC_BTN2, KC_UP,   KC_BTN1, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    G(KC_R), KC_WH_D, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        KC_LCTL, KC_BSPC, KC_ENT,           TO_HOME, XXXXXXX, XXXXXXX
    )
};
//clang-format on

// COMBOS
enum combos {
    COMBO_ONEHAND,
//     COMBO_NOMOD,
//     COMBO_HOME,
//     COMBO_OS,
//     COMBO_ONEHAND_HOME,
//     //ZB_STENO,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM EQ_combo[] = {KC_ESC,    KC_Q,    COMBO_END};
// const uint16_t PROGMEM pe_combo[] = {KC_P,    KC_EQL,  COMBO_END};
// const uint16_t PROGMEM sq_combo[] = {KC_SCLN, KC_QUOT, COMBO_END};
// const uint16_t PROGMEM os_combo[] = {KC_BSLS, KC_SLSH, COMBO_END};
// const uint16_t PROGMEM oh_combo[] = {KC_BTN2, KC_UP,   COMBO_END};

combo_t key_combos[] = {
    [COMBO_ONEHAND]               = COMBO(EQ_combo, TO(_ONEHAND)),
//     [COMBO_NOMOD]	              = COMBO(pe_combo, TO(_BASE_NOMOD)),
//     [COMBO_HOME]                  = COMBO(sq_combo, TO(_BASE)),
//     [COMBO_OS]                    = COMBO(os_combo, CG_TOGG),
//     [COMBO_ONEHAND_HOME]          = COMBO(oh_combo, TO(_BASE)),
};


