/* Copyright 2016 Didier Loiseau
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
#ifndef KEYMAP_CANADIAN_MULTILINGUAL_H
#define KEYMAP_CANADIAN_MULTILINGUAL_H

#include "keymap.h"

#ifndef GR2A
#    define GR2A(kc) RCTL(kc)
#endif

// Normal characters
// First row
#define CSA_SLASH KC_GRV  // /
#define CSA_SLSH CSA_SLASH

// Second row
#define CSA_DEAD_CIRCUMFLEX KC_LBRACKET  // dead ^
#define CSA_DCRC CSA_DEAD_CIRCUMFLEX
#define CSA_C_CEDILLA KC_RBRACKET  // Ç
#define CSA_CCED CSA_C_CEDILLA

// Third row
#define CSA_E_GRAVE KC_QUOT  // è
#define CSA_EGRV CSA_E_GRAVE
#define CSA_A_GRAVE KC_BSLASH  // à
#define CSA_AGRV CSA_A_GRAVE

// Fourth row
#define CSA_U_GRAVE KC_NONUS_BSLASH  // ù
#define CSA_UGRV CSA_U_GRAVE
#define CSA_E_ACUTE KC_SLSH  // é
#define CSA_ECUT CSA_E_ACUTE

// Shifted characters
// First row
#define CSA_BACKSLASH LSFT(CSA_SLASH) /* \ */
#define CSA_BSLS CSA_BACKSLASH
#define CSA_QUESTION LSFT(KC_6)  // ?
#define CSA_QEST CSA_QUESTION

// Second row
#define CSA_DEAD_TREMA LSFT(CSA_DEAD_CIRCUMFLEX)  // dead trema/umlaut/diaresis for ä ë ï ö ü
#define CSA_DTRM CSA_DEAD_TREMA

// Third row
// all same as US-QWERTY, or capitalised character of the non-shifted key

// Fourth row
#define CSA_APOSTROPHE LSFT(KC_COMMA)  // '
#define CSA_APOS CSA_APOSTROPHE
#define CSA_DOUBLE_QUOTE LSFT(KC_DOT)  // "
#define CSA_DQOT CSA_DOUBLE_QUOTE

// Alt Gr-ed characters
// First row
#define CSA_PIPE ALGR(CSA_SLASH)  // |
#define CSA_CURRENCY ALGR(KC_4)   // ¤
#define CSA_CURR CSA_CURRENCY
#define CSA_LEFT_CURLY_BRACE ALGR(KC_7)  // {
#define CSA_LCBR CSA_LEFT_CURLY_BRACE
#define CSA_RIGHT_CURLY_BRACE ALGR(KC_8)  // }
#define CSA_RCBR CSA_RIGHT_CURLY_BRACE
#define CSA_LBRACKET ALGR(KC_9)  // [
#define CSA_LBRC CSA_LBRACKET
#define CSA_RBRACKET ALGR(KC_0)  // ]
#define CSA_RBRC CSA_RBRACKET
#define CSA_NEGATION ALGR(KC_EQUAL)  // ¬
#define CSA_NEGT CSA_NEGATION

// Second row
// euro symbol not available on Linux? (X.org)
#define CSA_EURO ALGR(KC_E)  // €
#define CSA_DEAD_GRAVE ALGR(CSA_DEAD_CIRCUMFLEX)
#define CSA_DGRV CSA_DEAD_GRAVE             // dead `
#define CSA_DEAD_TILDE ALGR(CSA_C_CEDILLA)  // ~
#define CSA_DTLD CSA_DEAD_TILDE

// Third row
#define CSA_DEGREE ALGR(KC_SCOLON)  // °
#define CSA_DEGR CSA_DEGREE

// Fourth row
#define CSA_LEFT_GUILLEMET ALGR(KC_Z)  // «
#define CSA_LGIL CSA_LEFT_GUILLEMET
#define CSA_RIGHT_GUILLEMET ALGR(KC_X)  // »
#define CSA_RGIL CSA_RIGHT_GUILLEMET
#define CSA_LESS ALGR(KC_COMMA)   // <
#define CSA_GREATER ALGR(KC_DOT)  // >
#define CSA_GRTR CSA_GREATER

// Space bar
#define CSA_NON_BREAKING_SPACE ALGR(KC_SPACE)
#define CSA_NBSP CSA_NON_BREAKING_SPACE

// GR2A-ed characters
// First row
#define CSA_SUPERSCRIPT_ONE GR2A(KC_1)  // ¹
#define CSA_SUP1 CSA_SUPERSCRIPT_ONE
#define CSA_SUPERSCRIPT_TWO GR2A(KC_2)  // ²
#define CSA_SUP2 CSA_SUPERSCRIPT_TWO
#define CSA_SUPERSCRIPT_THREE GR2A(KC_3)  // ³
#define CSA_SUP3 CSA_SUPERSCRIPT_THREE
#define CSA_ONE_QUARTER GR2A(KC_4)  // ¼
#define CSA_1QRT CSA_ONE_QUARTER
#define CSA_ONE_HALF GR2A(KC_5)  // ½
#define CSA_1HLF CSA_ONE_HALF
#define CSA_THREE_QUARTERS GR2A(KC_6)  // ¾
#define CSA_3QRT CSA_THREE_QUARTERS
// nothing on 7-0 and -
#define CSA_DEAD_CEDILLA GR2A(KC_EQUAL)  // dead ¸
#define CSA_DCED CSA_DEAD_CEDILLA

// Second row
#define CSA_OMEGA GR2A(KC_Q)  // ω
#define CSA_OMEG CSA_OMEGA
#define CSA_L_STROKE GR2A(KC_W)  // ł
#define CSA_LSTK CSA_L_STROKE
#define CSA_OE_LIGATURE GR2A(KC_E)  // œ
#define CSA_OE CSA_OE_LIGATURE
#define CSA_PARAGRAPH GR2A(KC_R)  // ¶
#define CSA_PARG CSA_PARAGRAPH
#define CSA_T_STROKE GR2A(KC_T)    // ŧ
#define CSA_LEFT_ARROW GR2A(KC_Y)  // ←
#define CSA_LARW CSA_LEFT_ARROW
#define CSA_DOWN_ARROW GR2A(KC_U)  // ↓
#define CSA_DARW CSA_DOWN_ARROW
#define CSA_RIGHT_ARROW GR2A(KC_I)  // →
#define CSA_RARW CSA_RIGHT_ARROW
#define CSA_O_STROKE GR2A(KC_O)  // ø
#define CSA_OSTK CSA_O_STROKE
#define CSA_THORN GR2A(KC_P)  // þ
#define CSA_THRN CSA_THORN
// nothing on ^
#define CSA_TILDE GR2A(CSA_C_CEDILLA)  // dead ~
#define CSA_TILD CSA_TILDE

// Third row
#define CSA_AE_LIGATURE GR2A(KC_A)  // æ
#define CSA_AE CSA_AE_LIGATURE
#define CSA_SHARP_S GR2A(KC_S)  // ß
#define CSA_SRPS CSA_SHARP_S
#define CSA_ETH GR2A(KC_D)  // ð
// nothing on F
#define CSA_ENG GR2A(KC_G)       // ŋ
#define CSA_H_SRTOKE GR2A(KC_H)  // ħ
#define CSA_HSTK CSA_H_SRTOKE
#define CSA_IJ_LIGATURE GR2A(KC_J)  // ĳ
#define CSA_IJ CSA_IJ_LIGATURE
#define CSA_KRA GR2A(KC_K)          // ĸ
#define CSA_L_FLOWN_DOT GR2A(KC_L)  // ŀ
#define CSA_LFLD CSA_L_FLOWN_DOT
#define CSA_DEAD_ACUTE GR2A(KC_SCLN)  // dead acute accent
#define CSA_DACT CSA_DEAD_ACUTE
// nothing on È & À

// Fourth row
#define CSA_CENT GR2A(KC_C)               // ¢
#define CSA_LEFT_DOUBLE_QUOTE GR2A(KC_V)  // “
#define CSA_LDQT CSA_LEFT_DOUBLE_QUOTE
#define CSA_RIGHT_DOUBLE_QUOTE GR2A(KC_B)  // ”
#define CSA_RDQT CSA_RIGHT_DOUBLE_QUOTE
#define CSA_N_APOSTROPHE GR2A(KC_N)  // ŉ (deprecated unicode codepoint)
#define CSA_NAPO CSA_N_APOSTROPHE
#define CSA_MU GR2A(KC_M)                  // μ
#define CSA_HORIZONTAL_BAR GR2A(KC_COMMA)  // ―
#define CSA_HZBR CSA_HORIZONTAL_BAR
#define CSA_DEAD_DOT_ABOVE GR2A(KC_DOT)  // dead ˙
#define CSA_DDTA CSA_DEAD_DOT_ABOVE

// GR2A-shifted characters (different from capitalised GR2A-ed characters)
// First row
#define CSA_SOFT_HYPHEN GR2A(LSFT(CSA_SLASH))  // soft-hyphen, appears as a hyphen in wrapped word
#define CSA_SHYP CSA_SOFT_HYPHEN
#define CSA_INVERTED_EXCLAIM GR2A(KC_EXCLAIM)  // ¡
#define CSA_IXLM CSA_INVERTED_EXCLAIM
// nothing on 2
#define CSA_POUND GR2A(LSFT(KC_3))  // £
#define CSA_GBP CSA_POUND_SIGN
// already on ALGR(KC_E)
#define CSA_EURO_BIS GR2A(LSFT(KC_4))  // €
#define CSA_EURB CSA_EURO_BIS
#define CSA_THREE_EIGHTHS GR2A(LSFT(KC_5))  // ⅜
#define CSA_3ON8 CSA_THREE_EIGHTHS
#define CSA_FIVE_EIGHTHS GR2A(LSFT(KC_6))  // ⅝
#define CSA_5ON8 CSA_FIVE_EIGHTHS
#define CSA_SEVEN_EIGHTHS GR2A(LSFT(KC_7))  // ⅞
#define CSA_7ON8 CSA_SEVEN_EIGHTHS
#define CSA_TRADEMARK GR2A(LSFT(KC_8))  // ™
#define CSA_TM CSA_TRADEMARK
#define CSA_PLUS_MINUS GR2A(LSFT(KC_9))  // ±
#define CSA_PSMS CSA_PLUS_MINUS
// nothing on 0
#define CSA_INVERTED_QUESTION GR2A(LSFT(KC_MINUS))  // ¿
#define CSA_IQST CSA_INVERTED_QUESTION
#define CSA_DEAD_OGONEK GR2A(LSFT(KC_EQUAL))  // dead ˛
#define CSA_DOGO CSA_DEAD_OGONEK

// Second row
#define CSA_REGISTERED_TRADEMARK GR2A(LSFT(KC_R))  // ®
#define CSA_RTM CSA_REGISTERED_TRADEMARK
#define CSA_YEN GR2A(LSFT(KC_Y))  // ¥
#define CSA_YUAN CSA_YEN
#define CSA_UP_ARROW LSFT(CSA_DOWN_ARROW)  // ↑
#define CSA_DOTLESS_I GR2A(LSFT(KC_I))     // ı
#define CSA_DLSI CSA_DOTLESS_I
#define CSA_DEAD_RING GR2A(LSFT(CSA_DCRC))  // dead °
#define CSA_DRNG CSA_DEAD_RING
#define CSA_DEAD_MACRON GR2A(LSFT(CSA_C_CEDILLA))  // dead ¯
#define CSA_DMCR CSA_DEAD_MACRON

// Third row
#define CSA_SECTION GR2A(LSFT(KC_S))  // §
#define CSA_SECT CSA_SECTION
#define CSA_ORDINAL_INDICATOR_A GR2A(LSFT(KC_F))  // ª
#define CSA_ORDA CSA_ORDINAL_INDICATOR_A
#define CSA_DEAD_DOUBLE_ACUTE LSFT(CSA_DEAD_ACUTE)  // ˝
#define CSA_DDCT CSA_DEAD_DOUBLE_ACUTE
#define CSA_DEAD_CARON GR2A(LSFT(CSA_E_GRAVE))  // dead ˇ
#define CSA_DCAR CSA_DEAD_CARON
#define CSA_DEAD_BREVE GR2A(LSFT(CSA_A_GRAVE))  // dead ˘
#define CSA_DBRV CSA_DEAD_BREVE

// Fourth row
#define CSA_BROKEN_PIPE GR2A(LSFT(CSA_U_GRAVE))  // ¦
#define CSA_BPIP CSA_BROKEN_PIPE
#define CSA_COPYRIGHT GR2A(LSFT(KC_C))  // ©
#define CSA_CPRT CSA_COPYRIGHT
#define CSA_LEFT_QUOTE GR2A(LSFT(KC_V))  // ‘
#define CSA_LQOT CSA_LEFT_QUOTE
#define CSA_RIGHT_QUOTE GR2A(LSFT(KC_B))  // ’
#define CSA_RQOT CSA_RIGHT_QUOTE
#define CSA_EIGHTH_NOTE GR2A(LSFT(KC_N))  // ♪
#define CSA_8NOT CSA_EIGHTH_NOTE
#define CSA_ORDINAL_INDICATOR_O GR2A(LSFT(KC_M))  // º
#define CSA_ORDO CSA_ORDINAL_INDICATOR_O
#define CSA_TIMES GR2A(LSFT(KC_COMMA))  // ×
#define CSA_TIMS CSA_TIMES
#define CSA_OBELUS GR2A(LSFT(KC_DOT))  // ÷
#define CSA_OBEL CSA_OBELUS
// more conventional name of the symbol
#define CSA_DIVISION_SIGN CSA_OBELUS
#define CSA_DVSN CSA_DIVISION_SIGN
// TODO GR2A(LSFT(CSA_E_ACUTE))

#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            /* Copyright 2020 elagil
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

#include "murcielago.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  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