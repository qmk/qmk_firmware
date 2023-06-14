/* Copyright 2021 @nstickney
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
#include "nstickney.h"
#include "unicodemap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL,
		CC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, CC_QUOT,
		SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, TD(LOCKS), TD(LAYERS), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SC_RSPC,
		AC_SLSH, FC_BSLS, KC_SPC, KC_ENT, FC_MINS, AC_EQL
		),

    [SYMB] = LAYOUT(
        _______, XP(IEX, SS1), X(SS2), X(SS3), XP(CUR, GBP), X(EUR), X(V14), X(V12), X(V34), XP(LSQ, LDQ), XP(RSQ, RDQ), _______,
        _______, XP(A_D, AXD), XP(A_R, ACR), XP(E_A, ECA), XP(REG, CPL), X(THR), XP(U_D, UCD), XP(U_A, UCA), XP(I_A, ICA), XP(O_A, OCA), XP(O_D, OCD), _______,
        _______, XP(A_A, ACA), XP(S_S, SEC), XP(ETH, ETC), X(EMD), _______, _______, _______, _______, XP(O_S, OCS), XP(PLC, DEG), XP(ACT, DIS),
        _______, XP(AEL, AEC), _______, XP(CPR, CNT), _______, _______, _______, _______, XP(N_T, NCT), X(MCR), XP(C_C, CCC), _______, _______, _______,
        X(IQM), XP(NOT, BKB), _______, _______, X(YEN), XP(MLT, DIV)
        ),

    [NUMP] = LAYOUT(
        _______, _______, KC_P7, KC_P8, KC_P9, KC_PSLS, _______, KC_P7, KC_P8, KC_P9, KC_PSLS, _______,
        _______, _______, KC_P4, KC_P5, KC_P6, KC_PAST, _______, KC_P4, KC_P5, KC_P6, KC_PAST, _______,
        _______, _______, KC_P1, KC_P2, KC_P3, KC_PMNS, _______, KC_P1, KC_P2, KC_P3, KC_PMNS, _______,
        _______, _______, KC_P0, KC_PCMM, KC_PDOT, KC_PPLS, _______, _______, _______, KC_P0, KC_PCMM, KC_PDOT, KC_PPLS, _______,
        _______, _______, _______, KC_PENT, _______, _______
        ),

    [FCTN] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_SYRQ,
        KC_PSCR, RGB_TOG, KC_HOME, KC_UP, KC_END, KC_PGUP, QK_LOCK, KC_LBRC, KC_RBRC, S(KC_LBRC), S(KC_RBRC), KC_INS,
        KC_PAUS, RGB_VAI, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BRIU, KC_CLR,
        _______, KC_MPRV, KC_MRWD, KC_MPLY, KC_MFFD, KC_MNXT, KC_F11, KC_F12, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, _______,
        _______, _______, _______, _______, _______, _______
        )

};
