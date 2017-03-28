/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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


#define USE_SERIAL

#define TAPPING_TERM 150

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#ifdef SUBPROJECT_rev1
    #include "../../rev1/config.h"
    #define COMPACT_KEYMAP( \
      k00, k01, k02, k03, k04, k05, k40, k41, k42, k43, k44, k45, \
      k10, k11, k12, k13, k14, k15, k50, k51, k52, k53, k54, k55, \
      k20, k21, k22, k23, k24, k25, k60, k61, k62, k63, k64, k65, \
      k30, k31, k32, k33, k34, k35, k70, k71, k72, k73, k74, k75 \
    ) \
    { \
      { KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05 }, \
      { KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15 }, \
      { KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25 }, \
      { KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35 }, \
      { KC_##k40, KC_##k41, KC_##k42, KC_##k43, KC_##k44, KC_##k45 }, \
      { KC_##k50, KC_##k51, KC_##k52, KC_##k53, KC_##k54, KC_##k55 }, \
      { KC_##k60, KC_##k61, KC_##k62, KC_##k63, KC_##k64, KC_##k65 }, \
      { KC_##k70, KC_##k71, KC_##k72, KC_##k73, KC_##k74, KC_##k75 } \
    }
#endif
#ifdef SUBPROJECT_rev2
    #include "../../rev2/config.h"
    #define COMPACT_KEYMAP( \
      k00, k01, k02, k03, k04, k05, k45, k44, k43, k42, k41, k40, \
      k10, k11, k12, k13, k14, k15, k55, k54, k53, k52, k51, k50, \
      k20, k21, k22, k23, k24, k25, k65, k64, k63, k62, k61, k60, \
      k30, k31, k32, k33, k34, k35, k75, k74, k73, k72, k71, k70 \
      ) \
      { \
        { KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05 }, \
        { KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15 }, \
        { KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25 }, \
        { KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35 }, \
        { KC_##k40, KC_##k41, KC_##k42, KC_##k43, KC_##k44, KC_##k45 }, \
        { KC_##k50, KC_##k51, KC_##k52, KC_##k53, KC_##k54, KC_##k55 }, \
        { KC_##k60, KC_##k61, KC_##k62, KC_##k63, KC_##k64, KC_##k65 }, \
        { KC_##k70, KC_##k71, KC_##k72, KC_##k73, KC_##k74, KC_##k75 } \
      }
#endif
#ifdef SUBPROJECT_rev2fliphalf
	#include "../../rev2fliphalf/config.h"
#endif
