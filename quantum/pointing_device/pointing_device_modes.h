/* Copyright 2023 Alabastard (@Alabastard-64)
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

// default settings
#ifndef POINTING_TAP_DELAY
#    define POINTING_TAP_DELAY TAP_CODE_DELAY
#endif
#ifndef POINTING_MODE_DEFAULT
#    define POINTING_MODE_DEFAULT PM_NONE
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
#endif

#ifdef POINTING_NUM_DIRECTIONS
#    undefine POINTING_NUM_DIRECTIONS
#endif
#define POINTING_NUM_DIRECTIONS 4

// default divisors
#ifndef POINTING_DEFAULT_DIVISOR
#    define POINTING_DEFAULT_DIVISOR 64
#endif
#ifndef POINTING_HISTORY_DIVISOR
#    define POINTING_HISTORY_DIVISOR 64
#endif
#ifndef POINTING_VOLUME_DIVISOR
#    define POINTING_VOLUME_DIVISOR 64
#endif
#ifndef POINTING_CARET_DIVISOR
#    define POINTING_CARET_DIVISOR 32
#endif
#ifndef POINTING_CARET_DIVISOR_H
#    define POINTING_CARET_DIVISOR_H POINTING_CARET_DIVISOR
#endif
#ifndef POINTING_CARET_DIVISOR_V
#    define POINTING_CARET_DIVISOR_V POINTING_CARET_DIVISOR
#endif
#ifndef POINTING_PRECISION_DIVISOR
#    define POINTING_PRECISION_DIVISOR 2
#endif
#ifndef POINTING_DRAG_DIVISOR
#    define POINTING_DRAG_DIVISOR 4
#endif

// error checking
#if POINTING_DEFAULT_DIVISOR < 1
#    pragma message "DEFAULT_DIVISOR must be 1 or greater"
#    error DEFAULT_DIVISOR less than 1
#endif
#if POINTING_MODES_NUM_DEVICES < 2 && ((defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)) || defined(POINTING_MODES_SINGLE_CONTROL))
#    pragma message "POINTING_MODE_NUM_DEVICES should be at least 2 with SPLIT_POINTING_ENABLE & POINTING_DEVICE_COMBINED or POINTING_MODES_SINGLE_CONTROL defined"
#    error POINTING_MODE_NUM_DEVICES set too low
#endif

/* enums */
enum pointing_device_directions {
    PD_DOWN  = 0, // default value
    PD_UP    = 1,
    PD_LEFT  = 2,
    PD_RIGHT = 3
};

enum pointing_devide_mode_devices {
#ifdef MASTER_RIGHT
    PM_RIGHT_DEVICE = 0,
    PM_LEFT_DEVICE
#else
    PM_LEFT_DEVICE = 0,
    PM_RIGHT_DEVICE
#endif
};

/* local data structures */
typedef struct {
    uint8_t id;
    int16_t x;
    int16_t y;
} pointing_mode_t;

/* ----------Controlling pointing device modes-------------------------------------------------------------------- */
void    set_pointing_mode_id(uint8_t mode_id);    // set current pointing_mode.id to mode_id
void    toggle_pointing_mode_id(uint8_t mode_id); // toggle pointing mode
uint8_t get_pointing_mode_id(void);               // return current pointing_mode.id
uint8_t get_toggled_pointing_mode_id(void);       // return current tg_mode_id
void    pointing_mode_reset(void);                // reset pointing mode to current toggle mode

/* ----------Controlling pointing device data conversion---------------------------------------------------------- */
report_mouse_t pointing_modes_axes_conv(pointing_mode_t pointing_mode, report_mouse_t mouse_report); // converts x & y axes to local h & v

/* ----------Crontrolling pointing mode data---------------------------------------------------------------------- */
void              set_pointing_mode(pointing_mode_t pointing_mode); // overwrite local pointing_mode status
void              pointing_mode_update(void);                       // update direction & divisor from current mode id, x, y
mouse_xy_report_t apply_divisor_xy(int16_t value);                  // divide value by current divisor and clamp to x/y range
int8_t            apply_divisor_hv(int16_t value);                  // divide value by current divisor and clamps to h/v range
int16_t           multiply_divisor_xy(mouse_xy_report_t value);     // multiply mouse x/y value by current divisor
int16_t           multiply_divisor_hv(int8_t value);                // multiply mousen h/v value by current divisor
void              pointing_mode_divisor_override(uint8_t divisor);  // override current divisor
uint8_t           current_pointing_mode_divisor(void);              // return current divisor
uint8_t           current_pointing_mode_direction(void);            // return current direction

/* ----------For Custom modes without maps---------------------------------------------------------------------- */
void pointing_tap_codes(uint16_t kc_left, uint16_t kc_down, uint16_t kc_up, uint16_t kc_right); // pointing_mode x/y to keycode taps

/* ----------Callbacks for modifying and adding pointing modes---------------------------------------------------- */
bool process_pointing_mode_kb(pointing_mode_t pointing_mode, report_mouse_t* mouse_report);   // keyboard level
bool process_pointing_mode_user(pointing_mode_t pointing_mode, report_mouse_t* mouse_report); // user/keymap level

/* ----------Callbacks for adding/modifying pointing device mode divisors----------------------------------------- */
uint8_t get_pointing_mode_divisor_kb(uint8_t mode_id, uint8_t direction);   // adding new divisors at keyboard level
uint8_t get_pointing_mode_divisor_user(uint8_t mode_id, uint8_t direction); // adding new divisors at user/keymap level
bool    pointing_mode_divisor_postprocess_kb(uint8_t* divisor);             // keyboard level modifying of divisors after get_pointing_mode_divisor_* stack
bool    pointing_mode_divisor_postprocess_user(uint8_t* divisor);           // user/keymap level modifying of divisors after get_pointing_mode_divisor_* stack

/* ----------Core functions (only used in custom pointing devices or key processing)------------------------------ */
report_mouse_t pointing_device_modes_task(report_mouse_t mouse_report); // intercepts mouse_report (in pointing_device_task_* stack)

/* ----------Pointing Device mode Mapping------------------------------------------------------------------------- */
#ifdef POINTING_MODE_MAP_ENABLE
#    define POINTING_MODE_LAYOUT(Y_POS, X_NEG, X_POS, Y_NEG) \
        { Y_NEG, Y_POS, X_NEG, X_POS }
#    ifndef POINTING_MODE_MAP_START
#        define POINTING_MODE_MAP_START PM_SAFE_RANGE
#    endif

extern const uint16_t PROGMEM pointing_mode_maps[][POINTING_NUM_DIRECTIONS];

#endif // POINTING_MODE_MAP_ENABLE
/* ----------For multiple pointing devices------------------------------------------------------------------------ */
uint8_t get_pointing_mode_device(void);           // get current active device for pointing modes
void    set_pointing_mode_device(uint8_t device); // set current active pointing mode side (PM_LEFT_SIDE, PM_RIGHT_SIDE, etc.)
