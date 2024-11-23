//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "led_hc595.h"

#ifndef LED_HC595_ST_PIN
#    error hc595: no storage register clock pins defined!
#endif

#ifndef LED_HC595_SH_PIN
#    error hc595: no shift register clock pins defined!
#endif

#ifndef LED_HC595_DS
#    error hc595: no serial data input pins defined!
#endif

#define LED_CLOCK_TIME 15

static inline void gpio_set_pin_output_write_low(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void gpio_set_pin_output_write_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_high(pin);
    }
}

static inline void select_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    };
}

static inline void clockPulse(uint16_t n) {
    gpio_write_pin_high(LED_HC595_SH_PIN);
    gpio_write_pin_high(LED_HC595_ST_PIN);
    select_delay(n);
    gpio_write_pin_low(LED_HC595_SH_PIN);
    gpio_write_pin_low(LED_HC595_ST_PIN);
}

void s_serial_to_parallel(uint8_t data) __attribute__((unused));
void s_serial_to_parallel(uint8_t data) { // Serial port to parallel port function
    gpio_set_pin_output_write_low(LED_HC595_DS);
    gpio_set_pin_output_write_low(LED_HC595_SH_PIN);
    gpio_set_pin_output_write_low(LED_HC595_ST_PIN);
    for(uint8_t i = 0; i < 8; i++) {
        if(data & 0x01){
            gpio_write_pin_high(LED_HC595_DS);
        }else{
            gpio_write_pin_low(LED_HC595_DS);
        }
        clockPulse(LED_CLOCK_TIME);
        data >>= 1; // Move the data one digit to the right
    }
}

