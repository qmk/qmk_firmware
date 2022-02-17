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

// STM32 compatibility
#if defined(MCU_STM32)
#    define CPU_CLOCK STM32_SYSCLK

#    if defined(STM32F1XX)
#        define USE_GPIOV1
#        define PAL_MODE_ALTERNATE_OPENDRAIN PAL_MODE_STM32_ALTERNATE_OPENDRAIN
#        define PAL_MODE_ALTERNATE_PUSHPULL PAL_MODE_STM32_ALTERNATE_PUSHPULL
#    else
#        define PAL_OUTPUT_TYPE_OPENDRAIN PAL_STM32_OTYPE_OPENDRAIN
#        define PAL_OUTPUT_TYPE_PUSHPULL PAL_STM32_OTYPE_PUSHPULL
#        define PAL_OUTPUT_SPEED_HIGHEST PAL_STM32_OSPEED_HIGHEST
#        define PAL_PUPDR_FLOATING PAL_STM32_PUPDR_FLOATING
#    endif

#    if defined(STM32F1XX) || defined(STM32F2XX) || defined(STM32F4XX) || defined(STM32L1XX)
#        define USE_I2CV1
#    endif
#endif

// GD32 compatibility
#if defined(MCU_GD32V)
#    define CPU_CLOCK GD32_SYSCLK

#    if defined(GD32VF103)
#        define USE_GPIOV1
#        define USE_I2CV1
#        define PAL_MODE_ALTERNATE_OPENDRAIN PAL_MODE_GD32_ALTERNATE_OPENDRAIN
#        define PAL_MODE_ALTERNATE_PUSHPULL PAL_MODE_GD32_ALTERNATE_PUSHPULL
#    endif
#endif

// WB32 compatibility
#if defined(MCU_WB32)
#    define CPU_CLOCK WB32_MAINCLK

#    if defined(WB32F3G71xx)
#        define PAL_OUTPUT_TYPE_OPENDRAIN PAL_WB32_OTYPE_OPENDRAIN
#        define PAL_OUTPUT_TYPE_PUSHPULL PAL_WB32_OTYPE_PUSHPULL
#        define PAL_OUTPUT_SPEED_HIGHEST PAL_WB32_OSPEED_HIGH
#        define PAL_PUPDR_FLOATING PAL_WB32_PUPDR_FLOATING
#    endif
#endif

#if defined(GD32VF103)
/* This chip has the same API as STM32F103, but uses different names for literally the same thing.
 * As of 4.7.2021 QMK is tailored to use STM32 defines/names, for compatibility sake
 * we just redefine the GD32 names. */
#    include "gd32v_compatibility.h"
#endif

// teensy compatibility
#if defined(MCU_KINETIS)
#    define CPU_CLOCK KINETIS_SYSCLK_FREQUENCY

#    if defined(K20x) || defined(KL2x)
#        define USE_I2CV1
#        define USE_I2CV1_CONTRIB  // for some reason a bunch of ChibiOS-Contrib boards only have clock_speed
#        define USE_GPIOV1
#    endif
#endif

#if defined(HT32)
#    define CPU_CLOCK HT32_CK_SYS_FREQUENCY
#    define PAL_MODE_ALTERNATE PAL_HT32_MODE_AF
#    define PAL_OUTPUT_TYPE_OPENDRAIN (PAL_HT32_MODE_OD | PAL_HT32_MODE_DIR)
#    define PAL_OUTPUT_TYPE_PUSHPULL PAL_HT32_MODE_DIR
#    define PAL_OUTPUT_SPEED_HIGHEST 0
#endif
