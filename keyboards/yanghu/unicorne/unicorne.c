/* Copyright 2021 Yang Hu
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
        // Use internal pull up since we do not have pull up on i2c pins in v1 design.
        palSetPadMode(I2C1_SCL_BANK, I2C1_SCL, PAL_MODE_ALTERNATE(I2C1_SCL_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
        palSetPadMode(I2C1_SDA_BANK, I2C1_SDA, PAL_MODE_ALTERNATE(I2C1_SDA_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP);
#endif
    }
}

// LED matrix
// physical location
// 2      3   4       5
//
// 1                  6
//        0   7
#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = {{
    // Key Matrix to LED Index
    // Since we only have 8 LEDs, map the keys near them to the same LED.
    {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5},
    {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5},
    {1, 1, 1, 0, 0, 0, 7, 7, 7, 6, 6, 6},
    {NO_LED, NO_LED, NO_LED, 0, 0, 0, 7, 7, 7, NO_LED, NO_LED, NO_LED},
}, {// LED Index to Physical Position
  {94, 60},
  {18, 44},
  {8, 10},
  {94, 10},
  {130,10},
  {216, 10},
  {208, 44},
  {130, 60}
}, {// LED Index to Flag
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, 
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
}};
// clang-format on
#endif
