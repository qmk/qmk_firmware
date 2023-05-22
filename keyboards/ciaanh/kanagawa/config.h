/* Copyright 2023 Ciaanh (@ciaanh)
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

/* OLED SPI Defines */
#ifdef OLED_ENABLE
#    define OLED_FONT_H "lib/oledfont.c"

/* I2C Conf */
#    define I2C_DRIVER I2CD0
#    define I2C1_SDA_PIN GP0
#    define I2C1_SCL_PIN GP1
#endif

#ifdef RGB_MATRIX_ENABLE
     /* RGB Defines */
#    define RGB_DI_PIN GP4
#    define WS2812_DI_PIN GP4

//      /* Enable Framebuffer and keypress effects */
// #    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #    define RGB_MATRIX_KEYPRESSES
#endif
