/* Copyright 2017 Joseph Wasson
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

#pragma once

#include "keycodes.h"

// List of keycodes for the steno keyboard. To prevent
// errors, this must be <= 42 total entries in order to
// support the GeminiPR protocol.
enum steno_keycodes {
    STN__MIN = QK_STENO,
    STN_FN   = STN__MIN,
    STN_NUM,
    STN_N1 = STN_NUM,
    STN_N2,
    STN_N3,
    STN_N4,
    STN_N5,
    STN_N6,
    STN_SL,
    STN_S1 = STN_SL,
    STN_S2,
    STN_TL,
    STN_KL,
    STN_PL,
    STN_WL,
    STN_HL,
    STN_RL,
    STN_A,
    STN_O,
    STN_STR,
    STN_ST1 = STN_STR,
    STN_ST2,
    STN_RES1,
    STN_RE1 = STN_RES1,
    STN_RES2,
    STN_RE2 = STN_RES2,
    STN_PWR,
    STN_ST3,
    STN_ST4,
    STN_E,
    STN_U,
    STN_FR,
    STN_RR,
    STN_PR,
    STN_BR,
    STN_LR,
    STN_GR,
    STN_TR,
    STN_SR,
    STN_DR,
    STN_N7,
    STN_N8,
    STN_N9,
    STN_NA,
    STN_NB,
    STN_NC,
    STN_ZR,
    STN__MAX = STN_ZR, // must be less than QK_STENO_BOLT
};

#ifdef STENO_COMBINEDMAP
enum steno_combined_keycodes {
    STN_S3 = QK_STENO_COMB,
    STN_TKL,
    STN_PWL,
    STN_HRL,
    STN_FRR,
    STN_PBR,
    STN_LGR,
    STN_TSR,
    STN_DZR,
    STN_AO,
    STN_EU,
    STN_COMB_MAX = STN_EU,
};
#endif

#ifdef STENO_ENABLE_BOLT
// TxBolt Codes
#    define TXB_NUL 0
#    define TXB_S_L 0b00000001
#    define TXB_T_L 0b00000010
#    define TXB_K_L 0b00000100
#    define TXB_P_L 0b00001000
#    define TXB_W_L 0b00010000
#    define TXB_H_L 0b00100000
#    define TXB_R_L 0b01000001
#    define TXB_A_L 0b01000010
#    define TXB_O_L 0b01000100
#    define TXB_STR 0b01001000
#    define TXB_E_R 0b01010000
#    define TXB_U_R 0b01100000
#    define TXB_F_R 0b10000001
#    define TXB_R_R 0b10000010
#    define TXB_P_R 0b10000100
#    define TXB_B_R 0b10001000
#    define TXB_L_R 0b10010000
#    define TXB_G_R 0b10100000
#    define TXB_T_R 0b11000001
#    define TXB_S_R 0b11000010
#    define TXB_D_R 0b11000100
#    define TXB_Z_R 0b11001000
#    define TXB_NUM 0b11010000
#endif // STENO_ENABLE_BOLT
