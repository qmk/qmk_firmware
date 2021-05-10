/* Copyright 2020 Yang Hu
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
#include "unicorne.h"

void matrix_init_kb(void) { matrix_init_user(); }

void matrix_scan_kb(void) { matrix_scan_user(); }

// Custom i2c init to enable internal pull up resistor for i2c.
void i2c_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_INPUT);
        palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_INPUT);

        chThdSleepMilliseconds(10);
#if defined(USE_GPIOV1)
        palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, I2C1_SCL_PAL_MODE);
        palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, I2C1_SDA_PAL_MODE);
#else
        palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
        palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
#endif
    }
}
