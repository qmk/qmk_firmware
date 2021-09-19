/*
Copyright 2021 Takeshi Nishio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//------------------------------------------------------------------------------
// Rotary Encoder
//------------------------------------------------------------------------------
// Encoder triggers specific key matrix position,
// when turn knob clockwise or counterclockwise.
// This is handy to assign key codes by VIA.

// Number of endoder
#define ENCODERS 2

// Mappings of encoder rotation to key position in key matrix.
// First encoder,  Left side  : k85, k86
// Second encoder, Right side : k95, k96
#define ENCODERS_CW_KEY  { { 6, 8 }, { 6, 9 } }
#define ENCODERS_CCW_KEY { { 5, 8 }, { 5, 9 } }
