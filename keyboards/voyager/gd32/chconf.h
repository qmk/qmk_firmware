/* Copyright 2021 QMK
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

 #pragma once

#define CH_CFG_ST_RESOLUTION 16

#define CH_CFG_ST_FREQUENCY 2000

#define CH_CFG_INTERVALS_SIZE 32

#define CH_CFG_TIME_TYPES_SIZE 32

#define CH_CFG_USE_CONDVARS_TIMEOUT FALSE

#include_next <chconf.h>
