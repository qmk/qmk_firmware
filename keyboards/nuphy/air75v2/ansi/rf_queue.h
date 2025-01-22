/*
Copyright 2024 @ jincao1

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

<<<<<<< HEAD:keyboards/nuphy/air75v2/ansi/rf_queue.h
typedef struct {
    uint8_t cmd;
    uint8_t length;
    uint8_t repeat;     // track number of times it's been resent
    uint8_t buffer[16]; // set to max length used
} report_buffer_t;

typedef struct {
    bool (*enqueue)(report_buffer_t *report);
    bool (*dequeue)(report_buffer_t *report);
    bool (*is_empty)(void);
    void (*clear)(void);
} rf_queue_t;
||||||| f156e57f8e:keyboards/work_louder/loop/config.h
#define RGB_MATRIX_DISABLE_KEYCODES

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
=======
#define RGB_MATRIX_DISABLE_SHARED_KEYCODES
>>>>>>> master:keyboards/work_louder/loop/config.h
