# Backlighting {#backlighting}

Many keyboards support backlit keys by way of individual LEDs placed through or underneath the keyswitches. This feature is distinct from both the [RGB Underglow](rgblight) and [RGB Matrix](rgb_matrix) features as it usually allows for only a single colour per switch, though you can obviously install multiple different single coloured LEDs on a keyboard.

QMK is able to control the brightness of these LEDs by switching them on and off rapidly in a certain ratio, a technique known as *Pulse Width Modulation*, or PWM. By altering the duty cycle of the PWM signal, it creates the illusion of dimming.

## Usage {#usage}

Most keyboards have backlighting enabled by default if they support it, but if it is not working for you (or you have added support), check that your `rules.mk` includes the following:

```make
BACKLIGHT_ENABLE = yes
```

## Keycodes {#keycodes}

|Key                            |Aliases  |Description                        |
|-------------------------------|---------|-----------------------------------|
|`QK_BACKLIGHT_TOGGLE`          |`BL_TOGG`|Turn the backlight on or off       |
|`QK_BACKLIGHT_STEP`            |`BL_STEP`|Cycle through backlight levels     |
|`QK_BACKLIGHT_ON`              |`BL_ON`  |Set the backlight to max brightness|
|`QK_BACKLIGHT_OFF`             |`BL_OFF` |Turn the backlight off             |
|`QK_BACKLIGHT_UP`              |`BL_UP`  |Increase the backlight level       |
|`QK_BACKLIGHT_DOWN`            |`BL_DOWN`|Decrease the backlight level       |
|`QK_BACKLIGHT_TOGGLE_BREATHING`|`BL_BRTG`|Toggle backlight breathing         |

## Basic Configuration {#basic-configuration}

Add the following to your `config.h`:

|Define                       |Default           |Description                                                                                                      |
|-----------------------------|------------------|-----------------------------------------------------------------------------------------------------------------|
|`BACKLIGHT_PIN`              |*Not defined*     |The pin that controls the LEDs                                                                                   |
|`BACKLIGHT_LEVELS`           |`3`               |The number of brightness levels (maximum 31 excluding off)                                                       |
|`BACKLIGHT_CAPS_LOCK`        |*Not defined*     |Enable Caps Lock indicator using backlight (for keyboards without dedicated LED)                                 |
|`BACKLIGHT_BREATHING`        |*Not defined*     |Enable backlight breathing, if supported                                                                         |
|`BREATHING_PERIOD`           |`6`               |The length of one backlight "breath" in seconds                                                                  |
|`BACKLIGHT_ON_STATE`         |`1`               |The state of the backlight pin when the backlight is "on" - `1` for high, `0` for low                            |
|`BACKLIGHT_LIMIT_VAL`        |`255`             |The maximum duty cycle of the backlight -- `255` allows for full brightness, any lower will decrease the maximum.|
|`BACKLIGHT_DEFAULT_ON`       |`true`            |Enable backlight upon clearing the EEPROM                                                                        |
|`BACKLIGHT_DEFAULT_BREATHING`|`false`           |Whether to enable backlight breathing upon clearing the EEPROM                                                   |
|`BACKLIGHT_DEFAULT_LEVEL`    |`BACKLIGHT_LEVELS`|The default backlight level to use upon clearing the EEPROM                                                      |

Unless you are designing your own keyboard, you generally should not need to change the `BACKLIGHT_PIN` or `BACKLIGHT_ON_STATE`.

### "On" State {#on-state}

Most backlight circuits are driven by an N-channel MOSFET or NPN transistor. This means that to turn the transistor *on* and light the LEDs, you must drive the backlight pin, connected to the gate or base, *high*.
Sometimes, however, a P-channel MOSFET, or a PNP transistor is used. In this case, when the transistor is on, the pin is driven *low* instead.

To configure the "on" state of the backlight circuit, add the following to your `config.h`:

```c
#define BACKLIGHT_ON_STATE 0
```

### Multiple Backlight Pins {#multiple-backlight-pins}

Most keyboards have only one backlight pin which controls all backlight LEDs (especially if the backlight is connected to a hardware PWM pin).
The `timer` and `software` drivers allow you to define multiple backlight pins, which will be turned on and off at the same time during the PWM duty cycle.

This feature allows to set, for instance, the Caps Lock LED's (or any other controllable LED) brightness at the same level as the other LEDs of the backlight. This is useful if you have mapped Control in place of Caps Lock and you need the Caps Lock LED to be part of the backlight instead of being activated when Caps Lock is on, as it is usually wired to a separate pin from the backlight.

To configure multiple backlight pins, add something like this to your `config.h`, instead of `BACKLIGHT_PIN`:

```c
#define BACKLIGHT_PINS { F5, B2 }
```

## Driver Configuration {#driver-configuration}

Backlight driver selection is configured in `rules.mk`. Valid drivers are `pwm` (default), `timer`, `software`, or `custom`. See below for information on individual drivers.

### PWM Driver {#pwm-driver}

This is the default backlight driver, which leverages the hardware PWM output capability of the microcontroller.

```make
BACKLIGHT_DRIVER = pwm
```

### Timer Driver {#timer-driver}

This driver is similar to the PWM driver, but instead of directly configuring the pin to output a PWM signal, an interrupt handler is attached to the timer to turn the pin on and off as appropriate.

```make
BACKLIGHT_DRIVER = timer
```

### Software Driver {#software-driver}

In this mode, PWM is "emulated" while running other keyboard tasks. It offers maximum hardware compatibility without extra platform configuration. However, breathing is not supported, and the backlight can flicker when the keyboard is busy.

```make
BACKLIGHT_DRIVER = software
```

### Custom Driver {#custom-driver}

If none of the above drivers apply to your board (for example, you are using a separate IC to control the backlight), you can implement a custom backlight driver using a simple API.

```make
BACKLIGHT_DRIVER = custom
```

```c
void backlight_init_ports(void) {
    // Optional - runs on startup
    //   Usually you want to configure pins here
}
void backlight_set(uint8_t level) {
    // Optional - runs on level change
    //   Usually you want to respond to the new value
}

void backlight_task(void) {
    // Optional - runs periodically
    //   Note that this is called in the main keyboard loop,
    //   so long running actions here can cause performance issues
}
```

## AVR Configuration {#avr-configuration}

### PWM Driver {#avr-pwm-driver}

The following table describes the supported pins for the PWM driver. Only cells marked with a timer number are capable of hardware PWM output; any others must use the `timer` driver.

|Backlight Pin|AT90USB64/128|AT90USB162|ATmega16/32U4|ATmega16/32U2|ATmega32A|ATmega328/P|
|-------------|-------------|----------|-------------|-------------|---------|-----------|
|`B1`         |             |          |             |             |         |Timer 1    |
|`B2`         |             |          |             |             |         |Timer 1    |
|`B5`         |Timer 1      |          |Timer 1      |             |         |           |
|`B6`         |Timer 1      |          |Timer 1      |             |         |           |
|`B7`         |Timer 1      |Timer 1   |Timer 1      |Timer 1      |         |           |
|`C4`         |Timer 3      |          |             |             |         |           |
|`C5`         |Timer 3      |Timer 1   |             |Timer 1      |         |           |
|`C6`         |Timer 3      |Timer 1   |Timer 3      |Timer 1      |         |           |
|`D4`         |             |          |             |             |Timer 1  |           |
|`D5`         |             |          |             |             |Timer 1  |           |

### Timer Driver {#avr-timer-driver}

Any GPIO pin can be used with this driver. The following table describes the supported timers:

|AT90USB64/128|AT90USB162|ATmega16/32U4|ATmega16/32U2|ATmega32A|ATmega328/P|
|-------------|----------|-------------|-------------|---------|-----------|
|Timers 1 & 3 |Timer 1   |Timers 1 & 3 |Timer 1      |Timer 1  |Timer 1    |

The following `#define`s apply only to the `timer` driver:

|Define                 |Default|Description     |
|-----------------------|-------|----------------|
|`BACKLIGHT_PWM_TIMER`  |`1`    |The timer to use|

Note that the choice of timer may conflict with the [Audio](audio) feature.

## ChibiOS/ARM Configuration {#arm-configuration}

### PWM Driver {#arm-pwm-driver}

Depending on the ChibiOS board configuration, you may need to enable PWM at the keyboard level. For STM32, this would look like:

`halconf.h`:
```c
#define HAL_USE_PWM TRUE
```
`mcuconf.h`:
```c
#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE
```

The following `#define`s apply only to the `pwm` driver:

|Define                 |Default      |Description                                                    |
|-----------------------|-------------|---------------------------------------------------------------|
|`BACKLIGHT_PWM_DRIVER` |`PWMD4`      |The PWM driver to use                                          |
|`BACKLIGHT_PWM_CHANNEL`|`3`          |The PWM channel to use                                         |
|`BACKLIGHT_PAL_MODE`   |`2`          |The pin alternative function to use                            |
|`BACKLIGHT_PWM_PERIOD` |*Not defined*|The PWM period in counter ticks - Default is platform dependent|


Refer to the ST datasheet for your particular MCU to determine these values. For example, these defaults are set up for pin `B8` on a Proton-C (STM32F303) using `TIM4_CH3` on AF2. Unless you are designing your own keyboard, you generally should not need to change them.

### Timer Driver {#arm-timer-driver}

Depending on the ChibiOS board configuration, you may need to enable general-purpose timers at the keyboard level. For STM32, this would look like:

`halconf.h`:
```c
#define HAL_USE_GPT TRUE
```
`mcuconf.h`:
```c
#undef STM32_GPT_USE_TIM15
#define STM32_GPT_USE_TIM15 TRUE
```

The following `#define`s apply only to the `timer` driver:

|Define                |Default |Description     |
|----------------------|--------|----------------|
|`BACKLIGHT_GPT_DRIVER`|`GPTD15`|The timer to use|

## Example Schematic

Since the MCU can only supply so much current to its GPIO pins, instead of powering the backlight directly from the MCU, the backlight pin is connected to a transistor or MOSFET that switches the power to the LEDs.

In this typical example, the backlight LEDs are all connected in parallel towards an N-channel MOSFET. Its gate pin is wired to one of the microcontroller's GPIO pins through a 470Ω resistor to avoid ringing.
A pulldown resistor is also placed between the gate pin and ground to keep it at a defined state when it is not otherwise being driven by the MCU.
The values of these resistors are not critical - see [this Electronics StackExchange question](https://electronics.stackexchange.com/q/68748) for more information.

![Backlight example circuit](https://i.imgur.com/BmAvoUC.png)

## API {#api}

### `void backlight_toggle(void)` {#api-backlight-toggle}

Toggle the backlight on or off.

---

### `void backlight_enable(void)` {#api-backlight-enable}

Turn the backlight on.

---

### `void backlight_disable(void)` {#api-backlight-disable}

Turn the backlight off.

---

### `void backlight_step(void)` {#api-backlight-step}

Cycle through backlight levels.

---

### `void backlight_increase(void)` {#api-backlight-increase}

Increase the backlight level.

---

### `void backlight_decrease(void)` {#api-backlight-decrease}

Decrease the backlight level.

---

### `void backlight_level(uint8_t level)` {#api-backlight-level}

Set the backlight level.

#### Arguments {#api-backlight-level-arguments}

 - `uint8_t level`  
   The level to set, from 0 to `BACKLIGHT_LEVELS`.

---

### `uint8_t get_backlight_level(void)` {#api-get-backlight-level}

Get the current backlight level.

#### Return Value {#api-get-backlight-level-return}

The current backlight level, from 0 to `BACKLIGHT_LEVELS`.

---

### `bool is_backlight_enabled(void)` {#api-is-backlight-enabled}

Get the current backlight state.

#### Return Value {#api-is-backlight-enabled-return}

`true` if the backlight is enabled.

---

### `void backlight_toggle_breathing(void)` {#api-backlight-toggle-breathing}

Toggle backlight breathing on or off.

---

### `void backlight_enable_breathing(void)` {#api-backlight-enable-breathing}

Turn backlight breathing on.

---

### `void backlight_disable_breathing(void)` {#api-backlight-disable-breathing}

Turn backlight breathing off.

---

### `bool is_backlight_breathing(void)` {#api-is-backlight-breathing}

Get the current backlight breathing state.

#### Return Value {#api-is-backlight-breathing-return}

`true` if backlight breathing is enabled.
