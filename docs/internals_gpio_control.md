# GPIO Control

QMK has a GPIO control abstraction layer which is micro-controller agnostic. This is done to allow easy access to pin control across different platforms.

## Functions

The following functions can provide basic control of GPIOs and are found in `quantum/quantum.h`.

|Function              |Description                                                       |
|----------------------|------------------------------------------------------------------|
|`setPinInput(pin)`    |Set pin as input with high impedance (High-Z)                     |
|`setPinInputHigh(pin)`|Set pin as input with build in pull-up                            |
|`setPinInputLow(pin)` |Set pin as input with build in pull-down (Supported only on STM32)|
|`setPinOutput(pin)`   |Set pin as output                                                 |
|`writePinHige(pin)`   |Set pin level as high, assuming it is an output                   |
|`writePinLow(pin)`    |Set pin level as low, assuming it is an output                    |
|`writePin(pin, level)`|Set pin level, assuming it is an output                           |
|`readPin(pin)`        |Returns the level of the pin                                      |

## Advance settings

Each micro-controller can have multiple advance settings regarding its GPIO. This abstraction layer does not limit the use of architecture specific functions. Advance users should consult the datasheet of there desired device and include any needed libraries. For AVR the standard avr/io.h library is used and for STM32 the Chibios [PAL library](http://chibios.sourceforge.net/docs3/hal/group___p_a_l.html) is used.

