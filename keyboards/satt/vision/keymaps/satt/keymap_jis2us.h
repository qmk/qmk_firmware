/* Copyright 2020 shela
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

#include "keymap_jp.h"

// clang-format off
/* Keymap for converting JIS to US */
const uint16_t PROGMEM keymap_jis2us[][2] = {
    [KC_A ... KC_CAPS] = { 0x00, 0x00 }, /* default value */

    [KC_1]    = { KC_1,    JP_EXLM }, /* 1 and ! -> 1 and ! */
    [KC_2]    = { KC_2,    JP_AT   }, /* 2 and " -> 2 and @ */
    [KC_3]    = { KC_3,    JP_HASH }, /* 3 and # -> 3 and # */
    [KC_4]    = { KC_4,    JP_DLR  }, /* 4 and $ -> 4 and $ */
    [KC_5]    = { KC_5,    JP_PERC }, /* 5 and % -> 5 and % */
    [KC_6]    = { KC_6,    JP_CIRC }, /* 6 and & -> 6 and ^ */
    [KC_7]    = { KC_7,    JP_AMPR }, /* 7 and ' -> 7 and & */
    [KC_8]    = { KC_8,    JP_ASTR }, /* 8 and ( -> 8 and * */
    [KC_9]    = { KC_9,    JP_LPRN }, /* 9 and ) -> 9 and ( */
    [KC_0]    = { KC_0,    JP_RPRN }, /* 0       -> 0 and ) */
    [KC_MINS] = { JP_MINS, JP_UNDS }, /* - and = -> - and _ */
    [KC_EQL]  = { JP_EQL,  JP_PLUS }, /* ^ and ~ -> = and + */
    [KC_LBRC] = { JP_LBRC, JP_LCBR }, /* @ and ` -> [ and { */
    [KC_RBRC] = { JP_RBRC, JP_RCBR }, /* [ and { -> ] and } */
    [KC_BSLS] = { JP_YEN,  JP_PIPE }, /* ] and } -> \ and | */
    [KC_NUHS] = { JP_YEN,  JP_PIPE }, /* ] and } -> \ and | */
    [KC_SCLN] = { JP_SCLN, JP_COLN }, /* ; and + -> ; and : */
    [KC_QUOT] = { JP_QUOT, JP_DQUO }, /* : and * -> ' and " */
    [KC_GRV]  = { JP_GRV,  JP_TILD }, /* Han/Zen -> ` and ~ */
    [KC_COMM] = { JP_COMM, JP_LABK }, /* , and < -> , and < */
    [KC_DOT]  = { JP_DOT,  JP_RABK }, /* . and > -> . and > */
    [KC_SLSH] = { JP_SLSH, JP_QUES }, /* / and ? -> / and ? */
};
// clang-format on
