/* Copyright 2023 iiWoodstocK
   
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

// Force n-key rollover
#define FORCE_NKRO

//Set keyboard debounce time
#define DEBOUNCE 7

#ifdef RGB_MATRIX_ENABLE 
    // RGB step values
    #define RGBLIGHT_HUE_STEP 32             // The number of steps to cycle through the hue by (default 10)
    #define RGBLIGHT_SAT_STEP 17             // The number of steps to increment the saturation by (default 17)
    #define RGBLIGHT_VAL_STEP 17             // The number of steps to increment the brightness by (default 17)

    // Startup values, when none have been set
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR // Sets the default effect mode, if none has been set (was RGB_MATRIX_SOLID_COLOR)
    #define RGB_MATRIX_DEFAULT_HUE 0                         // Sets the default hue value, if none has been set
    #define RGB_MATRIX_DEFAULT_SAT 191                        // Sets the default saturation value, if none has been set
    #define RGB_MATRIX_DEFAULT_VAL 255                        // Sets the default brightness value, if none has been set
    #define RGB_MATRIX_DEFAULT_SPD 127                        // Sets the default animation speed, if none has been set

#endif //RGB_MATRIX_ENABLE

