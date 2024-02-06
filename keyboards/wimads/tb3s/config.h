/* Copyright 2024 Wimads
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

#define ROTATIONAL_TRANSFORM_ANGLE -90
#define POINTING_DEVICE_INVERT_Y

#define MOUSE_EXTENDED_REPORT

#undef  POINTING_DEVICE_TASK_THROTTLE_MS
#define POINTING_DEVICE_TASK_THROTTLE_MS 5 //to tame the buffer-less dragscroll a bit

#undef  PRINTF_SUPPORT_DECIMAL_SPECIFIERS
#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1  //enable floats in debug console

/* PMW3360 Settings */
#define PMW33XX_LIFTOFF_DISTANCE 0x00
#define PMW33XX_CS_PIN GP5
#define SPI_SCK_PIN GP2
#define SPI_MISO_PIN GP0
#define SPI_MOSI_PIN GP7
