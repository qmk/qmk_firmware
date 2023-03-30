/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_ADC_H
#define _HARDWARE_ADC_H

#include "pico.h"
#include "hardware/structs/adc.h"
#include "hardware/gpio.h"

/** \file hardware/adc.h
 *  \defgroup hardware_adc hardware_adc
 *
 * Analog to Digital Converter (ADC) API
 *
 * The RP2040 has an internal analogue-digital converter (ADC) with the following features:
 * - SAR ADC
 * - 500 kS/s (Using an independent 48MHz clock)
 * - 12 bit (8.7 ENOB)
 * - 5 input mux:
 *  - 4 inputs that are available on package pins shared with GPIO[29:26]
 *  - 1 input is dedicated to the internal temperature sensor
 * - 4 element receive sample FIFO
 * - Interrupt generation
 * - DMA interface
 *
 * Although there is only one ADC you can specify the input to it using the adc_select_input() function.
 * In round robin mode (adc_set_round_robin()), the ADC will use that input and move to the next one after a read.
 *
 * User ADC inputs are on 0-3 (GPIO 26-29), the temperature sensor is on input 4.
 *
 * Temperature sensor values can be approximated in centigrade as:
 *
 * T = 27 - (ADC_Voltage - 0.706)/0.001721
 *
 * The FIFO, if used, can contain up to 4 entries.
 *
 * \subsection adc_example Example
 * \addtogroup hardware_adc
 *
 * \include hello_adc.c
 */

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_ADC, Enable/disable assertions in the ADC module, type=bool, default=0, group=hardware_adc
#ifndef PARAM_ASSERTIONS_ENABLED_ADC
#define PARAM_ASSERTIONS_ENABLED_ADC 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief  Initialise the ADC HW
 *  \ingroup hardware_adc
 *
 */
void adc_init(void);

/*! \brief  Initialise the gpio for use as an ADC pin
 *  \ingroup hardware_adc
 *
 * Prepare a GPIO for use with ADC by disabling all digital functions.
 *
 * \param gpio The GPIO number to use. Allowable GPIO numbers are 26 to 29 inclusive.
 */
static inline void adc_gpio_init(uint gpio) {
    invalid_params_if(ADC, gpio < 26 || gpio > 29);
    // Select NULL function to make output driver hi-Z
    gpio_set_function(gpio, GPIO_FUNC_NULL);
    // Also disable digital pulls and digital receiver
    gpio_disable_pulls(gpio);
    gpio_set_input_enabled(gpio, false);
}

/*! \brief  ADC input select
 *  \ingroup hardware_adc
 *
 * Select an ADC input. 0...3 are GPIOs 26...29 respectively.
 * Input 4 is the onboard temperature sensor.
 *
 * \param input Input to select.
 */
static inline void adc_select_input(uint input) {
    valid_params_if(ADC, input < NUM_ADC_CHANNELS);
    hw_write_masked(&adc_hw->cs, input << ADC_CS_AINSEL_LSB, ADC_CS_AINSEL_BITS);
}

/*! \brief  Get the currently selected ADC input channel
 *  \ingroup hardware_adc
 *
 * \return The currently selected input channel. 0...3 are GPIOs 26...29 respectively. Input 4 is the onboard temperature sensor.
 */
static inline uint adc_get_selected_input(void) {
    return (adc_hw->cs & ADC_CS_AINSEL_BITS) >> ADC_CS_AINSEL_LSB;
}

/*! \brief  Round Robin sampling selector
 *  \ingroup hardware_adc
 *
 * This function sets which inputs are to be run through in round robin mode.
 * Value between 0 and 0x1f (bit 0 to bit 4 for GPIO 26 to 29 and temperature sensor input respectively)
 *
 * \param input_mask A bit pattern indicating which of the 5 inputs are to be sampled. Write a value of 0 to disable round robin sampling.
 */
static inline void adc_set_round_robin(uint input_mask) {
    valid_params_if(ADC, input_mask < (1 << NUM_ADC_CHANNELS));
    hw_write_masked(&adc_hw->cs, input_mask << ADC_CS_RROBIN_LSB, ADC_CS_RROBIN_BITS);
}

/*! \brief Enable the onboard temperature sensor
 *  \ingroup hardware_adc
 *
 * \param enable Set true to power on the onboard temperature sensor, false to power off.
 *
 */
static inline void adc_set_temp_sensor_enabled(bool enable) {
    if (enable)
        hw_set_bits(&adc_hw->cs, ADC_CS_TS_EN_BITS);
    else
        hw_clear_bits(&adc_hw->cs, ADC_CS_TS_EN_BITS);
}

/*! \brief Perform a single conversion
 *  \ingroup hardware_adc
 *
 *  Performs an ADC conversion, waits for the result, and then returns it.
 *
 * \return Result of the conversion.
 */
static inline uint16_t adc_read(void) {
    hw_set_bits(&adc_hw->cs, ADC_CS_START_ONCE_BITS);

    while (!(adc_hw->cs & ADC_CS_READY_BITS))
        tight_loop_contents();

    return (uint16_t) adc_hw->result;
}

/*! \brief Enable or disable free-running sampling mode
 *  \ingroup hardware_adc
 *
 * \param run false to disable, true to enable free running conversion mode.
 */
static inline void adc_run(bool run) {
    if (run)
        hw_set_bits(&adc_hw->cs, ADC_CS_START_MANY_BITS);
    else
        hw_clear_bits(&adc_hw->cs, ADC_CS_START_MANY_BITS);
}

/*! \brief Set the ADC Clock divisor
 *  \ingroup hardware_adc
 *
 * Period of samples will be (1 + div) cycles on average. Note it takes 96 cycles to perform a conversion,
 * so any period less than that will be clamped to 96.
 *
 * \param clkdiv If non-zero, conversion will be started at intervals rather than back to back.
 */
static inline void adc_set_clkdiv(float clkdiv) {
    invalid_params_if(ADC, clkdiv >= 1 << (ADC_DIV_INT_MSB - ADC_DIV_INT_LSB + 1));
    adc_hw->div = (uint32_t)(clkdiv * (float) (1 << ADC_DIV_INT_LSB));
}

/*! \brief Setup the ADC FIFO
 *  \ingroup hardware_adc
 *
 * FIFO is 4 samples long, if a conversion is completed and the FIFO is full, the result is dropped.
 *
 * \param en Enables write each conversion result to the FIFO
 * \param dreq_en Enable DMA requests when FIFO contains data
 * \param dreq_thresh Threshold for DMA requests/FIFO IRQ if enabled.
 * \param err_in_fifo If enabled, bit 15 of the FIFO contains error flag for each sample
 * \param byte_shift Shift FIFO contents to be one byte in size (for byte DMA) - enables DMA to byte buffers.
 */
 static inline void adc_fifo_setup(bool en, bool dreq_en, uint16_t dreq_thresh, bool err_in_fifo, bool byte_shift) {
    hw_write_masked(&adc_hw->fcs,
                   (bool_to_bit(en) << ADC_FCS_EN_LSB) |
                   (bool_to_bit(dreq_en) << ADC_FCS_DREQ_EN_LSB) |
                   (((uint)dreq_thresh) << ADC_FCS_THRESH_LSB) |
                   (bool_to_bit(err_in_fifo) << ADC_FCS_ERR_LSB) |
                   (bool_to_bit(byte_shift) << ADC_FCS_SHIFT_LSB),
                   ADC_FCS_EN_BITS |
                   ADC_FCS_DREQ_EN_BITS |
                   ADC_FCS_THRESH_BITS |
                   ADC_FCS_ERR_BITS |
                   ADC_FCS_SHIFT_BITS
    );
}

/*! \brief Check FIFO empty state
 *  \ingroup hardware_adc
 *
 * \return Returns true if the FIFO is empty
 */
static inline bool adc_fifo_is_empty(void) {
    return !!(adc_hw->fcs & ADC_FCS_EMPTY_BITS);
}

/*! \brief Get number of entries in the ADC FIFO
 *  \ingroup hardware_adc
 *
 * The ADC FIFO is 4 entries long. This function will return how many samples are currently present.
 */
static inline uint8_t adc_fifo_get_level(void) {
    return (adc_hw->fcs & ADC_FCS_LEVEL_BITS) >> ADC_FCS_LEVEL_LSB;
}

/*! \brief Get ADC result from FIFO
 *  \ingroup hardware_adc
 *
 * Pops the latest result from the ADC FIFO.
 */
static inline uint16_t adc_fifo_get(void) {
    return (uint16_t)adc_hw->fifo;
}

/*! \brief Wait for the ADC FIFO to have data.
 *  \ingroup hardware_adc
 *
 * Blocks until data is present in the FIFO
 */
static inline uint16_t adc_fifo_get_blocking(void) {
    while (adc_fifo_is_empty())
        tight_loop_contents();
    return (uint16_t)adc_hw->fifo;
}

/*! \brief Drain the ADC FIFO
 *  \ingroup hardware_adc
 *
 * Will wait for any conversion to complete then drain the FIFO, discarding any results.
 */
static inline void adc_fifo_drain(void) {
    // Potentially there is still a conversion in progress -- wait for this to complete before draining
    while (!(adc_hw->cs & ADC_CS_READY_BITS))
        tight_loop_contents();
    while (!adc_fifo_is_empty())
        (void) adc_fifo_get();
}

/*! \brief Enable/Disable ADC interrupts.
 *  \ingroup hardware_adc
 *
 * \param enabled Set to true to enable the ADC interrupts, false to disable
 */
static inline void adc_irq_set_enabled(bool enabled) {
    adc_hw->inte = !!enabled;
}

#ifdef __cplusplus
}
#endif

#endif
