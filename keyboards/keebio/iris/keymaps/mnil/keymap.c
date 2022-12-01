/* Copyright 2021 Mats Nilsson
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

#include "mnil.h"

const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {5, 5, 5, 5};

#define HSV_DEFAULT 32, 255, 255

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _SYMBOLS, _NAVIGATION, _NUMPAD);

    switch (get_highest_layer(state)) {
        case _NUMPAD:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _NAVIGATION:
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            break;
        case _SYMBOLS:
            rgblight_sethsv_noeeprom(HSV_AZURE);
            break;
        default:  //  for any other layers, or the default layer
            rgblight_sethsv_noeeprom(HSV_DEFAULT);
            break;
    }
    return state;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
                  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
                     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
                  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    TD(OAA), KC_NO,
                  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_LSFT, TD(AAE), KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_NO,
                  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    _NAV_SPC,         _SYM_ENT,KC_K,    KC_H,    KC_COMM, KC_DOT,  SE_MINS, KC_LGUI,
                  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                                    KC_LGUI, SFT_TAB, _NAV_SPC,                  _SYM_ENT,CTL_BSPC,ALT_DEL),
                  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  [_SYMBOLS] = LAYOUT(
                  //┌────────┬────────┬────────┬────────┬────────┬────────┐                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
                     KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
                  //├────────┼────────┼────────┼────────┼────────┼────────┤                           ├────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, KC_NO,   SE_PIPE, SE_LBRC, SE_RBRC, KC_NO,                               S(KC_5), SE_QUES, SE_AT,   SE_EQL,  SE_DLR,  KC_TRNS,
                  //├────────┼────────┼────────┼────────┼────────┼────────┤                           ├────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, SE_LCBR, SE_RCBR, SE_LPRN, SE_RPRN, KC_NO,                               SE_PLUS, S(KC_1), S(KC_2), S(KC_3), SE_AMPR, KC_TRNS,
                  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, M_TILD,  M_CIRC,  SE_LABK, SE_RABK, KC_NO,   KC_TRNS,           KC_TRNS, SE_QUOT, SE_SLSH, SE_BSLS, SE_ASTR, M_BTCK,  KC_TRNS,
                  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘         └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                                    KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS ),
                  //                               └────────┴────────┴────────┘                  └────────┴────────┴────────┘
  [_NAVIGATION] = LAYOUT(
                  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, KC_NO,   CUT,     COPY,    PASTE,   AUTOFILL,                           KC_NO,   KC_HOME, KC_WH_D, KC_WH_U, KC_END,  KC_NO,
                  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, KC_ACL0, KC_ACL1, KC_BTN2, KC_BTN1, KC_LCTL,                            KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_R,
                  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, KC_ACL2, KC_BTN4, KC_BTN3, KC_BTN5, KC_NO,   KC_TRNS,          KC_TRNS, KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LCTL,
                  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS ),
                  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  [_NUMPAD] = LAYOUT(
                  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
                     RGB_TOG, RGB_M_P, RGB_M_B, KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
                  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, QUIT,    WIN,     MVWSL  , MVWSR,   CRYWS,                              TERM,    KC_7,    KC_8,    KC_9,    KC_COMM, KC_NO,
                  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, CS_TAB,  C_TAB,   PRVWS,   NXTWS,   I3MOD,                              OPEN,    KC_4,    KC_5,    KC_6,    KC_0,    KC_NO,
                  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                     KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, MOVWS,   KC_TRNS,          KC_TRNS, BROWSER, KC_1,    KC_2,    KC_3,    KC_DOT,  KC_NO,
                  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS ),
                  //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
};
// clang-format on
