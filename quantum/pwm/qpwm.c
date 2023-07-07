// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <quantum.h>
#include "qpwm_internal.h"

///////////////////////////////////////////////////////////
// Internal driver validation
static bool validate_driver_vtable(pwm_driver_t *driver) {
    return (driver->driver_vtable && driver->driver_vtable->init && driver->driver_vtable->power && driver->driver_vtable->set_frequency && driver->driver_vtable->set_duty_cycle) ? true : false;
}

///////////////////////////////////////////////////////////
// Quantum PWM External API: qpwm_init

bool qpwm_init(pwm_device_t device) {
    qpwm_dprintf("qpwm_init:entry\n");
    pwm_driver_t *driver = (pwm_driver_t *)device;

    driver->validate_ok = false;
    if (!validate_driver_vtable(driver)) {
        qpwm_dprintf("Failed to validate driver integrity in qpwm_init\n");
        return false;
    }

    driver->validate_ok = true;

    bool ret = driver->driver_vtable->init(device);
    qpwm_dprintf("qpwm_init: %s\n", ret ? "ok" : "fail");
    return ret;
}



///////////////////////////////////////////////////////////
// Quantum PWM External API: qpwm_power

bool qpwm_power(pwm_device_t device, bool power_on) {
    qpwm_dprintf("qpwm_power:entry\n");
    pwm_driver_t *driver = (pwm_driver_t *)device;
    if (!driver->validate_ok) {
        qpwm_dprintf("qpwm_power: fail) (validation_ok == false)\n");
        return false;
    }

    bool ret = driver->driver_vtable->power(device, power_on);
    qpwm_dprintf("qpwm_power: %s\n", ret ? "ok" : "fail");
    return ret;
}

///////////////////////////////////////////////////////////
// Quantum PWM External API: qpwm_set_frequency

bool qpwm_set_frequency(pwm_device_t device, float frequency) {
    qpwm_dprintf("pwm_set_frequency:entry\n");
    pwm_driver_t *driver = (pwm_driver_t *)device;
    if (!driver->validate_ok) {
        qpwm_dprintf("pwm_set_frequency: fail) (validation_ok == false)\n");
        return false;
    }

    bool ret = driver->driver_vtable->set_frequency(device, frequency);
    qpwm_dprintf("pwm_set_frequency: %s\n", ret ? "ok" : "fail");
    return ret;
}

///////////////////////////////////////////////////////////
// Quantum PWM External API: qpwm_set_duty_cycle

bool qpwm_set_duty_cycle(pwm_device_t device, float duty_cycle) {
    qpwm_dprintf("qpwm_set_duty_cycle:entry\n");
    pwm_driver_t *driver = (pwm_driver_t *)device;
    if (!driver->validate_ok) {
        qpwm_dprintf("qpwm_set_duty_cycle: fail) (validation_ok == false)\n");
        return false;
    }

    bool ret = driver->driver_vtable->set_duty_cycle(device, duty_cycle);
    qpwm_dprintf("qpwm_set_duty_cycle: %s\n", ret ? "ok" : "fail");
    return ret;
}

///////////////////////////////////////////////////////////
// Quantum PWM External API: qpwm_set_trigger_callback

bool qpwm_set_trigger_callback(pwm_device_t device, pwm_driver_callback_t trigger_callback) {
    qpwm_dprintf("qpwm_set_trigger_callback:entry\n");
    pwm_driver_t *driver = (pwm_driver_t *)device;
    if (!driver->validate_ok) {
        qpwm_dprintf("qpwm_set_trigger_callback: fail) (validation_ok == false)\n");
        return false;
    }

    bool ret = driver->driver_vtable->set_trigger_callback(device, trigger_callback);
    qpwm_dprintf("qpwm_set_trigger_callback: %s\n", ret ? "ok" : "fail");
    return ret;
}

///////////////////////////////////////////////////////////
// Quantum PWM External API: qpwm_set_period_callback

bool qpwm_set_period_callback(pwm_device_t device, pwm_driver_callback_t period_callback) {
    qpwm_dprintf("qpwm_set_period_callback:entry\n");
    pwm_driver_t *driver = (pwm_driver_t *)device;
    if (!driver->validate_ok) {
        qpwm_dprintf("qpwm_set_period_callback: fail) (validation_ok == false)\n");
        return false;
    }

    bool ret = driver->driver_vtable->set_period_callback(device, period_callback);
    qpwm_dprintf("qpwm_set_period_callback: %s\n", ret ? "ok" : "fail");
    return ret;
}

