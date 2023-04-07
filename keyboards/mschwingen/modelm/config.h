/*
 * Copyright 2020 Michael Schwingen

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


/* key matrix size */
#define MATRIX_ROWS 16
#define MATRIX_COLS 8

/* pins for external shift registers */
#define SR_LOAD_PIN B0
#define SR_CLK_PIN B1
#define SR_DIN_PIN B3
#define SR_DOUT_PIN B2

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT
#define NORMAL_PRINT
//#define USER_PRINT


/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

//#define DEBUG_MATRIX_SCAN_RATE
#define DYNAMIC_MACRO_NO_NESTING

#define MODELM_STATUS_LED E6

#define MODELM_LED1 B5
#define MODELM_LED2 B6
#define MODELM_LED3 D0

#if defined(KEYBOARD_mschwingen_modelm_led_wired)
# define MODELM_LED_CAPSLOCK  MODELM_LED1
# define MODELM_LED_SCROLLOCK MODELM_LED2
# define MODELM_LED_NUMLOCK   MODELM_LED3
#elif defined(KEYBOARD_mschwingen_modelm_led_ffc)
# define MODELM_LED_CAPSLOCK  MODELM_LED2
# define MODELM_LED_SCROLLOCK MODELM_LED3
# define MODELM_LED_NUMLOCK   MODELM_LED1
#elif defined(KEYBOARD_mschwingen_modelm_led_ws2812)
#else
# error one of MODELM_LEDS_FFC, MODELM_LEDS_WIRED or MODELM_LEDS_WS2812 must be set!
#endif

// 3* WS2812 LEDs instead of singlecolor GPIO LEDs
#define RGBLED_NUM 3

// disabled, needs PCB patch.
//#define AUDIO_PIN C6
//#define NO_MUSIC_MODE
