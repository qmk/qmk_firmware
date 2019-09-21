# Backlighting

Many keyboards support backlit keys by way of individual LEDs placed through or underneath the keyswitches. QMK is able to control the brightness of these LEDs by switching them on and off rapidly in a certain ratio, a technique known as *Pulse Width Modulation*, or PWM. By altering the duty cycle of the PWM signal, it creates the illusion of dimming.

The MCU can only supply so much current to its GPIO pins. Instead of powering the backlight directly from the MCU, the backlight pin is connected to a transistor or MOSFET that switches the power to the LEDs.

## Usage

Most keyboards have backlighting enabled by default if they support it, but if it is not working for you, check that your `rules.mk` includes the following:

```make
BACKLIGHT_ENABLE = yes
```

You should then be able to use the keycodes below to change the backlight level.

## Keycodes

|Key      |Description                               |
|---------|------------------------------------------|
|`BL_TOGG`|Turn the backlight on or off              |
|`BL_STEP`|Cycle through backlight levels            |
|`BL_ON`  |Set the backlight to max brightness       |
|`BL_OFF` |Turn the backlight off                    |
|`BL_INC` |Increase the backlight level              |
|`BL_DEC` |Decrease the backlight level              |
|`BL_BRTG`|Toggle backlight breathing                |

## Caveats

This feature is distinct from both the [RGB underglow](feature_rgblight.md) and [RGB matrix](feature_rgb_matrix.md) features as it usually allows for only a single colour per switch, though you can obviously use multiple different coloured LEDs on a keyboard.

Hardware PWM is supported according to the following table:

|Backlight Pin|AT90USB64/128|ATmega16/32U4|ATmega16/32U2|ATmega32A|ATmega328P|
|-------------|-------------|-------------|-------------|---------|----------|
|`B1`         |             |             |             |         |Timer 1   |
|`B2`         |             |             |             |         |Timer 1   |
|`B5`         |Timer 1      |Timer 1      |             |         |          |
|`B6`         |Timer 1      |Timer 1      |             |         |          |
|`B7`         |Timer 1      |Timer 1      |Timer 1      |         |          |
|`C4`         |Timer 3      |             |             |         |          |
|`C5`         |Timer 3      |             |Timer 1      |         |          |
|`C6`         |Timer 3      |Timer 3      |Timer 1      |         |          |
|`D4`         |             |             |             |Timer 1  |          |
|`D5`         |             |             |             |Timer 1  |          |

All other pins will use software PWM. If the [Audio](feature_audio.md) feature is disabled or only using one timer, the backlight PWM can be triggered by a hardware timer:

|Audio Pin|Audio Timer|Software PWM Timer|
|---------|-----------|------------------|
|`C4`     |Timer 3    |Timer 1           |
|`C5`     |Timer 3    |Timer 1           |
|`C6`     |Timer 3    |Timer 1           |
|`B5`     |Timer 1    |Timer 3           |
|`B6`     |Timer 1    |Timer 3           |
|`B7`     |Timer 1    |Timer 3           |

When both timers are in use for Audio, the backlight PWM will not use a hardware timer, but will instead be triggered during the matrix scan. In this case, breathing is not supported, and the backlight might flicker, because the PWM computation may not be called with enough timing precision.

## Configuration

To change the behaviour of the backlighting, `#define` these in your `config.h`:

|Define               |Default      |Description                                                                                                  |
|---------------------|-------------|-------------------------------------------------------------------------------------------------------------|
|`BACKLIGHT_PIN`      |`B7`         |The pin that controls the LEDs. Unless you are designing your own keyboard, you shouldn't need to change this|
|`BACKLIGHT_PINS`     |*Not defined*|experimental: see below for more information                                                                 |
|`BACKLIGHT_LEVELS`   |`3`          |The number of brightness levels (maximum 31 excluding off)                                                   |
|`BACKLIGHT_CAPS_LOCK`|*Not defined*|Enable Caps Lock indicator using backlight (for keyboards without dedicated LED)                             |
|`BACKLIGHT_BREATHING`|*Not defined*|Enable backlight breathing, if supported                                                                     |
|`BREATHING_PERIOD`   |`6`          |The length of one backlight "breath" in seconds                                                              |
|`BACKLIGHT_ON_STATE` |`0`          |The state of the backlight pin when the backlight is "on" - `1` for high, `0` for low                        |

## Backlight On State

Most backlight circuits are driven by an N-channel MOSFET or NPN transistor. This means that to turn the transistor *on* and light the LEDs, you must drive the backlight pin, connected to the gate or base, *high*.
Sometimes, however, a P-channel MOSFET, or a PNP transistor is used. In this case, when the transistor is on, the pin is driven *low* instead.

This functionality is configured at the keyboard level with the `BACKLIGHT_ON_STATE` define.

## Multiple backlight pins

Most keyboards have only one backlight pin which control all backlight LEDs (especially if the backlight is connected to an hardware PWM pin).
In software PWM, it is possible to define multiple backlight pins. All those pins will be turned on and off at the same time during the PWM duty cycle.
This feature allows to set for instance the Caps Lock LED (or any other controllable LED) brightness at the same level as the other LEDs of the backlight. This is useful if you have mapped LCTRL in place of Caps Lock and you need the Caps Lock LED to be part of the backlight instead of being activated when Caps Lock is on.

To activate multiple backlight pins, you need to add something like this to your user `config.h`:

~~~c
#define BACKLIGHT_LED_COUNT 2
#undef BACKLIGHT_PIN
#define BACKLIGHT_PINS { F5, B2 }
~~~

## Hardware PWM Implementation

When using the supported pins for backlighting, QMK will use a hardware timer configured to output a PWM signal. This timer will count up to `ICRx` (by default `0xFFFF`) before resetting to 0.
The desired brightness is calculated and stored in the `OCRxx` register. When the counter reaches this value, the backlight pin will go low, and is pulled high again when the counter resets.
In this way `OCRxx` essentially controls the duty cycle of the LEDs, and thus the brightness, where `0x0000` is completely off and `0xFFFF` is completely on.

The breathing effect is achieved by registering an interrupt handler for `TIMER1_OVF_vect` that is called whenever the counter resets, roughly 244 times per second.
In this handler, the value of an incrementing counter is mapped onto a precomputed brightness curve. To turn off breathing, the interrupt handler is simply disabled, and the brightness reset to the level stored in EEPROM.

## Software PWM Implementation

When `BACKLIGHT_PIN` is not set to a hardware backlight pin, QMK will use a hardware timer configured to trigger software interrupts. This time will count up to `ICRx` (by default `0xFFFF`) before resetting to 0.
When resetting to 0, the CPU will fire an OVF (overflow) interrupt that will turn the LEDs on, starting the duty cycle.
The desired brightness is calculated and stored in the `OCRxx` register. When the counter reaches this value, the CPU will fire a Compare Output match interrupt, which will turn the LEDs off.
In this way `OCRxx` essentially controls the duty cycle of the LEDs, and thus the brightness, where `0x0000` is completely off and `0xFFFF` is completely on.

The breathing effect is the same as in the hardware PWM implementation.

## Backlight Functions

|Function  |Description                                                |
|----------|-----------------------------------------------------------|
|`backlight_toggle()`    |Turn the backlight on or off                 |
|`backlight_enable()`    |Turn the backlight on                        |
|`backlight_disable()`   |Turn the backlight off                       |
|`backlight_step()`      |Cycle through backlight levels               |
|`backlight_increase()`  |Increase the backlight level                 |
|`backlight_decrease()`  |Decrease the backlight level                 |
|`backlight_level(x)`    |Sets the backlight level, from 0 to          |
|                        |`BACKLIGHT_LEVELS`                           |
|`get_backlight_level()` |Return the current backlight level           |
|`is_backlight_enabled()`|Return whether the backlight is currently on |

### Backlight Breathing Functions

|Function  |Description                                               |
|----------|----------------------------------------------------------|
|`breathing_toggle()`  |Turn the backlight breathing on or off        |
|`breathing_enable()`  |Turns on backlight breathing                  |
|`breathing_disable()` |Turns off backlight breathing                 |
