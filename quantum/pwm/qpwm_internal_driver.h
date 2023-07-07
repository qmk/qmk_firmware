// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qpwm_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver callbacks

typedef bool (*pwm_driver_init_func)(pwm_device_t device);
typedef bool (*pwm_driver_power_func)(pwm_device_t device, bool power_on);
typedef bool (*pwm_driver_set_frequency_func)(pwm_device_t device, float frequency);
typedef bool (*pwm_driver_set_duty_cycle_func)(pwm_device_t device, float duty);
typedef bool (*pwm_driver_set_trigger_callback_func)(pwm_device_t device, pwm_driver_callback_t trigger_callback);
typedef bool (*pwm_driver_set_period_callback_func)(pwm_device_t device, pwm_driver_callback_t period_callback);

// Driver vtable definition
typedef struct pwm_driver_vtable_t {
    pwm_driver_init_func                 init;
    pwm_driver_power_func                power;
    pwm_driver_set_frequency_func        set_frequency;
    pwm_driver_set_duty_cycle_func       set_duty_cycle;
    pwm_driver_set_trigger_callback_func set_trigger_callback;
    pwm_driver_set_period_callback_func  set_period_callback;
} pwm_driver_vtable_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver base definition

typedef struct pwm_driver_t {
    const pwm_driver_vtable_t *driver_vtable;

    // Flag signifying if validation was successful
    bool validate_ok;

    float frequency;
    float duty_cycle;

    pwm_driver_callback_t trigger_callback;
    pwm_driver_callback_t period_callback;

} pwm_driver_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Device internals

bool qpwm_internal_register_device(pwm_device_t driver);