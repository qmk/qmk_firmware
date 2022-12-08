/* Copyright 2018 mtdjr - modified by ishtob
 * Driver for solenoid written for QMK
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

#ifndef SOLENOID_DEFAULT_DWELL
#    define SOLENOID_DEFAULT_DWELL 12
#endif

#ifndef SOLENOID_MAX_DWELL
#    define SOLENOID_MAX_DWELL 100
#endif

#ifndef SOLENOID_MIN_DWELL
#    define SOLENOID_MIN_DWELL 4
#endif

#ifndef SOLENOID_DWELL_STEP_SIZE
#    define SOLENOID_DWELL_STEP_SIZE 1
#endif

#ifndef SOLENOID_DEFAULT_BUZZ
#    define SOLENOID_DEFAULT_BUZZ 0
#endif

#ifndef SOLENOID_BUZZ_ACTUATED
#    define SOLENOID_BUZZ_ACTUATED SOLENOID_MIN_DWELL
#endif

#ifndef SOLENOID_BUZZ_NONACTUATED
#    define SOLENOID_BUZZ_NONACTUATED SOLENOID_MIN_DWELL
#endif

#ifndef SOLENOID_PINS
#    ifdef SOLENOID_PIN
#        define SOLENOID_PINS \
            { SOLENOID_PIN }
#    else
#        error SOLENOID_PINS array not defined
#    endif
#endif

void solenoid_buzz_on(void);
void solenoid_buzz_off(void);
void solenoid_set_buzz(uint8_t buzz);

void solenoid_set_dwell(uint8_t dwell);

void solenoid_stop(uint8_t index);
void solenoid_fire(uint8_t index);
void solenoid_fire_handler(void);

void solenoid_check(void);

void solenoid_setup(void);
void solenoid_shutdown(void);
