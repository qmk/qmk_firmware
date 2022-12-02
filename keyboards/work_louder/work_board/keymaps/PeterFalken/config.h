/*
  *  Copyright (C) 2022  Luis Garcia
  *
  *  This program is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
  */

 #pragma once

 #include "config_common.h"

 // Avoid warning - "Attached USB accessory uses too much power."
 #ifndef USB_MAX_POWER_CONSUMPTION
     #define USB_MAX_POWER_CONSUMPTION 100
 #endif

 // Configuration
 #define RGB_DISABLE_WHEN_USB_SUSPENDED

 // Space optimizations - 01
 #undef LOCKING_SUPPORT_ENABLE
 #undef LOCKING_RESYNC_ENABLE
