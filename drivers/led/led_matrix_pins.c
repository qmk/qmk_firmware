/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
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

#ifdef __AVR__
#    include <avr/interrupt.h>
#    include <avr/io.h>
#    include <util/delay.h>
#    define led_wait_us(us) wait_us(us)
#else
#    include "ch.h"
#    include "hal.h"
#    define led_wait_us(us) chSysPolledDelayX(US2RTC(STM32_SYSCLK, us))
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "led_matrix_pins.h"
#include "led_tables.h"
#include "progmem.h"
#include "quantum.h"
#include "backlight.h"


/*
 * g_pwm_buffer is an array that represents the duty cycle (0-255) for each LED.
 */
uint8_t g_pwm_buffer[LED_DRIVER_LED_COUNT];
const pin_t led_pins[LED_DRIVER_LED_COUNT] = LED_MATRIX_PINS;

#ifdef LED_MATRIX_PIN_SINK
#    define led_pin_on(pin) writePinLow(pin)
#    define led_pin_off(pin) writePinHigh(pin)
#else
#    define led_pin_on(pin) writePinHigh(pin)
#    define led_pin_off(pin) writePinLow(pin)
#endif

void led_matrix_pins_init_pins(void) {
    /* Set all pins to output, we are not interested in reading any information.
     */
    for (uint8_t x = 0; x < LED_DRIVER_LED_COUNT; x++) {
        setPinOutput(led_pins[x]);
        led_pin_off(led_pins[x]);
    }
}

void led_matrix_pins_set_value(int index, uint8_t value) {
    /* Set the brighness for a single LED.
     */
    if (index >= 0 && index < LED_DRIVER_LED_COUNT) {
        g_pwm_buffer[index] = value;
    }
}

void led_matrix_pins_set_value_all(uint8_t value) {
    /* Set the brighness for all LEDs.
     */
    for (int i = 0; i < LED_DRIVER_LED_COUNT; i++) {
        led_matrix_pins_set_value(i, value);
    }
}

void led_matrix_pins_flush(void) {
    /* This is a basic bit-banged pwm implementation.
     */
    for (uint8_t i = 0; i < LED_DRIVER_LED_COUNT; i++) {
        /* We spend ~1.3ms on each LED, dividing that time between lit and unlit.
         */
        if (g_pwm_buffer[i] > 0) {
            uint8_t brightness = pgm_read_byte(&CIE1931_CURVE[g_pwm_buffer[i]]) / 2;
            led_pin_on(led_pins[i]);
            led_wait_us(brightness);
            led_pin_off(led_pins[i]);
            led_wait_us(128 - brightness);
        } else {
            led_wait_us(128);
        }
    }
}
