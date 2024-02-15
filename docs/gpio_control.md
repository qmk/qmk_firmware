# GPIO Control :id=gpio-control

QMK has a GPIO control abstraction layer which is microcontroller agnostic. This is done to allow easy access to pin control across different platforms.

## Macros :id=macros

The following macros provide basic control of GPIOs and are found in `platforms/<platform>/gpio.h`.

|Macro                                |Description                                                          |
|-------------------------------------|---------------------------------------------------------------------|
|`gpio_set_pin_input(pin)`            |Set pin as input with high impedance (High-Z)                        |
|`gpio_set_pin_input_high(pin)`       |Set pin as input with builtin pull-up resistor                       |
|`gpio_set_pin_input_low(pin)`        |Set pin as input with builtin pull-down resistor (unavailable on AVR)|
|`gpio_set_pin_output(pin)`           |Set pin as output (alias of `gpio_set_pin_output_push_pull`)         |
|`gpio_set_pin_output_push_pull(pin)` |Set pin as output, push/pull mode                                    |
|`gpio_set_pin_output_open_drain(pin)`|Set pin as output, open-drain mode (unavailable on AVR and ATSAM)    |
|`gpio_write_pin_high(pin)`           |Set pin level as high, assuming it is an output                      |
|`gpio_write_pin_low(pin)`            |Set pin level as low, assuming it is an output                       |
|`gpio_write_pin(pin, level)`         |Set pin level, assuming it is an output                              |
|`gpio_read_pin(pin)`                 |Returns the level of the pin                                         |
|`gpio_toggle_pin(pin)`               |Invert pin level, assuming it is an output                           |

## Advanced Settings :id=advanced-settings

Each microcontroller can have multiple advanced settings regarding its GPIO. This abstraction layer does not limit the use of architecture-specific functions. Advanced users should consult the datasheet of their desired device. For AVR, the standard `avr/io.h` library is used; for STM32, the ChibiOS [PAL library](https://chibios.sourceforge.net/docs3/hal/group___p_a_l.html) is used.

## Atomic Operation :id=atomic-operation

The above functions are not always guaranteed to work atomically. Therefore, if you want to prevent interruptions in the middle of operations when using multiple combinations of the above functions, use the following `ATOMIC_BLOCK_FORCEON` macro.

eg.
```c
void some_function(void) {
     // some process
     ATOMIC_BLOCK_FORCEON {
        // Atomic Processing
     }
     // some process
}
```

`ATOMIC_BLOCK_FORCEON` forces interrupts to be disabled before the block is executed, without regard to whether they are enabled or disabled. Then, after the block is executed, the interrupt is enabled.

Note that `ATOMIC_BLOCK_FORCEON` can therefore be used if you know that interrupts are enabled before the execution of the block, or if you know that it is OK to enable interrupts at the completion of the block.
