/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
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

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

// no association keycode
#    define XXX \
        { 0, 0, 0 }

// clang-format off
#   define RGB_MATRIX_LAYOUT_LEDMAP( \
        ul1,   k13, k26, k36, k31, k33, k07, k63, k71, k76, ka6, ka7, ka3, ka5, k97,     k01,   ur1, \
        ul2,   k16, k17, k27, k37, k47, k46, k56, k57, k67, k77, k87, k86, k66, ka1,     k65,   ur2, \
        ul3,   k11, k10, k20, k30, k40, k41, k51, k50, k60, k70, k80, k81, k61, ka2,     k15,   ur3, \
        ul4,   k21, k12, k22, k32, k42, k43, k53, k52, k62, k72, k82, k83,     ka4,      k25,   ur4, \
        ul5,   k00, k14, k24, k34, k44, k45, k55, k54, k64, k74, k85,    k91,       k35, k75,   ur5, \
        ul6,   k06,    k90,    k93,       k94,          k95,     k92, k04,     k03, k73, k05,   ur6 \
    ) \
    { \
        k13, k16, k11, k21, k00, k06, k26, k17, \
        k10, k12, k14, k90, k36, k27, k20, k22, \
        k24, k93, k31, k37, k30, k32, k34, k33, \
        k47, k40, k42, k44, k07, k46, k41, k43, \
        k45, k94, k63, k56, k51, k53, k55, k71, \
        k57, k50, k52, k54, k76, k67, k60, k62, \
        k64, k95, ka6, k77, k70, k72, k74, k92, \
        ka7, k87, k80, k82, k85, ka3, k86, k81, \
        k83, k04, ka5, ul1, ur1, k97, ul2, ur2, \
        k65, ul2, ur2, k15, ul3, ur3, k66, k05, \
        ul3, ur3, k75, ul4, ur4, ka1, k25, ul5, \
        ur5, k61, k91, ul6, ur6, ka2, k35, k03, \
        ka4, k73 \
    }
// clang-format on
typedef uint8_t ledmap[DRIVER_LED_TOTAL][3];
extern const ledmap ledmaps[];

void set_layer_rgb(uint8_t led_min, uint8_t led_max, int layer);

void rgb_matrix_layers_enable(void);
void rgb_matrix_layers_disable(void);

// Just a handy defines to make our ledmaps look better
#    define RED \
        { HSV_RED }
#    define CORAL \
        { HSV_CORAL }
#    define ORANGE \
        { HSV_ORANGE }
#    define GOLDEN \
        { HSV_GOLDENROD }
#    define GOLD \
        { HSV_GOLD }
#    define YELLOW \
        { HSV_YELLOW }
#    define CHART \
        { HSV_CHARTREUSE }
#    define GREEN \
        { HSV_GREEN }
#    define SPRING \
        { HSV_SPRINGGREEN }
#    define TURQ \
        { HSV_TURQUOISE }
#    define TEAL \
        { HSV_TEAL }
#    define CYAN \
        { HSV_CYAN }
#    define AZURE \
        { HSV_AZURE }
#    define BLUE \
        { HSV_BLUE }
#    define PURPLE \
        { HSV_PURPLE }
#    define MAGENT \
        { HSV_MAGENTA }
#    define PINK \
        { HSV_PINK }
#    define BLACK \
        { HSV_BLACK }

#endif  // RGB_MATRIX_LEDMAPS_ENABLED

void rgb_matrix_indicators_keymap(void);
void rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
