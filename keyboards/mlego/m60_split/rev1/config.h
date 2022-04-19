/* Copyright 2021-2022 alin m elena <alinm.elena@gmail.com>
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
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001

#define MATRIX_ROW_PINS \
    { B0, A6, A7, B1, A5 }
#define MATRIX_COL_PINS \
    { B14, A10, A15, B3, B4, B5 }

#define MATRIX_ROW_PINS_RIGHT \
    { B1, A4, A5, A6, A7 }

#define MATRIX_COL_PINS_RIGHT \
    { B0, A3, A2, A1, B7, B5 }  // cols are from right to left to match the layout

#define ENCODERS_PAD_A \
    { A0 }
#define ENCODERS_PAD_B \
    { B8 }
#define ENCODER_RESOLUTIONS \
    { 4 }

#define LED_NUM_LOCK_PIN B12
#define LED_SCROLL_LOCK_PIN B13
#define LED_CAPS_LOCK_PIN C13

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

#define RGB_DI_PIN B15

#define SPLIT_HAND_PIN B9
#define SERIAL_USART_TX_PIN B6
#define RGBLIGHT_SPLIT
#define RGBLIGHT_LAYERS

#define UNUSED_PINS
#define SERIAL_USART_SPEED 921600

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define MATRIX_IO_DELAY 5

#define RGBLIGHT_LIMIT_VAL 128
#define RGBLIGHT_DEFAULT_HUE 213

#define RGBLED_NUM 16
#define RGBLED_SPLIT \
    { 8, 8 }

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0
