/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Drashna Jael're @drashna
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

#include "drashna.h"

#define LAYOUT_charybdis_3x5_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)
#define LAYOUT_charybdis_3x5_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
    ) \
    LAYOUT_charybdis_3x5 ( \
       K01,    K02,      K03,     K04,     K05,                K06,     K07,     K08,     K09,     K0A, \
       ALT_T(K11), K12,  K13,     K14,     GUI_T(K15),  LGUI_T(K16),    K17,     K18,     K19, LALT_T(K1A), \
       CTL_T(K21), K22,  K23,     K24,     K25,                K26,     K27,     K28,     K29, RCTL_T(K2A), \
                LSFT_T(KC_GRV), KC_SPC,  BK_LWER,              DL_RAIS, RSFT_T(KC_ENT) \
    )
#define LAYOUT_charybdis_3x5_base_wrapper(...)       LAYOUT_charybdis_3x5_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEFAULT_LAYER_1] = LAYOUT_charybdis_3x5_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_DEFAULT_LAYER_2] = LAYOUT_charybdis_3x5_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),
    [_DEFAULT_LAYER_3] = LAYOUT_charybdis_3x5_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DEFAULT_LAYER_4] = LAYOUT_charybdis_3x5_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_MOUSE] = LAYOUT_charybdis_3x5(
        _______, _______, _______, S_D_MOD, DPI_MOD,    KC_WH_U, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,    KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN6,
        _______, _______, _______, S_D_RMOD,DPI_RMOD,   KC_BTN7, KC_BTN4, KC_BTN5, KC_BTN8, _______,
                          _______, SNIPING, _______,    _______, _______
    ),
    [_LOWER] = LAYOUT_charybdis_3x5_wrapper(
        _________________LOWER_L1__________________,    _________________LOWER_R1__________________,
        _________________LOWER_L2__________________,    _________________LOWER_R2__________________,
        _________________LOWER_L3__________________,    _________________LOWER_R3__________________,
                          _______, _______, _______,    _______, AUTO_CTN
    ),
    [_RAISE] = LAYOUT_charybdis_3x5_wrapper(
        _________________RAISE_L1__________________,    _________________RAISE_R1__________________,
        _________________RAISE_L2__________________,    _________________RAISE_R2__________________,
        _________________RAISE_L3__________________,    _________________RAISE_R3__________________,
                          REBOOT,  KEYLOCK, _______,    _______, _______
    ),
    [_ADJUST] = LAYOUT_charybdis_3x5_wrapper(
        _________________ADJUST_L1_________________,    _________________ADJUST_R1_________________,
        _________________ADJUST_L2_________________,    _________________ADJUST_R2_________________,
        _________________ADJUST_L3_________________,    _________________ADJUST_R3_________________,
                          EEP_RST, KC_NUKE, _______,    _______, RESET
    ),
};

void matrix_init_keyemap(void) { setPinInputHigh(A0); }

void matrix_scan_keymap(void) {
    if (!readPin(A0)) {
        reset_keyboard();
    }
}

#ifdef USB_VBUS_PIN
bool usb_vbus_state(void) {
    setPinInputLow(USB_VBUS_PIN);
    wait_us(5);
    return readPin(USB_VBUS_PIN);
}
#endif
