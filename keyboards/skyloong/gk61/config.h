/* Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
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

/*
 * RGB matrix driver config (IS31FL3733)
 *
 * This is a 7-bit address, that gets left-shifted and bit 0
 * set to 0 for write, 1 for read (as per I2C protocol)
 * The address will vary depending on your wiring:
 * 00 <-> GND
 * 01 <-> SCL
 * 10 <-> SDA
 * 11 <-> VCC
 * ADDR1 represents A1:A0 of the 7-bit address.
 * ADDR2 represents A3:A2 of the 7-bit address.
 * The result is: 0b101(ADDR2)(ADDR1)
 */
#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010011

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 192
#define DRIVER_2_LED_TOTAL 0
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define ISSI_PWM_FREQUENCY 10000

#define RGB_MATRIX_KEYPRESSES  //Reacts to keypress
#define RGB_DISABLE_WHEN_USB_SUSPENDED   //turn off effects when suspended

//RGB Matrix Effects lists
#define ENABLE_RGB_MATRIX_ALPHAS_MODS	//Enables RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN	//Enables RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT	//Enables RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING	//Enables RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT	//Enables RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL	//Enables RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT	//Enables RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL	//Enables RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT	//Enables RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL	//Enables RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL	//Enables RGB_MATRIX_CYCLE_ALL
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
#define ENABLE_RGB_MATRIX_RAINDROPS	//Enables RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS	//Enables RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING	//Enables RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM	//Enables RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE	//Enables RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL	//Enables RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_RAIN	//Enables RGB_MATRIX_PIXEL_RAIN

#define RGB_MATRIX_DEFAULT_VAL 150  //Sets the default mode, if none has been set
#define RGB_TRIGGER_ON_KEYDOWN  //Triggers RGB keypress events on key down
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 1



