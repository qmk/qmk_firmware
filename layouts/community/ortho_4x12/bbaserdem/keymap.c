/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base layer
    [_BASE] = LAYOUT_ortho_4x12_wrapper(
        _BL1_5_,_BL1_1_,_BR1_1_,_BR1_5_,
        _BL2_5_,_BL2_1_,_BR2_1_,_BR2_5_,
        _BL3_5_,_BL3_1_,_BR3_1_,_BR3_5_,
        BB_ENC0,KC_DOWN,KC_UP,  _BL4_3_,_BR4_3_,KC_LEFT,KC_RGHT,RGB_TOG
    ),
    // Extra characters overlay
    [_CHAR] = LAYOUT_ortho_4x12_wrapper(
        _CL1_5_,xxx2xxx,_CR1_5_,
        _CL2_5_,xxx2xxx,_CR2_5_,
        _CL3_5_,xxx2xxx,_CR3_5_,
        ___3___,_CL4_3_,_CR4_3_,___3___
    ),
    // Game layer: left_half
    [_GAME] = LAYOUT_ortho_4x12_wrapper(
        _GA1_5_,_GA1_1_,___6___,
        _GA2_5_,_GA2_1_,___6___,
        _GA3_5_,_GA3_1_,___6___,
        ___3___,_GA4_3_,___6___
    ),
    // Media layer: right_half
    [_MEDI] = LAYOUT_ortho_4x12_wrapper(
        ___6___,xxx1xxx,_ME1_5_,
        ___6___,xxx1xxx,_ME2_5_,
        ___6___,xxx1xxx,_ME3_5_,
        ___6___,_ME4_3_,___3___
    ),
    // Navigation layer: right_half
    [_NAVI] = LAYOUT_ortho_4x12_wrapper(
        ___6___,xxx1xxx,_NA1_5_,
        ___6___,xxx1xxx,_NA2_5_,
        ___6___,xxx1xxx,_NA3_5_,
        ___6___,_NA4_3_,___3___
    ),
    // Symbol layer: right_half
    [_SYMB] = LAYOUT_ortho_4x12_wrapper(
        ___6___,xxx1xxx,_SY1_5_,
        ___6___,xxx1xxx,_SY2_5_,
        ___6___,xxx1xxx,_SY3_5_,
        ___6___,_SY4_3_,___3___
    ),
    // Number layer: left_half
    [_NUMB] = LAYOUT_ortho_4x12_wrapper(
        xxx1xxx,_NU1_5_,___6___,
        xxx1xxx,_NU2_5_,___6___,
        xxx1xxx,_NU3_5_,___6___,
        ___3___,_NU4_3_,___6___
    ),
    // Function layer: left_half
    [_FUNC] = LAYOUT_ortho_4x12_wrapper(
        _FU1_5_,xxx1xxx,___6___,
        _FU2_5_,xxx1xxx,___6___,
        _FU3_5_,xxx1xxx,___6___,
        ___3___,_FU4_3_,___6___
    ),
    // Mouse layer: left_half
    [_MOUS] = LAYOUT_ortho_4x12_wrapper(
        _MO1_5_,xxx1xxx,___6___,
        _MO2_5_,xxx1xxx,___6___,
        _MO3_5_,xxx1xxx,___6___,
        ___3___,_MO4_3_,___6___
    ),
    // Music layer: everything
    [_MUSI] = LAYOUT_ortho_4x12_wrapper(
        _MU_12_,_MU_12_,_MU_12_,
        ___1___,_MU_02_,_MUL_3_,_MUR_3_,_MU_02_,___1___)
};
