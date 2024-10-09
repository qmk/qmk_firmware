/* Copyright 2023 QMK
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

#undef RP_I2C_USE_I2C0
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C0 TRUE
#define RP_I2C_USE_I2C1 FALSE

#undef I2C_DRIVER
#define I2C_DRIVER I2CD0
#undef I2C1_SCL_PIN
#undef I2C1_SDA_PIN
#define I2C0_SDA_PIN        GP0
#define I2C0_SCL_PIN        GP1
#define I2C1_SDA_PIN        GP0
#define I2C1_SCL_PIN        GP1

