/* Copyright 2022
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

// keymap adapted for https://qwerty-fr.org/

/* AltGr symbols (* symbol = dead key)
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │* `│ ¹ │ ² │ ê │ € │* ¯│* ^│ û │ î │ ô │ ø │ – │ ≠ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ â │ é │ è │ ® │ þ │* ̑ │ ù │ î │ ò │ œ │ « │ » │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ à │ æ │ ë │   │* Ω│ ÿ │ ü │ ï │ ö │ ´ │ ̀  │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ≤ │ ä │ × │ ç │   │ ß │ ñ │* ∫│* ¸│ · │ ’ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │   non-breaking space   │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define QF_DGRV RALT(KC_GRV)   // ` (dead)
#define QF_SUP1 RALT(KC_1)     // ¹
#define QF_SUP2 RALT(KC_2)     // ²
#define QF_ECIR RALT(KC_3)     // ê
#define QF_EURO RALT(KC_4)     // €
#define QF_MACR RALT(KC_5)     // ¯ (dead)
#define QF_DCIR RALT(KC_6)     // ^ (dead)
#define QF_UCIR RALT(KC_7)     // û
#define QF_ICIR RALT(KC_8)     // î
#define QF_OCIR RALT(KC_9)     // ô
#define QF_OSTR RALT(KC_0)     // ø
#define QF_DASH RALT(KC_MINUS) // –
#define QF_NEQL RALT(KC_EQUAL) // ≠
// Row 2
#define QF_ACIR RALT(KC_Q)    // â
#define QF_EACU RALT(KC_W)    // é
#define QF_EGRV RALT(KC_E)    // è
#define QF_REGD RALT(KC_R)    // ®
#define QF_THRN RALT(KC_T)    // þ
#define QF_RBRV RALT(KC_Y)    // ̑  (dead)
#define QF_UGRV RALT(KC_U)    // ù
#define QF_IGRV RALT(KC_I)    // ì
#define QF_OGRV RALT(KC_O)    // ò
#define QF_OE   RALT(KC_P)    // œ
#define QF_LDAQ RALT(KC_LBRC) // «
#define QF_RDAQ RALT(KC_RBRC) // »
// Row 3
#define QF_AGRV RALT(KC_A)    // à
#define QF_AE   RALT(KC_S)    // æ
#define QF_EDIA RALT(KC_D)    // ë
#define QF_GR   RALT(KC_G)    // Greek (dead)
#define QF_YDIA RALT(KC_H)    // ÿ
#define QF_UDIA RALT(KC_J)    // ü
#define QF_IDIA RALT(KC_K)    // ï
#define QF_ODIA RALT(KC_L)    // ö
#define QF_ACUT RALT(KC_SCLN) // ´ (dead)
#define QF_AGR  RALT(KC_QUOT) // ̀  (dead)
// Row 4
#define QF_LTEQ RALT(KC_NUBS) // ≤
#define QF_ADIA RALT(KC_Z)    // ä
#define QF_MUL  RALT(KC_X)    // ×
#define QF_CCED RALT(KC_C)    // ç
#define QF_SS   RALT(KC_B)    // ß
#define QF_NTIL RALT(KC_N)    // ñ
#define QF_MATH RALT(KC_M)    // Math (dead)
#define QF_CEDL RALT(KC_COMM) // ¸ (dead)
#define QF_MED  RALT(KC_DOT)  // ·
#define QF_APO  RALT(KC_SLSH) // ’
// Row 5
#define QF_NBSP RALT(KC_SPC) //   (non-breaking space)


/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │* ~│ ¡ │* ˝│ Ê │* ¤│* ˙│* ˇ│ Û │ Î │ Ô │ Ø │ — │ ≈ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Â │ É │ È │ © │ Þ │* ˘│ Ù │ Ì │ Ò │ Œ │ “ │ ” │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ À │ Æ │ Ë │   │   │ Ÿ │ Ü │ Ï │ Ö │* °│* ¨│ „ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ≥ │ Ä │ ÷ │ Ç │   │ ẞ │ Ñ │   │ ˛ │ … │ ¿ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │ narrow non-breaking spc│    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define QF_DTIL S(RALT(KC_GRV))   // ~ (dead)
#define QF_IEXL S(RALT(KC_1))     // ¡
#define QF_DACU S(RALT(KC_2))     // ˝ (dead)
#define QF_ECIU S(RALT(KC_3))     // Ê
#define QF_CURR S(RALT(KC_4))     // ¤ (dead)
#define QF_NTON S(RALT(KC_5))     // ˙ (dead)
#define QF_CARN S(RALT(KC_6))     // ˇ (dead)
#define QF_UCIU S(RALT(KC_7))     // Û
#define QF_ICIU S(RALT(KC_8))     // Î
#define QF_OCIO S(RALT(KC_9))     // Ô
#define QF_UOST S(RALT(KC_0))     // Ø
#define QF_NDSH S(RALT(KC_MINUS)) // —
#define QF_APPR S(RALT(KC_EQUAL)) // ≈
// Row 2
#define QF_ACIU S(RALT(KC_Q))    // Â
#define QF_ECUU S(RALT(KC_W))    // É
#define QF_EGRU S(RALT(KC_E))    // È
#define QF_COPY S(RALT(KC_R))    // ©
#define QF_UTRN S(RALT(KC_T))    // Þ
#define QF_BRV  S(RALT(KC_Y))    // ˘ (dead)
#define QF_UGRU S(RALT(KC_U))    // Ù
#define QF_IGRU S(RALT(KC_I))    // Ì
#define QF_OGRU S(RALT(KC_O))    // Ò
#define QF_OEU  S(RALT(KC_P))    // Œ
#define QF_LDQU S(RALT(KC_LBRC)) // “
#define QF_RDQU S(RALT(KC_RBRC)) // ”
// Row 3
#define QF_AGRU S(RALT(KC_A))    // À
#define QF_AEU  S(RALT(KC_S))    // Æ
#define QF_EDIU S(RALT(KC_D))    // Ë
#define QF_YDIU S(RALT(KC_H))    // Ÿ
#define QF_UDIU S(RALT(KC_J))    // Ü
#define QF_IDIU S(RALT(KC_K))    // Ï
#define QF_ODIU S(RALT(KC_L))    // Ö
#define QF_DEG  S(RALT(KC_SCLN)) // ° (dead)
#define QF_DIAE S(RALT(KC_QUOT)) // ¨ (dead)
#define QF_DLQM S(RALT(KC_BSLS)) // „
// Row 4
#define QF_GTEQ S(RALT(KC_NUBS)) // ≥
#define QF_ADIU S(RALT(KC_Z))    // Ä
#define QF_DIV  S(RALT(KC_X))    // ÷
#define QF_CCDU S(RALT(KC_C))    // Ç
#define QF_USS  S(RALT(KC_B))    // ẞ
#define QF_NTIU S(RALT(KC_N))    // Ñ
#define QF_OGON S(RALT(KC_COMM)) // ˛ (dead)
#define QF_SUSP S(RALT(KC_DOT))  // …
#define QF_IQUE S(RALT(KC_SLSH)) // ¿
// Row 5
#define QF_NNBS RALT(KC_SPC)     //   (narrow non-breaking space)
