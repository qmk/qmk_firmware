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
    KC_ESC,  __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, KC_EQL,
    KC_CAPS, __________________QWERTY_SACS_L2___________,                            __________________QWERTY_HOME_R2___________, KC_QUOT,
    KC_LSFT, __________________QWERTY_GUIZ_L3___________,                            __________________QWERTY_R3________________, KC_BSLS,
                                        THUMB_L1, THUMB_L2, KC_DEL,       THUMB_R3, THUMB_R2, THUMB_R1
    ),
  [_BASE_NOMOD] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, KC_EQL,
    KC_CAPS, __________________QWERTY_L2_SFTA___________,                            __________________QWERTY_R2________________, KC_QUOT,
    KC_LSFT, __________________QWERTY_L3________________,                            __________________QWERTY_R3________________, KC_BSLS,
                                        THUMB_L1, THUMB_L2, KC_DEL,        THUMB_R3, THUMB_R2, THUMB_R1
),
  [_IPC] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    PDF_HL,  HAEN_B,  HAEN_C,  CLASS_E, CLASS_A, KC_SLSH,                            KC_GRV,  _________NUM_789_________, KC_RBRC, KC_PLUS,
    _______, IPC(A),  IPC(S),  IPC_MIN, IPC_COMM,KC_DOT,                             KC_LBRC, _________NUM_456_________, KC_COLN, KC_DQUO,
    KC_LANG1,IPC(Z),  HWP_CITE,IPC(C),  KC_EQL,  KC_BSLS,                            KC_RBRC, _________NUM_123_________, _______, KC_PIPE,
                                        _______, _______, _______,          _______, LT(_NAV,KC_0), _______
    ),
  [_NUM] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
    _______, KC_LGUI, KC_LALT, _NUM_MIN,KC_LSFT, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COLN, KC_DQUO,
    _______, KC_SPC,  BULLET_U,KC_COMM, BULLET_D,KC_DOT,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE,
                                        _______, _______, _______,          A(KC_1), LT(_NAV,KC_0),KC_SPC
    ),
  [_NAV] = LAYOUT_split_3x6_3(          //Navigations
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    ALT_F4,  LCA(KC_H),LCA(KC_J),LCA(KC_K),LCA(KC_L),KC_F6,                          XXXXXXX, A(KC_4), A(KC_6), A(KC_7), A(KC_8), XXXXXXX,
    KC_F2,   KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_F7,                          KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    C(KC_F1),C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  C(KC_B),                        KC_APP,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                                           _______, KC_BSPC, KC_DEL,        _______, _______, _______
    ),
  [_FUNC] = LAYOUT_crkbd_wrapper(       //Functions
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    XXXXXXX, C(KC_F1),KC_F2,   KC_F3,   A(KC_F4),KC_F5,                              _____________FUNC_2789____________, XXXXXXX, KC_BSPC,
    XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_F6,                              _____________FUNC_1456____________, XXXXXXX, KC_DEL,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            _____________FUNC_0123____________, XXXXXXX, XXXXXXX,
                                        _______, _______, _______,          _______, _______, _______
    ),
  [_MOUSE] = LAYOUT_split_3x6_3(       //Mouse keys
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_U,    C(KC_F1), KC_WH_D, KC_MS_U, KC_WH_U, XXXXXXX,                              XXXXXXX,KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX,  RESET,
    KC_P,    KC_H,     KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,                              KC_INS, KC_ACL0, KC_BTN1, KC_BTN2, KC_BTN3,  KC_ENT,
    KC_X,    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                KC_APP, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_DEL,
                                        _______, _______, _______,          _______, _______, _______
    ),
  [_ONEHAND] = LAYOUT_split_3x6_3( //Trackball Manipulation
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  KC_WH_U, KC_BTN2, KC_UP,   KC_BTN1, ALT_F4,                             XXXXXXX, G(KC_7), G(KC_8), G(KC_9), XXXXXXX, XXXXXXX,
    XXXXXXX, KC_WH_D, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,                            XXXXXXX, G(KC_4), G(KC_5), G(KC_6), XXXXXXX, XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, G(KC_1), G(KC_2), G(KC_3), XXXXXXX, XXXXXXX,
                                        KC_DEL,  KC_SPC, KC_ENT,            XXXXXXX, XXXXXXX, XXXXXXX
    )
};
//clang-format on

// COMBOS
enum combos {
    COMBO_ONEHAND,
    COMBO_NOMOD,
    COMBO_HOME,
    COMBO_OS,
    COMBO_ONEHAND_HOME,
    //ZB_STENO,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM qw_combo[] = {KC_W,    KC_E,    COMBO_END};
const uint16_t PROGMEM pe_combo[] = {KC_P,    KC_EQL,  COMBO_END};
const uint16_t PROGMEM sq_combo[] = {KC_SCLN, KC_QUOT, COMBO_END};
const uint16_t PROGMEM os_combo[] = {KC_BSLS, KC_SLSH, COMBO_END};
const uint16_t PROGMEM oh_combo[] = {KC_BTN2, KC_UP,   COMBO_END};

combo_t key_combos[] = {
    [COMBO_ONEHAND]               = COMBO(qw_combo, TO(_ONEHAND)),
    [COMBO_NOMOD]	              = COMBO(pe_combo, TO(_BASE_NOMOD)),
    [COMBO_HOME]                  = COMBO(sq_combo, TO(_BASE)),
    [COMBO_OS]                    = COMBO(os_combo, CG_TOGG),
    [COMBO_ONEHAND_HOME]          = COMBO(oh_combo, TO(_BASE)),
};

// Key overrides

const key_override_t DEL_override = ko_make_basic(MOD_MASK_SHIFT, KC_DEL, KC_BSPC);   // Shift + del = bspc
//   // shift + caps lock = toggle control - gui

const key_override_t **key_overrides = (const key_override_t *[]){                              // This globally defines all key overrides to be used
    &DEL_override, //&OS_override,
    NULL                                                                                        // Null terminate the array of overrides!
};

