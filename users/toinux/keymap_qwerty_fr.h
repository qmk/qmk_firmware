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

// keymap adapted for http://marin.jb.free.fr/qwerty-fr/

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ` │ ¹ │ ² │ ³ │ ê │ € │ ^ │ ŷ │ û │ î │ ô │ – │ ≠ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ â │ é │ è │ ® │ π │ ¥ │ ù │ î │ ò │ œ │ « │ » │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ à │ æ │ ë │ ε │ α │ ÿ │ ü │ ï │ ö │ ¶ │ ´ │ ¦ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ≤ │ ä │ × │ ç │ ω │ ß │ ñ │ µ │ ¸ │ ° │ ʕ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define QF_DGRV RALT(KC_GRV)   // ` (dead)
#define QF_SUP1 RALT(KC_1)     // ¹
#define QF_SUP2 RALT(KC_2)     // ²
#define QF_SUP3 RALT(KC_3)     // ³
#define QF_ECIR RALT(KC_4)     // ê
#define QF_EURO RALT(KC_5)     // €
#define QF_DCIR RALT(KC_6)     // ^ (dead)
#define QF_YCIR RALT(KC_7)     // ŷ
#define QF_UCIR RALT(KC_8)     // û
#define QF_ICIR RALT(KC_9)     // î
#define QF_OCIR RALT(KC_0)     // ô
#define QF_DASH RALT(KC_MINUS) // –
#define QF_NEQL RALT(KC_EQUAL) // ≠
// Row 2
#define QF_ACIR RALT(KC_Q)    // â
#define QF_EACU RALT(KC_W)    // é
#define QF_EGRV RALT(KC_E)    // è
#define QF_REGD RALT(KC_R)    // ®
#define QF_PI   RALT(KC_T)    // π
#define QF_YEN  RALT(KC_Y)    // ¥
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
#define QF_EPSL RALT(KC_F)    // ε
#define QF_ALPH RALT(KC_G)    // α
#define QF_YDIA RALT(KC_H)    // ÿ
#define QF_UDIA RALT(KC_J)    // ü
#define QF_IDIA RALT(KC_K)    // ï
#define QF_ODIA RALT(KC_L)    // ö
#define QF_PILC RALT(KC_SCLN) // ¶
#define QF_ACUT RALT(KC_QUOT) // ´ (dead)
#define QF_BRKP RALT(KC_BSLS) // ¦
// Row 4
#define QF_LTEQ RALT(KC_NUBS) // ≤
#define QF_ADIA RALT(KC_Z)    // ä
#define QF_MUL  RALT(KC_X)    // ×
#define QF_CCED RALT(KC_C)    // ç
#define QF_OMEG RALT(KC_V)    // ω
#define QF_SS   RALT(KC_B)    // ß
#define QF_NTIL RALT(KC_N)    // ñ
#define QF_MICR RALT(KC_M)    // µ
#define QF_CEDL RALT(KC_COMM) // ¸ (dead)
#define QF_DEG  RALT(KC_DOT)  // °
#define QF_VOPH RALT(KC_SLSH) // ʕ
// Row 5
#define QF_NBSP RALT(KC_SPC) //   (non-breaking space)


/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ¡ │ ˝ │ ¯ │ Ê │ £ │ ˇ │ Ŷ │ Û │ Î │ Ô │ — │ ± │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Â │ É │ È │ © │ Π │ ¤ │ Ù │ Ì │ Ò │ Œ │ “ │ ” │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ À │ Æ │ Ë │ Δ │ β │ Ÿ │ Ü │ Ï │ ö │ § │ ¨ │ ø │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ≥ │ Ä │ ÷ │ Ç │ Ω │ þ │ Ñ │ Σ │ ˛ │ ˚ │ ¿ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define QF_DTIL S(RALT(KC_GRV))   // ~ (dead)
#define QF_IEXL S(RALT(KC_1))     // ¡
#define QF_DACU S(RALT(KC_2))     // ˝ (dead)
#define QF_MACR S(RALT(KC_3))     // ¯ (dead)
#define QF_ECIU S(RALT(KC_4))     // Ê
#define QF_PND  S(RALT(KC_5))     // £
#define QF_CARN S(RALT(KC_6))     // ˇ (dead)
#define QF_YCIU S(RALT(KC_7))     // Ŷ
#define QF_UCIU S(RALT(KC_8))     // Û
#define QF_ICIU S(RALT(KC_9))     // Î
#define QF_OCIO S(RALT(KC_0))     // Ô
#define QF_NDSH S(RALT(KC_MINUS)) // —
#define QF_PLMN S(RALT(KC_EQUAL)) // ±
// Row 2
#define QF_ACIU S(RALT(KC_Q))    // Â
#define QF_ECUU S(RALT(KC_W))    // É
#define QF_EGRU S(RALT(KC_E))    // È
#define QF_COPY S(RALT(KC_R))    // ©
#define QF_PIU  S(RALT(KC_T))    // Π
#define QF_CURR S(RALT(KC_Y))    // ¤
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
#define QF_DELT S(RALT(KC_F))    // Δ
#define QF_BETA S(RALT(KC_G))    // β
#define QF_YDIU S(RALT(KC_H))    // Ÿ
#define QF_UDIU S(RALT(KC_J))    // Ü
#define QF_IDIU S(RALT(KC_K))    // Ï
#define QF_ODIU S(RALT(KC_L))    // Ö
#define QF_SECT S(RALT(KC_SCLN)) // §
#define QF_DIAE S(RALT(KC_QUOT)) // ¨ (dead)
#define QF_OSTR S(RALT(KC_BSLS)) // ø
// Row 4
#define QF_GTEQ S(RALT(KC_NUBS)) // ≥
#define QF_ADIU S(RALT(KC_Z))    // Ä
#define QF_DIV  S(RALT(KC_X))    // ÷
#define QF_CCDU S(RALT(KC_C))    // Ç
#define QF_OMEU S(RALT(KC_V))    // Ω
#define QF_THRN S(RALT(KC_B))    // þ
#define QF_NTIU S(RALT(KC_N))    // Ñ
#define QF_SIGM S(RALT(KC_M))    // Σ
#define QF_OGON S(RALT(KC_COMM)) // ˛ (dead)
#define QF_RNGA S(RALT(KC_DOT))  // ˚ (dead)
#define QF_IQUE S(RALT(KC_SLSH)) // ¿
