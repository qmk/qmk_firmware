/* Copyright 2022 IFo Hancroft
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

#include "config_common.h"

#define FORCE_NKRO

// fix VIA RGB_light
//#define VIA_HAS_BROKEN_KEYCODES

#define RGB_MATRIX_SPLIT {43, 43}
#define RGB_DI_PIN D3
#define RGBLED_NUM 86
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGBLIGHT_VAL_STEP 15
#define RGB_MATRIX_CENTER { 112, 32 }
#define RGB_DISABLE_WHEN_USB_SUSPENDED
//#define RGB_MATRIX_KEYPRESSES
//#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
//#define RGBLIGHT_ANIMATIONS

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_MODS_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_TRANSACTION_IDS_KB KEYBOARD_CURRENT_ALPA_SYNC

//#ifdef RGBLIGHT_ENABLE

//#    define RGBLIGHT_SPLIT
//#    define RGBLED_SPLIT {43, 43}
//#    define RGB_DI_PIN D3
//#    define DRIVER_LED_TOTAL RGBLED_NUM
//#    define RGBLIGHT_LIMIT_VAL 150
//#    define RGBLIGHT_SLEEP
//#    define WS2812_TRST_US 100

 //#    define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

//#endif
