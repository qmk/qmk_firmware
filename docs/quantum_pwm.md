# Quantum PWP :id=quantum-pwm

Quantum PWM is the standardised API for PWM devices. It currently includes support for software PWM (at the matrix scan rate) and hardware PWM using pin alternate functions and/or callback functions.

There is not yet support for Quantum PWM on AVR-based boards, but an AVR driver can be added in the future. Quantum PWM intended to be extensible to support a wide variety of PWM devices (e.g. controlling an I2C-based PWM chip).

Quantum PWM drivers typically generate effects by way of driving hardware pins and/or through callback functions. Pin assignments and callback functions can be assigned NULL if they are unused.

Certain implementations (like software-based PWM) have no ability to directly drive pins, such that any pin-driving functionality must be implemented by the callback functions.

The two main callback functions are the trigger callback (which occurs when the PWM threnshold is met) and a periodic callback (which occurs at the PWM period rate, equivalent to the 100% duty cycle point). Certain implementations (like an I2C-based PWM chip) may not be able to generate callbacks due to technical limitations.


To enable overall Quantum PWM to be built into your firmware, add the following to `rules.mk`:

```make
QUANTUM_PWM_ENABLE = yes
QUANTUM_PWM_DRIVERS += ......
```

You will also likely need to select an appropriate driver in `rules.mk`, which is listed below.

!> Quantum PWM is not currently integrated with system-level operations such as when the keyboard goes into suspend. Users will need to handle this manually at the current time.

Supported devices:

| PWM Type     | Driver                                   |
|--------------|------------------------------------------|
| Software     | `QUANTUM_PWM_DRIVERS += software_pwm`    |
| Integrated   | `QUANTUM_PWM_DRIVERS += integrated_pwm`  |

## Quantum PWM Configuration :id=quantum-pwm-config

| Option                                            | Default | Purpose                                                                                                                                      |
|---------------------------------------------------|---------|----------------------------------------------------------------------------------------------------------------------------------------------|
| `QUANTUM_PWM_TASK_THROTTLE`                       | `1`     | This controls the amount of time (in milliseconds) that the Quantum PWM internal task will wait between each execution.                      |
| `QUANTUM_PWM_DEBUG`                               | _unset_ | Prints out significant amounts of debugging information to CONSOLE output. Significant performance degradation, use only for debugging.      |


Drivers have their own set of configurable options, and are described in their respective sections.

## Quantum PWM Drivers :id=quantum-pwm-drivers

<!-- tabs:start -->


### ** Software **

The software PWM driver runs at the matrix scan rate, which can vary and may be slow to the point of unusable for certain applications. While a frequency value can be assigned, it is disregarded by this driver.

The software PWM driver can only generate trigger and periodic callbacks; there no mechanism to automatically drive output pins aside from using the callback functions.

<!-- tabs:start -->

#### ** Software PWM **

Enabling support for the Software PWM in Quantum PWM is done by adding the following to `rules.mk`:

```make
QUANTUM_PWM_ENABLE = yes
QUANTUM_PWM_DRIVERS += software_pwm
```

(Instead of `QUANTUM_PWM_ENABLE = yes`, you may instead add `"quantum_pwm": true` in the list of features in info.json)

Creating a software PWM device in firmware can then be done with the following API:

```c
pwm_device_t make_software_pwm_device(void (*trigger_callback)(void), void (*period_callback)(void));
```

The device handle returned from the `make_software_pwm_device` function can be used to perform all other PWM operations.

The maximum number of displays can be configured by changing the following in your `config.h` (default is 1):

```c
// 3 PWM devices:
#define SOFTWARE_PWM_NUM_DEVICES 3
```

<!-- tabs:end -->

### ** Integrated PWM **

Many microcontrollers have internal timers which can be used for PWM purposes. These timers can often to drive output pins directly and/or generate callbacks.

If the microcontroller requires timers to be enabled for PWM, that should be done before using integrated PWM capabilities. These drivers will only configure pin settings and PWM settings. If the microcontroller has DMA capabilities, DMA can configured to work with PWM sources, but should be configured outside of Quantum PWM.

<!-- tabs:start -->

#### ** ChibiOS Integrated PWM **

Enabling support for integrated PWM in Quantum PWM is done by adding the following to `rules.mk`:

```make
QUANTUM_PWM_ENABLE = yes
QUANTUM_PWM_DRIVERS += integrated_pwm
```

(Instead of `QUANTUM_PWM_ENABLE = yes`, you may instead add `"quantum_pwm": true` in the list of features in info.json)
Creating an integrated PWM device in firmware can then be done with the following API:

```c
pwm_device_t make_integrated_pwm_device(ch_integrated_pwm_config_t pwm_config, ch_integrated_pwm_pin_t *integrated_pwm_pin, void (*trigger_callback)(void), void (*period_callback)(void));
```

The device handle returned from the `make_integrated_pwm_device` function can be used to perform all other PWM operations. The integrated_pwm_pin, trigger_callback, and period_callback arguments can individually be assigned NULL if they are not needed.

The maximum number of PWM devices can be configured by changing the following in your `config.h` (default is 1, limit is currently 16 max):

```c
// 3 PWM devices:
#define INTEGRATED_PWM_NUM_DEVICES 3
```

The ChibiOS driver API also includes two helper functions that make it simple to create (and reuse, if desired) the `pwm_config` and `integrated_pwm_pin`:

```c
ch_integrated_pwm_pin_t make_ch_integrated_pwm_pin(pin_t pwm_pin, iomode_t pal_mode);
ch_integrated_pwm_config_t make_ch_integrated_pwm_config(PWMDriver *pwm_driver, pwmchannel_t channel, uint32_t pwm_timer_frequency, pwmcnt_t pwm_period, bool on_state_is_high, bool complementary_output);
```

In `make_ch_integrated_pwm_pin`, the `pal_mode` argument will be applied directly to the pin so as to allow ORing of modes. This means that for many microcontrollers (like GPIO_V2 microcontrollers), the alternate funtion mode indicated in the datasheet will need to have PAL_MODE_ALTERNATE() applied, like this:

```c
ch_integrated_pwm_pin_t mypwm_pin = make_ch_integrated_pwm_pin(B10, PAL_MODE_ALTERNATE(1));
```

For the `pwm_timer_frequency` argument in `make_ch_integrated_pwm_config`, the clock frequency for the timer should be used in units of Hz. This is typically divisor of the system clock frequency; as per ChibiOS documentation, the behavoir undefined if an invalid clock frequency is specified.

For the `pwm_period` argument in `make_ch_integrated_pwm_config`, the period should be specified in number of ticks of the PWM clock. After the specified number of ticks have elapsed, if periodic callbacks are enabled, the `period_callback` will be called.

pwm_period
<!-- tabs:end -->

## Quantum PWM API :id=quantum-pwm-api

All APIs require a `pwm_device_t` object as their first parameter -- this object comes from the specific device initialisation, and instructions on creating it can be found in each driver's respective section.

To use any of the APIs, you need to include `qpwm.h`:
```c
#include <qpwm.h>
```

<!-- tabs:start -->

### ** General Notes **

The units for frequency is in Hertz. Duty cycle is expressed as a perecentage out of 100.00% (precision smaller than hundredths of a percent are ignored).

Quantum PWM has no awareness of CIE lighting curves. If CIE ligthing curves are needed they must be implemented by the caller.

Callback functions must accept no arguments and return no values.


### ** Device Control **

<!-- tabs:start -->

#### ** PWM Initialisation **

```c
bool qpwm_init(pwm_device_t device);
```

The `qpwm_init` function is used to initialise a PWM device after it has been created.

```c
static pwm_device_t backlight_pwm;
void keyboard_post_init_kb(void) {
    backlight_pwm = qpwm_make_.......;         // Create the backlight pwm
    qpwm_init(backlight_pwm, );   // Initialise the backlight pwm
}
```

#### ** PWM Power **

```c
bool qpwm_power(pwm_device_t device, bool power_on);
```

The `qpwm_power` function instructs the PWM device as to whether or not the PWM should be running.

```c
static uint8_t last_backlight = 255;
void backlight_set(uint8_t backlight_pwm_level) {
    if (backlight_pwm_level == 0) {
        qpwm_power(backlight_pwm, false);
    } else {}
        qpwm_power(backlight_pwm, true);
    }
}

```

#### ** Set Frequency **

```c
bool qpwm_set_frequency(pwm_device_t device, float frequency);
```

The `qpwm_set_frequency` function sets the frequency at which the PWM should run. The units of frequency is in Hertz.

#### ** Set Duty Cycle **

```c
bool qpwm_set_duty_cycle(pwm_device_t device, float duty);
```

The `qpwm_set_duty_cycle` function sets the duty cycle for the PWM device. The duty cycle is expressed as a percentage, and ranges from 0.00% to 100.00%

```c
void update_backlight_pwm(float pwm_duty_cycle) {
    qpwm_set_duty_cycle(backlight_pwm, pwm_duty_cycle);
}
```

<!-- tabs:end -->

### ** Assigning Callbacks **

Callback functions can be assigned at the time the PWM device is created, and/or later be assigned different functions (or `NULL`).

<!-- tabs:start -->

#### ** Set Trigger Callback **

```c
bool qpwm_set_trigger_callback(pwm_device_t device, pwm_driver_callback_t trigger_callback);
```

The `qpwm_set_trigger_callback` can be used to assign a callback function to be called when the PWM is triggered at the target duty cycle.

```c
void b6_high(void) {
    writePinHigh(B6);
)

void trigger_pin_B6_high(void) {
    qpwm_set_trigger_callback(backlight_pwm, b6_high);
}

void trigger_pin_disable(void) {
    qpwm_set_trigger_callback(backlight_pwm, NULL);
}
```

#### ** Set Period Callback **

```c
bool qpwm_set_period_callback(pwm_device_t device, pwm_driver_callback_t period_callback);
```

The `qpwm_set_period_callback` can be used to assign a callback function to be called when the PWM period elapses.

```c
void b6_low(void) {
    writePinLow(B6);
}

void period_pin_B6_low(void) {
    qpwm_set_period_callback(backlight_pwm, b6_low);
}

void trigger_pin_disable(void) {
    qpwm_set_period_callback(backlight_pwm, NULL);
}
```

<!-- tabs:end -->

<!-- tabs:end -->
