// Copyright 2024 k-jun (@k-jun)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#pragma once

#define USE_I2C
#define SPLIT_HAND_PIN D2
#define POINTING_DEVICE_ROTATION_90
#define SSD1306OLED

#define LAYOUT_macro(\
    l0A, l1A, l2A, l3A, l4A, l5A,\
    l0B, l1B, l2B, l3B, l4B, l5B,\
    l0C, l1C, l2C, l3C, l4C, l5C,\
              l0D, l1D, l2D, l3D,\
    r0A, r1A, r2A, r3A, r4A, r5A,\
    r0B, r1B, r2B, r3B, r4B, r5B,\
    r0C, r1C, r2C, r3C, r4C, r5C,\
         r1D, r2D, r3D\
)\
{\
    { l5A, l4A, l3A, l2A, l1A, l0A },\
    { l5B, l4B, l3B, l2B, l1B, l0B },\
    { l5C, l4C, l3C, l2C, l1C, l0C },\
              { l3D, l2D, l1D, l0D },\
    { r0A, r1A, r2A, r3A, r4A, r5A },\
    { r0B, r1B, r2B, r3B, r4B, r5B },\
    { r0C, r1C, r2C, r3C, r4C, r5C },\
    { KC_NO, r1D, r2D, r3D },\
}

#define LAYOUT LAYOUT_macro
