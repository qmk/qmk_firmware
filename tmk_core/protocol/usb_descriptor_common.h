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

// The digitizer finger report is repetitive, so it has been moved into a macro
#define DIGITIZER_FINGER_REPORT                                                                                                                                                                                                                                                                                                                                   \
    HID_RI_USAGE_PAGE(8, 0x0D),                                                           /*  Digitizers */                                                                                                                                                                                                                                                       \
        HID_RI_USAGE(8, 0x22),                                                            /*  Finger */                                                                                                                                                                                                                                                           \
        HID_RI_COLLECTION(8, 0x00),                                                       /*  Physical */                                                                                                                                                                                                                                                         \
        HID_RI_PUSH(0), HID_RI_LOGICAL_MINIMUM(8, 0x00), HID_RI_LOGICAL_MAXIMUM(8, 0x01), /*  Tip Switch, Confidence (2 bits) */                                                                                                                                                                                                                                  \
        HID_RI_USAGE(8, 0x47),                                                            /*  Confidence */                                                                                                                                                                                                                                                       \
        HID_RI_USAGE(8, 0x42),                                                            /*  Tip Switch */                                                                                                                                                                                                                                                       \
        HID_RI_REPORT_COUNT(8, 0x02), HID_RI_REPORT_SIZE(8, 0x01), HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),                                                                                                                                                                                                                           \
                                                                                                                                                                                                                                                                                                                                                                  \
        /*  Padding (6 bits) */                                                                                                                                                                                                                                                                                                                                   \
        HID_RI_REPORT_SIZE(8, 0x01), HID_RI_REPORT_COUNT(8, 0x06), HID_RI_INPUT(8, HID_IOF_CONSTANT),                                                                                                                                                                                                                                                             \
                                                                                                                                                                                                                                                                                                                                                                  \
        /*  Contact identifier (3 bits) */                                                                                                                                                                                                                                                                                                                        \
        HID_RI_REPORT_COUNT(8, 0x01), HID_RI_REPORT_SIZE(8, 0x03), HID_RI_LOGICAL_MAXIMUM(8, 0x05), HID_RI_USAGE(8, 0x51), /*  Contact identifier */                                                                                                                                                                                                              \
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),                                                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                                                                                                                                  \
        /*  Padding (5 bits) */                                                                                                                                                                                                                                                                                                                                   \
        HID_RI_REPORT_SIZE(8, 0x01), HID_RI_REPORT_COUNT(8, 0x05), HID_RI_INPUT(8, HID_IOF_CONSTANT),                                                                                                                                                                                                                                                             \
                                                                                                                                                                                                                                                                                                                                                                  \
        /*  X/Y Position (4 bytes) */                                                                                                                                                                                                                                                                                                                             \
        HID_RI_USAGE_PAGE(8, 0x01),                                                                                                                                                                                                                                                                                                     /*  Generic Desktop */    \
        HID_RI_LOGICAL_MINIMUM(8, 0x0), HID_RI_LOGICAL_MAXIMUM(16, DIGITIZER_RESOLUTION_X), HID_RI_REPORT_SIZE(8, 16), HID_RI_UNIT_EXPONENT(8, 0x0E),                                                                                                                                                                                   /*  -2 */                 \
        HID_RI_UNIT(8, 0x11),                                                                                                                                                                                                                                                                                                           /*  CM, English Linear */ \
        HID_RI_USAGE(8, 0x30),                                                                                                                                                                                                                                                                                                          /*  X */                  \
        HID_RI_PHYSICAL_MINIMUM(8, 0x0), HID_RI_PHYSICAL_MAXIMUM(16, (DIGITIZER_WIDTH_MM * 10)), HID_RI_REPORT_COUNT(8, 0x01), HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE), HID_RI_LOGICAL_MAXIMUM(16, DIGITIZER_RESOLUTION_Y), HID_RI_PHYSICAL_MAXIMUM(16, (DIGITIZER_HEIGHT_MM * 10)), HID_RI_USAGE(8, 0x31), /*  Y */                  \
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE), HID_RI_POP(0), HID_RI_END_COLLECTION(0)
