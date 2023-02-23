// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "keymap.h"

// clang-format off

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ { │ } │  |  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │ : │ " │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │ < │ > │ ? │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define KC_TILD S(KC_GRAVE) // ~
#define KC_EXLM S(KC_1)     // !
#define KC_AT   S(KC_2)     // @
#define KC_HASH S(KC_3)     // #
#define KC_DLR  S(KC_4)     // $
#define KC_PERC S(KC_5)     // %
#define KC_CIRC S(KC_6)     // ^
#define KC_AMPR S(KC_7)     // &
#define KC_ASTR S(KC_8)     // *
#define KC_LPRN S(KC_9)     // (
#define KC_RPRN S(KC_0)     // )
#define KC_UNDS S(KC_MINUS) // _
#define KC_PLUS S(KC_EQUAL) // +
// Row 2
#define KC_LCBR S(KC_LEFT_BRACKET)  // {
#define KC_RCBR S(KC_RIGHT_BRACKET) // }
#define KC_PIPE S(KC_BACKSLASH)     // |
// Row 3
#define KC_COLN S(KC_SEMICOLON) // :
#define KC_DQUO S(KC_QUOTE)     // "
// Row 4
#define KC_LABK S(KC_COMMA) // <
#define KC_RABK S(KC_DOT)   // >
#define KC_QUES S(KC_SLASH) // ?

// alias stuff
#define KC_TILDE KC_TILD
#define KC_EXCLAIM KC_EXLM
#define KC_DOLLAR KC_DLR
#define KC_PERCENT KC_PERC
#define KC_CIRCUMFLEX KC_CIRC
#define KC_AMPERSAND KC_AMPR
#define KC_ASTERISK KC_ASTR
#define KC_LEFT_PAREN KC_LPRN
#define KC_RIGHT_PAREN KC_RPRN
#define KC_UNDERSCORE KC_UNDS

#define KC_LEFT_CURLY_BRACE KC_LCBR
#define KC_RIGHT_CURLY_BRACE KC_RCBR

#define KC_COLON KC_COLN
#define KC_DOUBLE_QUOTE KC_DQUO
#define KC_DQT KC_DQUO

#define KC_LEFT_ANGLE_BRACKET KC_LABK
#define KC_LT KC_LABK
#define KC_RIGHT_ANGLE_BRACKET KC_RABK
#define KC_GT KC_RABK
#define KC_QUESTION KC_QUES
