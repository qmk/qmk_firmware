/* Copyright 2021 Vincent Santillo (vincentsantillo@gmail.com)
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

// Tap Dance Controller - returns a state based on the pattern pressed
uint8_t tap_dance_controller(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) return SINGLE_TAP_INT;
        else if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_TAP_INT;
        else if (!state->pressed) return DOUBLE_TAP;
        else return DOUBLE_HOLD;
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else if (state->count == 4) {
        if (state->interrupted || !state->pressed) return QUAD_TAP;
        else return QUAD_HOLD;
    } else return 11;
}
