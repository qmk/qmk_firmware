/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Jonavin

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

enum custom_layers {
    _BASE,
    _FN1,
    _MO2,
    _MO3,
};

enum custom_keycodes {
  KC_00 = SAFE_RANGE,
  KC_WINLCK,    //Toggles Win key on and off
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

bool _isWinKeyDisabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_00:
        if (record->event.pressed) {
            // when keycode KC_00 is pressed
            SEND_STRING("00");
        } else {
            // when keycode KC_00 is released
        }
        break;

    case KC_WINLCK:
        if (record->event.pressed) {
            _isWinKeyDisabled = !_isWinKeyDisabled; //toggle status
            if(_isWinKeyDisabled) {
                process_magic(GUI_OFF, record);
            } else {
                process_magic(GUI_ON, record);
            }
        } else  unregister_code16(keycode);
        break;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Ins           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        TT(_MO2), KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFTCAPS,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_CALC,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
        _______, _______, RGB_VAI, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, _______, RESET,            KC_HOME,
        KC_CAPS, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_END,
        _______,          _______, RGB_HUI, _______, _______, _______, KC_NLCK, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, KC_WINLCK, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [_MO2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,          _______,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, _______, _______, _______,          KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_PAST,          KC_PENT,          KC_END,
        _______,          KC_NO,   KC_DEL,  KC_INS,  KC_NO,   KC_NO,   KC_NO,   KC_P0, KC_00, KC_PDOT, KC_PSLS,         _______, RCTL(KC_PGUP), _______,
        _______, _______, _______,                            KC_BSPC,                            _______, _______, _______, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)
    ),

   [_MO3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};

#ifdef ENCODER_ENABLE       // Encoder Functionality

    bool encoder_update_user(uint8_t index, bool clockwise) {

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
        return true;
    }
#endif
