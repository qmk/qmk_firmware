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

#include "quantum.h"
#include "pointing_device.h"

/* Check settings and set defaults */
#ifndef POINTING_DEVICE_AUTO_MOUSE_ENABLE
#    error "POINTING_DEVICE_AUTO_MOUSE_ENABLE not defined! check config settings"
#endif

#ifndef AUTO_MOUSE_DEFAULT_LAYER
#    define AUTO_MOUSE_DEFAULT_LAYER 1
#endif

#ifndef AUTO_MOUSE_TIME
#    define AUTO_MOUSE_TIME 650
#endif
#ifndef AUTO_MOUSE_DELAY
#    ifdef TAPPING_TERM
#        define AUTO_MOUSE_DELAY TAPPING_TERM
#    else
#        define AUTO_MOUSE_DELAY 200
#    endif
#endif

/* data structure */
typedef struct {
    struct {
        bool    enabled;
        uint8_t layer;
    } config;
    struct {
        uint16_t active;
        uint16_t delay;
    } timer;
    struct {
        bool   layer_toggled;
        int8_t mouse_key_tracker;
    } status;
} auto_mouse_context_t;

/* setting up use of automouse */
void set_auto_mouse_layer(uint8_t layer); // set in pointing_device_init_*, can be changed later

/* for use in custom pointing device/keyevent processing code */
void pointing_device_task_auto_mouse(report_mouse_t mouse_report); // add to pointing_device_task_*
void process_auto_mouse(uint16_t keycode, keyrecord_t* record);    // add to process_record_*

/* State control */
void set_auto_mouse_state(bool state); // enable/disable auto mouse feature (defaults to false at start) set to true in pointing_device_init_*
bool get_auto_mouse_state(void);       // allows for checking auto_mouse_enable

/* Toggle layer control */
void toggle_mouse_layer(void);     // toggle mouse layer flag disables mouse layer changes while on (meant for tap toggle or layer toggles)
bool get_toggle_mouse_state(void); // return toggle mouse bool value

/* handling key events */
void auto_mouse_keyevent(bool pressed); // trigger auto mouse keyevent (true: keydown, false: keyup)
void auto_mouse_reset_trigger(void);    // reset the active layer timer, mousekey_tracker and start debounce timer

/* Callbacks for adding keycodes to mouse record checking */
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record);
bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record);
bool is_mouse_record_keymap(uint16_t keycode, keyrecord_t* record);
