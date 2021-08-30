/* Copyright 2020 Jay Greco
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


// Encoders are defined in order. 1: B2 & B3, 2: B4 & B5, 3: D0 & D1, 4: D2 & D3
#define ENCODERS_PAD_A { B2, B4, D0, D3 }
#define ENCODERS_PAD_B { B3, B5, D1, D2 }
#define ENCODER_DIRECTION_FLIP
// For some reason, the 4th encoder is inverted and needs to actually be D3&D2 in the firmware. "Clockwise" makes sense in the keymap this way.