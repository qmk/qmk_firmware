/* Copyright 2020 Digid3ar
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

#include "quantum.h" // libreria core de qmk .. todo investigar

#define xxx KC_NO //

// primera matriz corresponde a el circuito de la pcb y
#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K113, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, K213, \
    K30, K31, K32, K36, K39, K310,K311,K313 \
    ) { \
    {K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013}, \
    {K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, xxx, K113}, \
    {K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, xxx, K213}, \
    {K30, K31, K32, xxx, xxx, xxx, K36, xxx, xxx, K39, K310, K311, xxx, K313} \
}
