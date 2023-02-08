/* Copyright 2022 oco9oco <oco9oco@gmail.com>
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

#include "oco9oco.h" //look for users/oco9oco/
// Keyboard Layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//clang-format off
[_BASE] = LAYOUT_ID75_wrapper( /* QWERTY */
    KC_ESC,    KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,    KC_MINS, KC_GRV,  KC_EQL,   KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,    KC_DEL,
    KC_TAB,    __________________QWERTY_L1________________, KC_HOME, BRKT,    KC_PGUP,    __________________QWERTY_R1________________,   KC_BSPC,
    KC_CAPS,   __________________QWERTY_SACS_L2___________, KC_END,  KC_UP,   KC_PGDN,    __________________QWERTY_HOME_R2___________,   KC_QUOT,
    KC_LSFT,   __________________QWERTY_GUIZ_L3___________, KC_LEFT, KC_DOWN, KC_RGHT,    __________________QWERTY_R3________________,   KC_BSLS,
    KC_LCTL,   KC_LGUI, KC_LALT, KC_SLSH, THUMB_L1,THUMB_L2,THUMB_L3,TG(_ALT),THUMB_R3, THUMB_R2,THUMB_R1,KC_LANG1,KC_LANG2, XXXXXXX,    _
),
[_ALT] = LAYOUT_ID75_wrapper( /* QWERTY */
    _______,   _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,      _______,
    _______,   __________________QWERTY_L1________________, _______, _______, _______,  __________________QWERTY_R1________________,      _______,
    _______,   __________________QWERTY_L1________________, _______, _______, _______,  __________________QWERTY_R2________________,      _______,
    _______,   __________________QWERTY_L3________________, _______, _______, KC_B,     __________________QWERTY_R3________________,      _______,
    _______,   _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,      _______
),
[_SORIZAVA_3BEOL] = LAYOUT_ID75_wrapper( /* MACRO */
    XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX, KC_U,    KC_P,    KC_X,    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,       XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, _______,  _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,      _______
),


[_NAV] = LAYOUT_ID75_wrapper( /* QWERTY */
    _______,   C(KC_F1),_______, _______, A(KC_F4),KC_F5,   _______, _______, _______,  _______, _______, _______, _______, _______,      _______, 
    _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F6,   _______, _______, _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      _______, 
    _______,   KC_LSFT, KC_LALT, KC_LCTL, KC_LSFT, KC_F7,   _______, _______, _______,  XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      _______, 
    _______,   NAV(Z), C(KC_X),C(KC_C), C(KC_V), C(KC_B),   _______, _______, _______,  KC_APP,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,       _______, 
    _______,   _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,      _______
),
[_IPC] = LAYOUT_ID75_wrapper(
   _______, PDF_HL,  KC_P,    KC_X,    XXXXXXX, XXXXXXX,    _______, _______, _______,  KC_LT,   KC_LPRN, KC_GRV,  KC_RPRN, KC_GT,        _______,
   _______, A(KC_1), A(KC_2), A(KC_3), A(KC_7), A(KC_8),    _______, _______, _______,  KC_LBRC, _________NUM_789_________, KC_RBRC,      _______,
   _______, IPC(A),  IPC(S),  IPC_MIN, IPC(F),  KC_DOT,     _______, _______, _______,  KC_GRV,  _________NUM_456_________, KC_COLN,      KC_DQUO,
   _______, IPC(Z),  BRKT,    IPC(C),  KC_EQL,  KC_COLN,    _______, _______, _______,  A(KC_2), _________NUM_123_________, _______,      KC_PIPE,
   _______, _______, _______, _______, _______, _______,    _______, _______, _______,  LT(_NAV, KC_0),_______, _______, _______, _______,_______
),
[_MOUSE] = LAYOUT_ID75_wrapper(
   _______,    C(KC_F1),_______, _______, A(KC_F4),KC_F5,   _______, _______, _______,  _______, _______, _______, _______, _______,      RESET,
    KC_U,      XXXXXXX, KC_WH_D, KC_MS_U, KC_WH_U, XXXXXXX, _______, _______, _______,  XXXXXXX, KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
    KC_P,      KC_LSFT, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, _______, _______, _______,  KC_INS,  KC_ACL0, KC_BTN1, KC_BTN2, KC_BTN3,      XXXXXXX,
    KC_X,      UNDO,    CUT,     COPY,    PASTE,   BOLDFACE,_______, _______, _______,  KC_APP,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      XXXXXXX,
    _______,   _______, _______, KC_LCTL, KC_SPC,  KC_ENT,  _______, _______, _______,  KC_TRNS, _______, _______, _______, _______,      _______
),
};
//clang-format on

// COMBOS
enum combos {
    COMBO_ONEHAND,
    //ZB_STENO, 
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM onehand_combo[] = {KC_Q, KC_W, COMBO_END};
//const uint16_t PROGMEM STENO_combo[] = {SFTT_Z, KC_B, COMBO_END};
combo_t key_combos[] = {
    [COMBO_ONEHAND]   = COMBO(onehand_combo, TO(_ONEHAND)),
//    [ZB_STENO]   = COMBO(STENO_combo, TO(_SORIZAVA_3BEOL)),
};

// // Tapping term
// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case THUMB_L2:
//             return TAPPING_TERM - 100;
//       case LGUI_T(KC_F): 
//       case LGUI_T(KC_Z):
//          return TAPPING_TERM + 200;
//         case SFTT_F:
//         case SFTT_J:
//         case GUIT_A:
//         case GUIT_SCL:   
//             return TAPPING_TERM + 50;
//          case SFTT_A:
//          case SFTT_Z:
//             return TAPPING_TERM + 100;
//         default:
//             return TAPPING_TERM;
//     }
// }
// //Get hold on other key press
// bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case THUMB_L2:
//             return true;    
//         case SFTT_A:
//         case SFTT_Z:    
//             return true;// KEY_ROW, KEY_COL: look for oco9oco.h 
//         default:
//             return false;
//     }
// }
// // Ignore mod tap interrupt
// bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case THUMB_L2:
//         case THUMB_R1:
//         case THUMB_R2:
//         case THUMB_R3:
//         case LGUI_T(KC_F):
//         case SFTT_A:
//         case SFTT_Z:
//         case SFTT_F:
//         case SFTT_J:
//         case ALTT_S:
//         case CTLT_D:
//         case GUIT_SCL:
//         case ALTT_L:
//         case CTLT_K:
//         case GUIT_A:
//         case LGUI_T(KC_Z):
//         case LT(_NAV, KC_0):
//             return true;
//         default:
//             return false;
//     }
// }
