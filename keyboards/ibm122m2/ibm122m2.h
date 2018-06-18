/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
#ifndef IBM122M2_H
#define IBM122M2_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, k4I, k4J, \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H, k5I, k5J, \
    k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D, k6E, k6F, k6G, k6H, k6I, k6J, \
    k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A, k7B, k7C, k7D, k7E, k7F, k7G, k7H, k7I, k7J \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, k4I, k4J }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H, k5I, k5J }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D, k6E, k6F, k6G, k6H, k6I, k6J }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A, k7B, k7C, k7D, k7E, k7F, k7G, k7H, k7I, k7J }, \
}

#endif
