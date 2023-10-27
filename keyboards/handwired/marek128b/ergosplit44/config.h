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


//define rgb for ws2812b - 2020 leds 
//#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

//vial | get the uid: python3 util/vial_generate_keyboard_uid.py
#define VIAL_KEYBOARD_UID {0x5F, 0x97, 0x91, 0x98, 0xCB, 0x9F, 0x51, 0xCD}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

//layer count 
#define DYNAMIC_KEYMAP_LAYER_COUNT 5