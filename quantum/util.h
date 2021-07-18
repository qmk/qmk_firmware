/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/* GCC ≥ 10 and Clang have __has_builtin() & __has_attribute(); until then… */

#ifndef __has_builtin
#    define __has_builtin(_) 0
#endif

#ifndef __has_attribute
#    define __has_attribute(_) 0
#endif

#if defined(__GNUC__) || __has_attribute(noinline)
#    define Q_NEVER_INLINE __attribute__((noinline))
#else
#    define Q_NEVER_INLINE
#endif

#if defined(__GNUC__) || __has_attribute(always_inline)
#    define Q_ALWAYS_INLINE inline __attribute__((always_inline))
#else
#    define Q_ALWAYS_INLINE inline
#endif

#include "bitwise.h"

// convert to L string
#define LSTR(s) XLSTR(s)
#define XLSTR(s) L## #s
// convert to string
#define STR(s) XSTR(s)
#define XSTR(s) #s
