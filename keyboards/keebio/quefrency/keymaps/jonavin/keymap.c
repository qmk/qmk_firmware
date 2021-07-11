/* Copyright 2021 Jonavin Eng
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


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
    _BASE,
    _FN1,
    _MO2,
    _MO3,
};

enum custom_keycodes {
  DOUBLEZERO = SAFE_RANGE,
};

// Tap Dance Definitions
enum custom_tapdance {
  TD_LSFT_CAPSLOCK,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for shift, twice for Caps Lock
  [TD_LSFT_CAPSLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

#define KC_LSFTCAPS TD(TD_LSFT_CAPSLOCK)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DOUBLEZERO:
        if (record->event.pressed) {
            // when keycode DOUBLEZERO is pressed
            SEND_STRING("00");
        } else {
            // when keycode DOUBLEZERO is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65(
      KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_INS,
      KC_PSCR, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL,
      TT(_MO2), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
      KC_LSFTCAPS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LALT, LT(_FN1, KC_SPC), KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    [_FN1] = LAYOUT_65(
      KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_CALC, KC_NO,
      RGB_TOG, RGB_MOD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
      KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_HOME,
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, RCTL(KC_PGUP), KC_END,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_APP, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)),
    [_MO2] = LAYOUT_65(
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_P0, KC_PMNS, KC_PPLS, KC_PSLS, KC_PEQL, KC_TRNS,
      KC_TAB, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_TAB, KC_P1, KC_P2, KC_P3, KC_NO, KC_PAST, KC_PENT, KC_HOME,
      KC_TRNS, KC_NO, KC_DEL, KC_INS, KC_NO, KC_NO, KC_NLCK, KC_P0, DOUBLEZERO, KC_PDOT, KC_PSLS, KC_TRNS, RCTL(KC_PGUP), KC_END,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)),
    [_MO3] = LAYOUT_65(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_DOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

#ifdef ENCODER_ENABLE       // Encoder Functionality
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index)
    {
    case 0:  // first encoder (Left Macro set)
            if (clockwise) {
            tap_code(KC_PGDN);
        }  else {
            tap_code(KC_PGUP);
        }

    default: // other encoder (Top right)
        if ( clockwise ) {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, Page up
                unregister_mods(MOD_BIT(KC_LSFT));
                register_code(KC_PGDN);
                register_mods(MOD_BIT(KC_LSFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate next word
                    tap_code16(LCTL(KC_RGHT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next track
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else  {
                tap_code(KC_VOLU);                                                   // Otherwise it just changes volume
            }
        } else {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) {
                unregister_mods(MOD_BIT(KC_LSFT));
                register_code(KC_PGUP);
                register_mods(MOD_BIT(KC_LSFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate previous word
                tap_code16(LCTL(KC_LEFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media previous track
                tap_code(KC_MEDIA_PREV_TRACK);
            } else {
                tap_code(KC_VOLD);
            }
        }
        break;
    }
    return true;
}
#endif
