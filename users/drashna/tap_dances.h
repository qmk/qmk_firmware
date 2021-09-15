/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "drashna.h"

// define diablo macro timer variables
extern uint8_t diablo_times[];
typedef struct {
    uint16_t timer;
    uint8_t  key_interval;
    uint8_t  keycode;
} diablo_timer_t;

typedef struct {
    uint8_t index;
    uint8_t keycode;
} diable_keys_t;

extern diablo_timer_t diablo_timer[];

void run_diablo_macro_check(void);

#ifdef TAP_DANCE_ENABLE
enum {
    TD_D3_1 = 0,
    TD_D3_2,
    TD_D3_3,
    TD_D3_4,
};
#endif  // TAP_DANCE_ENABLE
