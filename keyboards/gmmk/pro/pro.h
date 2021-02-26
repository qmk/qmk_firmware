/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

#ifndef PRO_H
#define PRO_H

#include "gmmk.h"

#define LAYOUT_gmmk_pro( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, k0i, k0j, k0k, k0l, k0m, k0n,\
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j, k1k, k1l, k1m, k1n,\
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, k2i, k2j, k2k, k2l, k2m, k2n,\
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07}, \
    { k10, k11, k12, k13, k14, k15, k16, k17}, \
    { k20, k21, k22, k23, k24, k25, k26, k27}, \
    { k30, k31, k32, k33, k34, k35, k36, k37}, \
    { k08, k09, k0a, k0b, k0c, k0d, k0e, k0f}, \
    { k18, k19, k1a, k1b, k1c, k1d, k1e, k1f}, \
    { k28, k29, k2a, k2b, k2c, k2d, k2e, k2f}, \
    { k38, k39, k3a, k3b, k3c, k3d, k3e, k3f}, \
    { k0g, k0h, k0i, k0j, k0k, k0l, k0m, k0n}, \
    { k1g, k1h, k1i, k1j, k1k, k1l, k1m, k1n}, \
    { k2g, k2h, k2i, k2j, k2k, k2l, k2m, k2n}  \
}

#define KEYMAP LAYOUT_gmmk_pro

#endif
