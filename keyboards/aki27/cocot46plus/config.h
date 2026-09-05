/*
Copyright 2022 aki27

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

// These do not seem to have keyboard.json support yet.
#define ADNS5050_SCLK_PIN         GP23
#define ADNS5050_SDIO_PIN         GP8
#define ADNS5050_CS_PIN           GP9

#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

#define POINTING_DEVICE_ROTATION_180
#define OLED_FONT_H "keyboards/aki27/cocot46plus/glcdfont.c"
