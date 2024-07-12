/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software : you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */

#pragma once

#define _CHIBIOS_HAL_CONF_VER_8_0_

#define HAL_USE_SPI TRUE

#ifdef LK_WIRELESS_ENABLE
#    define HAL_USE_RTC TRUE
#endif

#if defined(LK_WIRELESS_ENABLE) || defined(ENCODER_ENABLE)
#    define PAL_USE_CALLBACKS TRUE
#endif

#include_next <halconf.h>
