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

/* Handedness. */
// #define MASTER_LEFT
#define MASTER_RIGHT

// TAP-HOLD OPTIONS
#define TAPPING_TERM 300
#define QUICK_TAP_TERM 0
//#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define CHORDAL_HOLD
// AUTO SHIFT OPTIONS
#define NO_AUTO_SHIFT_ALPHA

//MOUSEKEY OPTIONS

//#define MOUSEKEY_INERTIA
// #ifdef MOUSEKEY_INERTIA
    #undef MOUSEKEY_DELAY
    #undef MOUSEKEY_INTERVAL
    #undef MOUSEKEY_MAX_SPEED	//Maximum cursor speed at which acceleration stops
    #undef MOUSEKEY_TIME_TO_MAX	//Number of frames until maximum cursor speed is reached
    #undef MOUSEKEY_FRICTION		//How quickly the cursor stops after releasing a key
    #undef MOUSEKEY_MOVE_DELTA	//How much to move on first frame (1 strongly recommended)

    #define MOUSEKEY_DELAY 0
    #define MOUSEKEY_INTERVAL	16	//Time between cursor movements in milliseconds (16 = 60fps)
    #define MOUSEKEY_MAX_SPEED	18	//Maximum cursor speed at which acceleration stops
    #define MOUSEKEY_TIME_TO_MAX	20	//Number of frames until maximum cursor speed is reached
    #define MOUSEKEY_FRICTION	50	//How quickly the cursor stops after releasing a key
    #define MOUSEKEY_MOVE_DELTA 1	//How much to move on first frame (1 strongly recommended)
// #endif

#undef MOUSEKEY_WHEEL_DELAY		//Delay between pressing a wheel key and wheel movement
#undef MOUSEKEY_WHEEL_INTERVAL	//Time between wheel movements
#undef MOUSEKEY_WHEEL_MAX_SPEED	//Maximum number of scroll steps per scroll action
#undef MOUSEKEY_WHEEL_TIME_TO_MAX

#define MOUSEKEY_WHEEL_DELAY    0	//Delay between pressing a wheel key and wheel movement
#define MOUSEKEY_WHEEL_INTERVAL	50	//Time between wheel movements
#define MOUSEKEY_WHEEL_MAX_SPEED 3
#define MOUSEKEY_WHEEL_TIME_TO_MAX 0

#ifdef  MK_KINETIC_SPEED

    #define MOUSEKEY_MOVE_DELTA 30
    #define MOUSEKEY_INITIAL_SPEED 300
    #define MOUSEKEY_BASE_SPEED 2000
    #define MOUSEKEY_DECELERATED_SPEED 300
    #define MOUSEKEY_ACCELERATED_SPEED 2500
    #define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 5
    #define MOUSEKEY_WHEEL_BASE_MOVEMENTS 8
    #define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 12
    #define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 5
#endif
// ONESHOT OPTIONS
// #define ONESHOT_TAP_TOGGLE 1  /* Tapping this number of times holds the key until tapped once again. */
// #define ONESHOT_TIMEOUT 5000

// COMBO OPTIONS
#define COMBO_TERM 40
#define COMBO_TERM_PER_COMBO
#define COMBO_COUNT 4
