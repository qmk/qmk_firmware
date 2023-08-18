// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* ---------------------------
 * Common Spit Configuration
 * ---------------------------
 */
#define SPLIT_OLED_ENABLE

/* ---------------------------
 * Common OLED Configuration
 * ---------------------------
 */
#define OLED_TIMEOUT 0
#define CUSTOM_OLED_TIMEOUT 10000

/* ---------------------------
 * Common Bootmagic Lite
 * ---------------------------
 */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* ---------------------------
 * Common RGB Configuration
 * ---------------------------
 */
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_DISABLE_TIMEOUT CUSTOM_OLED_TIMEOUT
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
#define RGB_MATRIX_DEFAULT_HUE 215
#define RGB_MATRIX_DEFAULT_SAT 255
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

/* ---------------------------
 * Common other Configuration
 * ---------------------------
 */
#define ENABLE_COMPILE_KEYCODE

#if defined CONVERT_TO_KB2040 || defined CONVERT_TO_PROMICRO_RP2040
#    include "config_rp2040.h"
#else
#    include "config_avr.h"
#endif
