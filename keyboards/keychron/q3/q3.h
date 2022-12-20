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

#if   defined(KEYBOARD_keychron_q3_ansi)
#    include "ansi.h"
#elif defined(KEYBOARD_keychron_q3_ansi_encoder)
#    include "ansi_encoder.h"
#elif defined(KEYBOARD_keychron_q3_iso)
#    include "iso.h"
#elif defined(KEYBOARD_keychron_q3_iso_encoder)
#    include "iso_encoder.h"
#elif defined(KEYBOARD_keychron_q3_jis)
#    include "jis.h"
#elif defined(KEYBOARD_keychron_q3_jis_encoder)
#    include "jis_encoder.h"
#endif
