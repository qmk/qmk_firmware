/* 
 * Copyright 2023 KBDCraft
 * Copyright 2023 Adophoxia <andyao1528@gmail.com>
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

#define I2C1_SCL_PIN        B8
#define I2C1_SDA_PIN        B9
#define I2C1_CLOCK_SPEED	400000
#define I2C1_DUTY_CYCLE	FAST_DUTY_CYCLE_16_9

#define IS31FL3741_DRIVER_COUNT 1
#define DRIVER_ADDR_1 IS31FL3741_I2C_ADDRESS_GND
#define RGB_MATRIX_LED_COUNT 64

/* turn off effects when suspended */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES