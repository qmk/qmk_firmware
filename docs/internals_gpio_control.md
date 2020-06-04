# GPIO Control :id=gpio-control

QMK has a GPIO control abstraction layer which is microcontroller agnostic. This is done to allow easy access to pin control across different platforms.

## Functions :id=functions

The following functions can provide basic control of GPIOs and are found in `quantum/quantum.h`.

|Function                |Description                                       | Old AVR Examples                                    | Old ChibiOS/ARM Examples                        |
|------------------------|--------------------------------------------------|-----------------------------------------------------|-------------------------------------------------|
| `setPinInput(pin)`     | Set pin as input with high impedance (High-Z)    | `DDRB &= ~(1<<pin)`                                 | `palSetLineMode(pin, PAL_MODE_INPUT)`           |
| `setPinInputHigh(pin)` | Set pin as input with builtin pull-up resistor   | `DDRB &= ~(1<<pin); PORTB \|= (1<<pin)`             | `palSetLineMode(pin, PAL_MODE_INPUT_PULLUP)`    |
| `setPinInputLow(pin)`  | Set pin as input with builtin pull-down resistor | N/A (Not supported on AVR)                          | `palSetLineMode(pin, PAL_MODE_INPUT_PULLDOWN)`  |
| `setPinOutput(pin)`    | Set pin as output                                | `DDRB \|= (1<<pin)`                                 | `palSetLineMode(pin, PAL_MODE_OUTPUT_PUSHPULL)` |
| `writePinHigh(pin)`    | Set pin level as high, assuming it is an output  | `PORTB \|= (1<<pin)`                                | `palSetLine(pin)`                               |
| `writePinLow(pin)`     | Set pin level as low, assuming it is an output   | `PORTB &= ~(1<<pin)`                                | `palClearLine(pin)`                             |
| `writePin(pin, lvl)`   | Set pin level, assuming it is an output          | `(lvl) ? PORTB \|= (1<<pin) : PORTB &= ~(1<<pin)`   | `(lvl) ? palSetLine(pin) : palClearLine(pin)`   |
| `readPin(pin)`         | Returns the level of the pin                     | `_SFR_IO8(pin >> 4) & _BV(pin & 0xF)`               | `palReadLine(pin)`                              |
| `togglePin(pin)`       | Invert pin level, assuming it is an output       | `PORTB ^= (1<<pin)`                                 | `palToggleLine(pin)`                            |

## Advanced Settings :id=advanced-settings

Each microcontroller can have multiple advanced settings regarding its GPIO. This abstraction layer does not limit the use of architecture-specific functions. Advanced users should consult the datasheet of their desired device and include any needed libraries. For AVR, the standard avr/io.h library is used; for STM32, the ChibiOS [PAL library](http://chibios.sourceforge.net/docs3/hal/group___p_a_l.html) is used.
