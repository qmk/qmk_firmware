/*Copyright 2021 Blake Drayson / Draytronics

Contact info@draytronics.co.uk

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

#define _x_ KC_NO

#include "quantum.h"

#define LAYOUT_daisy( \
  K00,           K03, \
  K10, K11, K12, K13, \
  K20, K21, K22, K23  \
) { \
{ K00, _x_, _x_, K03, }, \
{ K10, K11, K12, K13, }, \
{ K20, K21, K22, K23, }, \
}
