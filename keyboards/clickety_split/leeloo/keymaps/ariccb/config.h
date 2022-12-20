/* Copyright 2022 Clickety Split Ltd.
 *                https://clicketysplit.ca
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

// Select hand configuration
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_TERM (TAPPING_TERM/5)
#define ADAPTIVE_TERM 350
#define ONESHOT_TIMEOUT 1000  //Time (in ms) before the one shot key is released

#ifdef TAPPING_TERM
    #undef TAPPING_TERM

    #define IGNORE_MOD_TAP_INTERRUPT
    #define TAPPING_FORCE_HOLD
    #define TAPPING_TERM 150
#endif

// #define TAPPING_TERM 150
// #define IGNORE_MOD_TAP_INTERRUPT

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifndef NO_DEBUG
#define NO_DEBUG
#endif  //!NO_DEBUG

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif //!NO_PRINT

#define LAYER_LOCK_IDLE_TIMEOUT 120000 // Turn off layer lock after 120 seconds
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

#define MOUSEKEY_INTERVAL 8            //Time between cursor movements in milliseconds.
                                       //If the refresh rate of your display is 60Hz, you could set it to 16 (1/60). As this raises the cursor speed significantly, you may want to lower MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 13          //Maximum cursor speed at which acceleration stops
#define MOUSEKEY_TIME_TO_MAX 90        //Time until maximum mouse cursor speed is reached
#define MOUSEKEY_DELAY 0               //Delay between pressing a movement key and cursor movement
#define MOUSEKEY_MOVE_DELTA 4          //Step size
#define MOUSEKEY_WHEEL_DELAY 0         //Delay between pressing a movement key and wheel scroll movement
#define MOUSEKEY_WHEEL_INTERVAL 60     //Time between wheel movements - setting it too low will make scrolling too fast
#define MK_KINETIC_SPEED               //Enable kinetic mode, acceleration follows quadratic curve
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 3     //Initial number of movements of the mouse wheel
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 35       //Maximum number of movements at which acceleration stops
//#define MOUSEKEY_WHEEL_MAX_SPEED 10           //Maximum number of scroll steps per scroll action
//#define MOUSEKEY_WHEEL_TIME_TO_MAX 400        //Time until maximum scroll speed is reached
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 50 //Accelerated wheel movements
#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 4 //Decelerated wheel movements


#define ENCODER_RESOLUTIONS {2}
#define DISABLE_LEADER
