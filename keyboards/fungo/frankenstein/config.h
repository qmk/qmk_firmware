/* Copyright 2022 bojiguard (@bojiguard)
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


/* select keyboard  master board  - I2C or Serial communication master    */
#define MASTER_RIGHT

//caps word, left shift + right shift => capslock
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 500   //default 5000msec

#define POINTING_DEVICE_RIGHT
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_ROTATION_90

#define ENCODERS_PAD_A { D1 }
#define ENCODERS_PAD_B { D0 }
