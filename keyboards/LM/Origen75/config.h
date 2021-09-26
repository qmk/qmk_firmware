/* Copyright 2021 JasonRen(biu)
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4C4D
#define PRODUCT_ID      0x4C02
#define DEVICE_VER      0x0002
#define MANUFACTURER    LM STUDIO
#define PRODUCT         Origen75


/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B4, B5, B6, C6, C7,C3 }
#define MATRIX_COL_PINS {F7,F6,F5,F4,F1,F0,E6,B0,B1,B2,B3,D0,D1,D2,C4}
#define UNUSED_PINS


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D4
#define RGBLIGHT_EFFECT_STATIC_GRADIEN//启用静态渐变模式。
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL//启用彩虹漩涡动画模式。
#define RGBLIGHT_EFFECT_BREATHING//呼吸动画

#define RGBLIGHT_LAYERS//启用动画层
#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF //RGB LAYERS在RGB关闭的情况下仍然有效，实现全局分层指示灯。

#define RGBLIGHT_EFFECT_BREATHE_MAX 255//限制亮度
#define RGBLED_NUM 16
#endif
