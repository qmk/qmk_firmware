/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#ifdef SSD1306OLED
#    define USE_I2C
#endif

#if defined(OLED_DRIVER_ENABLE) && (defined(USE_I2C) || defined(USE_MATRIX_I2C))
#    error Cannot use both legacy i2c driver and new i2c_master driver at the same time. Undefine USE_I2C and/or USE_MATRIX_I2C
#endif
