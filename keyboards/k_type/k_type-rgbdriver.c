/* Copyright 2021 Andrew Fahmy
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

#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix.h"
#include "i2c_master.h"
#include "is31fl3733-dual.h"



static void init(void) {
    i2c_init(&I2CD1, I2C1_SCL_PIN, I2C1_SDA_PIN);
    IS31FL3733_init(0, DRIVER_ADDR_1, 0);
#    ifdef USE_I2C2
    i2c_init(&I2CD2, I2C2_SCL_PIN, I2C2_SDA_PIN);
    IS31FL3733_init(1, DRIVER_ADDR_2, 0);
#    endif
    for (int index = 0; index < DRIVER_LED_TOTAL; index++) {
        bool enabled = true;
        // This only caches it for later
        IS31FL3733_set_led_control_register(index, enabled, enabled, enabled);
    }
    IS31FL3733_update_led_control_registers(DRIVER_ADDR_1, 0);
#    ifdef USE_I2C2
    IS31FL3733_update_led_control_registers(DRIVER_ADDR_2, 1);
#    endif
}

static void flush(void) {
    IS31FL3733_update_pwm_buffers(DRIVER_ADDR_1, 0);
#    ifdef USE_I2C2
    IS31FL3733_update_pwm_buffers(DRIVER_ADDR_2, 1);
#    endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3733_set_color,
    .set_color_all = IS31FL3733_set_color_all,
};

#endif
