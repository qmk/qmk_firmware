/* Protokeeb Copyright 2024 A-Tech Officials (@atechofficials)
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. 
 * If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */

#pragma once

// Define the pin connected to the encoder push button
#define ENCODER_BUTTON_PIN GP14

// Define the row and column for the encoder button
#define ENCODER_BUTTON_ROW 0
#define ENCODER_BUTTON_COL 4

/* Peripheral used */
#define WS2812_PIO_USE_PIO1

/* RGB lighting effects and animations settings */
#define RGBLIGHT_EFFECT_BREATHE_MAX 127
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 40
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 2
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 4
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0
#define RGBLIGHT_EFFECT_SWIRL_RANGE 255
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4
#define RGBLIGHT_EFFECT_TWINKLE_LIFE 200
#define RGBLIGHT_EFFECT_TWINKLE_PROBABILITY (1/127)

/* Double tap reset bootloader entry */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

/* Bootloader timeout window in milli-seconds */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

/* LED to blink when entering bootloader mode */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25

#define ENCODER_MAP_KEY_DELAY 10