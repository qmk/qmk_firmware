/*
Copyright 2022 oco9oco <oco9oco@gmail.com>
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

// TAP-HOLD OPTIONS
#define TAPPING_TERM 200
#define TAPPING_FORCE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// AUTO SHIFT OPTIONS
#define NO_AUTO_SHIFT_ALPHA

//MOUSEKEY OPTIONS
#define MOUSEKEY_INERTIA

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_MAX_SPEED	//Maximum cursor speed at which acceleration stops
#undef MOUSEKEY_TIME_TO_MAX	//Number of frames until maximum cursor speed is reached
#undef MOUSEKEY_FRICTION		//How quickly the cursor stops after releasing a key
#undef MOUSEKEY_MOVE_DELTA	//How much to move on first frame (1 strongly recommended)

#define MOUSEKEY_INTERVAL	8	//Time between cursor movements in milliseconds (16 = 60fps)
#define MOUSEKEY_MAX_SPEED	12	//Maximum cursor speed at which acceleration stops
#define MOUSEKEY_TIME_TO_MAX	30	//Number of frames until maximum cursor speed is reached
#define MOUSEKEY_FRICTION	40	//How quickly the cursor stops after releasing a key
#define MOUSEKEY_MOVE_DELTA	1	//How much to move on first frame (1 strongly recommended)
// #ifdef  MK_KINETIC_SPEED
//     #define MOUSEKEY_MOVE_DELTA 30
//     #define MOUSEKEY_INITIAL_SPEED 300
//     #define MOUSEKEY_BASE_SPEED 2000
//     #define MOUSEKEY_DECELERATED_SPEED 300
//     #define MOUSEKEY_ACCELERATED_SPEED 2500
//     #define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 5
//     #define MOUSEKEY_WHEEL_BASE_MOVEMENTS 8
//     #define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 12
//     #define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 5

#undef MOUSEKEY_WHEEL_MAX_SPEED
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_MAX_SPEED 2
#define MOUSEKEY_WHEEL_TIME_TO_MAX 7

    // #undef MOUSEKEY_MAX_SPEED
    // #undef MOUSEKEY_TIME_TO_MAX
    // #define MOUSEKEY_MAX_SPEED 7
    // #define MOUSEKEY_TIME_TO_MAX 60


// ONESHOT OPTIONS
#define ONESHOT_TAP_TOGGLE 1  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000

// COMBO OPTIONS
#define COMBO_TERM 40
#define COMBO_TERM_PER_COMBO
//#define COMBO_COUNT 4
