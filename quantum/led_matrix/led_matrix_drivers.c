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

#if defined(IS31FL3731) || defined(IS31FL3733) || defined(IS31FLCOMMON) || defined(CKLED2001)
#    include "i2c_master.h"

static void init(void) {
    i2c_init();

#    if defined(IS31FL3731)
    IS31FL3731_init(LED_DRIVER_ADDR_1);
#        if defined(LED_DRIVER_ADDR_2)
    IS31FL3731_init(LED_DRIVER_ADDR_2);
#            if defined(LED_DRIVER_ADDR_3)
    IS31FL3731_init(LED_DRIVER_ADDR_3);
#                if defined(LED_DRIVER_ADDR_4)
    IS31FL3731_init(LED_DRIVER_ADDR_4);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3733)
#        if !defined(LED_DRIVER_SYNC_1)
#            define LED_DRIVER_SYNC_1 0
#        endif
    IS31FL3733_init(LED_DRIVER_ADDR_1, LED_DRIVER_SYNC_1);
#        if defined(LED_DRIVER_ADDR_2)
#            if !defined(LED_DRIVER_SYNC_2)
#                define LED_DRIVER_SYNC_2 0
#            endif
    IS31FL3733_init(LED_DRIVER_ADDR_2, LED_DRIVER_SYNC_2);
#            if defined(LED_DRIVER_ADDR_3)
#                if !defined(LED_DRIVER_SYNC_3)
#                    define LED_DRIVER_SYNC_3 0
#                endif
    IS31FL3733_init(LED_DRIVER_ADDR_3, LED_DRIVER_SYNC_3);
#                if defined(LED_DRIVER_ADDR_4)
#                    if !defined(LED_DRIVER_SYNC_4)
#                        define LED_DRIVER_SYNC_4 0
#                    endif
    IS31FL3733_init(LED_DRIVER_ADDR_4, LED_DRIVER_SYNC_4);
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
#    elif defined(CKLED2001)
#        if defined(LED_DRIVER_SHUTDOWN_PIN)
    setPinOutput(LED_DRIVER_SHUTDOWN_PIN);
    writePinHigh(LED_DRIVER_SHUTDOWN_PIN);
#        endif

    CKLED2001_init(DRIVER_ADDR_1);
#        if defined(DRIVER_ADDR_2)
    CKLED2001_init(DRIVER_ADDR_2);
#            if defined(DRIVER_ADDR_3)
    CKLED2001_init(DRIVER_ADDR_3);
#                if defined(DRIVER_ADDR_4)
    CKLED2001_init(DRIVER_ADDR_4);
#                endif
#            endif
#        endif
#    endif

    for (int index = 0; index < DRIVER_LED_TOTAL; index++) {
#    if defined(IS31FL3731)
        IS31FL3731_set_led_control_register(index, true);
#    elif defined(IS31FL3733)
        IS31FL3733_set_led_control_register(index, true);
#    elif defined(IS31FLCOMMON)
        IS31FL_simple_set_scaling_buffer(index, true);
#    elif defined(CKLED2001)
        CKLED2001_set_led_control_register(index, true);
#    endif
    }

// This actually updates the LED drivers
#    if defined(IS31FL3731)
    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_1, 0);
#        if defined(LED_DRIVER_ADDR_2)
    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_2, 1);
#            if defined(LED_DRIVER_ADDR_3)
    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_3, 2);
#                if defined(LED_DRIVER_ADDR_4)
    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3733)
    IS31FL3733_update_led_control_registers(LED_DRIVER_ADDR_1, 0);
#        if defined(LED_DRIVER_ADDR_2)
    IS31FL3733_update_led_control_registers(LED_DRIVER_ADDR_2, 1);
#            if defined(LED_DRIVER_ADDR_3)
    IS31FL3733_update_led_control_registers(LED_DRIVER_ADDR_3, 2);
#                if defined(LED_DRIVER_ADDR_4)
    IS31FL3733_update_led_control_registers(LED_DRIVER_ADDR_4, 3);
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
#    elif defined(CKLED2001)
    CKLED2001_update_led_control_registers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    CKLED2001_update_led_control_registers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    CKLED2001_update_led_control_registers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    CKLED2001_update_led_control_registers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
#    endif
}

#    if defined(IS31FL3731)
static void flush(void) {
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_1, 0);
#        if defined(LED_DRIVER_ADDR_2)
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_2, 1);
#            if defined(LED_DRIVER_ADDR_3)
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_3, 2);
#                if defined(LED_DRIVER_ADDR_4)
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const led_matrix_driver_t led_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_value     = IS31FL3731_set_value,
    .set_value_all = IS31FL3731_set_value_all,
};

#    elif defined(IS31FL3733)
static void flush(void) {
    IS31FL3733_update_pwm_buffers(LED_DRIVER_ADDR_1, 0);
#        if defined(LED_DRIVER_ADDR_2)
    IS31FL3733_update_pwm_buffers(LED_DRIVER_ADDR_2, 1);
#            if defined(LED_DRIVER_ADDR_3)
    IS31FL3733_update_pwm_buffers(LED_DRIVER_ADDR_3, 2);
#                if defined(LED_DRIVER_ADDR_4)
    IS31FL3733_update_pwm_buffers(LED_DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_value = IS31FL3733_set_value,
    .set_value_all = IS31FL3733_set_value_all,
};

#    elif defined(IS31FLCOMMON)
static void flush(void) {
    IS31FL_common_update_pwm_register(DRIVER_ADDR_1, 0);
#        if defined(LED_DRIVER_ADDR_2)
    IS31FL_common_update_pwm_register(DRIVER_ADDR_2, 1);
#            if defined(LED_DRIVER_ADDR_3)
    IS31FL_common_update_pwm_register(DRIVER_ADDR_3, 2);
#                if defined(LED_DRIVER_ADDR_4)
    IS31FL_common_update_pwm_register(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_value = IS31FL_simple_set_brightness,
    .set_value_all = IS31FL_simple_set_brigntness_all,
};
#    elif defined(CKLED2001)
static void flush(void) {
    CKLED2001_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    CKLED2001_update_pwm_buffers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    CKLED2001_update_pwm_buffers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    CKLED2001_update_pwm_buffers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_value = CKLED2001_set_value,
    .set_value_all = CKLED2001_set_value_all,
};
#    endif
#endif
