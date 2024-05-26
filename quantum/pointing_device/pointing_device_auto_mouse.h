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

#include <stdint.h>
#include <stdbool.h>
#include "pointing_device.h"
#include "keycodes.h"
#include "action.h"
#include "report.h"
#include "action_layer.h"
#include "action_tapping.h"

/* check settings and set defaults */
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
#    define AUTO_MOUSE_DELAY GET_TAPPING_TERM(KC_MS_BTN1, &(keyrecord_t){})
#endif
#ifndef AUTO_MOUSE_DEBOUNCE
#    define AUTO_MOUSE_DEBOUNCE 25
#endif
#ifndef AUTO_MOUSE_THRESHOLD
#    define AUTO_MOUSE_THRESHOLD 10
#endif

/* data structure */
typedef struct {
    mouse_xy_report_t x;
    mouse_xy_report_t y;
    int8_t            v;
    int8_t            h;
} total_mouse_movement_t;
typedef struct {
    struct {
        bool     is_enabled;
        uint8_t  layer;
        uint16_t timeout;
        uint8_t  debounce;
    } config;
    struct {
        uint16_t active;
        uint16_t delay;
    } timer;
    struct {
        bool   is_activated;
        bool   is_toggled;
        int8_t mouse_key_tracker;
    } status;
    total_mouse_movement_t total_mouse_movement;
} auto_mouse_context_t;

/* ----------Set up and control------------------------------------------------------------------------------ */
void          set_auto_mouse_enable(bool enable);                       // enable/disable auto mouse feature
bool          get_auto_mouse_enable(void);                              // get auto_mouse_enable
void          set_auto_mouse_layer(uint8_t layer);                      // set target layer by index
uint8_t       get_auto_mouse_layer(void);                               // get target layer index
void          set_auto_mouse_timeout(uint16_t timeout);                 // set layer timeout
uint16_t      get_auto_mouse_timeout(void);                             // get layer timeout
void          set_auto_mouse_debounce(uint8_t debounce);                // set debounce
uint8_t       get_auto_mouse_debounce(void);                            // get debounce
void          set_auto_mouse_key_tracker(int8_t key_tracker);           // set key tracker
int8_t        get_auto_mouse_key_tracker(void);                         // get key tracker
void          auto_mouse_layer_off(void);                               // disable target layer if appropriate (DO NOT USE in layer_state_set stack!!)
layer_state_t remove_auto_mouse_layer(layer_state_t state, bool force); // remove auto mouse target layer from state if appropriate (can be forced)
bool          is_auto_mouse_active(void);                               // check if target layer is active
/* ----------For custom pointing device activation----------------------------------------------------------- */
bool auto_mouse_activation(report_mouse_t mouse_report); // handles pointing device trigger conditions for target layer activation (overwritable)

/* ----------Handling keyevents------------------------------------------------------------------------------ */
void auto_mouse_keyevent(bool pressed);      // trigger auto mouse keyevent: mouse_keytracker increment/decrement on press/release
void auto_mouse_reset_trigger(bool pressed); // trigger non mouse keyevent: reset and start delay timer (DO NOT USE in layer_state_set stack!!)
void auto_mouse_toggle(void);                // toggle mouse layer flag disables mouse layer deactivation while on (meant for tap toggle or toggle of target)
bool get_auto_mouse_toggle(void);            // get toggle mouse layer flag value

/* ----------Callbacks for adding keycodes to mouse record checking------------------------------------------ */
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record);
bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record);

/* ----------Core functions (only used in custom pointing devices or key processing)------------------------- */
void pointing_device_task_auto_mouse(report_mouse_t mouse_report); // add to pointing_device_task_*
bool process_auto_mouse(uint16_t keycode, keyrecord_t* record);    // add to process_record_*

/* ----------Macros/Aliases---------------------------------------------------------------------------------- */
#define AUTO_MOUSE_TARGET_LAYER get_auto_mouse_layer()
#define AUTO_MOUSE_ENABLED get_auto_mouse_enable()
