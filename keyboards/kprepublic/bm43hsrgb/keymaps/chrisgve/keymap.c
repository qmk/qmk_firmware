/* Copyright 2021 bitstarr
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

#include "chrisgve.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY_MAC] = LAYOUT(
        KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CPS_CTL, KC_A,    KC_S,    M_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SLS_SFT,
        KC_TAB,  KC_LALT, KC_LGUI,                   SPC_RSE, SPC_LWR,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_MAC_NAV_1] = LAYOUT(
        _______, _______, M_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, M_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,          _______,
        _______,          _______, _______, _______, _______, M_B_WRD, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
    ),

    [_MAC_NAV_2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
    ),

    [_QWERTY_LINUX] = LAYOUT(
        KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CPS_CTL, KC_A,    KC_S,    L_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SLS_SFT,
        KC_TAB, KC_LGUI, KC_LALT,                    SPC_RSE, SPC_LWR,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_LINUX_NAV_1] = LAYOUT(
        _______, _______, L_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, L_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,          _______,
        _______,          _______, _______, _______, _______, L_B_WRD, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
    ),

    [_LINUX_NAV_2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
    ),

    [_QWERTY_WIN] = LAYOUT(
        KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CPS_CTL, KC_A,    KC_S,    W_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SLS_SFT,
        KC_TAB,  KC_LGUI, KC_LALT,                   SPC_RSE, SPC_LWR,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_WIN_NAV_1] = LAYOUT(
        _______, _______, W_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, W_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,          _______,
        _______,          _______, _______, _______, _______, W_B_WRD, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
    ),

    [_WIN_NAV_2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
    ),

    [_LOWER] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TAB,  _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC,          KC_RBRC,
        _______,          _______, _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT, KC_BSLS,
        _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
    ),

    [_RAISE] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_TAB,  _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR,          KC_RCBR,
        _______,          _______, _______, _______, _______, _______, _______, _______, KC_COLN, KC_DQUO, KC_PIPE,
        _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
    ),

    [_CONFIG] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          DF_MAC,  DF_LNX,  DF_WIN,  _______, _______, _______, KC_MUTE, _______, _______, _______,
        RESET,   _______, _______,                   _______, _______,          KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
    ),

};

// RGB configuration and setup light layer for caps on

extern rgblight_config_t rgblight_config;

void keyboard_post_init_user(void) {
    // Disable the underglow
    rgblight_disable();
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    rgblight_enable();
    rgblight_setrgb(0xFF, 0xFF, 0xFF);
  } else {
    rgblight_disable();
  }
}

// Combo configuration, to make GUI/ALT-Esc as GUI/ALT-Tab

//enum combo_events {
//    SWITCH_MAC_WIN_FWD,
//    SWITCH_MAC_WIN_BKD,
//    SWITCH_WIN_WIN_FWD,
//    SWITCH_WIN_WIN_BKD,
//    COMBO_LENGTH,
//};
//uint16_t COMBO_LEN = COMBO_LENGTH;
//
//const uint16_t PROGMEM switch_mac_win_fwd[] = {G(KC_GESC), COMBO_END};
//const uint16_t PROGMEM switch_mac_win_bkd[] = {S(G(KC_GESC)), COMBO_END};
//const uint16_t PROGMEM switch_win_win_fwd[] = {A(KC_GESC), COMBO_END};
//const uint16_t PROGMEM switch_win_win_bkd[] = {S(A(KC_GESC)), COMBO_END};
//
//combo_t key_combos[] = {
//    COMBO(switch_mac_win_fwd, G(KC_TAB)),
//    COMBO(switch_mac_win_bkd, S(G(KC_TAB))),
//    COMBO(switch_win_win_fwd, A(KC_TAB)),
//    COMBO(switch_win_win_bkd, S(A(KC_TAB))),
//};

//combo_t key_combos[] = {
//    [SWITCH_MAC_WIN_FWD] = COMBO_ACTION(switch_mac_win_fwd),
//    [SWITCH_MAC_WIN_BKD] = COMBO_ACTION(switch_mac_win_bkd),
//    [SWITCH_WIN_WIN_FWD] = COMBO_ACTION(switch_win_win_fwd),
//    [SWITCH_WIN_WIN_FWD] = COMBO_ACTION(switch_win_win_bkd),
//};

//void process_combo_event(uint16_t combo_index, bool pressed) {
//    switch(combo_index) {
//        case SWITCH_MAC_WIN_FWD:
//            if (pressed) {
//                tap_code16(G(KC_TAB));
//            }
//            break;
//        case SWITCH_MAC_WIN_BKD:
//            if (pressed) {
//                tap_code16(S(G(KC_TAB)));
//            }
//            break;
//        case SWITCH_WIN_WIN_FWD:
//            if (pressed) {
//                tap_code16(A(KC_TAB));
//            }
//            break;
//        case SWITCH_WIN_WIN_BKD:
//            if (pressed) {
//                tap_code16(S(A(KC_TAB)));
//            }
//            break;
//    }
//};
// Allows to make both space bars to activate the layer CONFIG

bool lower_layer_state = false;
bool raise_layer_state = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_LWR:
            if (record->event.pressed) {
                lower_layer_state = true;
            } else {
                lower_layer_state = false;
            }
            break;
        case SPC_RSE:
            if (record->event.pressed) {
                raise_layer_state = true;
            } else {
                raise_layer_state = false;
            }
            break;
    }
    if (lower_layer_state & raise_layer_state) {
        layer_on(_CONFIG);
    } else {
        if (layer_state_is(_CONFIG)) {
            layer_off(_CONFIG);
        }
    }
    return true;
};
