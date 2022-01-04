/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#if defined(KEYBOARD_planck_ez)
#    include "ez.h"
#elif defined(KEYBOARD_planck_light)
#    include "light.h"
#elif defined(KEYBOARD_planck_thk)
#    include "thk.h"
#elif defined(KEYBOARD_planck_rev1)
#    include "rev1.h"
#elif defined(KEYBOARD_planck_rev2)
#    include "rev2.h"
#elif defined(KEYBOARD_planck_rev3)
#    include "rev3.h"
#elif defined(KEYBOARD_planck_rev4)
#    include "rev4.h"
#elif defined(KEYBOARD_planck_rev5)
#    include "rev5.h"
#elif defined(KEYBOARD_planck_rev6)
#    include "rev6.h"
#elif defined(KEYBOARD_planck_rev6_drop)
#    include "rev6_drop.h"
#endif  // Planck revisions
