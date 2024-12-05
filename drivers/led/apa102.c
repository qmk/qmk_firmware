/* Copyright 2020 Aldehir Rojas
 * Copyright 2017 Mikkel (Duckle29)
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

#include "apa102.h"
#include "gpio.h"

#ifndef APA102_NOPS
#    if defined(__AVR__)
#        define APA102_NOPS 0 // AVR at 16 MHz already spends 62.5 ns per clock, so no extra delay is needed
#    elif defined(PROTOCOL_CHIBIOS)
#        include "hal.h"
#        include "chibios_config.h"
#        if defined(STM32F0XX) || defined(STM32F1XX) || defined(STM32F3XX) || defined(STM32F4XX) || defined(STM32L0XX) || defined(GD32VF103) || defined(MCU_RP)
#            define APA102_NOPS (100 / (1000000000L / (CPU_CLOCK / 4))) // This calculates how many loops of 4 nops to run to delay 100 ns
#        else
#            error APA102_NOPS configuration required
#            define APA102_NOPS 0 // this just pleases the compile so the above error is easier to spot
#        endif
#    endif
#endif

#define io_wait                                 \
    do {                                        \
        for (int i = 0; i < APA102_NOPS; i++) { \
            __asm__ volatile("nop\n\t"          \
                             "nop\n\t"          \
                             "nop\n\t"          \
                             "nop\n\t");        \
        }                                       \
    } while (0)

#define APA102_SEND_BIT(byte, bit)                        \
    do {                                                  \
        gpio_write_pin(APA102_DI_PIN, (byte >> bit) & 1); \
        io_wait;                                          \
        gpio_write_pin_high(APA102_CI_PIN);               \
        io_wait;                                          \
        gpio_write_pin_low(APA102_CI_PIN);                \
        io_wait;                                          \
    } while (0)

rgb_t   apa102_leds[APA102_LED_COUNT];
uint8_t apa102_led_brightness = APA102_DEFAULT_BRIGHTNESS;

static void apa102_send_byte(uint8_t byte) {
    APA102_SEND_BIT(byte, 7);
    APA102_SEND_BIT(byte, 6);
    APA102_SEND_BIT(byte, 5);
    APA102_SEND_BIT(byte, 4);
    APA102_SEND_BIT(byte, 3);
    APA102_SEND_BIT(byte, 2);
    APA102_SEND_BIT(byte, 1);
    APA102_SEND_BIT(byte, 0);
}

static void apa102_start_frame(void) {
    gpio_write_pin_low(APA102_DI_PIN);
    gpio_write_pin_low(APA102_CI_PIN);

    for (uint16_t i = 0; i < 4; i++) {
        apa102_send_byte(0);
    }
}

static void apa102_end_frame(uint16_t num_leds) {
    // This function has been taken from: https://github.com/pololu/apa102-arduino/blob/master/APA102.h
    // and adapted. The code is MIT licensed. I think thats compatible?
    //
    // The data stream seen by the last LED in the chain will be delayed by
    // (count - 1) clock edges, because each LED before it inverts the clock
    // line and delays the data by one clock edge.  Therefore, to make sure
    // the last LED actually receives the data we wrote, the number of extra
    // edges we send at the end of the frame must be at least (count - 1).
    //
    // Assuming we only want to send these edges in groups of size K, the
    // C/C++ expression for the minimum number of groups to send is:
    //
    //   ((count - 1) + (K - 1)) / K
    //
    // The C/C++ expression above is just (count - 1) divided by K,
    // rounded up to the nearest whole number if there is a remainder.
    //
    // We set K to 16 and use the formula above as the number of frame-end
    // bytes to transfer.  Each byte has 16 clock edges.
    //
    // We are ignoring the specification for the end frame in the APA102
    // datasheet, which says to send 0xFF four times, because it does not work
    // when you have 66 LEDs or more, and also it results in unwanted white
    // pixels if you try to update fewer LEDs than are on your LED strip.
    uint16_t iterations = (num_leds + 14) / 16;
    for (uint16_t i = 0; i < iterations; i++) {
        apa102_send_byte(0);
    }

    gpio_write_pin_low(APA102_DI_PIN);
    gpio_write_pin_low(APA102_CI_PIN);
}

static void apa102_send_frame(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
    apa102_send_byte(0b11100000 | brightness);
    apa102_send_byte(blue);
    apa102_send_byte(green);
    apa102_send_byte(red);
}

void apa102_init(void) {
    gpio_set_pin_output(APA102_DI_PIN);
    gpio_set_pin_output(APA102_CI_PIN);
}

void apa102_set_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
    apa102_leds[index].r = red;
    apa102_leds[index].g = green;
    apa102_leds[index].b = blue;
}

void apa102_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint16_t i = 0; i < APA102_LED_COUNT; i++) {
        apa102_set_color(i, red, green, blue);
    }
}

void apa102_flush(void) {
    apa102_start_frame();
    for (uint8_t i = 0; i < APA102_LED_COUNT; i++) {
        apa102_send_frame(apa102_leds[i].r, apa102_leds[i].g, apa102_leds[i].b, apa102_led_brightness);
    }
    apa102_end_frame(APA102_LED_COUNT);
}

void apa102_set_brightness(uint8_t brightness) {
    if (brightness > APA102_MAX_BRIGHTNESS) {
        apa102_led_brightness = APA102_MAX_BRIGHTNESS;
    } else if (brightness < 0) {
        apa102_led_brightness = 0;
    } else {
        apa102_led_brightness = brightness;
    }
}
