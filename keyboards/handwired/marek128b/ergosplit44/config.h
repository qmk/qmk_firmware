// Copyright 2023 Marek128b (@Marek128b)
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


//define rgb for some ws2812b - 2020 leds 
//#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

//layer count 
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
