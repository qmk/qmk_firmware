/* Copyright 2020 QMK
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

/* PWM for AUDIO and RGB LED */
#define HAL_USE_PWM TRUE
/* GPT and PAL for Audio */
#define HAL_USE_GPT TRUE
#define HAL_USE_PAL TRUE
/* I2C for OLED display */
#define HAL_USE_I2C TRUE

#include_next <halconf.h>
