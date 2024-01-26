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

#include <stdbool.h>
#include "print.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Debug output control
 */
typedef union {
    struct {
        bool    enable : 1;
        bool    matrix : 1;
        bool    keyboard : 1;
        bool    mouse : 1;
        uint8_t reserved : 4;
    };
    uint8_t raw;
} debug_config_t;

extern debug_config_t debug_config;

#ifdef __cplusplus
}
#endif

/* for backward compatibility */
#define debug_enable (debug_config.enable)
#define debug_matrix (debug_config.matrix)
#define debug_keyboard (debug_config.keyboard)
#define debug_mouse (debug_config.mouse)

/*
 * Debug print utils
 */
#ifndef NO_DEBUG

#    define dprint(s)                   \
        do {                            \
            if (debug_enable) print(s); \
        } while (0)
#    define dprintln(s)                   \
        do {                              \
            if (debug_enable) println(s); \
        } while (0)
#    define dprintf(fmt, ...)                              \
        do {                                               \
            if (debug_enable) xprintf(fmt, ##__VA_ARGS__); \
        } while (0)
#    define dmsg(s) dprintf("%s at %d: %s\n", __FILE__, __LINE__, s)

#else /* NO_DEBUG */

#    define dprint(s)
#    define dprintln(s)
#    define dprintf(fmt, ...)
#    define dmsg(s)

#endif /* NO_DEBUG */
