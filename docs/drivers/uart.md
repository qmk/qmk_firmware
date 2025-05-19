# UART Driver {#uart-driver}

The UART drivers used in QMK have a set of common functions to allow portability between MCUs.

Currently, this driver does not support enabling hardware flow control (the `RTS` and `CTS` pins) if available, but may do so in future.

## Usage {#usage}

In most cases, the UART driver code is automatically included if you are using a feature or driver which requires it.

However, if you need to use the driver standalone, add the following to your `rules.mk`:

```make
UART_DRIVER_REQUIRED = yes
```

You can then call the UART API by including `uart.h` in your code.

## AVR Configuration {#avr-configuration}

No special setup is required - just connect the `RX` and `TX` pins of your UART device to the opposite pins on the MCU:

|MCU          |`TX`|`RX`|`CTS`|`RTS`|
|-------------|----|----|-----|-----|
|ATmega16/32U2|`D3`|`D2`|`D7` |`D6` |
|ATmega16/32U4|`D3`|`D2`|`D5` |`B7` |
|AT90USB64/128|`D3`|`D2`|*n/a*|*n/a*|
|ATmega32A    |`D1`|`D0`|*n/a*|*n/a*|
|ATmega328/P  |`D1`|`D0`|*n/a*|*n/a*|

## ChibiOS/ARM Configuration {#arm-configuration}

You'll need to determine which pins can be used for UART -- as an example, STM32 parts generally have multiple UART peripherals, labeled USART1, USART2, USART3 etc.

To enable UART, modify your board's `mcuconf.h` to enable the peripheral you've chosen, for example:

```c
#pragma once

#include_next <mcuconf.h>

#undef STM32_SERIAL_USE_USART2 // [!code focus]
#define STM32_SERIAL_USE_USART2 TRUE // [!code focus]
```

Configuration-wise, you'll need to set up the peripheral as per your MCU's datasheet -- the defaults match the pins for a Proton-C, i.e. STM32F303.

|`config.h` Override|Description                                                    |Default|
|-------------------|---------------------------------------------------------------|-------|
|`UART_DRIVER`      |USART peripheral to use - USART1 -> `SD1`, USART2 -> `SD2` etc.|`SD1`  |
|`UART_TX_PIN`      |The pin to use for TX                                          |`A9`   |
|`UART_TX_PAL_MODE` |The alternate function mode for TX                             |`7`    |
|`UART_RX_PIN`      |The pin to use for RX                                          |`A10`  |
|`UART_RX_PAL_MODE` |The alternate function mode for RX                             |`7`    |
|`UART_CTS_PIN`     |The pin to use for CTS                                         |`A11`  |
|`UART_CTS_PAL_MODE`|The alternate function mode for CTS                            |`7`    |
|`UART_RTS_PIN`     |The pin to use for RTS                                         |`A12`  |
|`UART_RTS_PAL_MODE`|The alternate function mode for RTS                            |`7`    |

## API {#api}

### `void uart_init(uint32_t baud)` {#api-uart-init}

Initialize the UART driver. This function must be called only once, before any of the below functions can be called.

#### Arguments {#api-uart-init-arguments}

 - `uint32_t baud`  
   The baud rate to transmit and receive at. This may depend on the device you are communicating with. Common values are 1200, 2400, 4800, 9600, 19200, 38400, 57600, and 115200.

---

### `void uart_write(uint8_t data)` {#api-uart-write}

Transmit a single byte.

#### Arguments {#api-uart-write-arguments}

 - `uint8_t data`  
   The byte to write.

---

### `uint8_t uart_read(void)` {#api-uart-read}

Receive a single byte.

#### Return Value {#api-uart-read-return}

The byte read from the receive buffer. This function will block if the buffer is empty (ie. no data to read).

---

### `void uart_transmit(const uint8_t *data, uint16_t length)` {#api-uart-transmit}

Transmit multiple bytes.

#### Arguments {#api-uart-transmit-arguments}

 - `const uint8_t *data`  
   A pointer to the data to write from.
 - `uint16_t length`  
   The number of bytes to write. Take care not to overrun the length of `data`.

---

### `void uart_receive(char *data, uint16_t length)` {#api-uart-receive}

Receive multiple bytes.

#### Arguments {#api-uart-receive-arguments}

 - `uint8_t *data`  
   A pointer to a buffer to read into.
 - `uint16_t length`  
   The number of bytes to read. Take care not to overrun the length of `data`.

---

### `bool uart_available(void)` {#api-uart-available}

Return whether the receive buffer contains data. Call this function to determine if `uart_read()` will return data immediately.

#### Return Value {#api-uart-available-return}

`true` if there is data available to read.
