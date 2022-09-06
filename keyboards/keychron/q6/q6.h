/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

#if   defined(KEYBOARD_keychron_q6_rev_0160)
#    include "rev_0160.h"
#elif defined(KEYBOARD_keychron_q6_rev_0161)
#    include "rev_0161.h"
#elif defined(KEYBOARD_keychron_q6_rev_0162)
#    include "rev_0162.h"
#elif defined(KEYBOARD_keychron_q6_rev_0163)
#    include "rev_0163.h"
#endif
