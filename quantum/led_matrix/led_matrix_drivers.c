/* Copyright 2018 James Laird-Wah
 * Copyright 2019 Clueboard
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

#include "led_matrix.h"

/* Each driver needs to define a struct:
 *
 *    const led_matrix_driver_t led_matrix_driver;
 *
 * All members must be provided. Keyboard custom drivers must define this
 * in their own files.
 */

#if defined(LED_MATRIX_IS31FL3218) || defined(LED_MATRIX_IS31FL3731) || defined(LED_MATRIX_IS31FL3733) || defined(LED_MATRIX_IS31FL3736) || defined(LED_MATRIX_IS31FL3737) || defined(LED_MATRIX_IS31FL3741) || defined(IS31FLCOMMON) || defined(LED_MATRIX_SNLED27351)
#    include "i2c_master.h"

static void init(void) {
    i2c_init();

#    if defined(LED_MATRIX_IS31FL3218)
    is31fl3218_init();

#    elif defined(LED_MATRIX_IS31FL3731)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_1);
#        if defined(IS31FL3731_I2C_ADDRESS_2)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_2);
#            if defined(IS31FL3731_I2C_ADDRESS_3)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_3);
#                if defined(IS31FL3731_I2C_ADDRESS_4)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_4);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_IS31FL3733)
#        if !defined(IS31FL3733_SYNC_1)
#            define IS31FL3733_SYNC_1 0
#        endif
    is31fl3733_init(IS31FL3733_I2C_ADDRESS_1, IS31FL3733_SYNC_1);
#        if defined(IS31FL3733_I2C_ADDRESS_2)
#            if !defined(IS31FL3733_SYNC_2)
#                define IS31FL3733_SYNC_2 0
#            endif
    is31fl3733_init(IS31FL3733_I2C_ADDRESS_2, IS31FL3733_SYNC_2);
#            if defined(IS31FL3733_I2C_ADDRESS_3)
#                if !defined(IS31FL3733_SYNC_3)
#                    define IS31FL3733_SYNC_3 0
#                endif
    is31fl3733_init(IS31FL3733_I2C_ADDRESS_3, IS31FL3733_SYNC_3);
#                if defined(IS31FL3733_I2C_ADDRESS_4)
#                    if !defined(IS31FL3733_SYNC_4)
#                        define IS31FL3733_SYNC_4 0
#                    endif
    is31fl3733_init(IS31FL3733_I2C_ADDRESS_4, IS31FL3733_SYNC_4);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_IS31FL3736)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_1);
#        if defined(IS31FL3736_I2C_ADDRESS_2)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_2);
#            if defined(IS31FL3736_I2C_ADDRESS_3)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_3);
#                if defined(IS31FL3736_I2C_ADDRESS_4)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_4);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_IS31FL3737)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_1);
#        if defined(IS31FL3737_I2C_ADDRESS_2)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_2);
#            if defined(IS31FL3737_I2C_ADDRESS_3)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_3);
#                if defined(IS31FL3737_I2C_ADDRESS_4)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_4);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_IS31FL3741)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_1);
#        if defined(IS31FL3741_I2C_ADDRESS_2)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_2);
#            if defined(IS31FL3741_I2C_ADDRESS_3)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_3);
#                if defined(IS31FL3741_I2C_ADDRESS_4)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_4);
#                endif
#            endif
#        endif

#    elif defined(IS31FLCOMMON)
    IS31FL_common_init(DRIVER_ADDR_1, ISSI_SSR_1);
#        if defined(LED_DRIVER_ADDR_2)
    IS31FL_common_init(DRIVER_ADDR_2, ISSI_SSR_2);
#            if defined(LED_DRIVER_ADDR_3)
    IS31FL_common_init(DRIVER_ADDR_3, ISSI_SSR_3);
#                if defined(LED_DRIVER_ADDR_4)
    IS31FL_common_init(DRIVER_ADDR_4, ISSI_SSR_4);
#                endif
#            endif
#        endif
#    elif defined(LED_MATRIX_SNLED27351)
#        if defined(LED_DRIVER_SHUTDOWN_PIN)
    setPinOutput(LED_DRIVER_SHUTDOWN_PIN);
    writePinHigh(LED_DRIVER_SHUTDOWN_PIN);
#        endif

    snled27351_init(SNLED27351_I2C_ADDRESS_1);
#        if defined(SNLED27351_I2C_ADDRESS_2)
    snled27351_init(SNLED27351_I2C_ADDRESS_2);
#            if defined(SNLED27351_I2C_ADDRESS_3)
    snled27351_init(SNLED27351_I2C_ADDRESS_3);
#                if defined(SNLED27351_I2C_ADDRESS_4)
    snled27351_init(SNLED27351_I2C_ADDRESS_4);
#                endif
#            endif
#        endif
#    endif

    for (int index = 0; index < LED_MATRIX_LED_COUNT; index++) {
#    if defined(LED_MATRIX_IS31FL3218)
        is31fl3218_set_led_control_register(index, true);
#    elif defined(LED_MATRIX_IS31FL3731)
        is31fl3731_set_led_control_register(index, true);
#    elif defined(LED_MATRIX_IS31FL3733)
        is31fl3733_set_led_control_register(index, true);
#    elif defined(LED_MATRIX_IS31FL3736)
        is31fl3736_set_led_control_register(index, true);
#    elif defined(LED_MATRIX_IS31FL3737)
        is31fl3737_set_led_control_register(index, true);
#    elif defined(LED_MATRIX_IS31FL3741)
        is31fl3741_set_led_control_register(index, true);
#    elif defined(IS31FLCOMMON)
        IS31FL_simple_set_scaling_buffer(index, true);
#    elif defined(LED_MATRIX_SNLED27351)
        snled27351_set_led_control_register(index, true);
#    endif
    }

// This actually updates the LED drivers
#    if defined(LED_MATRIX_IS31FL3218)
    is31fl3218_update_led_control_registers();

#    elif defined(LED_MATRIX_IS31FL3731)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3731_I2C_ADDRESS_2)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3731_I2C_ADDRESS_3)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3731_I2C_ADDRESS_4)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_IS31FL3733)
    is31fl3733_update_led_control_registers(IS31FL3733_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3733_I2C_ADDRESS_2)
    is31fl3733_update_led_control_registers(IS31FL3733_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3733_I2C_ADDRESS_3)
    is31fl3733_update_led_control_registers(IS31FL3733_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3733_I2C_ADDRESS_4)
    is31fl3733_update_led_control_registers(IS31FL3733_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_IS31FL3736)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3736_I2C_ADDRESS_2)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3736_I2C_ADDRESS_3)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3736_I2C_ADDRESS_4)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_IS31FL3737)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3737_I2C_ADDRESS_2)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3737_I2C_ADDRESS_3)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3737_I2C_ADDRESS_4)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_IS31FL3741)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3741_I2C_ADDRESS_2)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3741_I2C_ADDRESS_3)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3741_I2C_ADDRESS_4)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(IS31FLCOMMON)
#        ifdef ISSI_MANUAL_SCALING
    IS31FL_set_manual_scaling_buffer();
#        endif
    IS31FL_common_update_scaling_register(DRIVER_ADDR_1, 0);
#        if defined(LED_DRIVER_ADDR_2)
    IS31FL_common_update_scaling_register(DRIVER_ADDR_2, 1);
#            if defined(LED_DRIVER_ADDR_3)
    IS31FL_common_update_scaling_register(DRIVER_ADDR_3, 2);
#                if defined(LED_DRIVER_ADDR_4)
    IS31FL_common_update_scaling_register(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif

#    elif defined(LED_MATRIX_SNLED27351)
    snled27351_update_led_control_registers(SNLED27351_I2C_ADDRESS_1, 0);
#        if defined(SNLED27351_I2C_ADDRESS_2)
    snled27351_update_led_control_registers(SNLED27351_I2C_ADDRESS_2, 1);
#            if defined(SNLED27351_I2C_ADDRESS_3)
    snled27351_update_led_control_registers(SNLED27351_I2C_ADDRESS_3, 2);
#                if defined(SNLED27351_I2C_ADDRESS_4)
    snled27351_update_led_control_registers(SNLED27351_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif
#    endif
}

#    if defined(LED_MATRIX_IS31FL3218)
const led_matrix_driver_t led_matrix_driver = {
    .init          = init,
    .flush         = is31fl3218_update_pwm_buffers,
    .set_value     = is31fl3218_set_value,
    .set_value_all = is31fl3218_set_value_all,
};

#    elif defined(LED_MATRIX_IS31FL3731)
const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = is31fl3731_flush,
    .set_value = is31fl3731_set_value,
    .set_value_all = is31fl3731_set_value_all,
};

#    elif defined(LED_MATRIX_IS31FL3733)
const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = is31fl3733_flush,
    .set_value = is31fl3733_set_value,
    .set_value_all = is31fl3733_set_value_all,
};

#    elif defined(LED_MATRIX_IS31FL3736)
const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = is31fl3736_flush,
    .set_value = is31fl3736_set_value,
    .set_value_all = is31fl3736_set_value_all,
};

#    elif defined(LED_MATRIX_IS31FL3737)
const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = is31fl3737_flush,
    .set_value = is31fl3737_set_value,
    .set_value_all = is31fl3737_set_value_all,
};

#    elif defined(LED_MATRIX_IS31FL3741)
const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = is31fl3741_flush,
    .set_value = is31fl3741_set_value,
    .set_value_all = is31fl3741_set_value_all,
};

#    elif defined(IS31FLCOMMON)
const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = IS31FL_common_flush,
    .set_value = IS31FL_simple_set_brightness,
    .set_value_all = IS31FL_simple_set_brigntness_all,
};
#    elif defined(LED_MATRIX_SNLED27351)
const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = snled27351_flush,
    .set_value = snled27351_set_value,
    .set_value_all = snled27351_set_value_all,
};
#    endif
#endif
