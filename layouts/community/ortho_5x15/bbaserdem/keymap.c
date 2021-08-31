/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_5x15_wrapper(
        xxx6xxx,KC_NLCK,KC_PSLS,KC_PAST,xxx6xxx,
        _BL1_1_,_BL1_5_,KC_P7,  KC_P8,  KC_P9,  _BR1_5_,_BR1_1_,
        _BL2_1_,_BL2_5_,KC_P4,  KC_P5,  KC_P6,  _BR2_5_,_BR2_1_,
        _BL3_1_,_BL3_5_,KC_P1,  KC_P2,  KC_P3,  _BR3_5_,_BR3_1_,
        BL_STEP,XXXXXXX,KC_LEFT,KC_RGHT,_BL4_3_,KC_P0,  _BL4_3_,KC_DOWN,KC_UP,  MU_ON,  BL_TOGG
    ),
    [_CHAR] = LAYOUT_ortho_5x15_wrapper(
        xxx6xxx,xxx3xxx,xxx6xxx,
        XXXXXXX,_CL1_5_,xxx3xxx,_CR1_5_,XXXXXXX,
        XXXXXXX,_CL1_5_,xxx3xxx,_CR1_5_,XXXXXXX,
        XXXXXXX,_CL1_5_,xxx3xxx,_CR1_5_,XXXXXXX,
        ___4___,_CL4_3_,XXXXXXX,_CL4_3_,___4___
    ),
    [_GAME] = LAYOUT_ortho_5x15_wrapper(
        ___6___,___3___,___6___,
        _GA1_1_,_GA1_5_,___3___,___6___,
        _GA2_1_,_GA2_5_,___3___,___6___,
        _GA3_1_,_GA3_5_,___3___,___6___,
        ___4___,_GA4_3_,___1___,___3___,___4___
    ),
    [_MEDI] = LAYOUT_ortho_5x15_wrapper(
        ___6___,___3___,___6___,
        xxx1xxx,_ME1_5_,___3___,___6___,
        xxx1xxx,_ME2_5_,___3___,___6___,
        xxx1xxx,_ME3_5_,___3___,___6___,
        ___4___,___3___,___1___,_ME4_3_,___4___
    ),
    [_NAVI] = LAYOUT_ortho_5x15_wrapper(
        ___6___,___3___,___6___,
        xxx1xxx,_NA1_5_,___3___,___6___,
        xxx1xxx,_NA2_5_,___3___,___6___,
        xxx1xxx,_NA3_5_,___3___,___6___,
        ___4___,_NA4_3_,___1___,___3___,___4___
    ),
    [_SYMB] = LAYOUT_ortho_5x15_wrapper(
        ___6___,___3___,___6___,
        xxx1xxx,_SY1_5_,___3___,___6___,
        xxx1xxx,_SY2_5_,___3___,___6___,
        xxx1xxx,_SY3_5_,___3___,___6___,
        ___4___,_SY4_3_,___1___,___3___,___4___
    ),
    [_NUMB] = LAYOUT_ortho_5x15_wrapper(
        ___6___,___3___,___6___,
        ___6___,___3___,_NU1_5_,xxx1xxx,
        ___6___,___3___,_NU2_5_,xxx1xxx,
        ___6___,___3___,_NU3_5_,xxx1xxx,
        ___4___,___3___,___1___,_NU4_3_,___4___
    ),
    [_FUNC] = LAYOUT_ortho_5x15_wrapper(
        ___6___,___3___,___6___,
        ___6___,___3___,_FU1_5_,xxx1xxx,
        ___6___,___3___,_FU2_5_,xxx1xxx,
        ___6___,___3___,_FU3_5_,xxx1xxx,
        ___4___,___3___,___1___,_FU4_3_,___4___
    ),
    [_MOUS] = LAYOUT_ortho_5x15_wrapper(
        ___6___,___3___,___6___,
        ___6___,___3___,_MO1_5_,xxx1xxx,
        ___6___,___3___,_MO2_5_,xxx1xxx,
        ___6___,___3___,_MO3_5_,xxx1xxx,
        ___4___,___3___,___1___,_MO4_3_,___4___
    ),
    [_MUSI] = LAYOUT_ortho_5x15_wrapper(
        _MU_06_,_MU_03_,_MU_06_,
        _MU_06_,_MU_03_,_MU_06_,
        _MU_06_,_MU_03_,_MU_06_,
        _MU_06_,_MU_03_,_MU_06_,
        _MU_06_,_MU_01_,_MUS_4_,MU_SLOW,MU_FAST,MU_OFF, ___1___
    )
};

layer_state_t layer_state_set_keymap(layer_state_t state) {
    // XD75RE layer indicator
    #ifdef KEYBOARD_xd75
    if (layer_state_cmp(state, _CHAR)) {
        capslock_led_on();
        gp103_led_on();
        gp100_led_on();
    } else if (layer_state_cmp(state, _MEDI)) {
        capslock_led_off();
        gp103_led_off();
        gp100_led_on();
    } else if (layer_state_cmp(state, _NAVI)) {
        capslock_led_off();
        gp103_led_on();
        gp100_led_off();
    } else if (layer_state_cmp(state, _NUMB)) {
        capslock_led_on();
        gp103_led_off();
        gp100_led_off();
    } else if (layer_state_cmp(state, _SYMB)) {
        capslock_led_off();
        gp103_led_on();
        gp100_led_on();
    } else if (layer_state_cmp(state, _FUNC)) {
        capslock_led_on();
        gp103_led_off();
        gp100_led_on();
    } else if (layer_state_cmp(state, _MOUS)) {
        capslock_led_on();
        gp103_led_on();
        gp100_led_off();
    } else {
        capslock_led_off();
        gp103_led_off();
        gp100_led_off();
    }
    #endif
    return state;
};
