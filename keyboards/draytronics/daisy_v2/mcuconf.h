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

It also references the concept of glitching animations from Aleks (@aleksbrgt)

The pixel graphics used here are from a combination of sources;

1. Layer indicators are created by myself and free to use by anyone.
2. "Revengeday", "Cyber Cafe", "Cortex Implant" logos are used with kind permission of OBEY THE SYSTEM.
   A collective of Fediverse instances and creatives. https://git.cyberwa.re/obey-the-system.
   They are licenced as Non-Commercial and for use by members of the network, with attribution.
3. Key press indicator graphics were commissioned for this project and were designed by the
   amazing https://corteximplant.com/@jadedtwin / https://www.jadedtwin.com/
*/
#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
