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
/* Keymap macros for the French BÉPO layout - http://bepo.fr */
#ifndef KEYMAP_BEPO_H
#define KEYMAP_BEPO_H

#include "keymap.h"

// Alt gr
#ifndef ALTGR
#define ALTGR(kc)   RALT(kc)
#endif
#ifndef ALGR
#define ALGR(kc)    ALTGR(kc)
#endif
#define BP_ALGR KC_RALT

// Normal characters
// First row (on usual keyboards)
#define BP_DOLLAR           KC_GRAVE            // $
#define BP_DLR              BP_DOLLAR
#define BP_DOUBLE_QUOTE     KC_1                // "
#define BP_DQOT             BP_DOUBLE_QUOTE
#define BP_LEFT_GUILLEMET   KC_2                // «
#define BP_LGIL             BP_LEFT_GUILLEMET
#define BP_RIGHT_GUILLEMET  KC_3                // »
#define BP_RGIL             BP_RIGHT_GUILLEMET
#define BP_LEFT_PAREN       KC_4                // (
#define BP_LPRN             BP_LEFT_PAREN
#define BP_RIGHT_PAREN      KC_5                // )
#define BP_RPRN             BP_RIGHT_PAREN
#define BP_AT               KC_6                // @
#define BP_PLUS             KC_7                // +
#define BP_MINUS            KC_8                // -
#define BP_MINS             BP_MINUS
#define BP_SLASH            KC_9                // /
#define BP_SLSH             BP_SLASH
#define BP_ASTERISK         KC_0                // *
#define BP_ASTR             BP_ASTERISK
#define BP_EQUAL            KC_MINUS            // =
#define BP_EQL              BP_EQUAL
#define BP_PERCENT          KC_EQUAL            // %
#define BP_PERC             BP_PERCENT

// Second row
#define BP_B                KC_Q
#define BP_E_ACUTE          KC_W        // é
#define BP_ECUT             BP_E_ACUTE
#define BP_P                KC_E
#define BP_O                KC_R
#define BP_E_GRAVE          KC_T        // è
#define BP_EGRV             BP_E_GRAVE
#define BP_DEAD_CIRCUMFLEX  KC_Y        // dead ^
#define BP_DCRC             BP_DEAD_CIRCUMFLEX
#define BP_V                KC_U
#define BP_D                KC_I
#define BP_L                KC_O
#define BP_J                KC_P
#define BP_Z                KC_LBRACKET
#define BP_W                KC_RBRACKET

// Third row
#define BP_A            KC_A
#define BP_U            KC_S
#define BP_I            KC_D
#define BP_E            KC_F
#define BP_COMMA        KC_G        // ,
#define BP_COMM         BP_COMMA
#define BP_C            KC_H
#define BP_T            KC_J
#define BP_S            KC_K
#define BP_R            KC_L
#define BP_N            KC_SCOLON
#define BP_M            KC_QUOTE
#define BP_C_CEDILLA    KC_BSLASH   // ç
#define BP_CCED         BP_C_CEDILLA

// Fourth row
#define BP_E_CIRCUMFLEX     KC_NONUS_BSLASH // ê
#define BP_ECRC             BP_E_CIRCUMFLEX
#define BP_A_GRAVE          KC_Z            // à
#define BP_AGRV             BP_A_GRAVE
#define BP_Y                KC_X
#define BP_X                KC_C
#define BP_DOT              KC_V            // .
#define BP_K                KC_B
#define BP_APOSTROPHE       KC_N
#define BP_APOS             BP_APOSTROPHE   // '
#define BP_Q                KC_M
#define BP_G                KC_COMMA
#define BP_H                KC_DOT
#define BP_F                KC_SLASH

// Shifted characters
// First row
#define BP_HASH     LSFT(BP_DOLLAR)     // #
#define BP_1        LSFT(KC_1)
#define BP_2        LSFT(KC_2)
#define BP_3        LSFT(KC_3)
#define BP_4        LSFT(KC_4)
#define BP_5        LSFT(KC_5)
#define BP_6        LSFT(KC_6)
#define BP_7        LSFT(KC_7)
#define BP_8        LSFT(KC_8)
#define BP_9        LSFT(KC_9)
#define BP_0        LSFT(KC_0)
#define BP_DEGREE   LSFT(BP_EQUAL)      // °
#define BP_DEGR     BP_DEGREE
#define BP_GRAVE    LSFT(BP_PERCENT)    // `
#define BP_GRV      BP_GRAVE

// Second row
#define BP_EXCLAIM  LSFT(BP_DEAD_CIRCUMFLEX)    // !
#define BP_EXLM     BP_EXCLAIM

// Third row
#define BP_SCOLON   LSFT(BP_COMMA)  // ;
#define BP_SCLN     BP_SCOLON

// Fourth row
#define BP_COLON    LSFT(BP_DOT)    // :
#define BP_COLN     BP_COLON
#define BP_QUESTION LSFT(BP_APOS)  // ?
#define BP_QEST     BP_QUESTION

// Space bar
#define BP_NON_BREAKING_SPACE   LSFT(KC_SPACE)
#define BP_NBSP                 BP_NON_BREAKING_SPACE

// AltGr-ed characters
// First row
#define BP_EN_DASH          ALTGR(BP_DOLLAR)    // –
#define BP_NDSH             BP_EN_DASH
#define BP_EM_DASH          ALTGR(KC_1)         // —
#define BP_MDSH             BP_EM_DASH
#define BP_LESS             ALTGR(KC_2)         // <
#define BP_GREATER          ALTGR(KC_3)         // >
#define BP_GRTR             BP_GREATER
#define BP_LBRACKET         ALTGR(KC_4)         // [
#define BP_LBRC             BP_LBRACKET
#define BP_RBRACKET         ALTGR(KC_5)         // ]
#define BP_RBRC             BP_RBRACKET
#define BP_CIRCUMFLEX       ALTGR(KC_6)         // ^
#define BP_CIRC             BP_CIRCUMFLEX
#define BP_PLUS_MINUS       ALTGR(KC_7)         // ±
#define BP_PSMS             BP_PLUS_MINUS
#define BP_MATH_MINUS       ALTGR(KC_8)         // −
#define BP_MMNS             BP_MATH_MINUS
#define BP_OBELUS           ALTGR(KC_9)         // ÷
#define BP_OBEL             BP_OBELUS
// more conventional name of the symbol
#define BP_DIVISION_SIGN    BP_OBELUS
#define BP_DVSN             BP_DIVISION_SIGN
#define BP_TIMES            ALTGR(KC_0)         // ×
#define BP_TIMS             BP_TIMES
#define BP_DIFFERENT        ALTGR(BP_EQUAL)     // ≠
#define BP_DIFF             BP_DIFFERENT
#define BP_PERMILLE         ALTGR(BP_PERCENT)   // ‰
#define BP_PMIL             BP_PERMILLE

// Second row
#define BP_PIPE                 ALTGR(BP_B)         // |
#define BP_DEAD_ACUTE           ALTGR(BP_E_ACUTE)   // dead ´
#define BP_DACT                 BP_DEAD_ACUTE
#define BP_AMPERSAND            ALTGR(BP_P)         // &
#define BP_AMPR                 BP_AMPERSAND
#define BP_OE_LIGATURE          ALTGR(BP_O)         // œ
#define BP_OE                   BP_OE_LIGATURE
#define BP_DEAD_GRAVE           ALTGR(BP_E_GRAVE)   // `
#define BP_DGRV                 BP_DEAD_GRAVE
#define BP_INVERTED_EXCLAIM     ALTGR(BP_DEAD_CIRCUMFLEX)   // ¡
#define BP_IXLM                 BP_INVERTED_EXCLAIM
#define BP_DEAD_CARON           ALTGR(BP_V)         // dead ˇ
#define BP_DCAR                 BP_DEAD_CARON
#define BP_ETH                  ALTGR(BP_D)         // ð
#define BP_DEAD_SLASH           ALTGR(BP_L)         // dead /
#define BP_DSLH                 BP_DEAD_SLASH
#define BP_IJ_LIGATURE          ALTGR(BP_J)         // ĳ
#define BP_IJ                   BP_IJ_LIGATURE
#define BP_SCHWA                ALTGR(BP_Z)         // ə
#define BP_SCWA                 BP_SCHWA
#define BP_DEAD_BREVE           ALTGR(BP_W)         // dead ˘
#define BP_DBRV                 BP_DEAD_BREVE

// Third row
#define BP_AE_LIGATURE              ALTGR(BP_A)         // æ
#define BP_AE                       BP_AE_LIGATURE
#define BP_U_GRAVE                  ALTGR(BP_U)           // ù
#define BP_UGRV                     BP_U_GRAVE
#define BP_DEAD_TREMA               ALTGR(BP_I)         // dead ¨ (trema/umlaut/diaresis)
#define BP_DTRM                     BP_DEAD_TREMA
#define BP_EURO                     ALTGR(BP_E)         // €
#define BP_TYPOGRAPHICAL_APOSTROPHE ALTGR(BP_COMMA)     // ’
#define BP_TAPO                     BP_TYPOGRAPHICAL_APOSTROPHE
#define BP_COPYRIGHT                ALTGR(BP_C)         // ©
#define BP_CPRT                     BP_COPYRIGHT
#define BP_THORN                    ALTGR(BP_T)         // þ
#define BP_THRN                     BP_THORN
#define BP_SHARP_S                  ALTGR(BP_S)         // ß
#define BP_SRPS                     BP_SHARP_S
#define BP_REGISTERED_TRADEMARK     ALTGR(BP_R)         // ®
#define BP_RTM                      BP_REGISTERED_TRADEMARK
#define BP_DEAD_TILDE               ALTGR(BP_N)         // dead ~
#define BP_DTLD                     BP_DEAD_TILDE
#define BP_DEAD_MACRON              ALTGR(BP_M)         // dead ¯
#define BP_DMCR                     BP_DEAD_MACRON
#define BP_DEAD_CEDILLA             ALTGR(BP_C_CEDILLA) // dead ¸
#define BP_DCED                     BP_DEAD_CEDILLA

// Fourth row
#define BP_NONUS_SLASH          ALTGR(BP_E_CIRCUMFLEX)  // / on non-us backslash key (102nd key, ê in bépo)
#define BP_NUSL                 BP_NONUS_SLASH
#define BP_BACKSLASH            ALTGR(BP_A_GRAVE)       /* \ */
#define BP_BSLS                 BP_BACKSLASH
#define BP_LEFT_CURLY_BRACE     ALTGR(BP_Y)             // {
#define BP_LCBR                 BP_LEFT_CURLY_BRACE
#define BP_RIGHT_CURLY_BRACE    ALTGR(BP_X)             // }
#define BP_RCBR                 BP_RIGHT_CURLY_BRACE
#define BP_ELLIPSIS             ALTGR(BP_DOT)           // …
#define BP_ELPS                 BP_ELLIPSIS
#define BP_TILDE                ALTGR(BP_K)             // ~
#define BP_TILD                 BP_TILDE
#define BP_INVERTED_QUESTION    ALTGR(BP_QUESTION)      // ¿
#define BP_IQST                 BP_INVERTED_QUESTION
#define BP_DEAD_RING            ALTGR(BP_Q)             // dead °
#define BP_DRNG                 BP_DEAD_RING
#define BP_DEAD_GREEK           ALTGR(BP_G)             // dead Greek key (following key will make a Greek letter)
#define BP_DGRK                 BP_DEAD_GREEK
#define BP_DAGGER               ALTGR(BP_H)             // †
#define BP_DAGR                 BP_DAGGER
#define BP_DEAD_OGONEK          ALTGR(BP_F)             // dead ˛
#define BP_DOGO                 BP_DEAD_OGONEK

// Space bar
#define BP_UNDERSCORE   ALTGR(KC_SPACE)     // _
#define BP_UNDS         BP_UNDERSCORE

// AltGr-Shifted characters (different from capitalised AltGr-ed characters)
// First row
#define BP_PARAGRAPH            ALTGR(BP_HASH)      // ¶
#define BP_PARG                 BP_PARAGRAPH
#define BP_LOW_DOUBLE_QUOTE     ALTGR(BP_1)         // „
#define BP_LWQT                 BP_LOW_DOUBLE_QUOTE
#define BP_LEFT_DOUBLE_QUOTE    ALTGR(BP_2)         // “
#define BP_LDQT                 BP_LEFT_DOUBLE_QUOTE
#define BP_RIGHT_DOUBLE_QUOTE   ALTGR(BP_3)         // ”
#define BP_RDQT                 BP_RIGHT_DOUBLE_QUOTE
#define BP_LESS_OR_EQUAL        ALTGR(BP_4)         // ≤
#define BP_LEQL                 BP_LESS_OR_EQUAL
#define BP_GREATER_OR_EQUAL     ALTGR(BP_5)         // ≥
#define BP_GEQL                 BP_GREATER_OR_EQUAL
// nothing on ALTGR(BP_6)
#define BP_NEGATION             ALTGR(BP_7)         // ¬
#define BP_NEGT                 BP_NEGATION
#define BP_ONE_QUARTER          ALTGR(BP_8)         // ¼
#define BP_1QRT                 BP_ONE_QUARTER
#define BP_ONE_HALF             ALTGR(BP_9)         // ½
#define BP_1HLF                 BP_ONE_HALF
#define BP_THREE_QUARTERS       ALTGR(BP_0)         // ¾
#define BP_3QRT                 BP_THREE_QUARTERS
#define BP_MINUTES              ALTGR(BP_DEGREE)    // ′
#define BP_MNUT                 BP_MINUTES
#define BP_SECONDS              ALTGR(BP_GRAVE)     // ″
#define BP_SCND                 BP_SECONDS

// Second row
#define BP_BROKEN_PIPE          LSFT(BP_PIPE)           // ¦
#define BP_BPIP                 BP_BROKEN_PIPE
#define BP_DEAD_DOUBLE_ACUTE    LSFT(BP_DEAD_ACUTE)     // ˝
#define BP_DDCT                 BP_DEAD_DOUBLE_ACUTE
#define BP_SECTION              ALTGR(LSFT(BP_P))       // §
#define BP_SECT                 BP_SECTION
// LSFT(BP_DEAD_GRAVE) is actually the same character as LSFT(BP_PERCENT)
#define BP_GRAVE_BIS            LSFT(BP_DEAD_GRAVE)     // `
#define BP_GRVB                 BP_GRAVE_BIS

// Third row
#define BP_DEAD_DOT_ABOVE       LSFT(BP_DEAD_TREMA)     // dead ˙
#define BP_DDTA                 BP_DEAD_DOT_ABOVE
#define BP_DEAD_CURRENCY        LSFT(BP_EURO)           // dead ¤ (next key will generate a currency code like ¥ or £)
#define BP_DCUR                 BP_DEAD_CURRENCY
#define BP_DEAD_HORN            LSFT(ALTGR(BP_COMMA))   // dead ̛
#define BP_DHRN                 BP_DEAD_HORN
#define BP_LONG_S               LSFT(ALTGR(BP_C))       // ſ
#define BP_LNGS                 BP_LONG_S
#define BP_TRADEMARK            LSFT(BP_REGISTERED_TRADEMARK)   // ™
#define BP_TM                   BP_TRADEMARK
#define BP_ORDINAL_INDICATOR_O  LSFT(ALTGR(BP_M))               // º
#define BP_ORDO                 BP_ORDINAL_INDICATOR_O
#define BP_DEAD_COMMA           LSFT(BP_DEAD_CEDILLA)   // dead ˛
#define BP_DCOM                 BP_DEAD_COMMA

// Fourth row
#define BP_LEFT_QUOTE           LSFT(ALTGR(BP_Y))       // ‘
#define BP_LQOT                 BP_LEFT_QUOTE
#define BP_RIGHT_QUOTE          LSFT(ALTGR(BP_X))       // ’
#define BP_RQOT                 BP_RIGHT_QUOTE
#define BP_INTERPUNCT           LSFT(ALTGR(BP_DOT))     // ·
#define BP_IPCT                 BP_INTERPUNCT
#define BP_DEAD_HOOK_ABOVE      LSFT(ALTGR(BP_QUESTION))    // dead ̉
#define BP_DHKA                 BP_DEAD_HOOK_ABOVE
#define BP_DEAD_UNDERDOT        LSFT(BP_DEAD_RING)      // dead ̣
#define BP_DUDT                 BP_DEAD_UNDERDOT
#define BP_DOUBLE_DAGGER        LSFT(BP_DAGGER)         // ‡
#define BP_DDGR                 BP_DOUBLE_DAGGER
#define BP_ORDINAL_INDICATOR_A  LSFT(ALTGR(BP_F))       // ª
#define BP_ORDA                 BP_ORDINAL_INDICATOR_A

// Space bar
#define BP_NARROW_NON_BREAKING_SPACE    ALTGR(BP_NON_BREAKING_SPACE)
#define BP_NNBS                         BP_NARROW_NON_BREAKING_SPACE

#endif
