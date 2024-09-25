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
#ifndef POINTING_MODE_TAP_DELAY
#    define POINTING_MODE_TAP_DELAY TAP_CODE_DELAY
#endif
#ifndef POINTING_MODE_DEFAULT_MODE
#    define POINTING_MODE_DEFAULT_MODE PM_NONE
#endif

#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
#    ifndef POINTING_MODE_NUM_DEVICES
#        define POINTING_MODE_NUM_DEVICES 2
#    endif
#else
#    ifndef POINTING_MODE_NUM_DEVICES
#        define POINTING_MODE_NUM_DEVICES 1
#    endif
#endif
#ifdef POINTING_MODE_SINGLE_CONTROL
#    define POINTING_MODE_DEVICE_CONTROL_COUNT 1
#else
#    define POINTING_MODE_DEVICE_CONTROL_COUNT POINTING_MODE_NUM_DEVICES
#endif

#ifndef POINTING_MODE_DEFAULT_DEVICE
#    define POINTING_MODE_DEFAULT_DEVICE 0
#endif

#ifdef POINTING_MODE_NUM_DIRECTIONS
#    undefine POINTING_MODE_NUM_DIRECTIONS
#endif
#define POINTING_MODE_NUM_DIRECTIONS 4

#ifndef POINTING_MODE_THRESHOLD
#    define POINTING_MODE_THRESHOLD 0
#endif

// default divisors
#ifndef POINTING_MODE_DEFAULT_DIVISOR
#    define POINTING_MODE_DEFAULT_DIVISOR 64
#endif
#ifndef POINTING_MODE_PRECISION_MAX
#    define POINTING_MODE_PRECISION_MAX 4
#endif
#ifndef POINTING_MODE_PRECISION_STEP
#    define POINTING_MODE_PRECISION_STEP 2
#endif
#ifndef POINTING_MODE_DRAG_DIVISOR
#    define POINTING_MODE_DRAG_DIVISOR 4
#endif

// error checking
#if POINTING_MODE_DEFAULT_DIVISOR < 1
#    pragma message "POINTING_MODE_DEFAULT_DIVISOR must be 1 or greater"
#    error DEFAULT_DIVISOR less than 1
#endif
#if POINTING_MODE_PRECISION_MIN < 1
#    pragma message "POINTING_MODE_PRECISION_MIN must be 1 or greater"
#    error DEFAULT_DIVISOR less than 1
#endif
#if POINTING_MODE_NUM_DEVICES < 2 && ((defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)) || defined(POINTING_MODE_SINGLE_CONTROL))
#    pragma message "POINTING_MODE_NUM_DEVICES should be at least 2 with SPLIT_POINTING_ENABLE & POINTING_DEVICE_COMBINED or POINTING_MODE_SINGLE_CONTROL defined"
#    error POINTING_MODE_NUM_DEVICES set too low
#endif

/* enums */
enum pointing_mode_directions {
    PMD_NONE  = 0x00, // [0000]
    PMD_DOWN  = 0x01, // [0001]
    PMD_UP    = 0x02, // [0010]
    PMD_LEFT  = 0x04, // [0100]
    PMD_RIGHT = 0x08, // [1000]
    PMD_VERT  = 0x03, // [0011]
    PMD_HORI  = 0x0C // [1100]
    //PMD_DNLT  = 0x05, // [0101]
    //PMD_UPLT  = 0x06, // [0110]
    //PMD_DNRT  = 0x09, // [1001]
    //PMD_UPRT  = 0x0A  // [1010]
};

enum pointing_mode_4_key_directions {
    PMK_UP    = 0,
    PMK_LEFT  = 1,
    PMK_RIGHT = 2,
    PMK_DOWN  = 3
};

enum pointing_mode_types {
    PMT_4WAY  = 0x00,
    PMT_DPAD  = 0x01,
    PMT_MODES = 0x0F,
    PMT_TAP   = 0x00,
    PMT_HOLD  = 0x10,
    PMT_OPTS  = 0xF0
};

enum pointing_mode_devices {
#ifdef MASTER_RIGHT
    PM_RIGHT_DEVICE = 0,
    PM_LEFT_DEVICE
#else
    PM_LEFT_DEVICE = 0,
    PM_RIGHT_DEVICE
#endif
};

/* local pointing device data structures */
typedef struct {
    uint8_t precision;
    uint8_t toggle_id;
    uint8_t mode_id;
    mouse_xy_report_t x;
    mouse_xy_report_t y;
    uint16_t held_key[2];
} pointing_mode_device_t;

/* ----------Controlling active device pointing mode-------------------------------------------------------------- */
void    pointing_mode_set_precision(uint8_t precision); // set active device precision divisor
void    pointing_mode_set_mode(uint8_t mode_id);        // set active device mode to mode_id
void    pointing_mode_toggle_mode(uint8_t mode_id);     // set toggle mode to mode_id or default if toggle_id==mode_id
uint8_t pointing_mode_get_precision(void);              // get active device precision
uint8_t pointing_mode_get_mode(void);                   // return active device mode_id
uint8_t pointing_mode_get_toggled_mode(void);           // return active device toggle_id
void    pointing_mode_reset(void);                      // reset active device to current base settings

/* ----------Crontrolling pointing mode data---------------------------------------------------------------------- */
// Justify all the functions in this category
void              pointing_mode_update(void);                       // update direction & divisor from current mode id, x, y
mouse_xy_report_t apply_divisor_xy(int16_t value);                  // divide value by current divisor and clamp to x/y range
int8_t            apply_divisor_hv(int16_t value);                  // divide value by current divisor and clamps to h/v range
int16_t           multiply_divisor_xy(mouse_xy_report_t value);     // multiply mouse x/y value by current divisor
int16_t           multiply_divisor_hv(int8_t value);                // multiply mouse h/v value by current divisors
uint8_t           current_pointing_mode_divisor(void);              // access current divisor value
uint8_t           current_pointing_mode_direction(void);            // access current direction value

/* ----------For Custom modes without maps---------------------------------------------------------------------- */
void pointing_tap_codes(uint16_t kc_left, uint16_t kc_down, uint16_t kc_up, uint16_t kc_right); // pointing_mode x/y to keycode taps

/* ----------Callbacks for modifying and adding pointing modes---------------------------------------------------- */
bool process_pointing_mode_kb(pointing_mode_t pointing_mode, report_mouse_t* mouse_report);   // keyboard level
bool process_pointing_mode_user(pointing_mode_t pointing_mode, report_mouse_t* mouse_report); // user/keymap level
uint8_t get_pointing_mode_type_kb(uint8_t mode_id);                                           // setting mode type at keyboard level
uint8_t get_pointing_mode_type_user(uint8_t mode_id);                                         // setting mode type at user level
uint8_t get_pointing_mode_divisor_kb(uint8_t mode_id, uint8_t direction);                     // setting divisors at keyboard level
uint8_t get_pointing_mode_divisor_user(uint8_t mode_id, uint8_t direction);                   // setting divisors at user/keymap level

/* ----------Core functions (only used in custom pointing devices or key processing)------------------------------ */
void           pointing_mode_set_device_settings(pointing_mode_device_t device); // set active device settings
report_mouse_t pointing_device_modes_task(report_mouse_t mouse_report); // intercepts mouse_report (in pointing_device_task_* stack)

/* ----------Pointing Device mode Mapping------------------------------------------------------------------------- */
#ifdef POINTING_MODE_MAP_ENABLE
#    define POINTING_MODE_LAYOUT(Y_POS, X_NEG, X_POS, Y_NEG) \
        { Y_NEG, Y_POS, X_NEG, X_POS }
#    ifndef POINTING_MODE_MAP_START
#        define POINTING_MODE_MAP_START PM_SAFE_RANGE
#    endif

extern const uint16_t PROGMEM pointing_mode_maps[][POINTING_MODE_NUM_DIRECTIONS];

#endif // POINTING_MODE_MAP_ENABLE
/* ----------For multiple pointing devices------------------------------------------------------------------------ */
pointing_mode_device_t pointing_mode_get_device_settings(uint8_t device_id) // access device status
uint8_t                pointing_mode_get_active_device(void);            // get active device id
void                   pointing_mode_set_active_device(uint8_t device_id);  // set active device (PM_LEFT_SIDE, PM_RIGHT_SIDE, etc.)
