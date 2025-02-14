/* Copyright 2019 Michiel Visser (@msvisser)
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

/* Custom keycodes for Lighting and Bluetooth control */
enum anne_pro_keycodes {
    APL_RGB = QK_USER,
    APL_RAT,
    APL_BRT,
    APL_MOD,
    APB_OFF,
    APB_ON,
    APB_LGC,
    APB_HLQ,
    APB_HC1,
    APB_HC2,
    APB_HC3,
    APB_HC4,
    APB_HS1,
    APB_HS2,
    APB_HS3,
    APB_HS4,
    APB_HD1,
    APB_HD2,
    APB_HD3,
    APB_HD4,
};
