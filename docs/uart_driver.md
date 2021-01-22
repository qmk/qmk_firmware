# UART Driver

The UART drivers used in QMK have a set of common functions to allow portability between MCUs.

Currently, this driver does not support enabling hardware flow control (the `RTS` and `CTS` pins) if available, but may do so in future.

## AVR Configuration

No special setup is required - just connect the `RX` and `TX` pins of your UART device to the opposite pins on the MCU:

|MCU          |`TX`|`RX`|`CTS`|`RTS`|
|-------------|----|----|-----|-----|
|ATmega16/32U2|`D3`|`D2`|`D7` |`D6` |
|ATmega16/32U4|`D3`|`D2`|`D5` |`B7` |
|AT90USB64/128|`D3`|`D2`|*n/a*|*n/a*|
|ATmega32A    |`D1`|`D0`|*n/a*|*n/a*|
|ATmega328/P  |`D1`|`D0`|*n/a*|*n/a*|

## ChibiOS/ARM Configuration

You'll need to determine which pins can be used for UART -- as an example, STM32 parts generally have multiple UART peripherals, labeled USART1, USART2, USART3 etc.

To enable UART, modify your board's `halconf.h` to enable the serial driver:

```c
#define HAL_USE_SERIAL TRUE
```

Then, modify your board's `mcuconf.h` to enable the peripheral you've chosen, for example:

```c
#undef STM32_SERIAL_USE_USART2
#define STM32_SERIAL_USE_USART2 TRUE
```

Configuration-wise, you'll need to set up the peripheral as per your MCU's datasheet -- the defaults match the pins for a Proton-C, i.e. STM32F303.

|`config.h` override       |Description                                                    |Default Value|
|--------------------------|---------------------------------------------------------------|-------------|
|`#define SERIAL_DRIVER`   |USART peripheral to use - USART1 -> `SD1`, USART2 -> `SD2` etc.|`SD1`        |
|`#define SD1_TX_PIN`      |The pin to use for TX                                          |`A9`         |
|`#define SD1_TX_PAL_MODE` |The alternate function mode for TX                             |`7`          |
|`#define SD1_RX_PIN`      |The pin to use for RX                                          |`A10`        |
|`#define SD1_RX_PAL_MODE` |The alternate function mode for RX                             |`7`          |
|`#define SD1_CTS_PIN`     |The pin to use for CTS                                         |`A11`        |
|`#define SD1_CTS_PAL_MODE`|The alternate function mode for CTS                            |`7`          |
|`#define SD1_RTS_PIN`     |The pin to use for RTS                                         |`A12`        |
|`#define SD1_RTS_PAL_MODE`|The alternate function mode for RTS                            |`7`          |

## Functions

### `void uart_init(uint32_t baud)`

Initialize the UART driver. This function must be called only once, before any of the below functions can be called.

#### Arguments

 - `uint32_t baud`  
   The baud rate to transmit and receive at. This may depend on the device you are communicating with. Common values are 1200, 2400, 4800, 9600, 19200, 38400, 57600, and 115200.

---

### `void uart_putchar(uint8_t c)`

Transmit a single byte.

#### Arguments

 - `uint8_t c`  
   The byte (character) to send, from 0 to 255.

---

### `uint8_t uart_getchar(void)`

Receive a single byte.

#### Return Value

The byte read from the receive buffer.

---

### `bool uart_available(void)`

Return whether the receive buffer contains data. Call this function to determine if `uart_getchar()` will return meaningful data.

#### Return Value

`true` if the receive buffer length is non-zero.
