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

/* 
 * Linux and ChromeOS have a few differences vs. Windows in the
 * AltGr map.
 *
 * See keymap_us_international.h for the core codes.
 */

#pragma once

#include "keymap_us_international.h"

// clang-format off

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ` │ ¡ │ ² │ ³ │ ¤ │ € │ ¼ │ ½ │ ¾ │ ‘ │ ’ │ ¥ │ × │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Ä │ Å │ É │ ® │ Þ │ Ü │ Ú │ Í │ Ó │ Ö │ « │ » │  ¬  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │ Á │ ß │ Ð │   │   │   │   │ Œ │ Ø │ ¶ │ ' │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │ Æ │   │ © │   │   │ Ñ │ µ │ Ç │ ˙ │ ¿ │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */

// Row 1
#define US_GRV  ALGR(US_DGRV) // `
// Row 3
#define US_OE   ALGR(US_K)    // Œ
#define US_QUOT ALGR(US_ACUT) // '
#undef US_NDAC
// Row 4
#define US_DOTA ALGR(US_DOT)  // ˙ (dead)

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ~ │   │ ˝ │ ¯ │ £ │ ¸ │ ^ │  ̛  │ ˛ │ ˘ │ ° │  ̣ │ ÷ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │ “ │ ” │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │   │ " │        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │        │   │   │   │   │   │   │   │   │ ˇ │  ̉ │          │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define US_TILD S(ALGR(US_DGRV)) // ~
#define US_DACU S(ALGR(US_2))    // ˝ (dead)
#define US_MACR S(ALGR(US_3))    // ¯ (dead)
#define US_CEDL S(ALGR(US_5))    // ¸ (dead)
#define US_CIRC S(ALGR(US_6))    // ^
#define US_HORN S(ALGR(US_7))    //  ̛  (dead)
#define US_OGON S(ALGR(US_8))    // ˛ (dead)
#define US_BREV S(ALGR(US_9))    // ˘ (dead)
#define US_RNGA S(ALGR(US_0))    // ° (dead)
#define US_DOTB S(ALGR(US_MINS)) //  ̣ (dead)
// Row 2
#define US_LDQU S(ALGR(US_LBRC)) // “
#define US_RDQU S(ALGR(US_LBRC)) // ”
// Row 3
#define US_DQUO S(ALGR(US_ACUT)) // "
#undef US_NDDR
// Row 4
#define US_CENT S(ALGR(US_C))    // ¢
#define US_CARN S(ALGR(US_DOT))  // ˇ (dead)
#define US_HOKA S(ALGR(US_SLSH)) //  ̉ (dead)
