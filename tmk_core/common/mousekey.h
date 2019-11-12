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
#    define MOUSEKEY_H
#endif

#include <stdbool.h>
#include "host.h"

#ifndef MK_3_SPEED

/* max value on report descriptor */
#    ifndef MOUSEKEY_MOVE_MAX
#        define MOUSEKEY_MOVE_MAX 127
#    elif MOUSEKEY_MOVE_MAX > 127
#        error MOUSEKEY_MOVE_MAX needs to be smaller than 127
#    endif

#    ifndef MOUSEKEY_WHEEL_MAX
#        define MOUSEKEY_WHEEL_MAX 127
#    elif MOUSEKEY_WHEEL_MAX > 127
#        error MOUSEKEY_WHEEL_MAX needs to be smaller than 127
#    endif

#    ifndef MOUSEKEY_MOVE_DELTA
#        define MOUSEKEY_MOVE_DELTA 1
#    endif
#    ifndef MOUSEKEY_WHEEL_DELTA
#        define MOUSEKEY_WHEEL_DELTA 1
#    endif
#    ifndef MOUSEKEY_XY_INTERVAL
#        define MOUSEKEY_XY_INTERVAL 10
#    endif
#    ifndef MOUSEKEY_XY_DELAY
#        define MOUSEKEY_XY_DELAY 0
#    endif
#    ifndef MOUSEKEY_WH_INTERVAL
#        define MOUSEKEY_WH_INTERVAL 100
#    endif
#    ifndef MOUSEKEY_WH_DELAY
#        define MOUSEKEY_WH_DELAY 50
#    endif
#    ifndef MOUSEKEY_XY_MAX_SPEED
#        define MOUSEKEY_XY_MAX_SPEED 15
#    endif
#    ifndef MOUSEKEY_XY_TIME_TO_MAX
#        define MOUSEKEY_XY_TIME_TO_MAX 15
#    endif
#    ifndef MOUSEKEY_WH_MAX_SPEED
#        define MOUSEKEY_WH_MAX_SPEED 5
#    endif
#    ifndef MOUSEKEY_WH_TIME_TO_MAX
#        define MOUSEKEY_WH_TIME_TO_MAX 30
#    endif

#else /* #ifndef MK_3_SPEED */

#    ifndef MK_C_OFFSET_UNMOD
#        define MK_C_OFFSET_UNMOD 16
#    endif
#    ifndef MK_C_INTERVAL_UNMOD
#        define MK_C_INTERVAL_UNMOD 16
#    endif
#    ifndef MK_C_OFFSET_0
#        define MK_C_OFFSET_0 1
#    endif
#    ifndef MK_C_INTERVAL_0
#        define MK_C_INTERVAL_0 32
#    endif
#    ifndef MK_C_OFFSET_1
#        define MK_C_OFFSET_1 4
#    endif
#    ifndef MK_C_INTERVAL_1
#        define MK_C_INTERVAL_1 16
#    endif
#    ifndef MK_C_OFFSET_2
#        define MK_C_OFFSET_2 32
#    endif
#    ifndef MK_C_INTERVAL_2
#        define MK_C_INTERVAL_2 16
#    endif

#    ifndef MK_W_OFFSET_UNMOD
#        define MK_W_OFFSET_UNMOD 1
#    endif
#    ifndef MK_W_INTERVAL_UNMOD
#        define MK_W_INTERVAL_UNMOD 40
#    endif
#    ifndef MK_W_OFFSET_0
#        define MK_W_OFFSET_0 1
#    endif
#    ifndef MK_W_INTERVAL_0
#        define MK_W_INTERVAL_0 360
#    endif
#    ifndef MK_W_OFFSET_1
#        define MK_W_OFFSET_1 1
#    endif
#    ifndef MK_W_INTERVAL_1
#        define MK_W_INTERVAL_1 120
#    endif
#    ifndef MK_W_OFFSET_2
#        define MK_W_OFFSET_2 1
#    endif
#    ifndef MK_W_INTERVAL_2
#        define MK_W_INTERVAL_2 20
#    endif

#endif /* #ifndef MK_3_SPEED */

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t mk_xy_delay;
extern uint8_t mk_wh_delay;
extern uint8_t mk_xy_interval;
extern uint8_t mk_wh_interval;
extern uint8_t mk_xy_max_speed;
extern uint8_t mk_wh_max_speed;
extern uint8_t mk_xy_time_to_max;
extern uint8_t mk_wh_time_to_max;

void mousekey_task(void);
void mousekey_on(uint8_t code);
void mousekey_off(uint8_t code);
void mousekey_clear(void);
void mousekey_send(void);

#ifdef __cplusplus
}
#endif
