# GPIO Control :id=gpio-control

QMK has a GPIO control abstraction layer which is microcontroller agnostic. This is done to allow easy access to pin control across different platforms.

## Functions :id=functions

The following functions can provide basic control of GPIOs and are found in `quantum/quantum.h`.

### `setPinInput(pin)` :id=setpininput

Set pin as input with high impedance (High-Z).

| Architecture | Old Function                          |
|--------------|---------------------------------------|
| AVR          | `DDRB &= ~(1<<2)`                     |
| ARM/ChibiOS  | `palSetLineMode(pin, PAL_MODE_INPUT)` |

### `setPinInputHigh(pin)` :id=setpininputhigh

Set pin as input with builtin pull-up resistor.

| Architecture | Old Function                                 |
|--------------|----------------------------------------------|
| AVR          | `DDRB &= ~(1<<2); PORTB \|= (1<<2)`          |
| ARM/ChibiOS  | `palSetLineMode(pin, PAL_MODE_INPUT_PULLUP)` |

### `setPinInputLow(pin)` :id=setpininputlow

Set pin as input with builtin pull-down resistor.

| Architecture | Old Function                                   |
|--------------|------------------------------------------------|
| AVR          | N/A (Not supported on AVR)                     |
| ARM/ChibiOS  | `palSetLineMode(pin, PAL_MODE_INPUT_PULLDOWN)` |

### `setPinOutput(pin)` :id=setpinoutput

Set pin as output.

| Architecture | Old Function                                    |
|--------------|-------------------------------------------------|
| AVR          | `DDRB \|= (1<<2)`                               |
| ARM/ChibiOS  | `palSetLineMode(pin, PAL_MODE_OUTPUT_PUSHPULL)` |

### `writePinHigh(pin)` :id=writepinhigh

Set pin level as high, assuming it is an output.

| Architecture | Old Function       |
|--------------|--------------------|
| AVR          | `PORTB \|= (1<<2)` |
| ARM/ChibiOS  | `palSetLine(pin)`  |


### `writePinLow(pin)` :id=writepinlow

Set pin level as low, assuming it is an output.

| Architecture | Old Function                                 |
|--------------|----------------------------------------------|
| AVR          | `PORTB &= ~(1<<2)`                           |
| ARM/ChibiOS  | `palClearLine(pin)`                          |


### `writePin(pin, level)` :id=writepin

Set pin level, assuming it is an output.

| Architecture | Old Function                                    |
|--------------|-------------------------------------------------|
| AVR          | `(level) ? PORTB \|= (1<<2) : PORTB &= ~(1<<2)` |
| ARM/ChibiOS  | `(level) ? palSetLine(pin) : palClearLine(pin)` |


### `readPin(pin)` :id=readpin

Returns the level of the pin.

| Architecture | Old Function                          |
|--------------|---------------------------------------|
| AVR          | `_SFR_IO8(pin >> 4) & _BV(pin & 0xF)` |
| ARM/ChibiOS  | `palReadLine(pin)`                    |

## Advanced Settings :id=advanced-settings

Each microcontroller can have multiple advanced settings regarding its GPIO. This abstraction layer does not limit the use of architecture-specific functions. Advanced users should consult the datasheet of their desired device and include any needed libraries. For AVR, the standard avr/io.h library is used; for STM32, the ChibiOS [PAL library](http://chibios.sourceforge.net/docs3/hal/group___p_a_l.html) is used.
