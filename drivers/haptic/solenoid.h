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

#ifndef SOLENOID_ACTIVE
#    define SOLENOID_ACTIVE false
#endif

#ifndef SOLENOID_PIN
#    define SOLENOID_PIN F6
#endif

void solenoid_buzz_on(void);
void solenoid_buzz_off(void);
void solenoid_set_buzz(int buzz);

void solenoid_dwell_minus(uint8_t solenoid_dwell);
void solenoid_dwell_plus(uint8_t solenoid_dwell);
void solenoid_set_dwell(uint8_t dwell);

void solenoid_stop(void);
void solenoid_fire(void);

void solenoid_check(void);

void solenoid_setup(void);
void solenoid_shutdown(void);
