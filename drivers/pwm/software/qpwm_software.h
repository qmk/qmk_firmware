// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qpwm_internal.h"

////////////////////////////////////////////////////////////////////
// Quantum PWM configurables (add to your keyboard's config.h)

#ifndef SOFTWARE_PWM_NUM_DEVICES
#    define SOFTWARE_PWM_NUM_DEVICES 1
#endif // SOFTWARE_PWM_NUM_DEVICES

#define QUANTUM_PWM_UPDATE_TASK
void qpwm_internal_update_tick(void);

typedef void (*software_pwm_update_task_func_t)(pwm_device_t device, uint8_t tick);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM software device factories and helpers

#ifdef QUANTUM_PWM_SOFTWARE_PWM_ENABLE
/**
 * Factory function for creating a handle to the PWM device.
 *
 * NOTE: This PWM can only be used to trigger callback functions.
 * Any pin state changes must be implemented in the assigned callback
 * functions
 *
 * @param pwm_config[in] configures the PWM (e.g. frequency, duty cycle)
 * @param hardware_pwm_pin[in] optional output pin specification
 * @return the device handle used with all routines in Quantum PWM
 */
pwm_device_t make_software_pwm_device(void (*trigger_callback)(void), void (*period_callback)(void));

#endif // QUANTUM_PWM_SOFTWARE_PWM_ENABLE
