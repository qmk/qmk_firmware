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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//clang-format off

/*
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_LGUI, KC_SPC,   LOWER,      RAISE,  KC_ENT,
                                           KC_LALT, KC_BSPC,     KC_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
),
 */

[_BASE] = LAYOUT_charybdis_wrapper(
// ╭──────────────────────────────────────────────────────╮       ╭──────────────────────────────────────────────────────╮
     KC_ESC,  __________________NUMROW_L_________________,          __________________NUMROW_R_________________, KC_MINS,
     KC_TAB,  __________________QWERTY_L1________________,          __________________QWERTY_R1________________, KC_EQL,
     SFT_CAPS,__________________QWERTY_SACS_L2___________,          __________________QWERTY_R2________________, KC_QUOT,
     KC_LGUI, __________________QWERTY_L3________________,          __________________QWERTY_HOME_R3___________, KC_BSLS,
// ╰──────────────────────────────────────────────────────┤       ├──────────────────────────────────────────────────────╯
                                THUMB_L1,THUMB_L2,THUMB_L3,/*      */THUMB_R3,THUMB_R2,
                                          KC_LNG1, KC_LNG2,/*      */THUMB_R1
//                            ╰───────────────────────────╯       ╰──────────────────╯
),

[_IPC] = LAYOUT_charybdis_wrapper(
// ╭──────────────────────────────────────────────────────╮       ╭──────────────────────────────────────────────────────╮
     ALT_F4,  C(KC_F1),KC_P,    KC_X,    C(G(KC_C)),TO(_ONEHAND),        KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, XXXXXXX, _______,
     KC_LNG2, C(G(KC_C)), XXXXXXX, CLASS_E, CLASS_A, HWP_MACRO,     KC_GRV,  _________NUM_789_________, XXXXXXX, _______,
     _______, IPC(A),  IPC(S),  IPC_MIN, IPC(F), KC_DOT,            AT_IPC,  _________NUM_456_________, KC_COLN, KC_DQUO,
     G(C(KC_SPC)), IPC(Z),  HWP_CITE,IPC(C),  KC_EQL,  KC_BSLS,     XXXXXXX, _________NUM_123_________, _______, KC_PIPE,
// ╰──────────────────────────────────────────────────────┤       ├──────────────────────────────────────────────────────╯
                                _______, _______, _______,/*      */HWP_MACRO, LT(_NAV, KC_0),
                                         QK_BOOT, _______,/*      */G(C(KC_SPC))
//                            ╰───────────────────────────╯       ╰──────────────────╯
),
[_NAV] = LAYOUT_charybdis_wrapper(
// ╭──────────────────────────────────────────────────────╮       ╭──────────────────────────────────────────────────────╮
     _______, CTRL_F1, KC_F2,   KC_F3,   ALT_F4,   KC_F5,           XXXXXXX, A(KC_7), A(KC_5), A(KC_9), A(KC_0), XXXXXXX,
     ALT_TAB, NAV_NS,LCA(KC_J),LCA(KC_K),LCA(KC_L), KC_F6,          S(A(KC_3)), A(KC_4), A(KC_8), A(KC_6), KC_NO, KC_NO,
     KC_LGUI, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,  KC_F7,           KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, DPI_MOD,
     G(C(KC_D)), NAV(Z), C(KC_X), C(KC_C), C(KC_V), C(KC_B),        KC_APP,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  DPI_RMOD,
// ╰──────────────────────────────────────────────────────┤       ├──────────────────────────────────────────────────────╯
                                 _______, KC_BSPC, KC_DEL,/*      */_______, _______,
                                         _______, _______,/*      */_______
//                            ╰───────────────────────────╯       ╰──────────────────╯
),
[_MOUSE] = LAYOUT_charybdis_wrapper(
// ╭──────────────────────────────────────────────────────╮       ╭──────────────────────────────────────────────────────╮
     _______, CTRL_F1, KC_F2,   KC_F3,   ALT_F4,  KC_F5,            KC_F8,  KC_F7,   KC_F8,   KC_F9,   KC_F10,   QK_BOOT,
     KC_U,    KC_BTN4, KC_WH_D, KC_MS_U, KC_WH_U, KC_F6,            KC_F9,  KC_WH_L, XXXXXXX, XXXXXXX, XXXXXXX, QK_MAKE,
     KC_P,    KC_LSFT, KC_MS_L, KC_MS_D, KC_MS_R, KC_F7,            KC_F10, KC_ACL0, KC_BTN1, KC_BTN2, KC_BTN3, KC_ENT,
     KC_X,    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, BOLDFACE,         KC_APP, KC_ACL0, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX,
// ╰──────────────────────────────────────────────────────┤       ├──────────────────────────────────────────────────────╯
                                 _______, KC_BSPC, KC_DEL,/*      */_______, _______,
                                         _______, _______,/*      */QK_BOOT
//                            ╰───────────────────────────╯       ╰──────────────────╯
),

[_FUNC] = LAYOUT_charybdis_wrapper(
// ╭──────────────────────────────────────────────────────╮       ╭──────────────────────────────────────────────────────╮
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_F12, KC_F7,   KC_F8,  KC_F9,    XXXXXXX,  XXXXXXX,
     XXXXXXX, KC_LSFT, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,          KC_F11, KC_F4,   KC_F5,   KC_F6,   XXXXXXX,   XXXXXXX,
     XXXXXXX, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_F10, KC_F1,   KC_F2,   KC_F3,   XXXXXXX,   XXXXXXX,
// ╰──────────────────────────────────────────────────────┤       ├──────────────────────────────────────────────────────╯
                                _______, _______, _______,/*      */_______, _______,
                                         _______, _______,/*      */_______
//                            ╰───────────────────────────╯       ╰──────────────────╯
),

[_ONEHAND] = LAYOUT_charybdis_wrapper(
// ╭──────────────────────────────────────────────────────╮       ╭──────────────────────────────────────────────────────╮
     XXXXXXX, CTRL_F1, KC_F2,   KC_F3,   ALT_F4,  KC_F5,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
     XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, KC_WH_U, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_MAKE,
     S_D_MOD, KC_LCTL, KC_BTN2, KC_LSFT, KC_BTN1, DPI_MOD,          XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX, XXXXXXX,
     S_D_RMOD,KC_LGUI, KC_BTN3, KC_BTN4, KC_BTN5, DPI_RMOD,         C(KC_W), KC_BTN4, KC_BTN5, DRGSCRL, SNIPING, XXXXXXX,
// ╰──────────────────────────────────────────────────────┤       ├──────────────────────────────────────────────────────╯
                                KC_LCTL, DRGSCRL, SNIPING,/*      */_______, _______,
                                         _______, _______,/*      */TO(_BASE)
//                            ╰───────────────────────────╯       ╰──────────────────╯
),
};
// in keymap.c:
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_ONEHAND); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // checks highest layer other than target layer
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case _MOUSE:
            // remove_auto_mouse_target must be called to adjust state *before* setting enable
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
    }
    // recommend that any code that makes adjustment based on auto mouse layer state would go here
    return state;
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case DRGSCRL:
        case SNIPING:
        case KC_LCTL:
        case KC_LALT:
        case KC_LSFT:
            return true;
        default:
            return false;
    }
    return is_mouse_record_user(keycode, record);
}

char chordal_hold_handedness(keypos_t key) {
    if (key.col == 0 || key.col == MATRIX_COLS - 1) {
        return '*';  // Exempt the outer columns.
    }
    // On split keyboards, typically, the first half of the rows are on the
    // left, and the other half are on the right.
    return key.row < MATRIX_ROWS / 2 ? 'L' : 'R';
}
