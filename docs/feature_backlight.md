# Backlighting :id=backlighting

Many keyboards support backlit keys by way of individual LEDs placed through or underneath the keyswitches. This feature is distinct from both the [RGB underglow](feature_rgblight.md) and [RGB matrix](feature_rgb_matrix.md) features as it usually allows for only a single colour per switch, though you can obviously install multiple different single coloured LEDs on a keyboard.

QMK is able to control the brightness of these LEDs by switching them on and off rapidly in a certain ratio, a technique known as *Pulse Width Modulation*, or PWM. By altering the duty cycle of the PWM signal, it creates the illusion of dimming.

The MCU can only supply so much current to its GPIO pins. Instead of powering the backlight directly from the MCU, the backlight pin is connected to a transistor or MOSFET that switches the power to the LEDs.

Most keyboards have backlighting enabled by default if they support it, but if it is not working for you, check that your `rules.mk` includes the following:

```makefile
BACKLIGHT_ENABLE = yes
```

## Keycodes :id=keycodes

Once enabled, the following keycodes below can be used to change the backlight level.

|Key      |Description                        |
|---------|-----------------------------------|
|`BL_TOGG`|Turn the backlight on or off       |
|`BL_STEP`|Cycle through backlight levels     |
|`BL_ON`  |Set the backlight to max brightness|
|`BL_OFF` |Turn the backlight off             |
|`BL_INC` |Increase the backlight level       |
|`BL_DEC` |Decrease the backlight level       |
|`BL_BRTG`|Toggle backlight breathing         |

## Functions :id=functions

These functions can be used to change the backlighting in custom code:

|Function                |Description                                 |
|------------------------|--------------------------------------------|
|`backlight_toggle()`    |Turn the backlight on or off                |
|`backlight_enable()`    |Turn the backlight on                       |
|`backlight_disable()`   |Turn the backlight off                      |
|`backlight_step()`      |Cycle through backlight levels              |
|`backlight_increase()`  |Increase the backlight level                |
|`backlight_decrease()`  |Decrease the backlight level                |
|`backlight_level(x)`    |Sets the backlight level to specified level |
|`get_backlight_level()` |Return the current backlight level          |
|`is_backlight_enabled()`|Return whether the backlight is currently on|

If backlight breathing is enabled (see below), the following functions are also available:

|Function             |Description                           |
|---------------------|--------------------------------------|
|`breathing_toggle()` |Turn the backlight breathing on or off|
|`breathing_enable()` |Turns on backlight breathing          |
|`breathing_disable()`|Turns off backlight breathing         |

## Configuration :id=configuration

To select which driver to use, configure your `rules.mk` with the following:

```makefile
BACKLIGHT_DRIVER = software
```

Valid driver values are `pwm`, `software`, `custom` or `no`. See below for help on individual drivers.

To configure the backlighting, `#define` these in your `config.h`:

| Define                 | Default       | Description                                                                                                       |
|------------------------|---------------|-------------------------------------------------------------------------------------------------------------------|
| `BACKLIGHT_PIN`        | *Not defined* | The pin that controls the LED(s)                                                                                  |
| `BACKLIGHT_LEVELS`     | `3`           | The number of brightness levels (maximum 31 excluding off)                                                        |
| `BACKLIGHT_CAPS_LOCK`  | *Not defined* | Enable Caps Lock indicator using backlight (for keyboards without dedicated LED)                                  |
| `BACKLIGHT_BREATHING`  | *Not defined* | Enable backlight breathing, if supported                                                                          |
| `BREATHING_PERIOD`     | `6`           | The length of one backlight "breath" in seconds                                                                   |
| `BACKLIGHT_ON_STATE`   | `1`           | The state of the backlight pin when the backlight is "on" - `1` for high, `0` for low                             |
| `BACKLIGHT_LIMIT_VAL ` | `255`         | The maximum duty cycle of the backlight -- `255` allows for full brightness, any lower will decrease the maximum. |

Unless you are designing your own keyboard, you generally should not need to change the `BACKLIGHT_PIN` or `BACKLIGHT_ON_STATE`.

### Backlight On State :id=backlight-on-state

Most backlight circuits are driven by an N-channel MOSFET or NPN transistor. This means that to turn the transistor *on* and light the LEDs, you must drive the backlight pin, connected to the gate or base, *high*.
Sometimes, however, a P-channel MOSFET, or a PNP transistor is used. In this case, when the transistor is on, the pin is driven *low* instead.

This functionality is configured at the keyboard level with the `BACKLIGHT_ON_STATE` define.

### AVR Driver :id=avr-driver

The `pwm` driver is configured by default, however the equivalent setting within `rules.mk` would be:

```makefile
BACKLIGHT_DRIVER = pwm
```

#### Caveats :id=avr-caveats

On AVR boards, QMK automatically decides which driver to use according to the following table:

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

All other pins will use timer-assisted software PWM:

|Audio Pin|Audio Timer|Software PWM Timer|
|---------|-----------|------------------|
|`C4`     |Timer 3    |Timer 1           |
|`C5`     |Timer 3    |Timer 1           |
|`C6`     |Timer 3    |Timer 1           |
|`B5`     |Timer 1    |Timer 3           |
|`B6`     |Timer 1    |Timer 3           |
|`B7`     |Timer 1    |Timer 3           |

When both timers are in use for Audio, the backlight PWM cannot use a hardware timer, and will instead be triggered during the matrix scan. In this case, breathing is not supported, and the backlight might flicker, because the PWM computation may not be called with enough timing precision.

#### Hardware PWM Implementation :id=hardware-pwm-implementation

When using the supported pins for backlighting, QMK will use a hardware timer configured to output a PWM signal. This timer will count up to `ICRx` (by default `0xFFFF`) before resetting to 0.
The desired brightness is calculated and stored in the `OCRxx` register. When the counter reaches this value, the backlight pin will go low, and is pulled high again when the counter resets.
In this way `OCRxx` essentially controls the duty cycle of the LEDs, and thus the brightness, where `0x0000` is completely off and `0xFFFF` is completely on.

The breathing effect is achieved by registering an interrupt handler for `TIMER1_OVF_vect` that is called whenever the counter resets, roughly 244 times per second.
In this handler, the value of an incrementing counter is mapped onto a precomputed brightness curve. To turn off breathing, the interrupt handler is simply disabled, and the brightness reset to the level stored in EEPROM.

#### Timer Assisted PWM Implementation :id=timer-assisted-implementation

When `BACKLIGHT_PIN` is not set to a hardware backlight pin, QMK will use a hardware timer configured to trigger software interrupts. This time will count up to `ICRx` (by default `0xFFFF`) before resetting to 0.
When resetting to 0, the CPU will fire an OVF (overflow) interrupt that will turn the LEDs on, starting the duty cycle.
The desired brightness is calculated and stored in the `OCRxx` register. When the counter reaches this value, the CPU will fire a Compare Output match interrupt, which will turn the LEDs off.
In this way `OCRxx` essentially controls the duty cycle of the LEDs, and thus the brightness, where `0x0000` is completely off and `0xFFFF` is completely on.

The breathing effect is the same as in the hardware PWM implementation.

### ARM Driver :id=arm-configuration

While still in its early stages, ARM backlight support aims to eventually have feature parity with AVR. The `pwm` driver is configured by default, however the equivalent setting within `rules.mk` would be:

```makefile
BACKLIGHT_DRIVER = pwm
```

#### ChibiOS Configuration :id=arm-configuration

The following `#define`s apply only to ARM-based keyboards:

|Define                 |Default|Description                        |
|-----------------------|-------|-----------------------------------|
|`BACKLIGHT_PWM_DRIVER` |`PWMD4`|The PWM driver to use              |
|`BACKLIGHT_PWM_CHANNEL`|`3`    |The PWM channel to use             |
|`BACKLIGHT_PAL_MODE`   |`2`    |The pin alternative function to use|

See the ST datasheet for your particular MCU to determine these values. Unless you are designing your own keyboard, you generally should not need to change them.

#### Caveats :id=arm-caveats

Currently only hardware PWM is supported, not timer assisted, and does not provide automatic configuration.

### Software PWM Driver :id=software-pwm-driver

In this mode, PWM is "emulated" while running other keyboard tasks. It offers maximum hardware compatibility without extra platform configuration. The tradeoff is the backlight might jitter when the keyboard is busy. To enable, add this to your `rules.mk`:

```makefile
BACKLIGHT_DRIVER = software
```

#### Multiple Backlight Pins :id=multiple-backlight-pins

Most keyboards have only one backlight pin which controls all backlight LEDs (especially if the backlight is connected to a hardware PWM pin).
In software PWM, it is possible to define multiple backlight pins, which will be turned on and off at the same time during the PWM duty cycle.

This feature allows to set, for instance, the Caps Lock LED's (or any other controllable LED) brightness at the same level as the other LEDs of the backlight. This is useful if you have mapped Control in place of Caps Lock and you need the Caps Lock LED to be part of the backlight instead of being activated when Caps Lock is on, as it is usually wired to a separate pin from the backlight.

To activate multiple backlight pins, add something like this to your `config.h`, instead of `BACKLIGHT_PIN`:

```c
#define BACKLIGHT_PINS { F5, B2 }
```

### Custom Driver :id=custom-driver

If none of the above drivers apply to your board (for example, you are using a separate IC to control the backlight), you can implement a custom backlight driver using this simple API provided by QMK. To enable, add this to your `rules.mk`:

```makefile
BACKLIGHT_DRIVER = custom
```

Then implement any of these hooks:

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

## Example Schematic

In this typical example, the backlight LEDs are all connected in parallel towards an N-channel MOSFET. Its gate pin is wired to one of the microcontroller's GPIO pins through a 470Ω resistor to avoid ringing.
A pulldown resistor is also placed between the gate pin and ground to keep it at a defined state when it is not otherwise being driven by the MCU.
The values of these resistors are not critical - see [this Electronics StackExchange question](https://electronics.stackexchange.com/q/68748) for more information.

![Backlight example circuit](https://i.imgur.com/BmAvoUC.png)
