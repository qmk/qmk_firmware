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

Hardware PWM is only supported on certain pins of the MCU, so if the backlighting is not connected to one of them, a software implementation will be used, and backlight breathing will not be available. Currently the supported pins are `B5`, `B6`, `B7`, and `C6`.

## Configuration

To change the behaviour of the backlighting, `#define` these in your `config.h`:

|Define               |Default      |Description                                                                                                  |
|---------------------|-------------|-------------------------------------------------------------------------------------------------------------|
|`BACKLIGHT_PIN`      |`B7`         |The pin that controls the LEDs. Unless you are designing your own keyboard, you shouldn't need to change this|
|`BACKLIGHT_LEVELS`   |`3`          |The number of brightness levels (maximum 15 excluding off)                                                   |
|`BACKLIGHT_BREATHING`|*Not defined*|Enable backlight breathing, if hardware PWM is used                                                          |
|`BREATHING_PERIOD`   |`6`          |The length of one backlight "breath" in seconds                                                              |

## Hardware PWM Implementation

When using the supported pins for backlighting, QMK will use a hardware timer configured to output a PWM signal. This timer will count up to `ICRx` (by default `0xFFFF`) before resetting to 0.
The desired brightness is calculated and stored in the `OCRxx` register. When the counter reaches this value, the backlight pin will go low, and is pulled high again when the counter resets.
In this way `OCRxx` essentially controls the duty cycle of the LEDs, and thus the brightness, where `0x0000` is completely off and `0xFFFF` is completely on.

The breathing effect is achieved by registering an interrupt handler for `TIMER1_OVF_vect` that is called whenever the counter resets, roughly 244 times per second.
In this handler, the value of an incrementing counter is mapped onto a precomputed brightness curve. To turn off breathing, the interrupt handler is simply disabled, and the brightness reset to the level stored in EEPROM.

## Backlight Functions

|Function  |Description                                               |
|----------|----------------------------------------------------------|
|`backlight_toggle()`   |Turn the backlight on or off                 |
|`backlight_step()`     |Cycle through backlight levels               |
|`backlight_increase()` |Increase the backlight level                 |
|`backlight_decrease()` |Decrease the backlight level                 |
|`backlight_level(x)`   |Sets the backlight level to specified level  |
|`get_backlight_level()`|Toggle backlight breathing                   |

### Backlight Breathing Functions

|Function  |Description                                               |
|----------|----------------------------------------------------------|
|`breathing_toggle()`  |Turn the backlight breathing on or off        |
|`breathing_enable()`  |Turns on backlight breathing                  |
|`breathing_disable()` |Turns off backlight breathing                 |
