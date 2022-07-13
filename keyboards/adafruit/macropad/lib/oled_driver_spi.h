/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#ifndef OLED_DC_PIN
#   error "The OLED driver in SPI needs a D/C pin defined"
#endif
#ifndef OLED_CS_PIN
#   error "The OLED driver in SPI needs a CS pin defined"
#endif
#ifndef OLED_SPI_MODE
#   define OLED_SPI_MODE 3
#endif
#ifndef OLED_SPI_DIVISOR
#   define OLED_SPI_DIVISOR 2
#endif
