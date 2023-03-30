/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/gpio.h"
#include "hardware/sync.h"

#include "hardware/structs/iobank0.h"
#include "hardware/irq.h"

#if LIB_PICO_BINARY_INFO
#include "pico/binary_info.h"
#endif

static gpio_irq_callback_t callbacks[NUM_CORES];
// a 1 bit means the IRQ is handled by a raw IRQ handler
static uint32_t raw_irq_mask[NUM_CORES];

// Get the raw value from the pin, bypassing any muxing or overrides.
int gpio_get_pad(uint gpio) {
    check_gpio_param(gpio);
    hw_set_bits(&padsbank0_hw->io[gpio], PADS_BANK0_GPIO0_IE_BITS);
    return (iobank0_hw->io[gpio].status & IO_BANK0_GPIO0_STATUS_INFROMPAD_BITS)
            >> IO_BANK0_GPIO0_STATUS_INFROMPAD_LSB;
}

/// \tag::gpio_set_function[]
// Select function for this GPIO, and ensure input/output are enabled at the pad.
// This also clears the input/output/irq override bits.
void gpio_set_function(uint gpio, enum gpio_function fn) {
    check_gpio_param(gpio);
    invalid_params_if(GPIO, ((uint32_t)fn << IO_BANK0_GPIO0_CTRL_FUNCSEL_LSB) & ~IO_BANK0_GPIO0_CTRL_FUNCSEL_BITS);
    // Set input enable on, output disable off
    hw_write_masked(&padsbank0_hw->io[gpio],
                   PADS_BANK0_GPIO0_IE_BITS,
                   PADS_BANK0_GPIO0_IE_BITS | PADS_BANK0_GPIO0_OD_BITS
    );
    // Zero all fields apart from fsel; we want this IO to do what the peripheral tells it.
    // This doesn't affect e.g. pullup/pulldown, as these are in pad controls.
    iobank0_hw->io[gpio].ctrl = fn << IO_BANK0_GPIO0_CTRL_FUNCSEL_LSB;
}
/// \end::gpio_set_function[]

enum gpio_function gpio_get_function(uint gpio) {
    check_gpio_param(gpio);
    return (enum gpio_function) ((iobank0_hw->io[gpio].ctrl & IO_BANK0_GPIO0_CTRL_FUNCSEL_BITS) >> IO_BANK0_GPIO0_CTRL_FUNCSEL_LSB);
}

// Note that, on RP2040, setting both pulls enables a "bus keep" function,
// i.e. weak pull to whatever is current high/low state of GPIO.
void gpio_set_pulls(uint gpio, bool up, bool down) {
    check_gpio_param(gpio);
    hw_write_masked(
            &padsbank0_hw->io[gpio],
            (bool_to_bit(up) << PADS_BANK0_GPIO0_PUE_LSB) | (bool_to_bit(down) << PADS_BANK0_GPIO0_PDE_LSB),
            PADS_BANK0_GPIO0_PUE_BITS | PADS_BANK0_GPIO0_PDE_BITS
    );
}

// Direct override for per-GPIO IRQ signal
void gpio_set_irqover(uint gpio, uint value) {
    check_gpio_param(gpio);
    hw_write_masked(&iobank0_hw->io[gpio].ctrl,
                   value << IO_BANK0_GPIO0_CTRL_IRQOVER_LSB,
                   IO_BANK0_GPIO0_CTRL_IRQOVER_BITS
    );
}

// Direct overrides for pad controls
void gpio_set_inover(uint gpio, uint value) {
    check_gpio_param(gpio);
    hw_write_masked(&iobank0_hw->io[gpio].ctrl,
                   value << IO_BANK0_GPIO0_CTRL_INOVER_LSB,
                   IO_BANK0_GPIO0_CTRL_INOVER_BITS
    );
}

void gpio_set_outover(uint gpio, uint value) {
    check_gpio_param(gpio);
    hw_write_masked(&iobank0_hw->io[gpio].ctrl,
                   value << IO_BANK0_GPIO0_CTRL_OUTOVER_LSB,
                   IO_BANK0_GPIO0_CTRL_OUTOVER_BITS
    );
}

void gpio_set_oeover(uint gpio, uint value) {
    check_gpio_param(gpio);
    hw_write_masked(&iobank0_hw->io[gpio].ctrl,
                   value << IO_BANK0_GPIO0_CTRL_OEOVER_LSB,
                   IO_BANK0_GPIO0_CTRL_OEOVER_BITS
    );
}

void gpio_set_input_hysteresis_enabled(uint gpio, bool enabled) {
    check_gpio_param(gpio);
    if (enabled)
        hw_set_bits(&padsbank0_hw->io[gpio], PADS_BANK0_GPIO0_SCHMITT_BITS);
    else
        hw_clear_bits(&padsbank0_hw->io[gpio], PADS_BANK0_GPIO0_SCHMITT_BITS);
}


bool gpio_is_input_hysteresis_enabled(uint gpio) {
    check_gpio_param(gpio);
    return (padsbank0_hw->io[gpio] & PADS_BANK0_GPIO0_SCHMITT_BITS) != 0;
}

void gpio_set_slew_rate(uint gpio, enum gpio_slew_rate slew) {
    check_gpio_param(gpio);
    hw_write_masked(&padsbank0_hw->io[gpio],
                    (uint)slew << PADS_BANK0_GPIO0_SLEWFAST_LSB,
                    PADS_BANK0_GPIO0_SLEWFAST_BITS
    );
}

enum gpio_slew_rate gpio_get_slew_rate(uint gpio) {
    check_gpio_param(gpio);
    return (enum gpio_slew_rate)((padsbank0_hw->io[gpio]
            & PADS_BANK0_GPIO0_SLEWFAST_BITS)
            >> PADS_BANK0_GPIO0_SLEWFAST_LSB);
}


// Enum encoding should match hardware encoding on RP2040
static_assert(PADS_BANK0_GPIO0_DRIVE_VALUE_8MA == GPIO_DRIVE_STRENGTH_8MA, "");
void gpio_set_drive_strength(uint gpio, enum gpio_drive_strength drive) {
    check_gpio_param(gpio);
    hw_write_masked(&padsbank0_hw->io[gpio],
                    (uint)drive << PADS_BANK0_GPIO0_DRIVE_LSB,
                    PADS_BANK0_GPIO0_DRIVE_BITS
    );
}

enum gpio_drive_strength gpio_get_drive_strength(uint gpio) {
    check_gpio_param(gpio);
    return (enum gpio_drive_strength)((padsbank0_hw->io[gpio]
            & PADS_BANK0_GPIO0_DRIVE_BITS)
            >> PADS_BANK0_GPIO0_DRIVE_LSB);
}

static void gpio_default_irq_handler(void) {
    uint core = get_core_num();
    gpio_irq_callback_t callback = callbacks[core];
    io_irq_ctrl_hw_t *irq_ctrl_base = core ? &iobank0_hw->proc1_irq_ctrl : &iobank0_hw->proc0_irq_ctrl;
    for (uint gpio = 0; gpio < NUM_BANK0_GPIOS; gpio+=8) {
        uint32_t events8 = irq_ctrl_base->ints[gpio >> 3u];
        // note we assume events8 is 0 for non-existent GPIO
        for(uint i=gpio;events8 && i<gpio+8;i++) {
            uint32_t events = events8 & 0xfu;
            if (events && !(raw_irq_mask[core] & (1u << i))) {
                gpio_acknowledge_irq(i, events);
                if (callback) {
                    callback(i, events);
                }
            }
            events8 >>= 4;
        }
    }
}

static void _gpio_set_irq_enabled(uint gpio, uint32_t events, bool enabled, io_irq_ctrl_hw_t *irq_ctrl_base) {
    // Clear stale events which might cause immediate spurious handler entry
    gpio_acknowledge_irq(gpio, events);

    io_rw_32 *en_reg = &irq_ctrl_base->inte[gpio / 8];
    events <<= 4 * (gpio % 8);

    if (enabled)
        hw_set_bits(en_reg, events);
    else
        hw_clear_bits(en_reg, events);
}

void gpio_set_irq_enabled(uint gpio, uint32_t events, bool enabled) {
    // Separate mask/force/status per-core, so check which core called, and
    // set the relevant IRQ controls.
    io_irq_ctrl_hw_t *irq_ctrl_base = get_core_num() ?
                                           &iobank0_hw->proc1_irq_ctrl : &iobank0_hw->proc0_irq_ctrl;
    _gpio_set_irq_enabled(gpio, events, enabled, irq_ctrl_base);
}

void gpio_set_irq_enabled_with_callback(uint gpio, uint32_t events, bool enabled, gpio_irq_callback_t callback) {
    gpio_set_irq_enabled(gpio, events, enabled);
    gpio_set_irq_callback(callback);
    if (enabled) irq_set_enabled(IO_IRQ_BANK0, true);
}

void gpio_set_irq_callback(gpio_irq_callback_t callback) {
    uint core = get_core_num();
    if (callbacks[core]) {
        if (!callback) {
            irq_remove_handler(IO_IRQ_BANK0, gpio_default_irq_handler);
        }
        callbacks[core] = callback;
    } else if (callback) {
        callbacks[core] = callback;
        irq_add_shared_handler(IO_IRQ_BANK0, gpio_default_irq_handler, GPIO_IRQ_CALLBACK_ORDER_PRIORITY);
    }
}

void gpio_add_raw_irq_handler_with_order_priority_masked(uint gpio_mask, irq_handler_t handler, uint8_t order_priority) {
    hard_assert(!(raw_irq_mask[get_core_num()] & gpio_mask)); // should not add multiple handlers for the same event
    raw_irq_mask[get_core_num()] |= gpio_mask;
    irq_add_shared_handler(IO_IRQ_BANK0, handler, order_priority);
}

void gpio_add_raw_irq_handler_masked(uint gpio_mask, irq_handler_t handler) {
    gpio_add_raw_irq_handler_with_order_priority_masked(gpio_mask, handler, GPIO_RAW_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
}

void gpio_remove_raw_irq_handler_masked(uint gpio_mask, irq_handler_t handler) {
    assert(raw_irq_mask[get_core_num()] & gpio_mask); // should not remove handlers that are not added
    irq_remove_handler(IO_IRQ_BANK0, handler);
    raw_irq_mask[get_core_num()] &= ~gpio_mask;
}

void gpio_set_dormant_irq_enabled(uint gpio, uint32_t events, bool enabled) {
    check_gpio_param(gpio);
    io_irq_ctrl_hw_t *irq_ctrl_base = &iobank0_hw->dormant_wake_irq_ctrl;
    _gpio_set_irq_enabled(gpio, events, enabled, irq_ctrl_base);
}

void gpio_acknowledge_irq(uint gpio, uint32_t events) {
    check_gpio_param(gpio);
    iobank0_hw->intr[gpio / 8] = events << (4 * (gpio % 8));
}

#define DEBUG_PIN_MASK (((1u << PICO_DEBUG_PIN_COUNT)-1) << PICO_DEBUG_PIN_BASE)
void gpio_debug_pins_init() {
    gpio_init_mask(DEBUG_PIN_MASK);
    gpio_set_dir_masked(DEBUG_PIN_MASK, DEBUG_PIN_MASK);
#if LIB_PICO_BINARY_INFO
    bi_decl_if_func_used(bi_pin_mask_with_names(DEBUG_PIN_MASK, "Debug"));
#endif
}

void gpio_set_input_enabled(uint gpio, bool enabled) {
    if (enabled)
        hw_set_bits(&padsbank0_hw->io[gpio], PADS_BANK0_GPIO0_IE_BITS);
    else
        hw_clear_bits(&padsbank0_hw->io[gpio], PADS_BANK0_GPIO0_IE_BITS);
}

void gpio_init(uint gpio) {
    sio_hw->gpio_oe_clr = 1ul << gpio;
    sio_hw->gpio_clr = 1ul << gpio;
    gpio_set_function(gpio, GPIO_FUNC_SIO);
}

void gpio_deinit(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_NULL);
}

void gpio_init_mask(uint gpio_mask) {
    for(uint i=0;i<NUM_BANK0_GPIOS;i++) {
        if (gpio_mask & 1) {
            gpio_init(i);
        }
        gpio_mask >>= 1;
    }
}

