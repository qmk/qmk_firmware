 /* Copyright 2020 Imam Rafii 
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

#include "config_common.h"

#define VENDOR_ID 0x4454
#define PRODUCT_ID 0x5444
#define DEVICE_VER 0x0001

#define MANUFACTURER "IktaS"
#define PRODUCT "Pill60"

#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 1

/* Backlighting include */
#define BACKLIGHT_PIN           B14
#define BACKLIGHT_PWM_DRIVER    PWMD5
#define BACKLIGHT_PWM_CHANNEL   1
#define BACKLIGHT_LEVELS        5
#define BREATHING_PERIOD        6

/* Encoder */
#define ENCODERS_PAD_A \
    { B9 }
#define ENCODERS_PAD_B \
    { B8 }
#define ENCODER_RESOLUTION 2
