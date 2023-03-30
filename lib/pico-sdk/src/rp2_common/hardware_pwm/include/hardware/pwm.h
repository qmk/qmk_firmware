/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_PWM_H
#define _HARDWARE_PWM_H

#include "pico.h"
#include "hardware/structs/pwm.h"
#include "hardware/regs/dreq.h"

#ifdef __cplusplus
extern "C" {
#endif

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_PWM, Enable/disable assertions in the PWM module, type=bool, default=0, group=hardware_pwm
#ifndef PARAM_ASSERTIONS_ENABLED_PWM
#define PARAM_ASSERTIONS_ENABLED_PWM 0
#endif

/** \file hardware/pwm.h
 *  \defgroup hardware_pwm hardware_pwm
 *
 * Hardware Pulse Width Modulation (PWM) API
 *
 * The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or
 * measure the frequency or duty cycle of an input signal. This gives a total of up to 16 controllable
 * PWM outputs. All 30 GPIOs can be driven by the PWM block.
 *
 * The PWM hardware functions by continuously comparing the input value to a free-running counter. This produces a
 * toggling output where the amount of time spent at the high output level is proportional to the input value. The fraction of
 * time spent at the high signal level is known as the duty cycle of the signal.
 *
 * The default behaviour of a PWM slice is to count upward until the wrap value (\ref pwm_config_set_wrap) is reached, and then
 * immediately wrap to 0. PWM slices also offer a phase-correct mode, where the counter starts to count downward after
 * reaching TOP, until it reaches 0 again.
 *
 * \subsection pwm_example Example
 * \addtogroup hardware_pwm
 * \include hello_pwm.c
 */

/** \brief PWM Divider mode settings
 *   \ingroup hardware_pwm
 *
 */
enum pwm_clkdiv_mode
{
    PWM_DIV_FREE_RUNNING = 0, ///< Free-running counting at rate dictated by fractional divider
    PWM_DIV_B_HIGH = 1,       ///< Fractional divider is gated by the PWM B pin
    PWM_DIV_B_RISING = 2,     ///< Fractional divider advances with each rising edge of the PWM B pin
    PWM_DIV_B_FALLING = 3    ///< Fractional divider advances with each falling edge of the PWM B pin
};

enum pwm_chan
{
    PWM_CHAN_A = 0,
    PWM_CHAN_B = 1
};

typedef struct {
    uint32_t csr;
    uint32_t div;
    uint32_t top;
} pwm_config;

static inline void check_slice_num_param(__unused uint slice_num) {
    valid_params_if(PWM, slice_num < NUM_PWM_SLICES);
}

/** \brief Determine the PWM slice that is attached to the specified GPIO
 *  \ingroup hardware_pwm
 *
 * \return The PWM slice number that controls the specified GPIO.
 */
static inline uint pwm_gpio_to_slice_num(uint gpio) {
    valid_params_if(PWM, gpio < NUM_BANK0_GPIOS);
    return (gpio >> 1u) & 7u;
}

/** \brief Determine the PWM channel that is attached to the specified GPIO.
 *  \ingroup hardware_pwm
 *
 * Each slice 0 to 7 has two channels, A and B.
 *
 * \return The PWM channel that controls the specified GPIO.
 */
static inline uint pwm_gpio_to_channel(uint gpio) {
    valid_params_if(PWM, gpio < NUM_BANK0_GPIOS);
    return gpio & 1u;
}

/** \brief Set phase correction in a PWM configuration
 *  \ingroup hardware_pwm
 *
 * \param c PWM configuration struct to modify
 * \param phase_correct true to set phase correct modulation, false to set trailing edge
 *
 * Setting phase control to true means that instead of wrapping back to zero when the wrap point is reached,
 * the PWM starts counting back down. The output frequency is halved when phase-correct mode is enabled.
 */
static inline void pwm_config_set_phase_correct(pwm_config *c, bool phase_correct) {
    c->csr = (c->csr & ~PWM_CH0_CSR_PH_CORRECT_BITS)
        | (bool_to_bit(phase_correct) << PWM_CH0_CSR_PH_CORRECT_LSB);
}

/** \brief Set PWM clock divider in a PWM configuration
 *  \ingroup hardware_pwm
 *
 * \param c PWM configuration struct to modify
 * \param div Value to divide counting rate by. Must be greater than or equal to 1.
 *
 * If the divide mode is free-running, the PWM counter runs at clk_sys / div.
 * Otherwise, the divider reduces the rate of events seen on the B pin input (level or edge)
 * before passing them on to the PWM counter.
 */
static inline void pwm_config_set_clkdiv(pwm_config *c, float div) {
    valid_params_if(PWM, div >= 1.f && div < 256.f);
    c->div = (uint32_t)(div * (float)(1u << PWM_CH0_DIV_INT_LSB));
}

/** \brief Set PWM clock divider in a PWM configuration using an 8:4 fractional value
 *  \ingroup hardware_pwm
 *
 * \param c PWM configuration struct to modify
 * \param integer 8 bit integer part of the clock divider. Must be greater than or equal to 1.
 * \param fract 4 bit fractional part of the clock divider
 *
 * If the divide mode is free-running, the PWM counter runs at clk_sys / div.
 * Otherwise, the divider reduces the rate of events seen on the B pin input (level or edge)
 * before passing them on to the PWM counter.
 */
static inline void pwm_config_set_clkdiv_int_frac(pwm_config *c, uint8_t integer, uint8_t fract) {
    valid_params_if(PWM, integer >= 1);
    valid_params_if(PWM, fract < 16);
    c->div = (((uint)integer) << PWM_CH0_DIV_INT_LSB) | (((uint)fract) << PWM_CH0_DIV_FRAC_LSB);
}

/** \brief Set PWM clock divider in a PWM configuration
 *  \ingroup hardware_pwm
 *
 * \param c PWM configuration struct to modify
 * \param div Integer value to reduce counting rate by. Must be greater than or equal to 1.
 *
 * If the divide mode is free-running, the PWM counter runs at clk_sys / div.
 * Otherwise, the divider reduces the rate of events seen on the B pin input (level or edge)
 * before passing them on to the PWM counter.
 */
static inline void pwm_config_set_clkdiv_int(pwm_config *c, uint div) {
    valid_params_if(PWM, div >= 1 && div < 256);
    pwm_config_set_clkdiv_int_frac(c, (uint8_t)div, 0);
}

/** \brief Set PWM counting mode in a PWM configuration
 *  \ingroup hardware_pwm
 *
 * \param c PWM configuration struct to modify
 * \param mode PWM divide/count mode
 *
 * Configure which event gates the operation of the fractional divider.
 * The default is always-on (free-running PWM). Can also be configured to count on
 * high level, rising edge or falling edge of the B pin input.
 */
static inline void pwm_config_set_clkdiv_mode(pwm_config *c, enum pwm_clkdiv_mode mode) {
    valid_params_if(PWM, mode == PWM_DIV_FREE_RUNNING ||
            mode == PWM_DIV_B_RISING ||
            mode == PWM_DIV_B_HIGH ||
            mode == PWM_DIV_B_FALLING);
    c->csr = (c->csr & ~PWM_CH0_CSR_DIVMODE_BITS)
        | (((uint)mode) << PWM_CH0_CSR_DIVMODE_LSB);
}

/** \brief Set output polarity in a PWM configuration
 *  \ingroup hardware_pwm
 *
 * \param c PWM configuration struct to modify
 * \param a true to invert output A
 * \param b true to invert output B
 */
static inline void pwm_config_set_output_polarity(pwm_config *c, bool a, bool b) {
    c->csr = (c->csr & ~(PWM_CH0_CSR_A_INV_BITS | PWM_CH0_CSR_B_INV_BITS))
        | ((bool_to_bit(a) << PWM_CH0_CSR_A_INV_LSB) | (bool_to_bit(b) << PWM_CH0_CSR_B_INV_LSB));
}

/** \brief Set PWM counter wrap value in a PWM configuration
 *  \ingroup hardware_pwm
 *
 * Set the highest value the counter will reach before returning to 0. Also known as TOP.
 *
 * \param c PWM configuration struct to modify
 * \param wrap Value to set wrap to
 */
static inline void pwm_config_set_wrap(pwm_config *c, uint16_t wrap) {
    c->top = wrap;
}

/** \brief Initialise a PWM with settings from a configuration object
 *  \ingroup hardware_pwm
 *
 * Use the \ref pwm_get_default_config() function to initialise a config structure, make changes as
 * needed using the pwm_config_* functions, then call this function to set up the PWM.
 *
 * \param slice_num PWM slice number
 * \param c The configuration to use
 * \param start If true the PWM will be started running once configured. If false you will need to start
 *  manually using \ref pwm_set_enabled() or \ref pwm_set_mask_enabled()
 */
static inline void pwm_init(uint slice_num, pwm_config *c, bool start) {
    check_slice_num_param(slice_num);
    pwm_hw->slice[slice_num].csr = 0;

    pwm_hw->slice[slice_num].ctr = PWM_CH0_CTR_RESET;
    pwm_hw->slice[slice_num].cc = PWM_CH0_CC_RESET;
    pwm_hw->slice[slice_num].top = c->top;
    pwm_hw->slice[slice_num].div = c->div;
    pwm_hw->slice[slice_num].csr = c->csr | (bool_to_bit(start) << PWM_CH0_CSR_EN_LSB);
}

/** \brief Get a set of default values for PWM configuration
 *  \ingroup hardware_pwm
 *
 * PWM config is free-running at system clock speed, no phase correction, wrapping at 0xffff,
 * with standard polarities for channels A and B.
 *
 * \return Set of default values.
 */
static inline pwm_config pwm_get_default_config(void) {
    pwm_config c = {0, 0, 0};
    pwm_config_set_phase_correct(&c, false);
    pwm_config_set_clkdiv_int(&c, 1);
    pwm_config_set_clkdiv_mode(&c, PWM_DIV_FREE_RUNNING);
    pwm_config_set_output_polarity(&c, false, false);
    pwm_config_set_wrap(&c, 0xffffu);
    return c;
}

/** \brief Set the current PWM counter wrap value
 *  \ingroup hardware_pwm
 *
 * Set the highest value the counter will reach before returning to 0. Also
 * known as TOP.
 *
 * The counter wrap value is double-buffered in hardware. This means that,
 * when the PWM is running, a write to the counter wrap value does not take
 * effect until after the next time the PWM slice wraps (or, in phase-correct
 * mode, the next time the slice reaches 0). If the PWM is not running, the
 * write is latched in immediately.
 *
 * \param slice_num PWM slice number
 * \param wrap Value to set wrap to
 */
static inline void pwm_set_wrap(uint slice_num, uint16_t wrap) {
    check_slice_num_param(slice_num);
    pwm_hw->slice[slice_num].top = wrap;
}

/** \brief Set the current PWM counter compare value for one channel
 *  \ingroup hardware_pwm
 *
 * Set the value of the PWM counter compare value, for either channel A or channel B.
 *
 * The counter compare register is double-buffered in hardware. This means
 * that, when the PWM is running, a write to the counter compare values does
 * not take effect until the next time the PWM slice wraps (or, in
 * phase-correct mode, the next time the slice reaches 0). If the PWM is not
 * running, the write is latched in immediately.
 *
 * \param slice_num PWM slice number
 * \param chan Which channel to update. 0 for A, 1 for B.
 * \param level new level for the selected output
 */
static inline void pwm_set_chan_level(uint slice_num, uint chan, uint16_t level) {
    check_slice_num_param(slice_num);
    hw_write_masked(
        &pwm_hw->slice[slice_num].cc,
        ((uint)level) << (chan ? PWM_CH0_CC_B_LSB : PWM_CH0_CC_A_LSB),
        chan ? PWM_CH0_CC_B_BITS : PWM_CH0_CC_A_BITS
    );
}

/** \brief Set PWM counter compare values
 *  \ingroup hardware_pwm
 *
 * Set the value of the PWM counter compare values, A and B.
 *
 * The counter compare register is double-buffered in hardware. This means
 * that, when the PWM is running, a write to the counter compare values does
 * not take effect until the next time the PWM slice wraps (or, in
 * phase-correct mode, the next time the slice reaches 0). If the PWM is not
 * running, the write is latched in immediately.
 *
 * \param slice_num PWM slice number
 * \param level_a Value to set compare A to. When the counter reaches this value the A output is deasserted
 * \param level_b Value to set compare B to. When the counter reaches this value the B output is deasserted
 */
static inline void pwm_set_both_levels(uint slice_num, uint16_t level_a, uint16_t level_b) {
    check_slice_num_param(slice_num);
    pwm_hw->slice[slice_num].cc = (((uint)level_b) << PWM_CH0_CC_B_LSB) | (((uint)level_a) << PWM_CH0_CC_A_LSB);
}

/** \brief Helper function to set the PWM level for the slice and channel associated with a GPIO.
 *  \ingroup hardware_pwm
 *
 * Look up the correct slice (0 to 7) and channel (A or B) for a given GPIO, and update the corresponding
 * counter compare field.
 *
 * This PWM slice should already have been configured and set running. Also be careful of multiple GPIOs
 * mapping to the same slice and channel (if GPIOs have a difference of 16).
 *
 * The counter compare register is double-buffered in hardware. This means
 * that, when the PWM is running, a write to the counter compare values does
 * not take effect until the next time the PWM slice wraps (or, in
 * phase-correct mode, the next time the slice reaches 0). If the PWM is not
 * running, the write is latched in immediately.
 *
 * \param gpio GPIO to set level of
 * \param level PWM level for this GPIO
 */
static inline void pwm_set_gpio_level(uint gpio, uint16_t level) {
    valid_params_if(PWM, gpio < NUM_BANK0_GPIOS);
    pwm_set_chan_level(pwm_gpio_to_slice_num(gpio), pwm_gpio_to_channel(gpio), level);
}

/** \brief Get PWM counter
 *  \ingroup hardware_pwm
 *
 * Get current value of PWM counter
 *
 * \param slice_num PWM slice number
 * \return Current value of the PWM counter
 */
static inline uint16_t pwm_get_counter(uint slice_num) {
    check_slice_num_param(slice_num);
    return (uint16_t)(pwm_hw->slice[slice_num].ctr);
}

/** \brief Set PWM counter
 *  \ingroup hardware_pwm
 *
 * Set the value of the PWM counter
 *
 * \param slice_num PWM slice number
 * \param c Value to set the PWM counter to
 *
 */
static inline void pwm_set_counter(uint slice_num, uint16_t c) {
    check_slice_num_param(slice_num);
    pwm_hw->slice[slice_num].ctr = c;
}

/** \brief Advance PWM count
 *  \ingroup hardware_pwm
 *
 * Advance the phase of a running the counter by 1 count.
 *
 * This function will return once the increment is complete.
 *
 * \param slice_num PWM slice number
 */
static inline void pwm_advance_count(uint slice_num) {
    check_slice_num_param(slice_num);
    hw_set_bits(&pwm_hw->slice[slice_num].csr, PWM_CH0_CSR_PH_ADV_BITS);
    while (pwm_hw->slice[slice_num].csr & PWM_CH0_CSR_PH_ADV_BITS) {
        tight_loop_contents();
    }
}

/** \brief Retard PWM count
 *  \ingroup hardware_pwm
 *
 * Retard the phase of a running counter by 1 count
 *
 * This function will return once the retardation is complete.
 *
 * \param slice_num PWM slice number
 */
static inline void pwm_retard_count(uint slice_num) {
    check_slice_num_param(slice_num);
    hw_set_bits(&pwm_hw->slice[slice_num].csr, PWM_CH0_CSR_PH_RET_BITS);
    while (pwm_hw->slice[slice_num].csr & PWM_CH0_CSR_PH_RET_BITS) {
        tight_loop_contents();
    }
}

/** \brief Set PWM clock divider using an 8:4 fractional value
 *  \ingroup hardware_pwm
 *
 * Set the clock divider. Counter increment will be on sysclock divided by this value, taking into account the gating.
 *
 * \param slice_num PWM slice number
 * \param integer  8 bit integer part of the clock divider
 * \param fract 4 bit fractional part of the clock divider
 */
static inline void pwm_set_clkdiv_int_frac(uint slice_num, uint8_t integer, uint8_t fract) {
    check_slice_num_param(slice_num);
    valid_params_if(PWM, integer >= 1);
    valid_params_if(PWM, fract < 16);
    pwm_hw->slice[slice_num].div = (((uint)integer) << PWM_CH0_DIV_INT_LSB) | (((uint)fract) << PWM_CH0_DIV_FRAC_LSB);
}

/** \brief Set PWM clock divider
 *  \ingroup hardware_pwm
 *
 * Set the clock divider. Counter increment will be on sysclock divided by this value, taking into account the gating.
 *
 * \param slice_num PWM slice number
 * \param divider Floating point clock divider,  1.f <= value < 256.f
 */
static inline void pwm_set_clkdiv(uint slice_num, float divider) {
    check_slice_num_param(slice_num);
    valid_params_if(PWM, divider >= 1.f && divider < 256.f);
    uint8_t i = (uint8_t)divider;
    uint8_t f = (uint8_t)((divider - i) * (0x01 << 4));
    pwm_set_clkdiv_int_frac(slice_num, i, f);
}

/** \brief Set PWM output polarity
 *  \ingroup hardware_pwm
 *
 * \param slice_num PWM slice number
 * \param a true to invert output A
 * \param b true to invert output B
 */
static inline void pwm_set_output_polarity(uint slice_num, bool a, bool b) {
    check_slice_num_param(slice_num);
    hw_write_masked(&pwm_hw->slice[slice_num].csr, bool_to_bit(a) << PWM_CH0_CSR_A_INV_LSB | bool_to_bit(b) << PWM_CH0_CSR_B_INV_LSB,
                     PWM_CH0_CSR_A_INV_BITS | PWM_CH0_CSR_B_INV_BITS);
}


/** \brief Set PWM divider mode
 *  \ingroup hardware_pwm
 *
 * \param slice_num PWM slice number
 * \param mode Required divider mode
 */
static inline void pwm_set_clkdiv_mode(uint slice_num, enum pwm_clkdiv_mode mode) {
    check_slice_num_param(slice_num);
    valid_params_if(PWM, mode == PWM_DIV_FREE_RUNNING ||
                         mode == PWM_DIV_B_RISING ||
                         mode == PWM_DIV_B_HIGH ||
                         mode == PWM_DIV_B_FALLING);
    hw_write_masked(&pwm_hw->slice[slice_num].csr, ((uint)mode) << PWM_CH0_CSR_DIVMODE_LSB, PWM_CH0_CSR_DIVMODE_BITS);
}

/** \brief Set PWM phase correct on/off
 *  \ingroup hardware_pwm
 *
 * \param slice_num PWM slice number
 * \param phase_correct true to set phase correct modulation, false to set trailing edge
 *
 * Setting phase control to true means that instead of wrapping back to zero when the wrap point is reached,
 * the PWM starts counting back down. The output frequency is halved when phase-correct mode is enabled.
 */
static inline void pwm_set_phase_correct(uint slice_num, bool phase_correct) {
    check_slice_num_param(slice_num);
    hw_write_masked(&pwm_hw->slice[slice_num].csr, bool_to_bit(phase_correct) << PWM_CH0_CSR_PH_CORRECT_LSB, PWM_CH0_CSR_PH_CORRECT_BITS);
}

/** \brief Enable/Disable PWM
 *  \ingroup hardware_pwm
 *
 * When a PWM is disabled, it halts its counter, and the output pins are left
 * high or low depending on exactly when the counter is halted. When
 * re-enabled the PWM resumes immediately from where it left off.
 *
 * If the PWM's output pins need to be low when halted:
 *
 * - The counter compare can be set to zero whilst the PWM is enabled, and
 *   then the PWM disabled once both pins are seen to be low
 *
 * - The GPIO output overrides can be used to force the actual pins low
 *
 * - The PWM can be run for one cycle (i.e. enabled then immediately disabled)
 *   with a TOP of 0, count of 0 and counter compare of 0, to force the pins
 *   low when the PWM has already been halted. The same method can be used
 *   with a counter compare value of 1 to force a pin high.
 *
 * Note that, when disabled, the PWM can still be advanced one count at a time
 * by pulsing the PH_ADV bit in its CSR. The output pins transition as though
 * the PWM were enabled.
 *
 * \param slice_num PWM slice number
 * \param enabled true to enable the specified PWM, false to disable.
 */
static inline void pwm_set_enabled(uint slice_num, bool enabled) {
    check_slice_num_param(slice_num);
    hw_write_masked(&pwm_hw->slice[slice_num].csr, bool_to_bit(enabled) << PWM_CH0_CSR_EN_LSB, PWM_CH0_CSR_EN_BITS);
}

/** \brief Enable/Disable multiple PWM slices simultaneously
 *  \ingroup hardware_pwm
 *
 * \param mask Bitmap of PWMs to enable/disable. Bits 0 to 7 enable slices 0-7 respectively
 */
static inline void pwm_set_mask_enabled(uint32_t mask) {
    pwm_hw->en = mask;
}

/*! \brief  Enable PWM instance interrupt
 *  \ingroup hardware_pwm
 *
 * Used to enable a single PWM instance interrupt.
 *
 * \param slice_num PWM block to enable/disable
 * \param enabled true to enable, false to disable
 */
static inline void pwm_set_irq_enabled(uint slice_num, bool enabled) {
    check_slice_num_param(slice_num);
    if (enabled) {
        hw_set_bits(&pwm_hw->inte, 1u << slice_num);
    } else {
        hw_clear_bits(&pwm_hw->inte, 1u << slice_num);
    }
}

/*! \brief  Enable multiple PWM instance interrupts
 *  \ingroup hardware_pwm
 *
 * Use this to enable multiple PWM interrupts at once.
 *
 * \param slice_mask Bitmask of all the blocks to enable/disable. Channel 0 = bit 0, channel 1 = bit 1 etc.
 * \param enabled true to enable, false to disable
 */
static inline void pwm_set_irq_mask_enabled(uint32_t slice_mask, bool enabled) {
    valid_params_if(PWM, slice_mask < 256);
    if (enabled) {
        hw_set_bits(&pwm_hw->inte, slice_mask);
    } else {
        hw_clear_bits(&pwm_hw->inte, slice_mask);
    }
}

/*! \brief  Clear a single PWM channel interrupt
 *  \ingroup hardware_pwm
 *
 * \param slice_num PWM slice number
 */
static inline void pwm_clear_irq(uint slice_num) {
    pwm_hw->intr = 1u << slice_num;
}

/*! \brief  Get PWM interrupt status, raw
 *  \ingroup hardware_pwm
 *
 * \return Bitmask of all PWM interrupts currently set
 */
static inline uint32_t pwm_get_irq_status_mask(void) {
    return pwm_hw->ints;
}

/*! \brief  Force PWM interrupt
 *  \ingroup hardware_pwm
 *
 * \param slice_num PWM slice number
 */
static inline void pwm_force_irq(uint slice_num) {
    pwm_hw->intf = 1u << slice_num;
}

/*! \brief Return the DREQ to use for pacing transfers to a particular PWM slice
 *  \ingroup hardware_pwm
 *
 * \param slice_num PWM slice number
 */
static inline uint pwm_get_dreq(uint slice_num) {
    static_assert(DREQ_PWM_WRAP1 == DREQ_PWM_WRAP0 + 1, "");
    static_assert(DREQ_PWM_WRAP7 == DREQ_PWM_WRAP0 + 7, "");
    check_slice_num_param(slice_num);
    return DREQ_PWM_WRAP0 + slice_num;
}

#ifdef __cplusplus
}
#endif

#endif
