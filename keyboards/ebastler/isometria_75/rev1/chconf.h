/* Copyright 2020 Moritz Plattner (ebastler)
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

/* Change system timer resolution, because TIM2 and TIM3 are different */
#define CH_CFG_ST_RESOLUTION                16
#define CH_CFG_INTERVALS_SIZE               16

/* no clue, wouldn't compile without */
#define CH_CFG_USE_TM                       FALSE

#include_next <chconf.h>
