/* Copyright 2022 charlesrocket
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

enum unicode_names {
  DIAMOND,
  QUAD_DIAMOND,
  DIAERESIS,
  IBEAM,
  MACRON,
  DEL_TILDE,
  LESS,
  DEL_STILE,
  LESS_EQUAL,
  DELTA_STILE,
  EQUALS,
  CIRCLE_STILE,
  GREATER_EQUAL,
  CIRCLE_BACKSLASH,
  GREATER,
  CIRCLED_MINUS,
  NOT_EQUAL,
  CIRCLE_STAR,
  OR,
  DOWN_CARET_TILDE,
  AND,
  UP_CARET_TILDE,
  MULT,
  EXCL,
  DIVISION,
  QUAD_DIVIDE,
  QUESTION_MARK,
  OMEGA,
  OMEGA_UNDERBAR,
  EPSILON,
  SMALL_ELEMENT,
  EPSILON_UNDERBAR,
  RHO,
  TILDE,
  TILDE_DIAERESIS,
  UPWARDS_ARROW,
  DOWNWARDS_ARROW,
  IOTA,
  IOTA_UNDERBAR,
  WHITE_CIRCLE,
  CIRCLE_DIAERESIS,
  STAR_OPERATOR,
  STAR_DIAERESIS,
  LEFT_ARROW,
  QUOTE_QUAD,
  RIGHT_ARROW,
  ZILDE,
  ALPHA,
  ALPHA_UNDERBAR,
  LEFT_CEILING,
  LEFT_FLOOR,
  LOW_LINE,
  NABLA,
  INCREMENT,
  DELTA_UNDERBAR,
  RING_OPERATOR,
  JOT_DIAERESIS,
  APOSTROPHE,
  QUAD_EQUAL,
  QUAD,
  SQUISH_QUAD,
  DOWN_TACK_JOT,
  IDENTICAL,
  UP_TACK_JOT,
  NOT_IDENTICAL,
  RIGHT_TACK,
  LEFT_TACK,
  SUBSET,
  SUPERSET,
  CHI,
  INTERSECTION,
  UNION,
  UP_TACK,
  DOWN_TACK,
  VERTICAL_LINE,
  UP_SHOE_JOT,
  COMMA_BAR,
  BACKSLASH_BAR,
  SLASH_BAR,
  QUAD_COLON
};

const uint32_t PROGMEM unicode_map[] = {
  [DIAMOND]          = 0x25CA, // ◊      0
  [QUAD_DIAMOND]     = 0x233A, // ⌺
  [DIAERESIS]        = 0x00A8, // ¨
  [IBEAM]            = 0x2336, // ⌶
  [MACRON]           = 0x00AF, // ¯
  [DEL_TILDE]        = 0x236B, // ⍫      5
  [LESS]             = 0x003C, // <
  [DEL_STILE]        = 0x2352, // ⍒
  [LESS_EQUAL]       = 0x2264, // ≤
  [DELTA_STILE]      = 0x234B, // ⍋
  [EQUALS]           = 0x003D, // =     10
  [CIRCLE_STILE]     = 0x233D, // ⌽
  [GREATER_EQUAL]    = 0x2265, // ≥
  [CIRCLE_BACKSLASH] = 0x2349, // ⍉
  [GREATER]          = 0x003E, // >
  [CIRCLED_MINUS]    = 0x2296, // ⊖     15
  [NOT_EQUAL]        = 0x2260, // ≠
  [CIRCLE_STAR]      = 0x235F, // ⍟
  [OR]               = 0x2228, // ∨
  [DOWN_CARET_TILDE] = 0x2371, // ⍱
  [AND]              = 0x2227, // ∧     20
  [UP_CARET_TILDE]   = 0x2372, // ⍲
  [MULT]             = 0x00D7, // ×
  [EXCL]             = 0x0021, // !
  [DIVISION]         = 0x00F7, // ÷
  [QUAD_DIVIDE]      = 0x2339, // ⌹     25
  [QUESTION_MARK]    = 0x003F, // ?
  [OMEGA]            = 0x2375, // ⍵
  [OMEGA_UNDERBAR]   = 0x2379, // ⍹
  [EPSILON]          = 0x03B5, // ε
  [SMALL_ELEMENT]    = 0x220A, // ∊     30
  [EPSILON_UNDERBAR] = 0x2377, // ⍷
  [RHO]              = 0x2374, // ⍴
  [TILDE]            = 0x007E, // ~
  [TILDE_DIAERESIS]  = 0x2368, // ⍨
  [UPWARDS_ARROW]    = 0x2191, // ↑     35
  [DOWNWARDS_ARROW]  = 0x2193, // ↓
  [IOTA]             = 0x2373, // ⍳
  [IOTA_UNDERBAR]    = 0x2378, // ⍸
  [WHITE_CIRCLE]     = 0x25CB, // ○
  [CIRCLE_DIAERESIS] = 0x2365, // ⍥     40
  [STAR_OPERATOR]    = 0x22C6, // ⋆
  [STAR_DIAERESIS]   = 0x2363, // ⍣
  [LEFT_ARROW]       = 0x2190, // ←
  [QUOTE_QUAD]       = 0x235E, // ⍞
  [RIGHT_ARROW]      = 0x2192, // →     45
  [ZILDE]            = 0x236C, // ⍬
  [ALPHA]            = 0x237A, // ⍺
  [ALPHA_UNDERBAR]   = 0x2376, // ⍶
  [LEFT_CEILING]     = 0x2308, // ⌈
  [LEFT_FLOOR]       = 0x230A, // ⌊     50
  [LOW_LINE]         = 0x005F, // _
  [NABLA]            = 0x2207, // ∇
  [INCREMENT]        = 0x2206, // ∆
  [DELTA_UNDERBAR]   = 0x2359, // ⍙
  [RING_OPERATOR]    = 0x2218, // ∘     55
  [JOT_DIAERESIS]    = 0x2364, // ⍤
  [APOSTROPHE]       = 0x0027, // '
  [QUAD_EQUAL]       = 0x2338, // ⌸
  [QUAD]             = 0x2395, // ⎕
  [SQUISH_QUAD]      = 0x2337, // ⌷     60
  [DOWN_TACK_JOT]    = 0x234E, // ⍎
  [IDENTICAL]        = 0x2261, // ≡
  [UP_TACK_JOT]      = 0x2355, // ⍕
  [NOT_IDENTICAL]    = 0x2262, // ≢
  [RIGHT_TACK]       = 0x22A2, // ⊢     65
  [LEFT_TACK]        = 0x22A3, // ⊣
  [SUBSET]           = 0x2282, // ⊂
  [SUPERSET]         = 0x2283, // ⊃
  [CHI]              = 0x03C7, // χ
  [INTERSECTION]     = 0x2229, // ∩     70
  [UNION]            = 0x222A, // ∪
  [UP_TACK]          = 0x22A5, // ⊥
  [DOWN_TACK]        = 0x22A4, // ⊤
  [VERTICAL_LINE]    = 0x007C, // |
  [UP_SHOE_JOT]      = 0x235D, // ⍝     75
  [COMMA_BAR]        = 0x236A, // ⍪
  [BACKSLASH_BAR]    = 0x2340, // ⍀
  [SLASH_BAR]        = 0x233F, // ⌿
  [QUAD_COLON]       = 0x2360, // ⍠     79
};
