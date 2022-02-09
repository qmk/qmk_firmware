/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
#include "keymap_norwegian.h"
// Macros
enum custom_keycodes {
    KIPAS = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KIPAS:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(50) "keepasseirik" SS_DELAY(50) SS_TAP(X_ENT));
        } else {
        }
        break;
    }
    return true;
};

// Rotary knob
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code_delay(KC_VOLU, 10);
    } else {
      tap_code_delay(KC_VOLD, 10);
    }
    return false;
}
#endif // ENCODER_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Home          Rotary(Mute)
//      |        1        2        3        4        5        6        7        8        9        0         +        \	     BackSpc           PgUp
//      Tab      Q        W        E        R        T        Y        U        I        O        P        Å        ¨                          PgDwn
//      Caps     A        S        D        F        G        H        J        K        L        Ø        Æ        '        Enter             End
//      Sh_L     <        Z        X        C        V        B        N        M        ,        .        -                 Sh_R     Up       Del
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME,          KC_MUTE,
        NO_PIPE, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_PLUS, NO_BSLS, KC_BSPC,          KC_PGUP,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_ARNG, NO_DIAE,                   KC_PGDN,
        KC_CAPS, NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_OSTR, NO_AE,   NO_QUOT, KC_ENT,           KC_END,
        KC_LSFT, NO_LABK, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS, KC_RSFT,          KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        KC_MSTP, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_VOLD, KC_VOLU,          KC_MUTE,
        KC_CALC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_TOGG, BL_STEP, BL_BRTG, KC_TRNS, KC_TRNS, KC_TRNS, RGB_RMOD, RGB_MOD,   RESET,          KC_PSCR,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_SPI, RGB_VAI, KC_TRNS, BL_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_MYCM, KC_TRNS,  KC_TRNS,                   KC_SCRL,
        KC_TRNS, RGB_HUD, RGB_SAD, RGB_SPD, RGB_VAD, KC_TRNS, BL_DEC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_PAST, KC_TRNS,          KC_PAUS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_CUT,  KC_COPY, KC_PSTE, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KIPAS,    KC_TRNS,          KC_TRNS, KC_INS,
        GUI_ON,  GUI_OFF, MEH_T(KC_NO),                       KC_TRNS,                            KC_TRNS, KC_TRNS,  TG(2),   KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT(
        _______, _______, _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,           KC_F24,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, KC_MS_U, _______, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, KC_LALT,                            KC_BTN1,                            _______, _______, _______, _______, _______, _______
    ),

   [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};
// clang-format on

// Suspend keyboard when PC is turned off
#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif // RGB_MATRIX_ENABLE
