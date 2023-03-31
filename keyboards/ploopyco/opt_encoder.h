/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2020 Ploopy Corporation
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

#ifndef SCROLLER_AR_SIZE
#    define SCROLLER_AR_SIZE 31
#endif

#ifndef SCROLL_THRESH_RANGE_LIM
#    define SCROLL_THRESH_RANGE_LIM 10
#endif

void opt_encoder_init(void);
/* Return the rotation direction, positive value means clockwise, negative value
 * means counter-clockwise */
int8_t opt_encoder_handler(uint16_t curA, uint16_t curB);
