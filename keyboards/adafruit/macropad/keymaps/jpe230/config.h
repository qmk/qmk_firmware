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

#include "transpiler.h"

/* Reduce max brightness and startup brightness */
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_STARTUP_VAL 120

/* Define number of layers */
#define NUMBER_OF_LAYERS TRANS_LAYER_NO

/* Enable more than 4 layers in VIA */
#define DYNAMIC_KEYMAP_LAYER_COUNT NUMBER_OF_LAYERS

/* Enable Compile keycode (i.e. qmk compile ...) */
#define ENABLE_COMPILE_KEYCODE

/* Enable RGB Matrix Configuration in VIA */
#define VIA_QMK_RGB_MATRIX_ENABLE

// I2C QMK driver def
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP20
#define I2C1_SCL_PIN GP21
