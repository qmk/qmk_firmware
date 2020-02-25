/* Copyright 2020 Holten Campbell
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

#include "quantum.h"

#define LAYOUT( \
    K040, K050, K041, K051, K042, K052,   K043, K053, K044, K054, K045, K055,     K046, K056, K047, K057, K048, K058, \
    K030, K060, K031, K061, K032, K062,   K033, K063, K034, K064, K035, K065,     K036, K066, K037, K067, K038, K068, K039, \
    K020, K070, K021, K071, K022, K072,   K023, K073, K024, K074, K025, K075,     K026, K076, K027, K077, K028,       K029, \
    K010, K080, K011, K081, K012, K082,   K013, K083, K014, K084, K015, K085,     K016, K086, K017, K087, K018, K088, K019, \
    K000, K090, K001, K091, K002, K092,   K003, K093,       K004,       K095,     K006,       K097,             K098, K009 \
) { \
    { K000,  K001,  K002,  K003,  K004,  KC_NO, K006,  KC_NO, KC_NO, K009 }, \
    { K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018,  K019 }, \
    { K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027,  K028,  K029 }, \
    { K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037,  K038,  K039 }, \
    { K040,  K041,  K042,  K043,  K044,  K045,  K046,  K047,  K048,  KC_NO }, \
    { K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057,  K058,  KC_NO }, \
    { K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067,  K068,  KC_NO }, \
    { K070,  K071,  K072,  K073,  K074,  K075,  K076,  K077,  KC_NO, KC_NO }, \
    { K080,  K081,  K082,  K083,  K084,  K085,  K086,  K087,  K088,  KC_NO }, \
    { K090,  K091,  K092,  K093,  KC_NO, K095,  KC_NO, K097,  K098,  KC_NO }  \
}
