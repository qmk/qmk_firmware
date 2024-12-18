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

#include "led_matrix_drivers.h"

/* Each driver needs to define a struct:
 *
 *    const led_matrix_driver_t led_matrix_driver;
 *
 * All members must be provided. Keyboard custom drivers must define this
 * in their own files.
 */

#if defined(LED_MATRIX_IS31FL3218)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3218_init,
    .flush         = is31fl3218_update_pwm_buffers,
    .set_value     = is31fl3218_set_value,
    .set_value_all = is31fl3218_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3236)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3236_init_drivers,
    .flush         = is31fl3236_flush,
    .set_value     = is31fl3236_set_value,
    .set_value_all = is31fl3236_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3729)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3729_init_drivers,
    .flush         = is31fl3729_flush,
    .set_value     = is31fl3729_set_value,
    .set_value_all = is31fl3729_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3731)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3731_init_drivers,
    .flush         = is31fl3731_flush,
    .set_value     = is31fl3731_set_value,
    .set_value_all = is31fl3731_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3733)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3733_init_drivers,
    .flush         = is31fl3733_flush,
    .set_value     = is31fl3733_set_value,
    .set_value_all = is31fl3733_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3736)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3736_init_drivers,
    .flush         = is31fl3736_flush,
    .set_value     = is31fl3736_set_value,
    .set_value_all = is31fl3736_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3737)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3737_init_drivers,
    .flush         = is31fl3737_flush,
    .set_value     = is31fl3737_set_value,
    .set_value_all = is31fl3737_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3741)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3741_init_drivers,
    .flush         = is31fl3741_flush,
    .set_value     = is31fl3741_set_value,
    .set_value_all = is31fl3741_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3742A)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3742a_init_drivers,
    .flush         = is31fl3742a_flush,
    .set_value     = is31fl3742a_set_value,
    .set_value_all = is31fl3742a_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3743A)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3743a_init_drivers,
    .flush         = is31fl3743a_flush,
    .set_value     = is31fl3743a_set_value,
    .set_value_all = is31fl3743a_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3745)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3745_init_drivers,
    .flush         = is31fl3745_flush,
    .set_value     = is31fl3745_set_value,
    .set_value_all = is31fl3745_set_value_all,
};

#elif defined(LED_MATRIX_IS31FL3746A)
const led_matrix_driver_t led_matrix_driver = {
    .init          = is31fl3746a_init_drivers,
    .flush         = is31fl3746a_flush,
    .set_value     = is31fl3746a_set_value,
    .set_value_all = is31fl3746a_set_value_all,
};

#elif defined(LED_MATRIX_SNLED27351)
const led_matrix_driver_t led_matrix_driver = {
    .init          = snled27351_init_drivers,
    .flush         = snled27351_flush,
    .set_value     = snled27351_set_value,
    .set_value_all = snled27351_set_value_all,
};

#endif

#ifdef LED_MATRIX_DOUBLE_BUFFER

static uint8_t led_buffer[LED_MATRIX_LED_COUNT];

void led_matrix_driver_init(void) {
    led_matrix_driver.init();
}

void led_matrix_driver_flush(void) {
    for (uint16_t i = 0; i < led_matrix_LED_COUNT; i++) {
        led_matrix_driver.set_color(i, led_buffer[i]);
    }
    led_matrix_driver.flush();
}

void led_matrix_driver_set_color(int index, uint8_t value) {
    led_buffer[index] = value;
}

void led_matrix_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint16_t i = 0; i < LED_MATRIX_LED_COUNT; i++) {
        led_matrix_driver_set_color(i, red, green, blue);
    }
}

const led_matrix_driver_t led_matrix_driver_wrapper = {
    .init          = led_matrix_driver_init,
    .flush         = led_matrix_driver_flush,
    .set_color     = led_matrix_driver_set_color,
    .set_color_all = led_matrix_driver_set_color_all,
};

#endif
