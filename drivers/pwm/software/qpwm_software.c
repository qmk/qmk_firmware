// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qpwm_internal.h"
#include "qpwm_software.h"
#include <math.h>

typedef struct software_pwm_device_t {
    pwm_driver_t base;
    
    software_pwm_update_task_func_t update_task_func;

    bool enabled;

} software_pwm_device_t;

// Driver storage
software_pwm_device_t software_pwm_drivers[SOFTWARE_PWM_NUM_DEVICES] = {0};


// Init control
bool software_pwm_init(pwm_device_t device) {
    return true;
}

// Power control
bool software_pwm_power(pwm_device_t device, bool power_on) {
    software_pwm_device_t *driver = (software_pwm_device_t *) device;
    driver->enabled = power_on;
    //driver->period_func(); 
    if (driver->base.period_callback) {    
        driver->base.period_callback();  // Return to the baseline state
    }
    return true;
}

// Frequency control
bool software_pwm_set_frequency(pwm_device_t device, float frequency) {
    pwm_driver_t *driver = (pwm_driver_t *) device;
    driver->frequency = frequency;
    return true;
}

// PWM duty cycle control
bool software_pwm_set_duty_cycle(pwm_device_t device, float duty_cycle) {
    pwm_driver_t *driver = (pwm_driver_t *) device;
    driver->duty_cycle = duty_cycle;
    return true;
}

// PWM trigger callback assignment
bool software_pwm_set_trigger_callback(pwm_device_t device, pwm_driver_callback_t trigger_callback) {
    pwm_driver_t *driver = (pwm_driver_t *) device;
    driver->trigger_callback = trigger_callback;
    return true;
}

// PWM period callback assignment
bool software_pwm_set_period_callback(pwm_device_t device, pwm_driver_callback_t period_callback) {
    pwm_driver_t *driver = (pwm_driver_t *) device;
    driver->period_callback = period_callback;
    return true;
}



void software_pwm_update_task_func(pwm_device_t device, uint8_t tick) {
    software_pwm_device_t *driver = (software_pwm_device_t *)device;
    if (driver->enabled) {
        uint8_t index;

        static const uint16_t duty_table[] = {
            0b0000000000000000,
            0b1000000000000000,
            0b1000000010000000,
            0b1000001000010000,
            0b1000100010001000,
            0b1001000100100100,
            0b1001001001001001,
            0b1010100101010100,
            0b1010101010101010,
            0b0101011010101011,
            0b0110110110110110,
            0b0110111011011011,
            0b0111011101110111,
            0b0111110111101111,
            0b0111111101111111,
            0b0111111111111111,
            0b1111111111111111,
        };
      
        index = floor(driver->base.duty_cycle*17.0/100.0);
        if (index > 16) {
            index = 16;
        }
        if(duty_table[index] & ((uint16_t)1 << (tick % 16))) {
            // driver->trigger_func(); 
            if (driver->base.trigger_callback) {
                driver->base.trigger_callback();  
            }
        } else {
            // driver->period_func();
            if (driver->base.period_callback) {
                driver->base.period_callback(); 
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

const pwm_driver_vtable_t software_pwm_driver_vtable = {
        .init                  = software_pwm_init,
        .power                 = software_pwm_power,
        .set_frequency         = software_pwm_set_frequency,
        .set_duty_cycle        = software_pwm_set_duty_cycle, 
        .set_trigger_callback  = software_pwm_set_trigger_callback, 
        .set_period_callback   = software_pwm_set_period_callback, 
};

// Factory function for creating a handle to the PWM device
pwm_device_t make_software_pwm_device(void (*trigger_callback)(void), void (*period_callback)(void)) {
    for (uint32_t i = 0; i < SOFTWARE_PWM_NUM_DEVICES; ++i) {
        software_pwm_device_t *driver = &software_pwm_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable = (const pwm_driver_vtable_t *)&software_pwm_driver_vtable;
            driver->base.frequency = 0;         /* unused in this implementation */
            driver->base.duty_cycle = 50;       /* default to 50% duty cycle upon creation */
            driver->base.period_callback = (pwm_driver_callback_t)period_callback;
            driver->base.trigger_callback = (pwm_driver_callback_t)trigger_callback;
            driver->update_task_func = (software_pwm_update_task_func_t)software_pwm_update_task_func;

            if (!qpwm_internal_register_device((pwm_device_t)driver)) {
                memset(driver, 0, sizeof(software_pwm_device_t));
                return NULL;
            }

            return (pwm_device_t)driver;
        }
    }
    return NULL;
}

__attribute__((weak)) void qpwm_internal_update_tick(void) {
    static uint8_t current_tick = 0;
    for (uint32_t i = 0; i < SOFTWARE_PWM_NUM_DEVICES; ++i) {
        software_pwm_device_t *driver = &software_pwm_drivers[i];
        if (driver) {
            if (driver->update_task_func) {
                driver->update_task_func(driver, current_tick);
            }
        }
    }
    current_tick++;
}