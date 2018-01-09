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

#ifndef MOUSEKEY_H
#define MOUSEKEY_H
#endif

#include <stdbool.h>
#include "host.h"

#ifndef MK_C_OFFSET_SLOW
#define MK_C_OFFSET_SLOW 1
#endif
#ifndef MK_C_INTERVAL_SLOW
#define MK_C_INTERVAL_SLOW 100
#endif
#ifndef MK_C_OFFSET_MED
#define MK_C_OFFSET_MED 4
#endif
#ifndef MK_C_INTERVAL_MED
#define MK_C_INTERVAL_MED 16
#endif
#ifndef MK_C_OFFSET_FAST
#define MK_C_OFFSET_FAST 12
#endif
#ifndef MK_C_INTERVAL_FAST
#define MK_C_INTERVAL_FAST 16
#endif

#ifndef MK_W_OFFSET_SLOW
#define MK_W_OFFSET_SLOW 1
#endif
#ifndef MK_W_INTERVAL_SLOW
#define MK_W_INTERVAL_SLOW 400
#endif
#ifndef MK_W_OFFSET_MED
#define MK_W_OFFSET_MED 1
#endif
#ifndef MK_W_INTERVAL_MED
#define MK_W_INTERVAL_MED 200
#endif
#ifndef MK_W_OFFSET_FAST
#define MK_W_OFFSET_FAST 1
#endif
#ifndef MK_W_INTERVAL_FAST
#define MK_W_INTERVAL_FAST 100
#endif

#ifdef __cplusplus
extern "C" {
#endif

void mousekey_task(void);
void mousekey_on(uint8_t code);
void mousekey_off(uint8_t code);
void mousekey_clear(void);
void mousekey_send(void);

#ifdef __cplusplus
}
#endif
