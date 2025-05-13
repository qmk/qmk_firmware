/* Copyright 2025 htx-studio (@https://github.com/htx-studio)
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

#ifndef ONE_HANDED_KEYBOARD_H
#define ONE_HANDED_KEYBOARD_H

#include "quantum.h"

typedef union {
    uint16_t TrackballDPI;
} user_config_t;

void pointing_adns9800_cpi_up(void);
void pointing_adns9800_cpi_down(void);
void pointing_adns9800_reset(void);

#endif // ONE_HANDED_KEYBOARD_H
