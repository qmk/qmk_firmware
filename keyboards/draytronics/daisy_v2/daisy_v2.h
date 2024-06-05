/*Copyright 2024 Blake Drayson / Draytronics

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

This code is inspired by and adapted from the code used in the Printed Pad by Noah Beidelman (@noahbei)

It also references the concept and some pixel frames (the arasaka logo) form Aleks (@aleksbrgt)

Other pixel images are either created by me or use the resources of Velency Grpahics https://www.valencygraphics.com/cyberpunk-2077

No claim for licence or ownership is made for any logos or similarities to logos or brand names.
*/

#pragma once

#include "quantum.h"

//for oled key press
extern bool key_pressed;

// for changing oled display mode
extern uint8_t current_display_mode;

// for hidden animation toggle
extern bool hidden;

//for determining when the layer is changed and having a timer for how long we flash the layer
extern uint32_t flash_timer;
extern bool layer_changed;
