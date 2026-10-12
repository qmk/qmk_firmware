/* Copyright 2024 Colin Lam (Ploopy Corporation)
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

#define UNUSABLE_PINS \
    { GP1, GP3, GP4, GP6, GP8, GP10, GP14, GP16, GP18, GP20, GP22, GP24, GP25, GP26, GP27, GP28, GP29 }

#define MOUSE_EXTENDED_REPORT

#define PLOOPY_DRAGSCROLL_MOMENTARY
#define PLOOPY_DRAGSCROLL_DIVISOR_H 64.0
#define PLOOPY_DRAGSCROLL_DIVISOR_V 64.0

#define PAW3222_CS_PIN GP5
#define PAW3222_MOTION_PIN GP9
#define PAW3222_SPI_DIVISOR 64
#define SPI_SCK_PIN GP2
#define SPI_MISO_PIN GP0
#define SPI_MOSI_PIN GP7
