/* Copyright 2020 Purdea Andrei
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

#define DEF_SERIAL_NUMBER "purdea.ro:overnumpad_controller"

#ifndef SERIAL_NUMBER
#define SERIAL_NUMBER DEF_SERIAL_NUMBER
#endif

#define SOLENOID_PIN B5
#define HAPTIC_ENABLE_PIN C13
#define SOLENOID_DEFAULT_DWELL 20
#define SOLENOID_MIN_DWELL 4
#define HAPTIC_OFF_IN_LOW_POWER 1
#define NO_HAPTIC_MOD
