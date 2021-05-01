/**
  * dp60.h
  *
  Copyright 2020 astro <yuleiz@gmail.com>
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

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
    // Matrix layout to accomodate all layouts. Good for VIA mapping correctly, and it doesnt exist yet
    //
    //┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐  ┌──────┐
    //│0A││0B││0C││0D││0E││0F││0G││4H││0H││0I││0J││0K││0L││0M││0N│  │  0N  │      split backspace support
    //└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘  └──────┘
    // 00  01  02  03  04  05  06  07  08  09  0a  0b  0c  0d  0e      0e
    //┌────┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌────┐    ┌────┐
    //│1A  ││1B││1C││1D││1E││1F││1G││1H││1I││1J││1K││1L││1M││1N  │    │    │      iso enter - see below
    //└────┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└────┘    └────┘
    //  10   11  12  13  14  15  16  17  18  19  1a  1b  1c   1e
    //┌─────┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌───────┐  ┌──┐┌──┐
    //│ 2A  ││2B││2C││2D││2E││2F││2G││2H││2I││2J││2K││2L││  2N   │  │2M││2N│      iso enter
    //└─────┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└───────┘  └──┘└──┘
    // 20     22  23  24  25  26  27  28  29  2a  2b  2c    2e       2d  2e
    //┌───────┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌─────────┐
    //│3A │ 3B││3C││3D││3E││3F││3G││3H││3I││3J││3K││3L││  3M  │3N│                split shifts (left and right)
    //└───────┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└─────────┘
    // 30   31  32  33  34  35  36  37  38  39  3a  3b    3c   3d
    //┌───┐┌───┐┌───┐┌───────────────────────┐┌───┐┌───┐┌───┐┌───┐
    //│4A ││4B ││4C ││         4G            ││4K ││4L ││4M ││4N │                wkl/hhkb use 4L (k49), 4M (k4a) , 4N (k4b)
    //└───┘└───┘└───┘└───────────────────────┘└───┘└───┘└───┘└───┘
    // 40   42   43            47              48   49   4a   4b
    //end of mapping
//
//added k0d
//added k2d KC_NUMS for iso
//added k31 split l-shift, k3d split r-shift

#define LAYOUT_all( \
  k00,  k01,  k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
k10,    k11,  k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, \
k20,          k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, \
k30,    k31,  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
k40,          k42, k43,                k47, k48, k49, k4a, k4b       \
) \
{ \
  {k00,   k01,  k02, k03,   k04,   k05,   k06,                          k08, k09, k0a, k0b, k0c, k0d, k0e}, \
  {k10,   k11,  k12, k13,   k14,   k15,   k16, k17,                     k18, k19, k1a, k1b, k1c,      k1e}, \
  {k20,         k22, k23,   k24,   k25,   k26, k27,                     k28, k29, k2a, k2b, k2c, k2d, k2e}, \
  {k30,   k31,  k32, k33,   k34,   k35,   k36, k37,                     k38, k39, k3a, k3b, k3c, k3d}, \
  {k40,         k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO,  k48, k49, k4a, k4b}  \
}

#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
	k40,      k42, k43,                k47, k48, k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c, KC_NO, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, KC_NO}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, k48, k49,   k4a, k4b}  \
}

#define LAYOUT_60_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
	k40,      k42, k43,                k47, k48, k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c, KC_NO, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, KC_NO}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c,   k2d, k2e}, \
    {k30,   k31, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, KC_NO}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, k48, k49,   k4a, k4b}  \
}

#define LAYOUT_60_wkl( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
	k40,      k42, k43,                k47,      k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a,   k0b, k0c, KC_NO, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19,   k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a,   k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39,   k3a, k3b,   k3c, k3d}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, KC_NO, k49,   k4a, k4b}  \
}

#define LAYOUT_60_hhkb( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
       k42, k43,                     k47,                k49, k4a \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c,   k0d, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, k3d}, \
    {KC_NO, k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, KC_NO, k49,   k4a, KC_NO}  \
}
#define LAYOUT_60_wkl_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
	k40,      k42, k43,                k47,      k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a,   k0b, k0c,   k0d, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19,   k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a,   k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39,   k3a, k3b,   k3c, k3d}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, KC_NO, k49,   k4a, k4b}  \
}
#define LAYOUT_60_ansi_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
	k40,      k42, k43,                k47,      k48,  k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c,   k0d, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, k3d}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, k48, k49,   k4a, k4b}  \
}
