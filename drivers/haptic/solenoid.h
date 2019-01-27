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
#include <timer.h>

#ifndef SOLENOID_ACTIVE
#define SOLENOID_DEFAULT_DWELL 12
#ifndef SOLENOID_ACTIVE

#define SOLENOID_MAX_DWELL 100
#ifndef SOLENOID_ACTIVE

#define SOLENOID_MIN_DWELL 4
#ifndef SOLENOID_ACTIVE
  #define SOLENOID_ACTIVE false
#endif
#ifndef SOLENOID_PIN
  #define SOLENOID_PIN F6
#endif


bool solenoid_enabled = SOLENOID_ACTIVE;
bool solenoid_on = false;
bool solenoid_buzz = false;
bool solenoid_buzzing = false;
uint16_t solenoid_start = 0;
uint8_t solenoid_dwell = SOLENOID_DEFAULT_DWELL;


void solenoid_buzz_on(void);
void solenoid_buzz_off(void);
void solenoid_set_buzz(bool buzz);

void solenoid_dwell_minus(void);
void solenoid_dwell_plus(void);
void solenoid_set_dwell(uint8_t dwell);

void solenoid_stop(void);
void solenoid_fire(void);

void solenoid_check(void);

void solenoid_setup(void);

#endif
