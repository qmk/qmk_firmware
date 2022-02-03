/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>
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

#include "quantum.h"

/* This a shortcut to help you visually see your layout */

#define ___ KC_NO

#define LAYOUT( \
             BN4, BN2,      \
        SW7, BN3, BN1, SW8, \
        SW4, SW5, SW6,      \
        SW3, SW2, SW1       \
    ) \
    { \
        { ___, BN4, BN2, ___ }, \
        { SW7, BN3, BN1, SW8 }, \
        { SW4, SW5, SW6, ___ }, \
        { SW3, SW2, SW1, ___ }, \
    }
