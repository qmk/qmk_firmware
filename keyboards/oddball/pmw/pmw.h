/* Copyright 2020 Alexander Tulloh
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

typedef struct {
    /* 100 - 12000 CPI supported */
    uint16_t cpi;
} config_pmw_t;

typedef struct {
    int16_t x;
    int16_t y;
} report_pmw_t;

void pmw_init(void);
config_pmw_t pmw_get_config(void);
void pmw_set_config(config_pmw_t);
/* Reads and clears the current delta values on the PMW sensor */
report_pmw_t pmw_get_report(void);
