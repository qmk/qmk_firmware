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

#pragma once

#include "quantum.h"

#if defined(KEYBOARD_gmmk_pro_rev1_ansi)
#    include "rev1/ansi/ansi.h"
#elif defined(KEYBOARD_gmmk_pro_rev1_iso)
#    include "rev1/iso/iso.h"
#elif defined(KEYBOARD_gmmk_pro_rev2_ansi)
#    include "rev2/ansi/ansi.h"
#elif defined(KEYBOARD_gmmk_pro_rev2_iso)
#    include "rev2/iso/iso.h"
#endif  // GMMK Pro revisions
