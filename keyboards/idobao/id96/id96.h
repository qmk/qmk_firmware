/*
 * This file is part of the QMK Firmware distribution (https://github.com/qmk/qmk_firmware).
 * Copyright 2018-2021 "kaylanm" <http://github.com/kaylanm> [Melody96]
 *                     Vino Rodrigues <http://github.com/vinorodrigues> [ID96]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/*
 * The layout macro for the ID96 keyboard, with illustrative grid of a typical
 * assignment.
 * ,---------------------------------------------------------------------------
 * |ESC|F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|PSC|HOM|END|PGU|PGD|DEL|
 * ,--------------------------------------------------------------------------|
 * | ` |1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | + | \ |BKS|NLK| / | * | - |
 * |--------------------------------------------------------------------------|
 * | TAB | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \ | 7 | 8 | 9 | + |
 * |--------------------------------------------------------------------------|
 * | CTRL  | A | S | D | F | G | H | J | K | L | ; | ' |  RET | 4 | 5 | 6 | + |
 * |--------------------------------------------------------------------------|
 * | LSHIFT | Z | X | C | V | B | N | M | , | . | / |RSHFT| ↑ | 1 | 2 | 3 |ENT|
 * |--------------------------------------------------------------------------|
 * |LCTL|LWIN|LALT|         SPACE         |CTL|ALT|FN | ← | ↓ | → | 0 | . |ENT|
 * `---------------------------------------------------------------------------
 */

#define ____ KC_NO

#define LAYOUT( \
  K050, K051, K052, K053, K054, K055, K056, K057, K058, K118, K117, K115, K114, K113, K116, K112, K111, K110, K063, \
  K040, K041, K042, K043, K044, K045, K046, K047, K048, K108, K107, K105, K104, K103, K106, K102, K101, K100, K064, \
  K030, K031, K032, K033, K034, K035, K036, K037, K038, K098, K097, K095, K094, K084,       K096, K092, K091, K090, \
  K020, K021, K022, K023, K024, K025, K026, K027, K028, K088, K087, K085, K093,             K086, K082, K081, K080, \
  K010, K011, K012, K013, K014, K015, K016, K017, K018, K078, K077, K075, K074,       K073, K076, K072, K071, K070, \
  K000, K001, K002,                   K006,                   K008, K007, K005, K004, K003, K066, K062, K061, K060  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008 }, \
    { K010, K011, K012, K013, K014, K015, K016, K017, K018 }, \
    { K020, K021, K022, K023, K024, K025, K026, K027, K028 }, \
    { K030, K031, K032, K033, K034, K035, K036, K037, K038 }, \
    { K040, K041, K042, K043, K044, K045, K046, K047, K048 }, \
    { K050, K051, K052, K053, K054, K055, K056, K057, K058 }, \
    { K060, K061, K062, K063, K064, ____, K066, ____, ____ }, \
    { K070, K071, K072, K073, K074, K075, K076, K077, K078 }, \
    { K080, K081, K082, ____, K084, K085, K086, K087, K088 }, \
    { K090, K091, K092, K093, K094, K095, K096, K097, K098 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108 }, \
    { K110, K111, K112, K113, K114, K115, K116, K117, K118 }  \
}
