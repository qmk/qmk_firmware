/* Copyright 2019 Ethan Durrant (emdarcher)
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

#define LAYOUT( \
    k0, k1, k2, \
    k3, k4, k5, \
                \
        k6, \
    k7, k8, k9 \
) \
{ \
    {k0, k1, k2}, \
    {k3, k4, k5}, \
    {KC_NO, k6, KC_NO}, \
    {k7, k8, k9}, \
}


