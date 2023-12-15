/*
Copyright 2022 Gondolindrim

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

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

//#define ALL_RGBS // Define the RGB option here
//#define LINE_RGBS
//#define RUNE_RGBS
#define LUKE_RGBS

#define RGBLIGHT_LED_MAP {17 , 0  , 1  , 2  , 3  , 18 , 20 , 16 , 4  , 5  , 6  , 7  , 8  , 9  , 10 , 11 , 19 , 12 , 13 , 14 , 15 , 21}
//                        D18, D19, D20, D21, D22, D23, D24, D25, D26, D27, D28, D29, D60, D61, D62, D63, D64, D65, D66, D67, D68, D69}

#ifdef RUNE_RGBS
#       undef RGBLIGHT_LED_MAP
#       define RGBLIGHT_LED_MAP {1  , 6  , 7  , 8  , 9  , 2  , 5  , 0  , 10 , 11 , 12 , 13 , 14 , 15 , 16 , 17  , 3  , 4 , 18 , 19 , 20 , 21 }
//                               D18, D19, D20, D21, D22, D23, D24, D25, D26, D27, D28, D29, D60, D61, D62, D63, D64, D65, D66, D67, D68, D69}
#endif

#ifdef LUKE_RGBS
#       undef RGBLIGHT_LED_MAP
#       define RGBLIGHT_LED_MAP {21 , 2  , 3  , 4  , 5  , 1  , 20 , 0  , 6  , 7  , 8  , 9  , 10 , 11 , 12 , 13 , 19 , 14 , 15 , 16 , 17 , 18 }
//                               D18, D19, D20, D21, D22, D23, D24, D25, D26, D27, D28, D29, D60, D61, D62, D63, D64, D65, D66, D67, D68, D69}
#endif

#define RGBLIGHT_DEFAULT_VAL 0
