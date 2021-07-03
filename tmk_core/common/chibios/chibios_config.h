/* Copyright 2019
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

#ifndef USB_VBUS_PIN
#    define SPLIT_USB_DETECT  // Force this on when dedicated pin is not used
#endif

#if defined(STM32F1XX) || defined(GD32VF103)
#    define USE_GPIOV1
#endif

#if defined(STM32F1XX) || defined(STM32F2XX) || defined(STM32F4XX) || defined(STM32L1XX) || defined(GD32VF103)
#    define USE_I2CV1
#endif

#if defined(GD32VF103)
/* This chip has the same API as STM32F103, but uses different names for literally the same thing.
 * As of 4.7.2021 QMK is tailored to use STM32 defines/names, for compatibility sake
 * we just redefine the GD32 names. */
#    include "gd32_compatibility.h"
#endif

// teensy
#if defined(K20x) || defined(KL2x)
#    define USE_I2CV1
#    define USE_I2CV1_CONTRIB  // for some reason a bunch of ChibiOS-Contrib boards only have clock_speed
#    define USE_GPIOV1
#    define STM32_SYSCLK KINETIS_SYSCLK_FREQUENCY
#endif

#if defined(MK66F18)
#    define STM32_SYSCLK KINETIS_SYSCLK_FREQUENCY
#endif
