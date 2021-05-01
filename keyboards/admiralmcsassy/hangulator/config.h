/* Copyright 2021 AdmiralMcSassy dinglefritzstinklepuss@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6660
#define DEVICE_VER 0x0001
#define MANUFACTURER AdmiralMcSassy
#define PRODUCT Hangulator
#define DESCRIPTION Pterodactyl shaped

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16
// clang-format off
#define DIRECT_PINS { \
    { A15,    C12,    D2,     D5,     B3,     B6,     E2, C14, F2, A3, C5,     B2,     E10,    E12,    E15,    B12 }, \
    { C10,    D0,     D3,     D6,     B4,     B8,     E3, C15, C3, A2, C4,     B1,     E8,     E11,    E14,    B11 }, \
    { C11,    D1,     D4,     D7,     B5,     B9,     E4, F9,  C2, A1, A7,     B0,     E7,     E9,     E13,    B10 }, \
    { NO_PIN, NO_PIN, NO_PIN, E0,     E1,     C13,    E5, F10, C1, A0, A4,     A5,     A6,     NO_PIN, NO_PIN, NO_PIN }, \
    { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, E6, F0,  F1, F3, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN } \
}
// clang-format on

#define DEBOUNCE 5