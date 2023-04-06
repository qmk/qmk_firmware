/*
Copyright 2019 Sidney Bovet <sidney.bovet@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/*
Note: the following configuration uses 98% of the flash memory, be
careful if you enable anything else. Also have a look at rules.mk
where some things are disabled to save space as well.
*/

#pragma once

/* RGB Underglow
This will not be used, as RGBLIGHT_ENABLE is set to 'no' in rules.mk
We do not have enough space in the flash for this at the moment, maybe
further optimizations can be done on that side.
*/
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLED_NUM 2
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* disable action features */
// #define NO_ACTION_ONESHOT // 462 bytes <- this needs to be un-commented out if Link Time Optimization is disabled, otherwise file is too large
// The two below are implicit since we use LTO_ENABLE (in rules.mk)
