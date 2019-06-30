/* Copyright 2018 MechMerlin
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

// place overrides here

#define TAPPING_TERM 50
#define RETRO_TAPPING

#ifdef RGB_DI_PIN
#define RGBLIGHT_SLEEP
#endif

#ifdef MANUFACTURER
#undef MANUFACTURER
#endif
#ifdef PRODUCT
#undef PRODUCT
#endif
#ifdef DESCRIPTION
#undef DESCRIPTION
#endif

#define MANUFACTURER    Potato Inc.
#define PRODUCT         Qt3.14
#define DESCRIPTION     Look, a keyboard!
