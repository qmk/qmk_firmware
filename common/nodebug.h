/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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

#ifndef NODEBUG_H
#define NODEBUG_H 1

#include "debug_config.h"

#define dprint(s)
#define dprintln(s)
#define dprintf(fmt, ...)
#define dmsg(s)

#define debug(s)
#define debugln(s)
#define debug_S(s)
#define debug_P(s)
#define debug_msg(s)
#define debug_dec(data)
#define debug_decs(data)
#define debug_hex4(data)
#define debug_hex8(data)
#define debug_hex16(data)
#define debug_hex32(data)
#define debug_bin8(data)
#define debug_bin16(data)
#define debug_bin32(data)
#define debug_bin_reverse8(data)
#define debug_bin_reverse16(data)
#define debug_bin_reverse32(data)
#define debug_hex(data)
#define debug_bin(data)
#define debug_bin_reverse(data)

#endif
