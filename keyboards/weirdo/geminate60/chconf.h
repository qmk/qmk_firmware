/* Copyright 2020 Weirdo
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

// Need to override the SysTick timer to use TIM3 -- this is a 16-bit timer on F303
// so we need to change resolution and frequency to match.
#define CH_CFG_ST_RESOLUTION 16
#define CH_CFG_ST_FREQUENCY 10000
#include_next <chconf.h>
