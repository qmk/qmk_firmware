/* Copyright 2021
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

#include <stdint.h>

#ifndef DIGITIZER_USAGE_ID
#    define DIGITIZER_USAGE_ID DIG_DIGITIZER
#endif
#ifndef DIGITIZER_MAX_X
#    define DIGITIZER_MAX_X 0x7FFF
#endif
#ifndef DIGITIZER_MAX_Y
#    define DIGITIZER_MAX_Y 0x7FFF
#endif
#if DIGITIZER_MAX_X > 0x7FFF
#    error "DIGITIZER_MAX_X must not exceed 0x7FFF"
#endif
#if DIGITIZER_MAX_Y > 0x7FFF
#    error "DIGITIZER_MAX_Y must not exceed 0x7FFF"
#endif

// Jitter x/y coords to allow consecutive touches at the same position
#ifdef DIGITIZER_FUZZ
#    define DIGITIZER_FUZZ_INRANGE
#    define DIGITIZER_FUZZ_MOUSE
#endif
#if defined(DIGITIZER_FUZZ_INRANGE) || defined(DIGITIZER_FUZZ_MOUSE)
#    ifndef DIGITIZER_FUZZ_X
#        define DIGITIZER_FUZZ_X 1
#    endif
#    ifndef DIGITIZER_FUZZ_Y
#        define DIGITIZER_FUZZ_Y 1
#    endif
#endif
#ifdef DIGITIZER_FUZZ_MOUSE
#    ifndef DIGITIZER_FUZZ_MOUSE_TIMES
#        define DIGITIZER_FUZZ_MOUSE_TIMES 2
#    endif
#endif
#if defined(DIGITIZER_FUZZ_MOUSE) && !defined(POINTING_DEVICE_ENABLE)
#    error "DIGITIZER_FUZZ_MOUSE requires POINTING_DEVICE_ENABLE = yes"
#endif

// Custom keycodes
#ifndef DIGITIZER_USER0_X
#    define DIGITIZER_USER0_X DIG_REL2ABS_X(0.25)
#endif
#ifndef DIGITIZER_USER0_Y
#    define DIGITIZER_USER0_Y DIG_REL2ABS_Y(0.25)
#endif
#ifndef DIGITIZER_USER1_X
#    define DIGITIZER_USER1_X DIG_REL2ABS_X(0.75)
#endif
#ifndef DIGITIZER_USER1_Y
#    define DIGITIZER_USER1_Y DIG_REL2ABS_Y(0.25)
#endif
#ifndef DIGITIZER_USER2_X
#    define DIGITIZER_USER2_X DIG_REL2ABS_X(0.25)
#endif
#ifndef DIGITIZER_USER2_Y
#    define DIGITIZER_USER2_Y DIG_REL2ABS_Y(0.75)
#endif
#ifndef DIGITIZER_USER3_X
#    define DIGITIZER_USER3_X DIG_REL2ABS_X(0.75)
#endif
#ifndef DIGITIZER_USER3_Y
#    define DIGITIZER_USER3_Y DIG_REL2ABS_Y(0.75)
#endif

#define DIG_BIT(code) (1 << DIG_INDEX(code))
#define DIG_INDEX(code) ((code) - DZ_BUTTON_MIN)
#define DIG_FUZZ_X(x) ((x) <= (DIGITIZER_MAX_X-DIGITIZER_FUZZ_X) ? ((x)+DIGITIZER_FUZZ_X) : ((x)-DIGITIZER_FUZZ_X))
#define DIG_FUZZ_Y(y) ((y) <= (DIGITIZER_MAX_Y-DIGITIZER_FUZZ_Y) ? ((y)+DIGITIZER_FUZZ_Y) : ((y)-DIGITIZER_FUZZ_Y))
#define DIG_REL2ABS_X(xrel) ((uint16_t)((xrel) * DIGITIZER_MAX_X))
#define DIG_REL2ABS_Y(yrel) ((uint16_t)((yrel) * DIGITIZER_MAX_Y))

enum digitizer_usages {
    DIG_DIGITIZER    = 0x01,
    DIG_PEN          = 0x02,
    DIG_LIGHT_PEN    = 0x03,
    DIG_TOUCH_SCREEN = 0x04,
    DIG_TOUCH_PAD    = 0x05,
    DIG_WHITEBOARD   = 0x06
};

enum digitizer_status { DZ_INITIALIZED = 1, DZ_UPDATED = 2 };
enum digitizer_buttons {
    DIG_TIP_PRIMARY      = 0x01,   // usage: 0x42
    DIG_TIP_SECONDARY    = 0x02,   // usage: 0x43
    DIG_BARREL_PRIMARY   = 0x04,   // usage: 0x44
    DIG_BARREL_SECONDARY = 0x08,   // usage: 0x5A
    DIG_TABLET_PICK      = 0x10,   // usage: 0x46
    DIG_INVERT           = 0x20,   // usage: 0x3C
    DIG_ERASER           = 0x40    // usage: 0x45
};

typedef struct {
    bool     inrange;
    uint8_t  buttons : 7;
    uint16_t x;
    uint16_t y;
    uint8_t  status : 2;
} digitizer_t;

extern digitizer_t digitizer;

void digitizer_task(void);

digitizer_t digitizer_get_report(void);
void digitizer_set_report(digitizer_t digitizer);
void host_digitizer_send(digitizer_t *digitizer);
void digitizer_send(void);

void digitizer_register_inrange(void);
void digitizer_unregister_inrange(void);
void digitizer_fuzz_inrange(uint16_t x, uint16_t y);
void digitizer_fuzz_mouse(void);
digitizer_t digitizer_fuzz_xy(uint16_t x, uint16_t y);
