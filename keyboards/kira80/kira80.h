/* Copyright 2020 Lorenz Wellmer
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_all(\
    K000,       K002, K003, K004, K005,    K007, K008, K009, K010,    K011, K012, K013, K001,    K091, K092, K102,  \
    K015, K016, K017, K018, K019, K020, K021, K022, K023, K024, K025, K026, K027, K028, K029,    K096, K095, K094,  \
    K030, K031, K032, K033, K034, K035, K036, K037, K038, K039, K040, K041, K042, K043,          K103, K098, K097,  \
    K045, K046, K047, K048, K049, K050, K051, K052, K053, K054, K055, K056,       K057,                             \
    K060, K058, K061, K062, K063, K064, K065, K066, K067, K068, K069, K070, K071, K072,                K073,        \
    K075, K076, K077,                   K079,                   K083, K084, K085, K086,          K087, K088, K082   \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  KC_NO, K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO }, \
    { K015,  K016,  K017,  K018,  K019,  K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027,  K028,  K029  }, \
    { K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037,  K038,  K039,  K040,  K041,  K042,  K043,  KC_NO }, \
    { K045,  K046,  K047,  K048,  K049,  K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057,  K058,  KC_NO }, \
    { K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067,  K068,  K069,  K070,  K071,  K072,  K073,  KC_NO }, \
    { K075,  K076,  K077,  KC_NO, K079,  KC_NO, KC_NO, K082,  K083,  K084,  K085,  K086,  K087,  K088,  KC_NO }, \
    { KC_NO, K091,  K092,  KC_NO, K094,  K095,  K096,  K097,  K098,  KC_NO, KC_NO, KC_NO, K102,  K103,  KC_NO }  \
}

#define LAYOUT_tkl_ansi(\
    K000,       K002, K003, K004, K005,    K007, K008, K009, K010,    K011, K012, K013, K001,    K091, K092, K102,  \
    K015, K016, K017, K018, K019, K020, K021, K022, K023, K024, K025, K026, K027, K028,          K096, K095, K094,  \
    K030, K031, K032, K033, K034, K035, K036, K037, K038, K039, K040, K041, K042, K043,          K103, K098, K097,  \
    K045, K046, K047, K048, K049, K050, K051, K052, K053, K054, K055, K056,       K057,                             \
    K060,       K061, K062, K063, K064, K065, K066, K067, K068, K069, K070,       K071,                K073,        \
    K075, K076, K077,                   K079,                   K083, K084, K085, K086,          K087, K088, K082   \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  KC_NO, K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO }, \
    { K015,  K016,  K017,  K018,  K019,  K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027,  K028,  KC_NO }, \
    { K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037,  K038,  K039,  K040,  K041,  K042,  K043,  KC_NO }, \
    { K045,  K046,  K047,  K048,  K049,  K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057,  KC_NO, KC_NO }, \
    { K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067,  K068,  K069,  K070,  K071,  KC_NO, K073,  KC_NO }, \
    { K075,  K076,  K077,  KC_NO, K079,  KC_NO, KC_NO, K082,  K083,  K084,  K085,  K086,  K087,  K088,  KC_NO }, \
    { KC_NO, K091,  K092,  KC_NO, K094,  K095,  K096,  K097,  K098,  KC_NO, KC_NO, KC_NO, K102,  K103,  KC_NO }  \
}

#define LAYOUT_tkl_ansi_wkl(\
    K000,       K002, K003, K004, K005,    K007, K008, K009, K010,    K011, K012, K013, K001,    K091, K092, K102,  \
    K015, K016, K017, K018, K019, K020, K021, K022, K023, K024, K025, K026, K027, K028,          K096, K095, K094,  \
    K030, K031, K032, K033, K034, K035, K036, K037, K038, K039, K040, K041, K042, K043,          K103, K098, K097,  \
    K045, K046, K047, K048, K049, K050, K051, K052, K053, K054, K055, K056,       K057,                             \
    K060,       K061, K062, K063, K064, K065, K066, K067, K068, K069, K070,       K071,                K073,        \
    K075,       K077,                   K079,                         K084,       K086,          K087, K088, K082   \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  KC_NO, K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO }, \
    { K015,  K016,  K017,  K018,  K019,  K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027,  K028,  KC_NO }, \
    { K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037,  K038,  K039,  K040,  K041,  K042,  K043,  KC_NO }, \
    { K045,  K046,  K047,  K048,  K049,  K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057,  KC_NO, KC_NO }, \
    { K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067,  K068,  K069,  K070,  K071,  KC_NO, K073,  KC_NO }, \
    { K075,  KC_NO, K077,  KC_NO, K079,  KC_NO, KC_NO, K082,  KC_NO, K084,  KC_NO, K086,  K087,  K088,  KC_NO }, \
    { KC_NO, K091,  K092,  KC_NO, K094,  K095,  K096,  K097,  K098,  KC_NO, KC_NO, KC_NO, K102,  K103,  KC_NO }  \
}

#define LAYOUT_tkl_iso(\
    K000,       K002, K003, K004, K005,    K007, K008, K009, K010,    K011, K012, K013, K001,    K091, K092, K102,  \
    K015, K016, K017, K018, K019, K020, K021, K022, K023, K024, K025, K026, K027, K028,          K096, K095, K094,  \
    K030, K031, K032, K033, K034, K035, K036, K037, K038, K039, K040, K041, K042,                K103, K098, K097,  \
    K045, K046, K047, K048, K049, K050, K051, K052, K053, K054, K055, K056, K043, K057,                             \
    K060, K058, K061, K062, K063, K064, K065, K066, K067, K068, K069, K070,       K071,                K073,        \
    K075, K076, K077,                   K079,                   K083, K084, K085, K086,          K087, K088, K082   \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  KC_NO, K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO }, \
    { K015,  K016,  K017,  K018,  K019,  K020,  K021,  K022,  K023,  K024,  K025,  K026,  K027,  K028,  KC_NO }, \
    { K030,  K031,  K032,  K033,  K034,  K035,  K036,  K037,  K038,  K039,  K040,  K041,  K042,  K043,  KC_NO }, \
    { K045,  K046,  K047,  K048,  K049,  K050,  K051,  K052,  K053,  K054,  K055,  K056,  K057,  K058,  KC_NO }, \
    { K060,  K061,  K062,  K063,  K064,  K065,  K066,  K067,  K068,  K069,  K070,  K071,  KC_NO, K073,  KC_NO }, \
    { K075,  K076,  K077,  KC_NO, K079,  KC_NO, KC_NO, K082,  K083,  K084,  K085,  K086,  K087,  K088,  KC_NO }, \
    { KC_NO, K091,  K092,  KC_NO, K094,  K095,  K096,  K097,  K098,  KC_NO, KC_NO, KC_NO, K102,  K103,  KC_NO }  \
}
