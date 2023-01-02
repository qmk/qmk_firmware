/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Tyler Thrailkill <@snowe/@snowe2010>

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
#include "snowe.h"

// Symbols chart
// ↯ hyper key (ctrl, alt, shift, super)
// ⌘ command
// ⌥ option
// ⌃ control
// ⇧ shift
// ⌫ backspace
// ⌦ delete
// ⎋ escape
// ↩ enter

/* Wrapper
 * ,-----------------------------------------------. .-----------------------------------------------.
 * |  Tab  |  K01  |  K02  |  K03  |  K04  |  K05  | |  K06  |  K07  |  K08  |  K09  |  K0A  |       |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |  ⌘/⎋  | ⌃/K11 |  K12  |  K13  |  K14  |  K15  | |  K16  |  K17  |  K18  |  K19  | ⌥/K1A |       |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |  ↯/⌦  | ⌥/K21 |  K22  |  K23  |  K24  |  K25  | |  K26  |  K27  |  K28  |  K29  | ⌃/K2A |       |
 * `-----------------------.                       | |                       .-----------------------'
 *                         |-------+-------+-------| |-------+-------+-------|
 *                         |   ⌃   |  ⇧/↩  | ⌫/LWR | | ␣/RAY |   ␣   |  R ⌥  |
 *                         `-----------------------' '-----------------------'
 */
// clang-format off
#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_TAB,         K01,         K02, K03, K04, K05,     K06, K07, K08, K09,        K0A,  KC_MINS, \
    GUI_ESC,        CTL_T(K11),  K12, K13, K14, K15,     K16, K17, K18, K19, ALT_T(K1A),  KC_QUOT, \
    HYPR_T(KC_DEL), ALT_T(K21),  K22, K23, K24, K25,     K26, K27, K28, K29, RCTL_T(K2A), KC_BSLS, \
                        KC_LCTL,    LOWER,  SH_BKSP,       KC_ENTER, SP_RAIS,  KC_LALT             \
  )
// clang-format on
#define LAYOUT_crkbd_base_wrapper(...) LAYOUT_crkbd_base(__VA_ARGS__)
// clang-format off
#define LAYOUT_crkbd_no_hold_shortcuts( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_TAB,   K01,  K02, K03, K04, K05,     K06, K07, K08, K09, K0A, KC_MINS, \
    GUI_ESC,  K11,  K12, K13, K14, K15,     K16, K17, K18, K19, K1A, KC_QUOT, \
    KC_LSFT,  K21,  K22, K23, K24, K25,     K26, K27, K28, K29, K2A, KC_BSLS, \
               KC_LCTL, LOWER, KC_BSPC,     KC_ENTER, SP_RAIS, KC_LALT                \
  )
// clang-format on
#define LAYOUT_crkbd_no_hold_shortcuts_wrapper(...) LAYOUT_crkbd_no_hold_shortcuts(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /* QWERTY
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       |   Q   |   W   |   E   |   R   |   T   | |   Y   |   U   |   I   |   O   |   P   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   A   |   S   |   D   |   F   |   G   | |   H   |   J   |   K   |   L   |   ;   |  '    |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |   Z   |   X   |   C   |   V   |   B   | |   N   |   M   |   ,   |   .   |   /   |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |       |       |       | |       |       |       |
     *                         `-----------------------' '-----------------------'
     */
    [_MAIN] = LAYOUT_crkbd_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),
    [_GAMING] = LAYOUT_crkbd_no_hold_shortcuts_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    /* Lower
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |   ~   |   !   |   @   |   #   |   $   |   %   | |   ^   |   &   |   *   |   (   |   )   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |       |   _   |   +   |   [   |   ]   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |       |   ←   |   ↑   |   ↓   |   →   |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |       |       |       | |       |       |       |
     *                         `-----------------------' '-----------------------'
     */
    [_LOWER] = LAYOUT_wrapper(
        KC_TILDE,  _________________LOWER_L1__________________,                    _________________LOWER_R1__________________, KC_F11,
        KC_F12  ,  _________________LOWER_L2__________________,                    _________________LOWER_R2__________________, KC_PIPE,
        _______ ,  _________________LOWER_L3__________________,                    _________________LOWER_R3__________________, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),


    /*
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |       |       |       |       |       |       | |       |       |       |       |       |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |       |       |       |       |       |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |       |       |       |       |       |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |       |       |       | |       |       |       |
     *                         `-----------------------' '-----------------------'
     */
    /* Raise
     * ,-----------------------------------------------. .-----------------------------------------------.
     * |   `   |   1   |   2   |   3   |   4   |   5   | |   6   |   7   |   8   |   9   |   0   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |       |   ←   |   ↑   |   ↓   |   →   |       |
     * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
     * |       |       |       |       |       |       | |       | home  |pg down| pg up |  end  |       |
     * `-----------------------.                       | |                       .-----------------------'
     *                         |-------+-------+-------| |-------+-------+-------|
     *                         |       |       |       | |       |       |       |
     *                         `-----------------------' '-----------------------'
     */
    [_UPPER] = LAYOUT_wrapper( \
         KC_GRV, _________________RAISE_L1__________________,                    _________________RAISE_R1__________________, _______,
        _______, _________________RAISE_L2__________________,                    _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________,                    _________________RAISE_R3__________________, _______,
                                         _______, _______, _______,        _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_wrapper( \
        _______, _________________ADJUST_L1_________________,                         _________________ADJUST_R1_________________, KC_RESET,
        _______, _________________ADJUST_L2_________________,                         _________________ADJUST_R2_________________, EE_CLR,
        _______, _________________ADJUST_L3_________________,                         _________________ADJUST_R3_________________, KC_MPLY,
                                            _______, _______, _______,        _______, _______, _______
    )
    // clang-format on
};

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _UPPER, _ADJUST); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
#ifdef OCEAN_DREAM_ENABLE
            is_calm = (record->event.pressed) ? true : false;
#endif
#ifdef LUNA_ENABLE
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
#endif
            break;
        case KC_SPC:
#ifdef LUNA_ENABLE
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
#endif
            break;
    }
    return true;
}

// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//    switch (keycode) {
//        case ALT_T(KC_A):
//        case SH_BKSP:
//            return TAPPING_TERM + 500;
//        default:
//            return TAPPING_TERM;
//    }
//}
//
// bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
//    switch (keycode) {
//        case ALT_T(KC_A):
//        case SH_BKSP:
//            return true;
//        default:
//            return false;
//    }
//}