# GPIO Control :id=gpio-control

QMK has a GPIO control abstraction layer which is microcontroller agnostic. This is done to allow easy access to pin control across different platforms.

## Functions :id=functions

The following functions provide basic control of GPIOs and are found in `platforms/<platform>/gpio.h`.

| Function                     | Description                                         | Old AVR Examples                                | Old ChibiOS/ARM Examples                         |
|------------------------------|-----------------------------------------------------|-------------------------------------------------|--------------------------------------------------|
| `setPinInput(pin)`           | Set pin as input with high impedance (High-Z)       | `DDRB &= ~(1<<2)`                               | `palSetLineMode(pin, PAL_MODE_INPUT)`            |
| `setPinInputHigh(pin)`       | Set pin as input with builtin pull-up resistor      | `DDRB &= ~(1<<2); PORTB \|= (1<<2)`             | `palSetLineMode(pin, PAL_MODE_INPUT_PULLUP)`     |
| `setPinInputLow(pin)`        | Set pin as input with builtin pull-down resistor    | N/A (Not supported on AVR)                      | `palSetLineMode(pin, PAL_MODE_INPUT_PULLDOWN)`   |
| `setPinOutput(pin)`          | Set pin as output (alias of `setPinOutputPushPull`) | `DDRB \|= (1<<2)`                               | `palSetLineMode(pin, PAL_MODE_OUTPUT_PUSHPULL)`  |
| `setPinOutputPushPull(pin)`  | Set pin as output, push/pull mode                   | `DDRB \|= (1<<2)`                               | `palSetLineMode(pin, PAL_MODE_OUTPUT_PUSHPULL)`  |
| `setPinOutputOpenDrain(pin)` | Set pin as output, open-drain mode                  | N/A (Not implemented on AVR)                    | `palSetLineMode(pin, PAL_MODE_OUTPUT_OPENDRAIN)` |
| `writePinHigh(pin)`          | Set pin level as high, assuming it is an output     | `PORTB \|= (1<<2)`                              | `palSetLine(pin)`                                |
| `writePinLow(pin)`           | Set pin level as low, assuming it is an output      | `PORTB &= ~(1<<2)`                              | `palClearLine(pin)`                              |
| `writePin(pin, level)`       | Set pin level, assuming it is an output             | `(level) ? PORTB \|= (1<<2) : PORTB &= ~(1<<2)` | `(level) ? palSetLine(pin) : palClearLine(pin)`  |
| `readPin(pin)`               | Returns the level of the pin                        | `_SFR_IO8(pin >> 4) & _BV(pin & 0xF)`           | `palReadLine(pin)`                               |
| `togglePin(pin)`             | Invert pin level, assuming it is an output          | `PORTB ^= (1<<2)`                               | `palToggleLine(pin)`                             |

## Advanced Settings :id=advanced-settings

Each microcontroller can have multiple advanced settings regarding its GPIO. This abstraction layer does not limit the use of architecture-specific functions. Advanced users should consult the datasheet of their desired device and include any needed libraries. For AVR, the standard avr/io.h library is used; for STM32, the ChibiOS [PAL library](https://chibios.sourceforge.net/docs3/hal/group___p_a_l.html) is used.

## Atomic Operation

The above functions are not always guaranteed to work atomically. Therefore, if you want to prevent interruptions in the middle of operations when using multiple combinations of the above functions, use the following `ATOMIC_BLOCK_FORCEON` macro.

eg.
```c
void some_function() {
     // some process
     ATOMIC_BLOCK_FORCEON {
        // Atomic Processing
     }
     // some process
}
```

`ATOMIC_BLOCK_FORCEON` forces interrupts to be disabled before the block is executed, without regard to whether they are enabled or disabled. Then, after the block is executed, the interrupt is enabled.

Note that `ATOMIC_BLOCK_FORCEON` can therefore be used if you know that interrupts are enabled before the execution of the block, or if you know that it is OK to enable interrupts at the completion of the block.
