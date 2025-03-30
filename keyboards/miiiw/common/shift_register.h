/* Copyright 2023 ArthurCyy <https://github.com/ArthurCyy>
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

#include <stdint.h>
#include "gpio.h"

#ifndef GPIOH_BASE
#   define GPIOH_BASE  (0xFF595A00U)
#endif

#ifndef SHR_SERIES_NUM
#   define SHR_SERIES_NUM 1
#endif

extern void shift_init(void);
extern void shift_enable(void);
extern void shift_disable(void);
extern void shift_writePin(pin_t pin, int level);
extern void shift_writeGroup(int group, uint8_t value);
extern void shift_writeAll(int level);
