/* Copyright 2020 Nick Brassel (tzarc)
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

// Prefix string literal with L for descriptors
#define USBCONCAT(a, b) a##b
#define USBSTR(s) USBCONCAT(L, s)

#define HID_VALUE_16(v) ((uint8_t)(v & 0xFF)), ((uint8_t)(v >> 8))

/////////////////////
// RAW Usage page and ID configuration

#ifndef RAW_USAGE_PAGE
#    define RAW_USAGE_PAGE 0xFF60
#endif

#ifndef RAW_USAGE_ID
#    define RAW_USAGE_ID 0x61
#endif

/////////////////////
// Hires Scroll Defaults

#ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
#    ifdef POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER
#        if POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER > 127 || POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER < 1
#            error "POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER must be between 1 and 127, inclusive!"
#        endif
#    else
#        define POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER 120
#    endif
#    ifdef POINTING_DEVICE_HIRES_SCROLL_EXPONENT
#        if POINTING_DEVICE_HIRES_SCROLL_EXPONENT > 127 || POINTING_DEVICE_HIRES_SCROLL_EXPONENT < 0
#            error "POINTING_DEVICE_HIRES_SCROLL_EXPONENT must be between 0 and 127, inclusive!"
#        endif
#    else
#        define POINTING_DEVICE_HIRES_SCROLL_EXPONENT 0
#    endif
#endif