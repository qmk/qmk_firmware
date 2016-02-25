#ifndef KEYMAP_CANADIAN_MULTILINGUAG_H
#define KEYMAP_CANADIAN_MULTILINGUAG_H

#include "keymap_common.h"

// Alt gr
#ifndef ALTGR
#define ALTGR(kc)   RALT(kc)
#endif
#ifndef ALGR
#define ALGR(kc)    ALTGR(kc)
#endif

#define CM_ALTGR    KC_RALT
#define CM_ALGR     CM_ALTGR

#ifndef GR2A
#define GR2A(kc)    RCTL(kc)
#endif

// Normal characters
// First row
#define CM_SLASH    KC_GRV      // /
#define CM_SLSH     CM_SLASH

// Second row
#define CM_DEAD_CIRCUMFLEX  KC_LBRACKET         // dead ^
#define CM_DCRC             CM_DEAD_CIRCUMFLEX
#define CM_C_CEDILLA        KC_RBRACKET         // Ç
#define CM_CCED             CM_C_CEDILLA

// Third row
#define CM_E_GRAVE  KC_QUOT     // è
#define CM_EGRV     CM_E_GRAVE
#define CM_A_GRAVE  KC_BSLASH   // à
#define CM_AGRV     CM_A_GRAVE

// Fourth row
#define CM_U_GRAVE  KC_NONUS_BSLASH     // ù
#define CM_UGRV     CM_U_GRAVE
#define CM_E_ACUTE  KC_SLSH             // é
#define CM_ECUT     CM_E_ACUTE

// Shifted characters
// First row
#define CM_BACKSLASH    LSFT(CM_SLASH)  /* \ */
#define CM_BSLS         CM_BACKSLASH
#define CM_QUESTION     LSFT(KC_6)      // ?
#define CM_QEST         CM_QUESTION

// Second row
#define CM_DEAD_TREMA   LSFT(CM_DEAD_CIRCUMFLEX)    // dead trema/umlaut/diaresis for ä ë ï ö ü
#define CM_DTRM         CM_DEAD_TREMA

// Third row
// all same as US-QWERTY, or capitalised character of the non-shifted key

// Fourth row
#define CM_APOSTROPHE   LSFT(KC_COMMA)  // '
#define CM_APOS         CM_APOSTROPHE
#define CM_DOUBLE_QUOTE LSFT(KC_DOT)    // "
#define CM_DQOT         CM_DOUBLE_QUOTE

// Alt Gr-ed characters
// First row
#define CM_PIPE                 ALTGR(CM_SLASH)         // |
#define CM_CURRENCY             ALTGR(KC_4)             // ¤
#define CM_CURR                 CM_CURRENCY
#define CM_LEFT_CURLY_BRACE     ALTGR(KC_7)             // {
#define CM_LCBR                 CM_LEFT_CURLY_BRACE
#define CM_RIGHT_CURLY_BRACE    ALTGR(KC_8)             // }
#define CM_RCBR                 CM_RIGHT_CURLY_BRACE
#define CM_LBRACKET             ALTGR(KC_9)             // [
#define CM_LBRC                 CM_LBRACKET
#define CM_RBRACKET             ALTGR(KC_0)             // ]
#define CM_RBRC                 CM_RBRACKET
#define CM_NEGATION             ALTGR(KC_EQUAL)         // ¬
#define CM_NEGT                 CM_NEGATION

// Second row
// euro symbol not available on Linux? (X.org)
#define CM_EURO         ALTGR(KC_E)                 // €
#define CM_DEAD_GRAVE   ALTGR(CM_DEAD_CIRCUMFLEX)
#define CM_DGRV         CM_DEAD_GRAVE               // dead `
#define CM_TILDE        ALTGR(CM_C_CEDILLA)         // ~
#define CM_TILD         CM_TILDE

// Third row
#define CM_DEGREE   ALTGR(KC_SCOLON)    // °
#define CM_DEGR     CM_DEGREE

// Fourth row
#define CM_LEFT_GUILLEMET   ALTGR(KC_Z)         // «
#define CM_LGIL             CM_LEFT_GUILLEMET
#define CM_RIGHT_GUILLEMET  ALTGR(KC_X)         // »
#define CM_RGIL             CM_RIGHT_GUILLEMET
#define CM_LESS             ALTGR(KC_COMMA)     // <
#define CM_GREATER          ALTGR(KC_DOT)       // >
#define CM_GRTR             CM_GREATER

// Space bar
#define CM_NON_BREAKING_SPACE   ALTGR(KC_SPACE)
#define CM_NBSP                 CM_NON_BREAKING_SPACE

// GR2A-ed characters (non-exhaustive list)
// First row
#define CM_SUPERSCRIPT_ONE      GR2A(KC_1)  // ¹
#define CM_SUP1                 CM_SUPERSCRIPT_ONE
#define CM_SUPERSCRIPT_TWO      GR2A(KC_2)  // ²
#define CM_SUP2                 CM_SUPERSCRIPT_TWO
#define CM_SUPERSCRIPT_THREE    GR2A(KC_3)  // ³
#define CM_SUP3                 CM_SUPERSCRIPT_THREE
#define CM_ONE_QUARTER          GR2A(KC_4)  // ¼
#define CM_1QRT                 CM_ONE_QUARTER
#define CM_ONE_HALF             GR2A(KC_5)  // ½
#define CM_1HLF                 CM_ONE_HALF
#define CM_THREE_QUARTERS       GR2A(KC_6)  // ¾
#define CM_3QRT                 CM_THREE_QUARTERS
// nothing on 7-0 and -
#define CM_DEAD_CEDILLA         GR2A(KC_EQUAL)  // dead ¸
#define CM_DCED                 CM_DEAD_CEDILLA

// Second row
#define CM_OMEGA            GR2A(KC_Q)  // ω
#define CM_OMEG             CM_OMEGA
#define CM_L_STROKE         GR2A(KC_W)  // ł
#define CM_LSTK             CM_L_STROKE
#define CM_OE_LIGATURE      GR2A(KC_E)  // œ
#define CM_OE               CM_OE_LIGATURE
#define CM_PARAGRAPH        GR2A(KC_R)  // ¶
#define CM_PARG             CM_PARAGRAPH
#define CM_T_STROKE         GR2A(KC_T)  // ŧ
#define CM_LEFT_ARROW       GR2A(KC_Y)  // ←
#define CM_LARW             CM_LEFT_ARROW
#define CM_DOWN_ARROW       GR2A(KC_U)  // ↓
#define CM_DARW             CM_DOWN_ARROW
#define CM_RIGHT_ARROW      GR2A(KC_I)  // →
#define CM_RARW             CM_RIGHT_ARROW
#define CM_O_STROKE         GR2A(KC_O)  // ø
#define CM_OSTK             CM_O_STROKE
#define CM_THORN            GR2A(KC_P)  // þ
#define CM_THRN             CM_THORN
// nothing on ^
#define CM_DEAD_TILDE       GR2A(CM_C_CEDILLA)  // dead ~
#define CM_DTLD             CM_DEAD_TILDE

// Third row
#define CM_AE_LIGATURE  GR2A(KC_A)      // æ
#define CM_AE           CM_AE_LIGATURE
#define CM_SHARP_S      GR2A(KC_S)      // ß
#define CM_SRPS         CM_SHARP_S
#define CM_ETH          GR2A(KC_D)      // ð
// nothing on F
#define CM_ENG          GR2A(KC_G)      // ŋ
#define CM_H_SRTOKE     GR2A(KC_H)      // ħ
#define CM_HSTK         CM_H_SRTOKE
#define CM_IJ_LIGATURE  GR2A(KC_J)      // ĳ
#define CM_IJ           CM_IJ_LIGATURE
#define CM_KRA          GR2A(KC_K)      // ĸ
#define CM_L_FLOWN_DOT  GR2A(KC_L)      // ŀ
#define CM_LFLD         CM_L_FLOWN_DOT
#define CM_DEAD_ACUTE   GR2A(KC_SCLN)   // dead acute accent
#define CM_DACT         CM_DEAD_ACUTE
// nothing on È & À

// Fourth row
#define CM_CENT                 GR2A(KC_C)  // ¢
#define CM_LEFT_DOUBLE_QUOTE    GR2A(KC_V)  // “
#define CM_LDQT                 CM_LEFT_DOUBLE_QUOTE
#define CM_RIGHT_DOUBLE_QUOTE   GR2A(KC_B)  // ”
#define CM_RDQT                 CM_RIGHT_DOUBLE_QUOTE
#define CM_N_APOSTROPHE         GR2A(KC_N)  // ŉ (deprecated unicode codepoint)
#define CM_NAPO                 CM_N_APOSTROPHE
#define CM_MU   GR2A(KC_M)      // μ
// ─ TODO box drawing character?
#define CM_HYPHENATION_POINT    GR2A(CM_DOT)    // ‧  TODO not an interpunct ?

// GR2A-shifted characters (non-exhaustive list)
// First row
#define CM_PLUS_MINUS   LSFT(GR2A(KC_9))    // ±
#define CM_PSMS         CM_PLUS_MINUS

// Fourth row
#define CM_LEFT_QUOTE           LSFT(GR2A(KC_V))    // ‘
#define CM_LQOT                 CM_LEFT_QUOTE
#define CM_RIGHT_QUOTE          LSFT(GR2A(KC_B))    // ’
#define CM_RQOT                 CM_RIGHT_QUOTE

#endif
