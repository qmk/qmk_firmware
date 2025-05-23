/* Copyright 2025 Alabastard (@Alabastard-64)
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

#include <string.h>
#include "quantum.h"
#include "pointing_device.h"

/* ----------Default Settings------------------------------------------------------------------------------------- */
#ifndef POINTING_MODES_DEFAULT_MODE
#    define POINTING_MODES_DEFAULT_MODE PM_NONE
#endif

#ifndef POINTING_MODES_MAP_START
#    define POINTING_MODES_MAP_START PM_SAFE_RANGE
#endif

#ifndef POINTING_MODES_TAP_DELAY
#    define POINTING_MODES_TAP_DELAY TAP_CODE_DELAY
#endif

#ifndef POINTING_MODES_HOLD_DECAY_RATE
#    define POINTING_MODES_HOLD_DECAY_RATE 2
#endif

#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
#    ifndef POINTING_MODES_NUM_DEVICES
#        define POINTING_MODES_NUM_DEVICES 2
#    endif
#else
#    ifndef POINTING_MODES_NUM_DEVICES
#        define POINTING_MODES_NUM_DEVICES 1
#    endif
#endif

#ifdef POINTING_MODES_SINGLE_CONTROL
#    define POINTING_MODES_DEVICE_CONTROL_COUNT 1
#else
#    define POINTING_MODES_DEVICE_CONTROL_COUNT POINTING_MODES_NUM_DEVICES
#endif

#ifndef POINTING_MODES_DEFAULT_DEVICE
#    define POINTING_MODES_DEFAULT_DEVICE 0
#endif // POINTING_MODES_DEFAULT_DEVICE

#ifdef POINTING_MODES_NUM_DIRECTIONS
#    undef POINTING_MODES_NUM_DIRECTIONS
#endif
#ifdef POINTING_MODES_8WAY_MAP_ENABLE
#    define POINTING_MODES_NUM_DIRECTIONS 8
#else
#    define POINTING_MODES_NUM_DIRECTIONS 4
#endif // POINTING_MODES_8WAY_MAP_ENABLE

#ifndef POINTING_MODES_THRESHOLD
#    define POINTING_MODES_THRESHOLD 0
#endif

/* ----------Default Divisors and Precision Settings-------------------------------------------------------------- */
#ifndef POINTING_MODES_DEFAULT_DIVISOR
#    define POINTING_MODES_DEFAULT_DIVISOR 32
#endif
#ifndef POINTING_MODES_PRECISION_MIN
#    define POINTING_MODES_PRECISION_MIN 1
#endif
#ifndef POINTING_MODES_PRECISION_MAX
#    define POINTING_MODES_PRECISION_MAX 4
#endif
#ifndef POINTING_MODES_PRECISION_STEP
#    define POINTING_MODES_PRECISION_STEP 2
#endif
#ifndef POINTING_MODES_DRAG_DIVISOR
#    define POINTING_MODES_DRAG_DIVISOR 4
#endif

/* ----------Error Checking -------------------------------------------------------------------------------------- */
_Static_assert((POINTING_MODES_DEFAULT_DIVISOR > MOUSE_REPORT_XY_MIN && POINTING_MODES_DEFAULT_DIVISOR <= MOUSE_REPORT_XY_MAX), "POINTING_MODES_DEFAULT_DIVISOR (" STR(POINTING_MODES_DEFAULT_DIVISOR) ") must be greater than " STR(MOUSE_REPORT_XY_MIN) " and less than or equal to " STR(MOUSE_REPORT_XY_MAX));
_Static_assert((POINTING_MODES_DRAG_DIVISOR > MOUSE_REPORT_XY_MIN && POINTING_MODES_DRAG_DIVISOR <= MOUSE_REPORT_XY_MAX), "POINTING_MODES_DRAG_DIVISOR (" STR(POINTING_MODES_DRAG_DIVISOR) ") must be greater than " STR(MOUSE_REPORT_XY_MIN) " and less than or equal to " STR(MOUSE_REPORT_XY_MAX));
_Static_assert((POINTING_MODES_PRECISION_MIN > MOUSE_REPORT_XY_MIN && POINTING_MODES_PRECISION_MIN <= MOUSE_REPORT_XY_MAX), "POINTING_MODES_PRECISION_MIN (" STR(POINTING_MODES_PRECISION_MIN) ") must be greater than " STR(MOUSE_REPORT_XY_MIN) " and less than or equal to " STR(MOUSE_REPORT_XY_MAX));
_Static_assert((POINTING_MODES_PRECISION_MAX > MOUSE_REPORT_XY_MIN && POINTING_MODES_PRECISION_MAX <= MOUSE_REPORT_XY_MAX), "POINTING_MODES_PRECISION_MAX (" STR(POINTING_MODES_PRECISION_MAX) ") must be greater than " STR(MOUSE_REPORT_XY_MIN) " and less than or equal to " STR(MOUSE_REPORT_XY_MAX));
_Static_assert((POINTING_MODES_PRECISION_STEP > MOUSE_REPORT_XY_MIN && POINTING_MODES_PRECISION_STEP <= MOUSE_REPORT_XY_MAX), "POINTING_MODES_PRECISION_STEP (" STR(POINTING_MODES_PRECISION_STEP) ") must be greater than " STR(MOUSE_REPORT_XY_MIN) " and less than or equal to " STR(MOUSE_REPORT_XY_MAX));

_Static_assert(POINTING_MODES_NUM_DEVICES > 0, "POINTING_MODES_NUM_DEVICES must be at least 1");

#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED) || defined(POINTING_MODES_SINGLE_CONTROL)
_Static_assert(POINTING_MODES_NUM_DEVICES > 1, "POINTING_MODES_NUM_DEVICES must be at least 2 with SPLIT_POINTING_ENABLE & POINTING_DEVICE_COMBINED or POINTING_MODES_SINGLE_CONTROL defined");
#endif

/* ----------Macros----------------------------------------------------------------------------------------------- */
#define member_size(t, m) (sizeof(((t*)0)->m))

/* ----------Enums------------------------------------------------------------------------------------------------ */
enum pointing_modes_axis {
    PM_X_AXIS = 0x00,
    PM_Y_AXIS = 0x01,
    PM_H_AXIS,
    PM_V_AXIS,
    PM_X_KEY,
    PM_Y_KEY,
    PM_XY_KEY,
};

enum pointing_modes_directions {
    PMD_NONE  = 0x00, // [0000] 00
    PMD_DOWN  = 0x01, // [0001] 01
    PMD_UP    = 0x02, // [0010] 02
    PMD_LEFT  = 0x04, // [0100] 04
    PMD_RIGHT = 0x08, // [1000] 08
    PMD_VERT  = 0x03, // [0011] 03
    PMD_HORI  = 0x0C, // [1100] 12
    PMD_DNLT  = 0x05, // [0101] 05
    PMD_UPLT  = 0x06, // [0110] 06
    PMD_DNRT  = 0x09, // [1001] 09
    PMD_UPRT  = 0x0A, // [1010] 10
};

#ifdef POINTING_MODES_8WAY_MAP_ENABLE
enum pointing_modes_8_key_map {
    PMK_UPLEFT    = 0x00,
    PMK_UP        = 0x01,
    PMK_UPRIGHT   = 0x02,
    PMK_LEFT      = 0x03,
    PMK_RIGHT     = 0x04,
    PMK_DOWNLEFT  = 0x05,
    PMK_DOWN      = 0x06,
    PMK_DOWNRIGHT = 0x07,
    PMK_NONE      = 0x08,
};

#else
enum pointing_modes_4_key_map {
    PMK_UP    = 0x00,
    PMK_LEFT  = 0x01,
    PMK_RIGHT = 0x02,
    PMK_DOWN  = 0x03,
    PMK_NONE  = 0x08,
    // to ensure all codess are always defined
    PMK_UPLEFT    = 0x04, // unused
    PMK_UPRIGHT   = 0x05, // unused
    PMK_DOWNLEFT  = 0x06, // unused
    PMK_DOWNRIGHT = 0x07, // unused
};
#endif // POINTING_MODES_8WAY_MAP_ENABLE

enum pointing_modes_types {
    PMT_4WAY  = 0x00, // [00000000] (DEFAULT)
    PMT_HORI  = 0x01, // [00000001]
    PMT_VERT  = 0x02, // [00000010]
    PMT_8WAY  = 0x03, // [00000011]
    PMT_DPAD  = 0x04, // [00000100]
    PMT_MODES = 0x0F, // [00001111] (MAX)
    // Options
    PMO_TAP  = 0x00, // [00000000] (DEFAULT)
    PMO_HOLD = 0x10, // [00010000]
    PMO_XINV = 0x20, // [00100000]
    PMO_YINV = 0x40, // [01000000]
    PMO_OPTS = 0xF0, // [11110000]
};

enum pointing_modes_devices {
#ifdef MASTER_RIGHT
    PM_RIGHT_DEVICE = 0,
    PM_LEFT_DEVICE,
#else
    PM_LEFT_DEVICE = 0,
    PM_RIGHT_DEVICE,
#endif
};

/* ----------Local Data Structures-------------------------------------------------------------------------------- */
typedef struct {
    mouse_xy_report_t x;
    mouse_xy_report_t y;
} pointing_modes_residuals_t;

typedef struct {
    uint8_t v;
    uint8_t h;
} pointing_modes_held_keys_t;

typedef struct {
    union {
        uint8_t raw;
#ifdef POINTING_MODES_8WAY_MAP_ENABLE
        struct {
            uint8_t map_id : 5;
            uint8_t dir : 3;
        };
#else
        struct {
            uint8_t map_id : 6;
            uint8_t dir : 2;
        };
#endif // POINTING_MODES_8WAY_MAP_ENABLE
    };
} pointing_modes_map_location_t;

/* ----------Controlling active device pointing mode-------------------------------------------------------------- */
void                       pointing_modes_set_precision(mouse_xy_report_t precision);          // set active device precision divisor
void                       pointing_modes_set_mode(uint8_t mode_id);                           // set active device mode to mode_id
void                       pointing_modes_set_residuals(pointing_modes_residuals_t residuals); // set active device residuals values
void                       pointing_modes_toggle_mode(uint8_t mode_id);                        // set toggle mode to mode_id or default if toggle_id==mode_id
mouse_xy_report_t          pointing_modes_get_precision(void);                                 // get active device precision
uint8_t                    pointing_modes_get_mode(void);                                      // return active device mode_id
uint8_t                    pointing_modes_get_toggled_mode(void);                              // return active device toggle_id
pointing_modes_residuals_t pointing_modes_get_residuals(void);                                 // return current residual values for active device
void                       pointing_modes_reset(void);                                         // reset active device to base settings

/* ----------Crontrolling pointing mode data---------------------------------------------------------------------- */
void              pointing_modes_update(void);                // update direction & divisor from current mode id, x, y
mouse_xy_report_t pointing_modes_apply_divisor(uint8_t axis); // return quotient from applying divisor & precision based on axis and update the residuals
mouse_xy_report_t pointing_modes_get_divisor(void);           // access current divisor value
uint8_t           pointing_modes_get_direction(void);         // access current direction value
uint8_t           pointing_modes_get_type(void);              // access current mode type

/* ----------For Modifying and custom modes outside of maps------------------------------------------------------- */
bool pointing_modes_task_kb(report_mouse_t* mouse_report, pointing_modes_residuals_t* residuals);   // keyboard level
bool pointing_modes_task_user(report_mouse_t* mouse_report, pointing_modes_residuals_t* residuals); // user/keymap level

/* ----------Callbacks for modifying pointing mode settings------------------------------------------------------- */
uint8_t           pointing_modes_get_type_kb(uint8_t mode_id);                         // setting mode type at keyboard level
uint8_t           pointing_modes_get_type_user(uint8_t mode_id);                       // setting mode type at user level
mouse_xy_report_t pointing_modes_get_divisor_kb(uint8_t mode_id, uint8_t direction);   // setting divisors at keyboard level
mouse_xy_report_t pointing_modes_get_divisor_user(uint8_t mode_id, uint8_t direction); // setting divisors at user/keymap level

/* ----------Core functions (only used in custom pointing devices or key processing)------------------------------ */
report_mouse_t pointing_modes_device_task(report_mouse_t mouse_report); // intercepts mouse_report (in pointing_device_task_* stack)

/* ----------For multiple pointing devices------------------------------------------------------------------------ */
uint8_t pointing_modes_get_active_device(void);              // get active device id
void    pointing_modes_set_active_device(uint8_t device_id); // set active device (PM_LEFT_SIDE, PM_RIGHT_SIDE, etc.)
