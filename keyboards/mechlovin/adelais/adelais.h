/* Copyright 2020 Team Mechlovin
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

#include "quantum.h"

#ifdef KEYBOARD_mechlovin_adelais_rgb_led_rev1
    #include "rev1.h"
#elif KEYBOARD_mechlovin_adelais_rgb_led_rev2
    #include "rev2.h"
#elif KEYBOARD_mechlovin_adelais_rgb_led_rev3
    #include "rev3.h"
#elif KEYBOARD_mechlovin_adelais_standard_led_arm_rev2
    #include "rev2.h"
#elif KEYBOARD_mechlovin_adelais_standard_led_arm_rev3
    #include "rev3.h"
#elif KEYBOARD_mechlovin_adelais_standard_led_arm_rev4
    #include "rev4.h"
#elif KEYBOARD_mechlovin_adelais_standard_led_avr_rev1
    #include "rev1.h"
#endif
