/* Copyright 2021 QMK
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

#define HAL_USE_PWM TRUE

#define ES32_PWM_USE_GP16C4T2   TRUE

#define BACKLIGHT_PWM_DRIVER    PWM_GP16C4T2
#define BACKLIGHT_PWM_CHANNEL   3

#define HAL_USE_USB TRUE
#define HAL_USE_PAL TRUE

#include_next <halconf.h>
