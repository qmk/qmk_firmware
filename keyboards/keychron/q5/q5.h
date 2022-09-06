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

#if   defined(KEYBOARD_keychron_q5_rev_0150)
#    include "rev_0150.h"
#elif defined(KEYBOARD_keychron_q5_rev_0151)
#    include "rev_0151.h"
#elif defined(KEYBOARD_keychron_q5_rev_0152)
#    include "rev_0152.h"
#elif defined(KEYBOARD_keychron_q5_rev_0153)
#    include "rev_0153.h"
#endif
