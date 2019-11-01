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

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "ledmatrix.h"

/* Each driver needs to define a struct:
 *
 *    const led_matrix_driver_t led_matrix_driver;
 *
 * All members must be provided. Keyboard custom drivers must define this
 * in their own files.
 */

#if defined(IS31FL3731) || defined(IS31FL3733)

#    if defined(IS31FL3731)
#        include "is31fl3731-simple.h"
#    endif

#    include "i2c_master.h"
#endif

#ifdef LED_MATRIX_PINMATRIX_ENABLE
#    include "led_matrix_pinmatrix.h"
#endif

#ifdef LED_MATRIX_PINS_ENABLE
#    include "led_matrix_pins.h"
#endif

static void init(void) {
#if defined(IS31FL3731) || defined(IS31FL3733)
    i2c_init();

#    ifdef IS31FL3731
#        ifdef LED_DRIVER_ADDR_1
    IS31FL3731_init(LED_DRIVER_ADDR_1);
#    endif
#        ifdef LED_DRIVER_ADDR_2
    IS31FL3731_init(LED_DRIVER_ADDR_2);
#        endif
#        ifdef LED_DRIVER_ADDR_3
    IS31FL3731_init(LED_DRIVER_ADDR_3);
#        endif
#        ifdef LED_DRIVER_ADDR_4
    IS31FL3731_init(LED_DRIVER_ADDR_4);
#        endif
#    else
#        ifdef LED_DRIVER_ADDR_1
    IS31FL3733_init(LED_DRIVER_ADDR_1, 0);
#        endif
#        ifdef LED_DRIVER_ADDR_2
    IS31FL3733_init(LED_DRIVER_ADDR_2, 0);
#        endif
#        ifdef LED_DRIVER_ADDR_3
    IS31FL3733_init(LED_DRIVER_ADDR_3, 0);
#        endif
#        ifdef LED_DRIVER_ADDR_4
    IS31FL3733_init(LED_DRIVER_ADDR_4, 0);
#        endif
#    endif

    for (int index = 0; index < LED_DRIVER_LED_COUNT; index++) {
#    ifdef IS31FL3731
        IS31FL3731_set_led_control_register(index, true);
#    endif
#    ifdef IS31FL3733
        IS31FL3733_set_led_control_register(index, true);
#    endif
    }

    // This actually updates the LED drivers
#    ifdef IS31FL3731
#        ifdef LED_DRIVER_ADDR_1
    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_1, 0);
#        endif
#        ifdef LED_DRIVER_ADDR_2
    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_2, 1);
#        endif
#        ifdef LED_DRIVER_ADDR_3
    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_3, 2);
#        endif
#        ifdef LED_DRIVER_ADDR_4
    IS31FL3731_update_led_control_registers(LED_DRIVER_ADDR_4, 3);
#        endif
#    else
#        ifdef LED_DRIVER_ADDR_1
    IS31FL3733_update_led_control_registers(LED_DRIVER_ADDR_1, 0);
#        endif
#        ifdef LED_DRIVER_ADDR_2
    IS31FL3733_update_led_control_registers(LED_DRIVER_ADDR_2, 1);
#        endif
#        ifdef LED_DRIVER_ADDR_3
    IS31FL3733_update_led_control_registers(LED_DRIVER_ADDR_3, 2);
#        endif
#        ifdef LED_DRIVER_ADDR_4
    IS31FL3733_update_led_control_registers(LED_DRIVER_ADDR_4, 3);
#        endif
#    endif
#endif

#ifdef LED_MATRIX_PINMATRIX_ENABLE
    led_matrix_pinmatrix_init_pins();
#endif

#ifdef LED_MATRIX_PINS_ENABLE
    led_matrix_pins_init_pins();
#endif
}

static void flush(void) {
#ifdef IS31FL3731
#    ifdef LED_DRIVER_ADDR_1
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_1, 0);
#    endif
#    ifdef LED_DRIVER_ADDR_2
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_2, 1);
#    endif
#    ifdef LED_DRIVER_ADDR_3
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_3, 2);
#    endif
#    ifdef LED_DRIVER_ADDR_4
    IS31FL3731_update_pwm_buffers(LED_DRIVER_ADDR_4, 3);
#    endif
#endif
#ifdef IS31FL3733
#    ifdef LED_DRIVER_ADDR_1
    IS31FL3733_update_pwm_buffers(LED_DRIVER_ADDR_1, 0);
#    endif
#    ifdef LED_DRIVER_ADDR_2
    IS31FL3733_update_pwm_buffers(LED_DRIVER_ADDR_2, 1);
#    endif
#    ifdef LED_DRIVER_ADDR_3
    IS31FL3733_update_pwm_buffers(LED_DRIVER_ADDR_3, 2);
#    endif
#    ifdef LED_DRIVER_ADDR_4
    IS31FL3733_update_pwm_buffers(LED_DRIVER_ADDR_4, 3);
#    endif
#endif

#ifdef LED_MATRIX_PINMATRIX_ENABLE
    led_matrix_pinmatrix_flush();
#endif

#ifdef LED_MATRIX_PINS_ENABLE
    led_matrix_pins_flush();
#endif
}

const led_matrix_driver_t led_matrix_driver = {
    .init  = init,
    .flush = flush,
#ifdef IS31FL3731
    .set_value     = IS31FL3731_set_value,
    .set_value_all = IS31FL3731_set_value_all,
#endif
#ifdef IS31FL3133
    .set_value = IS31FL3733_set_value,
    .set_value_all = IS31FL3733_set_value_all,
#endif
#ifdef LED_MATRIX_PINMATRIX_ENABLE
    .set_value = led_matrix_pinmatrix_set_value,
    .set_value_all = led_matrix_pinmatrix_set_value_all,
#endif
#ifdef LED_MATRIX_PINS_ENABLE
    .set_value = led_matrix_pins_set_value,
    .set_value_all = led_matrix_pins_set_value_all,
#endif
};
