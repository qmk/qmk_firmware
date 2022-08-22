/*
 * Copyright 2022 Paul Ewing
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

// The key_repeater_config_t type holds user configurable options set when
// allocating a new key repeater.
struct key_repeater_config_t {
    // The key code that will be repeatedly registered
    int key;

    // The minimum amount of time to press down the key when registered
    const uint32_t key_duration_min;

    // The maximum amount of time to press down the key when registered
    const uint32_t key_duration_max;

    // The minimum amount of time to wait between registering key presses
    const uint32_t wait_duration_min;

    // The maximum amount of time to wait between registering key presses
    const uint32_t wait_duration_max;
};

// The key_repeater_t type represents a key repeater. This is similar to the
// "Rapid fire" feature on many game controllers. The intention behind this is
// to periodically send a key code while the user is pressing a key.
//
// The duration of the key press as well as the time between key presses is
// slightly randomized by design. This is to simulate more realistic human
// behavior. By setting the minimum and maximum duration fields to the same
// value in the configuration, this randomization can be disabled.
//
// This type is intentionally opaque to avoid the user setting internal fields
// directly. It must be allocated and destroyed using the kr_new() and
// kr_free() functions respectively.
struct key_repeater_t;

// Allocate a new key repeater.
struct key_repeater_t* kr_new(struct key_repeater_config_t* cfg);

// Release an allocated key repeater.
void kr_free(struct key_repeater_t** kr);

// Enable the key repeater such that it will start periodically registering the
// configured key code.
void kr_enable(struct key_repeater_t* kr);

// Disable the key repeater such that it will stop periodically registering the
// configured key code.
void kr_disable(struct key_repeater_t* kr);

// Poll the key repeater to execute, tyically called from matrix_scan_user().
void kr_poll(struct key_repeater_t* kr);
