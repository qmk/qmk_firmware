/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

/**************************************************
** Include headers specific to keyboard revision **
**************************************************/
#if defined(KEYBOARD_preonic_rev1)
#    include "rev1.h"
#elif defined(KEYBOARD_preonic_rev2)
#    include "rev2.h"
#elif defined(KEYBOARD_preonic_rev3)
#    include "rev3.h"
#elif defined(KEYBOARD_preonic_rev3_drop)
#    include "rev3_drop.h"
#endif


/**************************************************
** Layout macros aliases common to all revisions **
**                                               **
**      Name of Alias     Matrix Name:           **
******* ----------------- ------------------- ****/
#define LAYOUT_preonic_grid LAYOUT_ortho_5x12
