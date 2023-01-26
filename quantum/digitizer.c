/* Copyright 2021
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

#include "digitizer.h"

digitizer_t digitizer_state = {
    .in_range = false,
    .tip      = false,
    .barrel   = false,
    .x        = 0,
    .y        = 0,
    .dirty    = false,
};

void digitizer_flush(void) {
    if (digitizer_state.dirty) {
        host_digitizer_send(&digitizer_state);
        digitizer_state.dirty = false;
    }
}

void digitizer_in_range_on(void) {
    digitizer_state.in_range = true;
    digitizer_state.dirty    = true;
    digitizer_flush();
}

void digitizer_in_range_off(void) {
    digitizer_state.in_range = false;
    digitizer_state.dirty    = true;
    digitizer_flush();
}

void digitizer_tip_switch_on(void) {
    digitizer_state.tip   = true;
    digitizer_state.dirty = true;
    digitizer_flush();
}

void digitizer_tip_switch_off(void) {
    digitizer_state.tip   = false;
    digitizer_state.dirty = true;
    digitizer_flush();
}

void digitizer_barrel_switch_on(void) {
    digitizer_state.barrel = true;
    digitizer_state.dirty  = true;
    digitizer_flush();
}

void digitizer_barrel_switch_off(void) {
    digitizer_state.barrel = false;
    digitizer_state.dirty  = true;
    digitizer_flush();
}

void digitizer_set_position(float x, float y) {
    digitizer_state.x     = x;
    digitizer_state.y     = y;
    digitizer_state.dirty = true;
    digitizer_flush();
}
