/*
Copyright 2022 Mechlovin'

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

#include "quantum.h"

#ifdef KEYBOARD_mechlovin_zed65_no_backlight_retro66
    #include "retro66.h"
#elif KEYBOARD_mechlovin_zed65_no_backlight_wearhaus66
    #include "wearhaus66.h"
#elif KEYBOARD_mechlovin_zed65_no_backlight_cor65
    #include "cor65.h"
#elif KEYBOARD_mechlovin_zed65_mono_led
    #include "mono_led.h"
#endif
