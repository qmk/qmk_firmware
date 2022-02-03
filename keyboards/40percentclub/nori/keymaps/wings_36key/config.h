/* Copyright 2018
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

#define IGNORE_MOD_TAP_INTERRUPT  // MT key must be held longer than tapping term for
                                  // modifer to be registered
#define RETRO_TAPPING_PER_KEY
#define TAPPING_TERM_PER_KEY

#define COMBO_COUNT 2             // number of combos used
#define COMBO_TERM 40             // time out for combos in ms
#define TAPPING_TERM 200          // time out for tap-hold in ms

