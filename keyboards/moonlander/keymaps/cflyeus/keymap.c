/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "version.h"

#define ESC_CTL LCTL_T(KC_ESC)
#define TOG_WS MT(MOD_LGUI | MOD_LSFT, KC_PSCR)

enum layers {
    _COLEMAK,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    VRSN = SAFE_RANGE,
    COLEMAK,
    QWERTY
};


enum unicode_names {
    AE_L,
    AE_U,
    OE_L,
    OE_U,
    AA_L,
    AA_U,
    IRONY,
    SNEK
};

const uint32_t unicode_map[] PROGMEM = {
    [AE_L]  = 0x00E6,  // æ
    [AE_U]  = 0x00C6,  // Æ
    [OE_L]  = 0x00F8,  // ø
    [OE_U]  = 0x00D8,  // Ø
    [AA_L]  = 0x00E5,  // å
    [AA_U]  = 0x00C5,  // Å
    [SNEK]  = 0x1F40D, // 🐍
};

#define KC_AE XP(AE_L,AE_U)
#define KC_OE XP(OE_L,OE_U)
#define KC_AA XP(AA_L,AA_U)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    [_COLEMAK] = LAYOUT_moonlander(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,           _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TOG_WS,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    _______,           KC_AA,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
        ESC_CTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_AE,             KC_OE,   KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_RCTL,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                                KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        _______, _______, _______, KC_LALT, MO(_LOWER),  KC_BSPC,               KC_RGUI, MO(_RAISE), KC_LALT, _______, _______, _______,
                                     KC_SPC,  KC_BSPC, KC_RGUI,                  KC_RGUI, KC_LALT, KC_ENT
    ),
    [_QWERTY] = LAYOUT_moonlander(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,           _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,           _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,           _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    _______, _______, _______, _______,
        _______,_______,_______,_______,  _______,       _______,                        _______,  _______, _______, _______, _______, _______,
                                          _______,  _______, _______,                  _______, _______, _______
    ),


    [_LOWER] = LAYOUT_moonlander(                                                                      
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_UP,   _______, _______, _______,           _______, KC_AA,   KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_WH_U, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, _______,           _______, KC_OE,   KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
        _______, KC_WH_D, _______, KC_HOME, KC_END,  KC_PGDN,                             KC_AE,   KC_1,    KC_2,    KC_3,    KC_MINS, _______,
        _______, _______, _______, _______, _______,       _______,                 _______,       _______, KC_0,    _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [_RAISE] = LAYOUT_moonlander(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,           _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_UNDS, KC_F12,
        _______, KC_GRV,  KC_LCBR, KC_LBRC, KC_LPRN, KC_LABK, _______,           _______, KC_QUOT, KC_DQUO, KC_QUES, KC_PLUS, KC_SCLN, _______,
        _______, KC_TILD, KC_RCBR, KC_RBRC, KC_RPRN, KC_RABK,                             KC_EQL,  KC_BSLS, KC_SLSH, KC_PIPE, KC_COLN, _______,
        EE_CLR,  _______, _______, _______, _______,       _______,                   _______,     _______, _______, _______, _______, _______,
                                            _______, _______, _______,             _______,_______, _______
    ),

    [_ADJUST] = LAYOUT_moonlander(
        RGB_TOG, _______, _______, _______, _______, _______, QWERTY,            COLEMAK, _______, _______, _______, _______, _______, _______,
        QK_BOOT, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,           VRSN,    _______, _______, _______, KC_MUTE, _______, _______,
      LED_LEVEL, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, _______,           _______, _______, KC_MPRV, KC_MNXT, KC_VOLU, _______, _______,
        _______, KC_WH_D, _______, _______, _______, KC_BTN2,                             _______, KC_MSTP, KC_MPLY, KC_VOLD, _______, _______,
        _______, _______, _______, _______, _______,       _______,                 _______,       _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QWERTY: 
                set_single_persistent_default_layer(_QWERTY);
                return false;   
            case COLEMAK: 
                set_single_persistent_default_layer(_COLEMAK);
                return false;      
            case VRSN:
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
        }
    }
    return true;
}
