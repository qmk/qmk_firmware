/* Copyright 2017 Balz Guenat
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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H


// place overrides here

// higher value means deeper actuation point, less sensitive
// be careful and only make small adjustments (steps of 1 or 2).
// too high and keys will fail to actuate. too low and keys will actuate spontaneously.
// test all keys before further adjustment.
// this should probably stay in the range +/-5.
#undef ACTUATION_DEPTH_ADJUSTMENT
#define ACTUATION_DEPTH_ADJUSTMENT +1

#endif
