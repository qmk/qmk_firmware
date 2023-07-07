// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qpwm_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM Peripherap PWM configurables (add to your keyboard's config.h)

#ifndef INTEGRATED_PWM_NUM_DEVICES
/**
 * @def This controls the maximum number of integrated PWM devices that Quantum PWM can control with at any one time.
 *      Increasing this number allows for multiple PWM integrateds to be used.
 */
#    define INTEGRATED_PWM_NUM_DEVICES 1
#endif

_Static_assert((INTEGRATED_PWM_NUM_DEVICES) >= 1 && (INTEGRATED_PWM_NUM_DEVICES) < 16, "INTEGRATED_PWM_NUM_DEVICES must be between 1 and 15");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM integrated device factories and helpers for ChibiOS
typedef struct ch_integrated_pwm_pin_t {
    pin_t    pin;
    iomode_t pal_mode;
} ch_integrated_pwm_pin_t;

typedef struct ch_integrated_pwm_config_t {
    PWMDriver *  pwm_driver;
    PWMConfig    pwmCFG;
    pwmchannel_t channel;
} ch_integrated_pwm_config_t;

#ifdef QUANTUM_PWM_INTEGRATED_PWM_ENABLE
/**
 * Factory function for creating a handle to the PWM device.
 *
 * NOTE: PWM can be used to trigger callback functions or change
 * an output pin state. If output pins are unused, leave
 * hardware_pwm_pin as NULL
 *
 * @param pwm_config[in] configures the PWM (e.g. frequency, duty cycle)
 * @param hardware_pwm_pin[in] optional output pin specification
 * @return the device handle used with all routines in Quantum PWM
 */
pwm_device_t make_integrated_pwm_device(ch_integrated_pwm_config_t pwm_config, ch_integrated_pwm_pin_t *integrated_pwm_pin, void (*trigger_callback)(void), void (*period_callback)(void));

// Helper functions
ch_integrated_pwm_pin_t make_ch_integrated_pwm_pin(pin_t pwm_pin, iomode_t pal_mode);

ch_integrated_pwm_config_t make_ch_integrated_pwm_config(PWMDriver *pwm_driver, pwmchannel_t channel, uint32_t pwm_timer_frequency, pwmcnt_t pwm_period, bool on_state_is_high, bool complementary_output);

#endif // QUANTUM_PWM_INTEGRATED_PWM_ENABLE
