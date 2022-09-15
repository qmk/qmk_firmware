/*
Copyright 2021-2022 Rocco Meli <@RMeli>

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

#ifndef RMELI
#define RMELI

#include "global_config.h"

#include "keyrecords/wrappers.h"

#ifdef UNICODEMAP_ENABLE
#    include "keyrecords/unicode.h"
#endif

#ifdef OLED_ENABLE
#    include "oled/oled.h"
#endif

#ifdef TAP_DANCE_ENABLE
#    include "keyrecords/tap_dances.h"
#endif

#endif // RMELI