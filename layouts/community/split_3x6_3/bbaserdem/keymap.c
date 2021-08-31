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
/* F layout
 * ┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
 * │+ *│ F │ G │ Ğ │ I │ O │         │ D │ R │ N │ H │ P │ Q │
 * ├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
 * │ X │ A │ S │ D │ F │ G │         │ T │ K │ M │ L │ Y │ Ş │
 * ├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
 * │< >│ J │ Ö │ V │ C │ Ç │         │ Z │ S │ B │. :│, ;│ W │
 * └───┴───┴───┴───┼───┼───┼───┐ ┌───┼───┼───┼───┴───┴───┴───┘
 *                 │Tab│Ent│Esc│ │Del│Spc│Bsp│
 *                 └───┴───┴───┘ └───┴───┴───┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_wrapper(
        _BL1_1_,_BL1_5_,_BR1_5_,_BR1_1_,
        _BL2_1_,_BL2_5_,_BR2_5_,_BR2_1_,
        _BL3_1_,_BL3_5_,_BR3_5_,_BR3_1_,
                _BL4_3_,_BR4_3_
    ),
    [_CHAR] = LAYOUT_split_3x6_3_wrapper(
        XXXXXXX,_CL1_5_,_CR1_5_,XXXXXXX,
        XXXXXXX,_CL2_5_,_CR2_5_,XXXXXXX,
        XXXXXXX,_CL3_5_,_CR3_5_,XXXXXXX,
                _CL4_3_,_CR4_3_
    ),
    [_GAME] = LAYOUT_split_3x6_3_wrapper(
        _GA1_1_,_GA1_5_,___6___,
        _GA2_1_,_GA2_5_,___6___,
        _GA3_1_,_GA3_5_,___6___,
                _GA4_3_,___3___
    ),
    [_MEDI] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_ME1_5_,xxx1xxx,
        ___6___,_ME2_5_,xxx1xxx,
        ___6___,_ME3_5_,xxx1xxx,
        ___3___,_ME4_3_
    ),
    [_NAVI] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_NA1_5_,xxx1xxx,
        ___6___,_NA2_5_,xxx1xxx,
        ___6___,_NA3_5_,xxx1xxx,
        ___3___,_NA4_3_
    ),
    [_SYMB] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_SY1_5_,xxx1xxx,
        ___6___,_SY2_5_,xxx1xxx,
        ___6___,_SY3_5_,xxx1xxx,
        ___3___,_SY4_3_
    ),
    [_NUMB] = LAYOUT_split_3x6_3_wrapper(
        xxx1xxx,_NU1_5_,___6___,
        xxx1xxx,_NU2_5_,___6___,
        xxx1xxx,_NU3_5_,___6___,
                _NU4_3_,___3___
    ),
    [_FUNC] = LAYOUT_split_3x6_3_wrapper(
        xxx1xxx,_FU1_5_,___6___,
        xxx1xxx,_FU2_5_,___6___,
        xxx1xxx,_FU3_5_,___6___,
                _FU4_3_,___3___
    ),
    [_MOUS] = LAYOUT_split_3x6_3_wrapper(
        xxx1xxx,_MO1_5_,___6___,
        xxx1xxx,_MO2_5_,___6___,
        xxx1xxx,_MO3_5_,___6___,
                _MO4_3_,___3___
    ),
    [_MUSI] = LAYOUT_split_3x6_3_wrapper(
            _MU_12_,
            _MU_12_,
            _MU_12_,
        _MUL_3_,_MUR_3_
    )
};

// RGB Matrix configuration
#ifdef RGB_MATRIX_ENABLE

// crkbd
#if defined(KEYBOARD_crkbd_rev1)
/* This is left-right for planck light indicator light
 *  - The LED 42 is for spacebar specifically, leave it out of the matrix
 *  - This is how it looks like
 * ┌──┬──┬──┬──┬──┬──┐      ┌──┬──┬──┬──┬──┬──┐
 * │24│23│18│17│10│09│      │36│37│44│45│50│51│
 * ├──┼02┼──┼01┼──┼00┤      ├27┼──┼28┼──┼29┼──┤
 * │25│22│19│16│11│08│      │35│38│43│46│49│52│
 * ├──┼03┼──┼04┼──┼05┤      ├32┼──┼31┼──┼30┼──┤
 * │26│21│20│15│12│07│      │34│39│42│47│48│53│
 * └──┴──┴──┴──┼──┼──┼──┐┌──┼──┼──┼──┴──┴──┴──┘
 *             │14│13│06││33│40│41│
 *             └──┴──┴──┘└──┴──┴──┘
 */
// Sided color-setting
void keylight_set_left(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < 27; i++) {
        rgb_matrix_set_color(i, red, green, blue);
    }
}
void keylight_set_right(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 28; i < 54; i++) {
        rgb_matrix_set_color(i, red, green, blue);
    }
}
// End of differentiations
#endif

// End of code for the RGB_MATRIX setup
#endif
