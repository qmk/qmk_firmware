/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "gpio_api.h"
#include "wait_api.h"
#include "toolchain.h"
#include "mbed_interface.h"

WEAK void mbed_die(void) {
#ifndef NRF51_H
	__disable_irq();	// dont allow interrupts to disturb the flash pattern
#endif
#if   (DEVICE_ERROR_RED == 1)
    gpio_t led_red; gpio_init_out(&led_red, LED_RED);
#elif (DEVICE_ERROR_PATTERN == 1)
    gpio_t led_1; gpio_init_out(&led_1, LED1);
    gpio_t led_2; gpio_init_out(&led_2, LED2);
    gpio_t led_3; gpio_init_out(&led_3, LED3);
    gpio_t led_4; gpio_init_out(&led_4, LED4);
#endif

    while (1) {
#if   (DEVICE_ERROR_RED == 1)
        gpio_write(&led_red, 1);

#elif (DEVICE_ERROR_PATTERN == 1)
        gpio_write(&led_1, 1);
        gpio_write(&led_2, 0);
        gpio_write(&led_3, 0);
        gpio_write(&led_4, 1);
#endif

        wait_ms(150);

#if   (DEVICE_ERROR_RED == 1)
        gpio_write(&led_red, 0);

#elif (DEVICE_ERROR_PATTERN == 1)
        gpio_write(&led_1, 0);
        gpio_write(&led_2, 1);
        gpio_write(&led_3, 1);
        gpio_write(&led_4, 0);
#endif

        wait_ms(150);
    }
}
