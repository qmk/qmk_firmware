/* Copyright 2020 Joseph Wasson
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

#include "../talljoe.h"
#include "actions/td.grave.c"
#include "actions/td.lock.c"
#include "actions/td.semicolon.c"
#include "actions/td.function.c"

tap_dance_action_t tap_dance_actions[] = {
  [TD_SEMICOLON] = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_semicolon_each, tap_dance_semicolon_finished, tap_dance_semicolon_reset),
  [TD_LOCK]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_lock_finished, tap_dance_lock_reset),
  [TD_GRAVE]     = ACTION_TAP_DANCE_FN_ADVANCED(tap_dance_grave_each, tap_dance_grave_finished, NULL),
  [TD_FUNCTION]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_function_finished, tap_dance_function_reset),
};
