/* Copyright 2018 fuge
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

#include "keymap.h"

// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ 0 │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ Ö │ Ü │ Ó │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ Ő │ Ú │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ É │ Á │ Ű │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ Í │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define HU_0    KC_GRV  // 0
#define HU_1    KC_1    // 1
#define HU_2    KC_2    // 2
#define HU_3    KC_3    // 3
#define HU_4    KC_4    // 4
#define HU_5    KC_5    // 5
#define HU_6    KC_6    // 6
#define HU_7    KC_7    // 7
#define HU_8    KC_8    // 8
#define HU_9    KC_9    // 9
#define HU_ODIA KC_0    // Ö
#define HU_UDIA KC_MINS // Ü
#define HU_OACU KC_EQL  // Ó
// Row 2
#define HU_Q    KC_Q    // Q
#define HU_W    KC_W    // W
#define HU_E    KC_E    // E
#define HU_R    KC_R    // R
#define HU_T    KC_T    // T
#define HU_Z    KC_Y    // Z
#define HU_U    KC_U    // U
#define HU_I    KC_I    // I
#define HU_O    KC_O    // O
#define HU_P    KC_P    // P
#define HU_ODAC KC_LBRC // Ő
#define HU_UACU KC_RBRC // Ú
// Row 3
#define HU_A    KC_A    // A
#define HU_S    KC_S    // S
#define HU_D    KC_D    // D
#define HU_F    KC_F    // F
#define HU_G    KC_G    // G
#define HU_H    KC_H    // H
#define HU_J    KC_J    // J
#define HU_K    KC_K    // K
#define HU_L    KC_L    // L
#define HU_EACU KC_SCLN // É
#define HU_AACU KC_QUOT // Á
#define HU_UDAC KC_NUHS // Ű
// Row 4
#define HU_IACU KC_NUBS // Í
#define HU_Y    KC_Z    // Y
#define HU_X    KC_X    // X
#define HU_C    KC_C    // C
#define HU_V    KC_V    // V
#define HU_B    KC_B    // B
#define HU_N    KC_N    // N
#define HU_M    KC_M    // M
#define HU_COMM KC_COMM // ,
#define HU_DOT  KC_DOT  // .
#define HU_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ § │ ' │ " │ + │ ! │ % │ / │ = │ ( │ ) │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │ ? │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define HU_SECT S(HU_0)    // §
#define HU_QUOT S(HU_1)    // '
#define HU_DQUO S(HU_2)    // "
#define HU_PLUS S(HU_3)    // +
#define HU_EXLM S(HU_4)    // !
#define HU_PERC S(HU_5)    // %
#define HU_SLSH S(HU_6)    // /
#define HU_EQL  S(HU_7)    // =
#define HU_LPRN S(HU_8)    // (
#define HU_RPRN S(HU_9)    // )
// Row 4
#define HU_QUES S(HU_COMM) // ?
#define HU_COLN S(HU_DOT)  // :
#define HU_UNDS S(HU_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │ ~ │ ˇ │ ^ │ ˘ │ ° │ ˛ │ ` │ ˙ │ ´ │ ˝ │ ¨ │ ¸ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ \ │ | │ Ä │   │   │   │ € │   │   │   │ ÷ │ × │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ ä │ đ │ Đ │ [ │ ] │   │   │ ł │ Ł │ $ │ ß │ ¤ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ > │ # │ & │ @ │ { │ } │   │ ; │   │ * │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define HU_TILD ALGR(HU_1)    // ~
#define HU_CARN ALGR(HU_2)    // ˇ (dead)
#define HU_CIRC ALGR(HU_3)    // ^ (dead)
#define HU_BREV ALGR(HU_4)    // ˘ (dead)
#define HU_RNGA ALGR(HU_5)    // ° (dead)
#define HU_OGON ALGR(HU_6)    // ˛ (dead)
#define HU_GRV  ALGR(HU_7)    // `
#define HU_DOTA ALGR(HU_8)    // ˙ (dead)
#define HU_ACUT ALGR(HU_9)    // ´ (dead)
#define HU_DACU ALGR(HU_ODIA) // ˝ (dead)
#define HU_DIAE ALGR(HU_UDIA) // ¨ (dead)
#define HU_CEDL ALGR(HU_OACU) // ¸ (dead)
// Row 2
#define HU_BSLS ALGR(HU_Q)    // (backslash)
#define HU_PIPE ALGR(HU_W)    // |
#define HU_CADI ALGR(HU_E)    // Ä
#define HU_EURO ALGR(HU_U)    // €
#define HU_DIV  ALGR(HU_ODAC) // ÷
#define HU_MUL  ALGR(HU_UACU) // ×
// Row 3
#define HU_LADI ALGR(HU_A)    // ä
#define HU_LDST ALGR(HU_S)    // đ
#define HU_CDST ALGR(HU_D)    // Đ
#define HU_LBRC ALGR(HU_F)    // [
#define HU_RBRC ALGR(HU_G)    // ]
#define HU_LLST ALGR(HU_K)    // ł
#define HU_CLST ALGR(HU_L)    // Ł
#define HU_DLR  ALGR(HU_EACU) // $
#define HU_SS   ALGR(HU_AACU) // ß
#define HU_CURR ALGR(HU_UDAC) // ¤
// Row 4
#define HU_LABK ALGR(HU_IACU) // <
#define HU_RABK ALGR(HU_Y)    // >
#define HU_HASH ALGR(HU_X)    // #
#define HU_AMPR ALGR(HU_C)    // &
#define HU_AT   ALGR(HU_V)    // @
#define HU_LCBR ALGR(HU_B)    // {
#define HU_RCBR ALGR(HU_N)    // }
#define HU_SCLN ALGR(HU_COMM) // ;
#define HU_ASTR ALGR(HU_MINS) // *

// DEPRECATED
#define HU_OE   HU_ODIA
#define HU_UE   HU_UDIA
#define HU_OO   HU_OACU
#define HU_OEE  HU_ODAC
#define HU_UU   HU_UACU
#define HU_EE   HU_EACU
#define HU_AA   HU_AACU
#define HU_UEE  HU_UDAC
#define HU_II   HU_IACU
#define HU_PARA HU_SECT
#define HU_DQOT HU_DQUO
#define HU_QST  HU_QUES
#define HU_BRV  HU_BREV
#define HU_RING HU_RNGA
#define HU_CRSS HU_MUL
#define HU_LESS HU_LABK
#define HU_MORE HU_RABK
