/* Copyright 2020
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
 * │ $ │ " │ « │ » │ ( │ ) │ @ │ + │ - │ / │ * │ = │ % │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ B │ É │ P │ O │ È │ ^ │ V │ D │ L │ J │ Z │ W │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ U │ I │ E │ , │ C │ T │ S │ R │ N │ M │ Ç │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ Ê │ À │ Y │ X │ . │ K │ ' │ Q │ G │ H │ F │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define BP_DLR  KC_GRV  // $
#define BP_DQUO KC_1    // "
#define BP_LDAQ KC_2    // «
#define BP_RDAQ KC_3    // »
#define BP_LPRN KC_4    // (
#define BP_RPRN KC_5    // )
#define BP_AT   KC_6    // @
#define BP_PLUS KC_7    // +
#define BP_MINS KC_8    // -
#define BP_SLSH KC_9    // /
#define BP_ASTR KC_0    // *
#define BP_EQL  KC_MINS // =
#define BP_PERC KC_EQL  // %
// Row 2
#define BP_B    KC_Q    // B
#define BP_EACU KC_W    // É
#define BP_P    KC_E    // P
#define BP_O    KC_R    // O
#define BP_EGRV KC_T    // È
#define BP_DCIR KC_Y    // ^ (dead)
#define BP_V    KC_U    // V
#define BP_D    KC_I    // D
#define BP_L    KC_O    // L
#define BP_J    KC_P    // J
#define BP_Z    KC_LBRC // Z
#define BP_W    KC_RBRC // W
// Row 3
#define BP_A    KC_A    // A
#define BP_U    KC_S    // U
#define BP_I    KC_D    // I
#define BP_E    KC_F    // E
#define BP_COMM KC_G    // ,
#define BP_C    KC_H    // C
#define BP_T    KC_J    // T
#define BP_S    KC_K    // S
#define BP_R    KC_L    // R
#define BP_N    KC_SCLN // N
#define BP_M    KC_QUOT // M
#define BP_CCED KC_BSLS // Ç
// Row 4
#define BP_ECIR KC_NUBS // Ê
#define BP_AGRV KC_Z    // À
#define BP_Y    KC_X    // Y
#define BP_X    KC_C    // X
#define BP_DOT  KC_V    // .
#define BP_K    KC_B    // K
#define BP_QUOT KC_N    // '
#define BP_Q    KC_M    // Q
#define BP_G    KC_COMM // G
#define BP_H    KC_DOT  // H
#define BP_F    KC_SLSH // F

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ # │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ° │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │ ! │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │ ; │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │ : │   │ ? │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define BP_HASH S(BP_DLR)  // #
#define BP_1    S(BP_DQUO) // 1
#define BP_2    S(BP_LDAQ) // 2
#define BP_3    S(BP_RDAQ) // 3
#define BP_4    S(BP_LPRN) // 4
#define BP_5    S(BP_RPRN) // 5
#define BP_6    S(BP_AT)   // 6
#define BP_7    S(BP_PLUS) // 7
#define BP_8    S(BP_MINS) // 8
#define BP_9    S(BP_SLSH) // 9
#define BP_0    S(BP_ASTR) // 0
#define BP_DEG  S(BP_EQL)  // °
#define BP_GRV  S(BP_PERC) // `
// Row 2
#define BP_EXLM S(BP_DCIR) // !
// Row 3
#define BP_SCLN S(BP_COMM) // ;
// Row 4
#define BP_COLN S(BP_DOT)  // :
#define BP_QUES S(BP_QUOT) // ?
// Row 5
#define BP_NBSP S(KC_SPC)  //   (non-breaking space)

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ – │ — │ < │ > │ [ │ ] │ ^ │ ± │ − │ ÷ │ × │ ≠ │ ‰ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ | │ ´ │ & │ Œ │ ` │ ¡ │ ˇ │ Ð │ / │ Ĳ │ Ə │ ˘ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Æ │ Ù │ ¨ │ € │   │ © │ Þ │ ẞ │ ® │ ~ │ ¯ │ ¸ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │ \ │ { │ } │ … │ ~ │ ¿ │ ° │   │ † │ ˛ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │           _            │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define BP_NDSH ALGR(BP_DLR)  // –
#define BP_MDSH ALGR(BP_DQUO) // —
#define BP_LABK ALGR(BP_LDAQ) // <
#define BP_RABK ALGR(BP_RDAQ) // >
#define BP_LBRC ALGR(BP_LPRN) // [
#define BP_RBRC ALGR(BP_RPRN) // ]
#define BP_CIRC ALGR(BP_AT)   // ^
#define BP_PLMN ALGR(BP_PLUS) // ±
#define BP_MMNS ALGR(BP_MINS) // −
#define BP_DIV  ALGR(BP_SLSH) // ÷
#define BP_MUL  ALGR(BP_ASTR) // ×
#define BP_NEQL ALGR(BP_EQL)  // ≠
#define BP_PERM ALGR(BP_PERC) // ‰
// Row 2
#define BP_PIPE ALGR(BP_B)    // |
#define BP_ACUT ALGR(BP_EACU) // ´ (dead)
#define BP_AMPR ALGR(BP_P)    // &
#define BP_OE   ALGR(BP_O)    // Œ
#define BP_DGRV ALGR(BP_EGRV) // ` (dead)
#define BP_IEXL ALGR(BP_DCIR) // ¡
#define BP_CARN ALGR(BP_V)    // ˇ (dead)
#define BP_ETH  ALGR(BP_D)    // Ð
#define BP_DSLS ALGR(BP_L)    // / (dead)
#define BP_IJ   ALGR(BP_J)    // Ĳ
#define BP_SCHW ALGR(BP_Z)    // Ə
#define BP_BREV ALGR(BP_W)    // ˘ (dead)
// Row 3
#define BP_AE   ALGR(BP_A)    // Æ
#define BP_UGRV ALGR(BP_U)    // Ù
#define BP_DIAE ALGR(BP_I)    // ¨ (dead)
#define BP_EURO ALGR(BP_E)    // €
#define BP_COPY ALGR(BP_C)    // ©
#define BP_THRN ALGR(BP_T)    // Þ
#define BP_SS   ALGR(BP_S)    // ẞ
#define BP_REGD ALGR(BP_R)    // ®
#define BP_DTIL ALGR(BP_N)    // ~ (dead)
#define BP_MACR ALGR(BP_M)    // ¯ (dead)
#define BP_CEDL ALGR(BP_CCED) // ¸ (dead)
// Row 4
#define BP_BSLS ALGR(BP_AGRV) // (backslash)
#define BP_LCBR ALGR(BP_Y)    // {
#define BP_RCBR ALGR(BP_X)    // }
#define BP_ELLP ALGR(BP_DOT)  // …
#define BP_TILD ALGR(BP_K)    // ~
#define BP_IQUE ALGR(BP_QUES) // ¿
#define BP_RNGA ALGR(BP_Q)    // ° (dead)
#define BP_DGRK ALGR(BP_G)    // µ (dead Greek key)
#define BP_DAGG ALGR(BP_H)    // †
#define BP_OGON ALGR(BP_F)    // ˛ (dead)
// Row 5
#define BP_UNDS ALGR(KC_SPC)  // _

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¶ │ „ │ “ │ ” │ ≤ │ ≥ │   │ ¬ │ ¼ │ ½ │ ¾ │ ′ │ ″ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ ¦ │ ˝ │ § │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │ ˙ │ ¤ │ ̛  │ ſ │   │   │ ™ │   │ º │ , │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │ ‘ │ ’ │ · │ ⌨ │ ̉  │ ̣  │   │ ‡ │ ª │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define BP_PARA S(ALGR(BP_DLR))  // ¶
#define BP_DLQU S(ALGR(BP_DQUO)) // „
#define BP_LDQU S(ALGR(BP_LDAQ)) // “
#define BP_RDQU S(ALGR(BP_RDAQ)) // ”
#define BP_LEQL S(ALGR(BP_LPRN)) // ≤
#define BP_GEQL S(ALGR(BP_RPRN)) // ≥
#define BP_NOT  S(ALGR(BP_PLUS)) // ¬
#define BP_QRTR S(ALGR(BP_MINS)) // ¼
#define BP_HALF S(ALGR(BP_SLSH)) // ½
#define BP_TQTR S(ALGR(BP_ASTR)) // ¾
#define BP_PRIM S(ALGR(BP_EQL))  // ′
#define BP_DPRM S(ALGR(BP_PERC)) // ″
// Row 2
#define BP_BRKP S(ALGR(BP_B))    // ¦
#define BP_DACU S(ALGR(BP_EACU)) // ˝ (dead)
#define BP_SECT S(ALGR(BP_P))    // §
// Row 3
#define BP_DOTA S(ALGR(BP_I))    // ˙ (dead)
#define BP_CURR S(ALGR(BP_E))    // ¤ (dead)
#define BP_HORN S(ALGR(BP_COMM)) // ̛  (dead)
#define BP_LNGS S(ALGR(BP_C))    // ſ
#define BP_TM   S(ALGR(BP_R))    // ™
#define BP_MORD S(ALGR(BP_M))    // º
#define BP_DCMM S(ALGR(BP_CCED)) // , (dead)
// Row 4
#define BP_LSQU S(ALGR(BP_Y))    // ‘
#define BP_RSQU S(ALGR(BP_X))    // ’
#define BP_MDDT S(ALGR(BP_DOT))  // ·
#define BP_KEYB S(ALGR(BP_K))    // ⌨
#define BP_HOKA S(ALGR(BP_QUOT)) // ̉  (dead)
#define BP_DOTB S(ALGR(BP_Q))    // ̣  (dead)
#define BP_DDAG S(ALGR(BP_H))    // ‡
#define BP_FORD S(ALGR(BP_F))    // ª
// Row 5
#define BP_NNBS S(ALGR(BP_))     //   (narrow non-breaking space)
