/* Copyright 2022 Basic I/O Instruments (@scottywei)
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

#include "command65.h"
#include "quantum.h"
#include "action.h"

bool dip_switch_update_kb(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
            } else {
                action_exec((keyevent_t){.key = (keypos_t){.row = 4, .col = 7}, .pressed = 0, .time = 5});
            }
            break;
        case 1:
            if (active) {
            } else {
                action_exec((keyevent_t){.key = (keypos_t){.row = 4, .col = 8}, .pressed = 0, .time = 5});
            }
            break;
    }
    return true;
}