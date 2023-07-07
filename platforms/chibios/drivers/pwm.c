// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qpwm_internal.h"
#include "pwm.h"

// Improves readability
#define CH_INTEGRATED_PWM_DRIVER_PTR ((driver->ch_integrated_pwm_config).pwm_driver)
#define CH_INTEGRATED_PWM_CONFIG ((driver->ch_integrated_pwm_config).pwmCFG)
#define CH_INTEGRATED_PWM_CHANNEL ((driver->ch_integrated_pwm_config).channel)
#define CH_INTEGRATED_PWM_PIN ((driver->ch_integrated_pwm_pin)->pin)
#define CH_INTEGRATED_PWM_PIN_PAL_MODE ((driver->ch_integrated_pwm_pin)->pal_mode)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

typedef struct ch_integrated_pwm_device_t {
    pwm_driver_t               base;
    ch_integrated_pwm_pin_t *  ch_integrated_pwm_pin;
    ch_integrated_pwm_config_t ch_integrated_pwm_config;
    bool                       pwm_started;
    uint32_t                   driver_index;

    void (*trigger_callback)(void);
    void (*period_callback)(void);

} ch_integrated_pwm_device_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver and callback storage
ch_integrated_pwm_device_t ch_integrated_pwm_drivers[INTEGRATED_PWM_NUM_DEVICES] = {0};

// These functions are used for the PWM driver callbacks directly, which
// requires accepting a (ChibiOS-specific) PWMDriver* argument. The only job
// of these callback functions is to redirect the call to a non-Chibios-specific
// callback function typed as void (*_callback)(void).
#define MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(index)                \
    void ch_integrated_pwm_trigger_callback##index(PWMDriver *pwmp) { \
        (void)pwmp;                                                   \
        ch_integrated_pwm_drivers[index].trigger_callback();          \
    }

#define MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(index)                \
    void ch_integrated_pwm_period_callback##index(PWMDriver *pwmp) { \
        (void)pwmp;                                                  \
        ch_integrated_pwm_drivers[index].period_callback();          \
    }

#define MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK_FN_NAME(index) ch_integrated_pwm_trigger_callback##index
#define MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK_FN_NAME(index) ch_integrated_pwm_period_callback##index

// Generate unique ChibiOS-compatible trigger callbacks and periodic callbacks for each PWM device (as-needed)
#if INTEGRATED_PWM_NUM_DEVICES > 0
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(0);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(0);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 1
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(1);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(1);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 2
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(2);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(2);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 3
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(3);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(3);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 4
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(4);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(4);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 5
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(5);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(5);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 6
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(6);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(6);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 7
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(7);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(7);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 8
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(8);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(8);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 9
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(9);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(9);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 10
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(10);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(10);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 11
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(11);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(11);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 12
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(12);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(12);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 13
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(13);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(13);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 14
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(14);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(14);
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 15
MAKE_CH_INTEGRATED_PWM_TRIGGER_CALLBACK(15);
MAKE_CH_INTEGRATED_PWM_PERIOD_CALLBACK(15);
#endif

// Store the callback function pointers in an array so they can be accessed by index value
pwmcallback_t ch_integrated_pwm_trigger_callbacks[INTEGRATED_PWM_NUM_DEVICES] = {
#if INTEGRATED_PWM_NUM_DEVICES > 0
    ch_integrated_pwm_trigger_callback0,
#else
    0
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 1
    ch_integrated_pwm_trigger_callback1,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 2
    ch_integrated_pwm_trigger_callback2,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 3
    ch_integrated_pwm_trigger_callback3,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 4
    ch_integrated_pwm_trigger_callback4,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 5
    ch_integrated_pwm_trigger_callback5,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 6
    ch_integrated_pwm_trigger_callback6,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 7
    ch_integrated_pwm_trigger_callback7,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 8
    ch_integrated_pwm_trigger_callback8,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 9
    ch_integrated_pwm_trigger_callback9,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 10
    ch_integrated_pwm_trigger_callback10,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 11
    ch_integrated_pwm_trigger_callback11,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 12
    ch_integrated_pwm_trigger_callback12,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 13
    ch_integrated_pwm_trigger_callback13,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 14
    ch_integrated_pwm_trigger_callback14,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 15
    ch_integrated_pwm_trigger_callback15,
#endif
};

pwmcallback_t ch_integrated_pwm_period_callbacks[INTEGRATED_PWM_NUM_DEVICES] = {
#if INTEGRATED_PWM_NUM_DEVICES > 0
    ch_integrated_pwm_period_callback0,
#else
    0
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 1
    ch_integrated_pwm_period_callback1,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 2
    ch_integrated_pwm_period_callback2,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 3
    ch_integrated_pwm_period_callback3,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 4
    ch_integrated_pwm_period_callback4,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 5
    ch_integrated_pwm_period_callback5,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 6
    ch_integrated_pwm_period_callback6,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 7
    ch_integrated_pwm_period_callback7,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 8
    ch_integrated_pwm_period_callback8,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 9
    ch_integrated_pwm_period_callback9,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 10
    ch_integrated_pwm_period_callback10,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 11
    ch_integrated_pwm_period_callback11,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 12
    ch_integrated_pwm_period_callback12,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 13
    ch_integrated_pwm_period_callback13,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 14
    ch_integrated_pwm_period_callback14,
#endif
#if INTEGRATED_PWM_NUM_DEVICES > 15
    ch_integrated_pwm_period_callback15,
#endif
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization
__attribute__((weak)) bool ch_integrated_pwm_init(pwm_device_t device) {
    ch_integrated_pwm_device_t *driver = (ch_integrated_pwm_device_t *)device;
    if (driver->ch_integrated_pwm_pin != NULL) {
        palSetPadMode(PAL_PORT(CH_INTEGRATED_PWM_PIN), PAL_PAD(CH_INTEGRATED_PWM_PIN), CH_INTEGRATED_PWM_PIN_PAL_MODE);
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM API implementations

// Power control
bool ch_integrated_pwm_power(pwm_device_t device, bool power_on) {
    ch_integrated_pwm_device_t *driver = (ch_integrated_pwm_device_t *)device;
    pwmStop((driver->ch_integrated_pwm_config).pwm_driver);
    driver->pwm_started = false;
    if (power_on) {
        pwmStart(CH_INTEGRATED_PWM_DRIVER_PTR, &CH_INTEGRATED_PWM_CONFIG);
        driver->pwm_started = true;

        chSysLockFromISR();
        pwmEnableChannelI(CH_INTEGRATED_PWM_DRIVER_PTR, (CH_INTEGRATED_PWM_CHANNEL - 1), PWM_PERCENTAGE_TO_WIDTH(CH_INTEGRATED_PWM_DRIVER_PTR, (uint16_t)(driver->base.duty_cycle * 100.0)));

        if (CH_INTEGRATED_PWM_CONFIG.channels[CH_INTEGRATED_PWM_CHANNEL - 1].callback) {
            pwmEnableChannelNotificationI(CH_INTEGRATED_PWM_DRIVER_PTR, CH_INTEGRATED_PWM_CHANNEL - 1);
        }
        if (CH_INTEGRATED_PWM_CONFIG.callback) {
            pwmEnablePeriodicNotificationI(CH_INTEGRATED_PWM_DRIVER_PTR);
        }
        chSysUnlockFromISR();
    }

    return true;
}

// PWM period control
bool ch_integrated_pwm_set_period(pwm_device_t device, uint32_t period) {
    ch_integrated_pwm_device_t *driver = (ch_integrated_pwm_device_t *)device;

    if (period == 0) {
        return true;
    }

    driver->base.frequency = CH_INTEGRATED_PWM_CONFIG.frequency / period; // (timer clock frequency / number of ticks)

    if (driver->pwm_started == false) {
        // PWM not running, update configuration data only
        CH_INTEGRATED_PWM_CONFIG.period      = period;
        CH_INTEGRATED_PWM_DRIVER_PTR->period = period;
        return true;
    }

    chSysLockFromISR();
    pwmChangePeriodI(CH_INTEGRATED_PWM_DRIVER_PTR, period);
    pwmEnableChannelI(CH_INTEGRATED_PWM_DRIVER_PTR, (pwmchnmsk_t)(CH_INTEGRATED_PWM_CHANNEL - 1), PWM_PERCENTAGE_TO_WIDTH(CH_INTEGRATED_PWM_DRIVER_PTR, (uint16_t)(driver->base.duty_cycle * 100.0)));
    chSysUnlockFromISR();

    return true;
}

// PWM frequency control
bool ch_integrated_pwm_set_frequency(pwm_device_t device, float frequency) {
    ch_integrated_pwm_device_t *driver = (ch_integrated_pwm_device_t *)device;
    if (frequency <= 0.0) {
        return true;
    }

    driver->base.frequency = frequency;

    if (driver->pwm_started == false) {
        // PWM not running, update configuration data only
        CH_INTEGRATED_PWM_CONFIG.period      = (CH_INTEGRATED_PWM_CONFIG.frequency / frequency ); // (timer clock frequency / PWM frequency)
        CH_INTEGRATED_PWM_DRIVER_PTR->period = CH_INTEGRATED_PWM_CONFIG.period;
        return true;
    }

    chSysLockFromISR();
    pwmChangePeriodI(CH_INTEGRATED_PWM_DRIVER_PTR, (CH_INTEGRATED_PWM_CONFIG.frequency / frequency ));
    pwmEnableChannelI(CH_INTEGRATED_PWM_DRIVER_PTR, (CH_INTEGRATED_PWM_CHANNEL - 1), PWM_PERCENTAGE_TO_WIDTH(CH_INTEGRATED_PWM_DRIVER_PTR, (uint16_t)(driver->base.duty_cycle * 100.0)));
    chSysUnlockFromISR();
    return true;
}

// PWM duty cycle control
bool ch_integrated_pwm_set_duty_cycle(pwm_device_t device, float duty_cycle) {
    ch_integrated_pwm_device_t *driver = (ch_integrated_pwm_device_t *)device;
    driver->base.duty_cycle            = duty_cycle;

    if (driver->pwm_started == false) {
        // PWM not running, nothing else to do
        return true;
    }

    chSysLockFromISR();
    if (duty_cycle == 0) {
        pwmDisableChannelI(CH_INTEGRATED_PWM_DRIVER_PTR, (CH_INTEGRATED_PWM_CHANNEL - 1));
        if (driver->trigger_callback) {
            // If callbacks are being used, the 0% duty cycle state is equivalent to
            // being perpetually post-triggered, so execute the trigger callback to
            // leave things in the correct state. However, this generally may be
            // insufficient when using callbacks becuse the period callback will continue to
            // execute even if the channel is disabled. Unlike the hardware PWM mode (for
            // which the hardware will suppress periodic events from affecting the assigned
            // pin when the channel is disabled), the periodic callback function will continue
            // to be called until the PWM is stopped by qpwm_power(my_qpm_device, false) or by
            // setting the periodic callback function to NULL.
            driver->trigger_callback();
        }
    } else {
        pwmEnableChannelI(CH_INTEGRATED_PWM_DRIVER_PTR, (CH_INTEGRATED_PWM_CHANNEL - 1), PWM_PERCENTAGE_TO_WIDTH(CH_INTEGRATED_PWM_DRIVER_PTR, (uint32_t)(duty_cycle * 100.0)));
    }
    chSysUnlockFromISR();
    return true;
}

// PWM trigger callback assignment
bool ch_integrated_pwm_set_trigger_callback(pwm_device_t device, pwm_driver_callback_t trigger_callback) {
    ch_integrated_pwm_device_t *driver = (ch_integrated_pwm_device_t *)device;
    driver->trigger_callback           = trigger_callback;
    if (trigger_callback) {
        CH_INTEGRATED_PWM_CONFIG.channels[CH_INTEGRATED_PWM_CHANNEL - 1].callback = ch_integrated_pwm_trigger_callbacks[driver->driver_index];
    } else {
        CH_INTEGRATED_PWM_CONFIG.channels[CH_INTEGRATED_PWM_CHANNEL - 1].callback = NULL;
    }
    return true;
}

// PWM period callback assignment
// NOTE: If multiple ChibiOS PWM devices share the PWM driver (for example, using multiple channels within the
// same PWM driver), setting the period callback for one PWM device will affect all the period callback for all
// PWM devices sharing that driver. There is only one period callback allowed per PWM driver.
bool ch_integrated_pwm_set_period_callback(pwm_device_t device, pwm_driver_callback_t period_callback) {
    ch_integrated_pwm_device_t *driver = (ch_integrated_pwm_device_t *)device;
    driver->period_callback            = period_callback;
    if (period_callback) {
        CH_INTEGRATED_PWM_CONFIG.callback = ch_integrated_pwm_period_callbacks[driver->driver_index];
    } else {
        CH_INTEGRATED_PWM_CONFIG.callback = NULL;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

const pwm_driver_vtable_t integrated_pwm_driver_vtable = {
    .init                   = ch_integrated_pwm_init,
    .power                  = ch_integrated_pwm_power,
    .set_frequency          = ch_integrated_pwm_set_frequency,
    .set_duty_cycle         = ch_integrated_pwm_set_duty_cycle,
    .set_trigger_callback   = ch_integrated_pwm_set_trigger_callback,
    .set_period_callback    = ch_integrated_pwm_set_period_callback,
};

// Factory function for creating a handle to the PWM device
pwm_device_t make_integrated_pwm_device(ch_integrated_pwm_config_t pwm_config, ch_integrated_pwm_pin_t *integrated_pwm_pin, void (*trigger_callback)(void), void (*period_callback)(void)) {
    for (uint32_t i = 0; i < INTEGRATED_PWM_NUM_DEVICES; ++i) {
        ch_integrated_pwm_device_t *driver = &ch_integrated_pwm_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable       = (const pwm_driver_vtable_t *)&integrated_pwm_driver_vtable;
            driver->ch_integrated_pwm_config = pwm_config;
            driver->ch_integrated_pwm_pin    = integrated_pwm_pin;
            driver->base.frequency           = pwm_config.pwmCFG.frequency / pwm_config.pwmCFG.period;
            driver->base.duty_cycle          = 50; /* default to 50% duty cycle upon creation */
            driver->driver_index             = i;
            driver->pwm_started              = false;

            ch_integrated_pwm_set_trigger_callback((pwm_device_t)driver, trigger_callback);
            ch_integrated_pwm_set_period_callback((pwm_device_t)driver, period_callback);

            if (!qpwm_internal_register_device((pwm_device_t)driver)) {
                memset(driver, 0, sizeof(ch_integrated_pwm_device_t));
                return NULL;
            }

            return (pwm_device_t)driver;
        }
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ChibiOS-specific Helper Functions

// Helper function that generates a new ch_integrated_pwm_config_t with one channel enabled.
// The resulting ch_integrated_pwm_config_t can be modified as needed (to enable multiple channels, configure DMA, etc.)
// A ch_integrated_pwm_config_t can also be made entirely from scratch similar to how this function creates it.
ch_integrated_pwm_config_t make_ch_integrated_pwm_config(PWMDriver *pwm_driver, pwmchannel_t channel, uint32_t pwm_clock_frequency, pwmcnt_t pwm_period, bool on_state_is_high, bool complementary_output) {
    PWMConfig pwmCFG = {
        .frequency = pwm_clock_frequency, /* PWM clock frequency  */
        .period    = pwm_period,          /* PWM period in counter ticks. e.g. clock frequency is 10KHz, period is 256 ticks then t_period is 25.6ms */
    };

    if (complementary_output) {
        if (on_state_is_high) {
            pwmCFG.channels[channel - 1].mode = PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW;
        } else {
            pwmCFG.channels[channel - 1].mode = PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH;
        }
    } else {
        if (on_state_is_high) {
            pwmCFG.channels[channel - 1].mode = PWM_OUTPUT_ACTIVE_HIGH;
        } else {
            pwmCFG.channels[channel - 1].mode = PWM_OUTPUT_ACTIVE_LOW;
        }
    }

    ch_integrated_pwm_config_t ch_integrated_pwm_config;

    ch_integrated_pwm_config.pwm_driver = pwm_driver;
    ch_integrated_pwm_config.pwmCFG     = pwmCFG;
    ch_integrated_pwm_config.channel    = channel;

    return ch_integrated_pwm_config;
}

// Helper function that generates a new ch_integrated_pwm_pin_t.
// NOTE: The pal_mode is applied directly, so if PAL_MODE_ALTERNATE() macro is needed (e.g. for GPIOV2)
// the macro and other bitwise ORing should be applied in the calling function.
// A integrated_pwm_config_t can also be made entirely from scratch similar to how this function creates it.
ch_integrated_pwm_pin_t make_ch_integrated_pwm_pin(pin_t pin, iomode_t pal_mode) {
    ch_integrated_pwm_pin_t ch_pwm_pin;
    ch_pwm_pin.pin = pin;
    ch_pwm_pin.pal_mode = pal_mode;

    return ch_pwm_pin;
}
