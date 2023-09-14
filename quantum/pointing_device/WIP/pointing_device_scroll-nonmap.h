/* Copyright 2022 Alabastard
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

/* Sanity check */
#if !defined(POINTING_DEVICE_SCROLL_ENABLE) || !defined(POINTING_DEVICE_ENABLE)
#    error "POINTING_DEVICE_SCROLL_ENABLE or POINTING_DEVICE_ENABLE not defined! check config.h settings!"
#endif

/* default settings */
#ifndef SCROLL_TAP_DELAY
#    define SCROLL_TAP_DELAY 0
#endif
#ifndef SCROLL_MODE_DEFAULT
#    define SCROLL_MODE_DEFAULT 0
#endif
#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
#    if defined(SCROLL_MODE_LEFT)
#        define SCROLL_LEFT_SIDE_DEFAULT true
#    else
#        define SCROLL_LEFT_SIDE_DEFAULT false
#    endif
#endif

/* default divisors */
#ifndef SCROLL_DRAG_DIVISOR
#    define SCROLL_DRAG_DIVISOR 16
#endif
#ifndef SCROLL_CARET_DIVISOR
#    define SCROLL_CARET_DIVISOR 32
#endif
#ifndef SCROLL_VOL_DIVISOR
#    define SCROLL_VOL_DIVISOR 32
#endif

#if SCROLL_DRAG_DIVISOR == 0 || SCROLL_CARET_DIVISOR == 0 || SCROLL_VOL_DIVISOR == 0
#    error "One or more scroll mode divisors set to zero!"
#endif

/* local data structure */
/* scroll record structure for passing user/keyboard scroll modes */
typedef struct {
    uint8_t mode;
    int16_t h;
    int16_t v;
} scroll_status_t;

typedef struct {
    struct {
#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
        bool is_left;
#endif
        uint8_t tg_mode;
    } config;
    scroll_status_t status;
} scroll_context_t;

/* ----------Controlling scroll modes----------------------------------------------------------------------------- */
void    set_scroll_mode(uint8_t scroll_mode);    // set scroll mode to scroll_mode ID
uint8_t get_scroll_mode(void);                   // returns active scroll mode ID
void    scroll_mode_toggle(uint8_t scroll_mode); // toggle scroll mode
uint8_t get_scroll_mode_toggle(void);            // get toggle scroll mode index

/* ----------Controlling scroll/mouse data------------------------------------------------------------------------ */
void           set_scroll_status(scroll_status_t scroll_status);                              // set scroll mode and axes to scroll_status
report_mouse_t scroll_conversion(scroll_status_t scroll_status, report_mouse_t mouse_report); // (overwritable) converts x & y axes to local h & v

/* ----------Setting up scroll mode keyrecords-------------------------------------------------------------------- */
void scroll_key_momentary(uint8_t scroll_mode, keyrecord_t* record); // momentary change of scroll mode while button is held
void scroll_key_toggle(uint8_t scroll_mode, keyrecord_t* record);    // toggles scroll mode on/off on keypress

/* ----------For custom scrolling modes--------------------------------------------------------------------------- */
// turn h/v axis values into key taps
void scroll_tap_codes(uint16_t st_kc_left, uint16_t st_kc_down, uint16_t st_kc_up, uint16_t st_kc_right, uint8_t divisor);

/* ----------For multiple pointing devices------------------------------------------------------------------------ */
#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
bool is_scroll_mode_left(void);      // check if left is current active scroll mode side
void scroll_mode_switch_hands(void); // change witch hand is active on scroll mode
#endif

/* ----------Callbacks for modifying and adding scroll modes------------------------------------------------------ */
report_mouse_t process_scroll_mode_kb(scroll_status_t scroll_status, report_mouse_t mouse_report);
report_mouse_t process_scroll_mode_user(scroll_status_t scroll_status, report_mouse_t mouse_report);

/* ----------Core functions (only used in custom pointing devices or key processing)------------------------------ */
report_mouse_t pointing_device_task_scroll(report_mouse_t mouse_report);       // handles mouse_report processing add to pointing_device_task
bool           process_record_scroll(uint16_t keyrecord, keyrecord_t* record); // handle processing of builtin keyrecords
