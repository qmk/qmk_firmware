/*
Copyright 2022 Team Mechlovin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef LED_MATRIX_ENABLE
#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_SDA
#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B10
#define I2C1_SDA_PIN B11
#define LED_MATRIX_LED_COUNT 94
#define LED_MATRIX_KEYPRESSES // reacts to keypresses
#define LED_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define LED_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
#define ENABLE_LED_MATRIX_ALPHAS_MODS	
#define ENABLE_LED_MATRIX_BREATHING	
#define ENABLE_LED_MATRIX_BAND	
#define ENABLE_LED_MATRIX_BAND_PINWHEEL	
#define ENABLE_LED_MATRIX_BAND_SPIRAL	
#define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT	
#define ENABLE_LED_MATRIX_CYCLE_UP_DOWN	
#define ENABLE_LED_MATRIX_CYCLE_OUT_IN	
#define ENABLE_LED_MATRIX_DUAL_BEACON	
#define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT	
#define ENABLE_LED_MATRIX_WAVE_UP_DOWN	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS	
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS	
#define ENABLE_LED_MATRIX_SOLID_SPLASH	
#define ENABLE_LED_MATRIX_SOLID_MULTISPLASH	

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#endif
