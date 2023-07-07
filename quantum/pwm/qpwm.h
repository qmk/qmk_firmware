// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM global configurables (add to your keyboard's config.h)

#ifndef QUANTUM_PWM_TASK_THROTTLE
/**
 * @def This controls the amount of time (in milliseconds) that the Quantum PWM internal task will wait between
 *      each execution.
 */
#    define QUANTUM_PWM_TASK_THROTTLE 1
#endif // QUANTUM_PWM_TASK_THROTTLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM types

/**
 * @typedef A handle to a Quantum PWM device, such as a hardware peripheral or external I2C PWM chip. Most Quantum PWM
 *          APIs require this argument in order to perform operations on the PWM device.
 *
 */
typedef const void *pwm_device_t;

/**
 * @typedef A function pointer to a Quantum PWM callback. Callback functions of this type may be called
 *          whenever PWM event triggers or the PWM period elapses.
 *
 */
typedef void (*pwm_driver_callback_t)(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM External API

/**
 * Initialize a PWM device.
 *
 * @param device[in] the handle of the device to initialize
 * @return true if initialization succeeded
 * @return false if initialization failed
 */
bool qpwm_init(pwm_device_t device);

/**
 * Controls whether a PWM device is running or not.
 *
 * @param device[in] the handle of the device to control
 * @param power_on[in] whether or not the device should be on
 * @return true if controlling the power state succeeded
 * @return false if controlling the power state failed
 */
bool qpwm_power(pwm_device_t device, bool power_on);

/**
 * Sets the frequency at which the PWM device is running.
 * Units are in Hz.
 *
 * @note qpwm_set_frequency and qpwm_set_period control the same
 * variable. Quantum PWM drivers may internally stores this
 * information as a period to match the underlying settings in
 * units of clock ticks. Drivers may also allow the period to be written
 * directly. Some driver implementations have limited frequency range
 * and/or precision, or may only permit fixed frequency operation.
 * set_frequency() applies a "best effort" approach to match the
 * assigned frequency.
 *
 * @param device[in] the handle of the device to control
 * @param frequency[in] the frequency of the PWM in Hz
 * @return true if setting the frequency succeeded
 * @return false if setting the frequency failed
 */
bool qpwm_set_frequency(pwm_device_t device, float frequency);

/**
 * Sets the duty cycle for the PWM device.
 *
 * @note Duty cycle is a float as a percentage, valid ranges are from 0.00% to 100.00%:
 *
 * @param device[in] the handle of the device to control
 * @param duty[in] the duty cycle of the PWM in percentage
 * @return true if setting the duty cycle succeeded
 * @return false if setting the duty cycle failed
 */
bool qpwm_set_duty_cycle(pwm_device_t device, float duty);

/**
 * Sets the trigger callback for the PWM device.
 *
 * @param device[in] the handle of the device to control
 * @param trigger_callback[in] the callback function to execute upon triggering
 * @return true if setting the callback function succeeded
 * @return false if setting the callback function failed
 */
bool qpwm_set_trigger_callback(pwm_device_t device, pwm_driver_callback_t trigger_callback);


/**
 * Sets the period callback for the PWM device.
 *
 * @param device[in] the handle of the device to control
 * @param period_callback[in] the callback function to execute upon PWM period elapsing
 * @return true if setting the callback function succeeded
 * @return false if setting the callback function failed
 */
bool qpwm_set_period_callback(pwm_device_t device, pwm_driver_callback_t period_callback);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM Drivers

#ifdef QUANTUM_PWM_INTEGRATED_PWM_ENABLE
#    include "pwm.h"
#else // QUANTUM_PWM_INTEGRATED_PWM_ENABLE
#    define INTEGRATED_PWM_NUM_DEVICES 0
#endif // QUANTUM_PWM_INTEGRATED_PWM_ENABLE

#ifdef QUANTUM_PWM_SOFTWARE_PWM_ENABLE
#    include "qpwm_software.h"
#else // QUANTUM_PWM_SOFTWARE_PWM_ENABLE
#    define SOFTWARE_PWM_NUM_DEVICES 0
#endif // QUANTUM_PWM_SOFTWARE_PWM_ENABLE
