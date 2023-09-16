/* Copyright 2021 s-ol
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

#include "quantum.h"

#define LED_LAYOUT(                                             \
                                                                \
    k01, k05, k02, k06, k10, k03, k07, k11, k15, k08, k12, k16) \
                                                                \
    { k01, k02, k03, k08, k07, k06, k05, k10, k11, k12, k16, k15, }
