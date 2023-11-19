/*
 * Copyright 2020 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2020 Anthony MARIN <anthony@hidtech.ca>
 * Copyright 2021 Stick <stick@stma.is>
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
 * along with this program.  If not, see <http:www.gnu.org/licenses/>.
 */
#include "nstickney.h"
#include "unicodemap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
                    //-------------------------------//
                    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL,
                    //-------------------------------//
                    CC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, CC_QUOT,
                    //-------------------------------//
                    SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SC_RSPC,
                    //-------------------------------//
                    AC_SLSH, FC_BSLS, KC_SPC, KC_ENT, FC_MINS, AC_EQL,
                    //-------------------------------//
                    KC_LBRC, TD(LOCKS), TD(LAYERS), KC_RBRC),

    [SYMB] = LAYOUT(_______, UP(IEX, SS1), UM(SS2), UM(SS3), UP(CUR, GBP), UM(EUR), UM(V14), UM(V12), UM(V34), UP(LSQ, LDQ), UP(RSQ, RDQ), _______,
                    //-------------------------------//
                    _______, UP(A_D, AXD), UP(A_R, ACR), UP(E_A, ECA), UP(REG, CPL), UM(THR), UP(U_D, UCD), UP(U_A, UCA), UP(I_A, ICA), UP(O_A, OCA), UP(O_D, OCD), _______,
                    //-------------------------------//
                    _______, UP(A_A, ACA), UP(S_S, SEC), UP(ETH, ETC), UM(EMD), _______, _______, _______, _______, UP(O_S, OCS), UP(PLC, DEG), UP(ACT, DIS),
                    //-------------------------------//
                    _______, UP(AEL, AEC), _______, UP(CPR, CNT), _______, _______, _______, _______, UP(N_T, NCT), UM(MCR), UP(C_C, CCC), _______,
                    //-------------------------------//
                    UM(IQM), UP(NOT, BKB), _______, _______, UM(YEN), UP(MLT, DIV),
                    //-------------------------------//
                    _______, _______, _______, _______),

    [NUMP] = LAYOUT(_______, _______, KC_P7, KC_P8, KC_P9, KC_PSLS, _______, KC_P7, KC_P8, KC_P9, KC_PSLS, _______,
                    //-------------------------------//
                    _______, _______, KC_P4, KC_P5, KC_P6, KC_PAST, _______, KC_P4, KC_P5, KC_P6, KC_PAST, _______,
                    //-------------------------------//
                    _______, _______, KC_P1, KC_P2, KC_P3, KC_PMNS, _______, KC_P1, KC_P2, KC_P3, KC_PMNS, _______,
                    //-------------------------------//
                    _______, _______, KC_P0, KC_PCMM, KC_PDOT, KC_PPLS, _______, KC_P0, KC_PCMM, KC_PDOT, KC_PPLS, _______,
                    //-------------------------------//
                    _______, _______, _______, KC_PENT, _______, _______,
                    //-------------------------------//
                    _______, _______, _______, _______),

    [FCTN] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_SYRQ,
                    //-------------------------------//
                    KC_PSCR, RGB_TOG, KC_HOME, KC_UP, KC_END, KC_PGUP, QK_LOCK, KC_LBRC, KC_RBRC, S(KC_LBRC), S(KC_RBRC), KC_INS,
                    //-------------------------------//
                    KC_PAUS, RGB_VAI, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BRIU, KC_CLR,
                    //-------------------------------//
                    _______, KC_MPRV, KC_MRWD, KC_MPLY, KC_MFFD, KC_MNXT, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, _______,
                    //-------------------------------//
                    QK_BOOT, _______, _______, _______, _______, QK_BOOT,
                    //-------------------------------//
                    _______, KC_F11, KC_F12, _______)};
