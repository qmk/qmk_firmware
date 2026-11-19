/* Copyright 2026 NUTWANG
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
/*qmk compile -kb sk32/kb17 -km default*/

/* Matrix size (MATRIX_ROWS / MATRIX_COLS) is generated from keyboard.json
 * ("matrix_size") by the data-driven system; only the pins are defined here. */

/* key matrix pins
 * ROW1-5: PB2 / PB1 / PB0 / PC5 / PC4
 * COL1-4: PB12 / PB11 / PB10 / PB13
 * Other key pads (informational):
 *   PA11 = USB_DM, PA12 = USB_DP, PA13 = SWDIO, PA14 = SWCLK
 */
#define MATRIX_COL_PINS { B12, B11, B10, B13 }
#define MATRIX_ROW_PINS { B2, B1, B0, C5, C4 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* BOOTMAGIC KEY */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* REAL CPU low power while the USB bus is suspended: enter the Cortex-M0 STOP
 * (deep sleep) instead of the default wait_ms(17) busy loop.  The core halts
 * until the armed USB RESUME / an EXTI wakes it; on wakeup the low power
 * driver (hal_low_power_lld) rebuilds the PLL/HSI clocks torn down by STOP.
 * Gated on SK32_HAL_USE_LOWPOWER so it only affects this board.  Same wiring
 * as the LD7_OLED board. */
#define SK32_HAL_USE_LOWPOWER TRUE

/*RGB MATRIX*/
/* LED string is driven by the SK32F077 SLED peripheral (WS2812_DRIVER=sled).
 * The data pad is SLED1_CH0 = PC0 in alternate function 14, served by the
 * SLED2 channel registers (DR[1]/DMAEN2).  Enable the SLED2 group in the
 * low level driver and select it for the ws2812 driver (see
 * platforms/chibios/drivers/ws2812_sled.c). */
#define WS2812_SLED_GROUP SLED2
#define SK32_SLED_USE_SLED2 TRUE
#define WS2812_SLED_PORT GPIOC
#define WS2812_SLED_PIN 0U
#define RGB_MATRIX_LED_COUNT 17

#define RGB_MATRIX_TIMEOUT 0 // number of milliseconds to wait until rgb automatically turns off
#define RGB_MATRIX_SLEEP // turn off effects when suspended
//#define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
//#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180 // limits maximum brightness of LEDs to 180 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_DEFAULT_VAL 180 // Sets the default brightness value, if none has been set
#define RGB_MATRIX_DEFAULT_SPD 127 // Sets the default animation speed, if none has been set
//#define RGB_MATRIX_DISABLE_KEYCODES // disables control of rgb matrix by keycodes (must use code functions to control the feature)
//#define RGB_TRIGGER_ON_KEYDOWN      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_DUAL_BEACON // Sets the default mode, if none has been set

/*other rgb set*/
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects

/*RGB MATIRX EFFECTS ON*/

//#define ENABLE_RGB_MATRIX_ALPHAS_MODS	//Enables RGB_MATRIX_ALPHAS_MODS
//#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN	//Enables RGB_MATRIX_GRADIENT_UP_DOWN
//#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT	//Enables RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING	//Enables RGB_MATRIX_BREATHING
//#define ENABLE_RGB_MATRIX_BAND_SAT	//Enables RGB_MATRIX_BAND_SAT
//#define ENABLE_RGB_MATRIX_BAND_VAL	//Enables RGB_MATRIX_BAND_VAL
//#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT	//Enables RGB_MATRIX_BAND_PINWHEEL_SAT
//#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL	//Enables RGB_MATRIX_BAND_PINWHEEL_VAL
//#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT	//Enables RGB_MATRIX_BAND_SPIRAL_SAT
//#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL	//Enables RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL	//Enable//RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT	//Enables RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN	//Enables RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON	//Enables RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN	//Enables RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL	//Enables RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL	//Enables RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL	//Enables RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON	//Enables RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON	//Enables RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS	//Enables RGB_MATRIX_RAINBOW_PINWHEELS
//#define ENABLE_RGB_MATRIX_RAINDROPS	//Enables RGB_MATRIX_RAINDROPS
//#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS	//Enables RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING	//Enables RGB_MATRIX_HUE_BREATHING
//#define ENABLE_RGB_MATRIX_HUE_PENDULUM	//Enables RGB_MATRIX_HUE_PENDULUM
//#define ENABLE_RGB_MATRIX_HUE_WAVE	//Enables RGB_MATRIX_HUE_WAVE
//#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL	//Enables RGB_MATRIX_PIXEL_FRACTAL
//#define ENABLE_RGB_MATRIX_PIXEL_FLOW	//Enables RGB_MATRIX_PIXEL_FLOW
//#define ENABLE_RGB_MATRIX_PIXEL_RAIN	//Enables RGB_MATRIX_PIXEL_RAIN

//#define ENABLE_RGB_MATRIX_TYPING_HEATMAP	//Enables RGB_MATRIX_TYPING_HEATMAP
//#define ENABLE_RGB_MATRIX_DIGITAL_RAIN	//Enables RGB_MATRIX_DIGITAL_RAIN

//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE	//Enables RGB_MATRIX_SOLID_REACTIVE_SIMPLE
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE	//Enables RGB_MATRIX_SOLID_REACTIVE
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE	//Enables RGB_MATRIX_SOLID_REACTIVE_WIDE
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE	//Enables RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS	//Enables RGB_MATRIX_SOLID_REACTIVE_CROSS
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS	//Enables RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS	//Enables RGB_MATRIX_SOLID_REACTIVE_NEXUS
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS	//Enables RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH	//Enables RGB_MATRIX_SPLASH
//#define ENABLE_RGB_MATRIX_MULTISPLASH	//Enables RGB_MATRIX_MULTISPLASH
//#define ENABLE_RGB_MATRIX_SOLID_SPLASH	//Enables RGB_MATRIX_SOLID_SPLASH
//#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH	//Enables RGB_MATRIX_SOLID_MULTISPLASH
