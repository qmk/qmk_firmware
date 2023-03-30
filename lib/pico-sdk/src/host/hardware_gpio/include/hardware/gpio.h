/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_GPIO_H
#define _HARDWARE_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pico.h"

enum gpio_function {
    GPIO_FUNC_XIP = 0,
    GPIO_FUNC_SPI = 1,
    GPIO_FUNC_UART = 2,
    GPIO_FUNC_I2C = 3,
    GPIO_FUNC_PWM = 4,
    GPIO_FUNC_SIO = 5,
    GPIO_FUNC_PIO0 = 6,
    GPIO_FUNC_PIO1 = 7,
    GPIO_FUNC_GPCK = 8,
    GPIO_FUNC_USB = 9,
    GPIO_FUNC_NULL = 0xf,
};

enum gpio_slew_rate {
    GPIO_SLEW_RATE_SLOW = 0,  ///< Slew rate limiting enabled
    GPIO_SLEW_RATE_FAST = 1   ///< Slew rate limiting disabled
};

enum gpio_drive_strength {
    GPIO_DRIVE_STRENGTH_2MA = 0, ///< 2 mA nominal drive strength
    GPIO_DRIVE_STRENGTH_4MA = 1, ///< 4 mA nominal drive strength
    GPIO_DRIVE_STRENGTH_8MA = 2, ///< 8 mA nominal drive strength
    GPIO_DRIVE_STRENGTH_12MA = 3 ///< 12 mA nominal drive strength
};

#define GPIO_OUT 1
#define GPIO_IN 0

#define NUM_BANK0_GPIOS 30

// ----------------------------------------------------------------------------
// Pad Controls + IO Muxing
// ----------------------------------------------------------------------------
// Declarations for gpio.c

void gpio_set_function(uint gpio, enum gpio_function fn);

enum gpio_function gpio_get_function(uint gpio);

void gpio_pull_up(uint gpio);

void gpio_pull_down(uint gpio);

void gpio_disable_pulls(uint gpio);

void gpio_set_pulls(uint gpio, bool up, bool down);

void gpio_set_irqover(uint gpio, uint value);

void gpio_set_outover(uint gpio, uint value);

void gpio_set_inover(uint gpio, uint value);

void gpio_set_oeover(uint gpio, uint value);

void gpio_set_input_enabled(uint gpio, bool enable);

void gpio_set_input_hysteresis_enabled(uint gpio, bool enabled);

bool gpio_is_input_hysteresis_enabled(uint gpio);

void gpio_set_slew_rate(uint gpio, enum gpio_slew_rate slew);

enum gpio_slew_rate gpio_get_slew_rate(uint gpio);

void gpio_set_drive_strength(uint gpio, enum gpio_drive_strength drive);

enum gpio_drive_strength gpio_get_drive_strength(uint gpio);

// Configure a GPIO for direct input/output from software
void gpio_init(uint gpio);

void gpio_init_mask(uint gpio_mask);

// ----------------------------------------------------------------------------
// Input
// ----------------------------------------------------------------------------

// Get the value of a single GPIO
bool gpio_get(uint gpio);

// Get raw value of all
uint32_t gpio_get_all();

// ----------------------------------------------------------------------------
// Output
// ----------------------------------------------------------------------------

// Drive high every GPIO appearing in mask
void gpio_set_mask(uint32_t mask);

void gpio_clr_mask(uint32_t mask);

// Toggle every GPIO appearing in mask
void gpio_xor_mask(uint32_t mask);


// For each 1 bit in "mask", drive that pin to the value given by
// corresponding bit in "value", leaving other pins unchanged.
// Since this uses the TOGL alias, it is concurrency-safe with e.g. an IRQ
// bashing different pins from the same core.
void gpio_put_masked(uint32_t mask, uint32_t value);

// Drive all pins simultaneously
void gpio_put_all(uint32_t value);


// Drive a single GPIO high/low
void gpio_put(uint gpio, int value);

// ----------------------------------------------------------------------------
// Direction
// ----------------------------------------------------------------------------

// Switch all GPIOs in "mask" to output
void gpio_set_dir_out_masked(uint32_t mask);

// Switch all GPIOs in "mask" to input
void gpio_set_dir_in_masked(uint32_t mask);

// For each 1 bit in "mask", switch that pin to the direction given by
// corresponding bit in "value", leaving other pins unchanged.
// E.g. gpio_set_dir_masked(0x3, 0x2); -> set pin 0 to input, pin 1 to output,
// simultaneously.
void gpio_set_dir_masked(uint32_t mask, uint32_t value);

// Set direction of all pins simultaneously.
// For each bit in value,
// 1 = out
// 0 = in
void gpio_set_dir_all_bits(uint32_t value);

// Set a single GPIO to input/output.
// true = out
// 0 = in
void gpio_set_dir(uint gpio, bool out);

// debugging
#ifndef PICO_DEBUG_PIN_BASE
#define PICO_DEBUG_PIN_BASE 19u
#endif

// note these two macros may only be used once per compilation unit
#define CU_REGISTER_DEBUG_PINS(p, ...)
#define CU_SELECT_DEBUG_PINS(x)
#define DEBUG_PINS_ENABLED(p) false

#define DEBUG_PINS_SET(p, v) ((void)0)
#define DEBUG_PINS_CLR(p, v) ((void)0)
#define DEBUG_PINS_XOR(p, v) ((void)0)

void gpio_debug_pins_init();

#ifdef __cplusplus
}
#endif

#endif
