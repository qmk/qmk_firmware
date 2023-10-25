# UART Driver :id=uart-driver

The UART drivers used in QMK have a set of common functions to allow portability between MCUs.

Currently, this driver does not support enabling hardware flow control (the `RTS` and `CTS` pins) if available, but may do so in future.

## Usage :id=usage

In most cases, the UART driver code is automatically included if you are using a feature or driver which requires it.

However, if you need to use the driver standalone, add the following to your `rules.mk`:

```make
UART_DRIVER_REQUIRED = yes
```

You can then call the UART API by including `uart.h` in your code.

## AVR Configuration :id=avr-configuration

No special setup is required - just connect the `RX` and `TX` pins of your UART device to the opposite pins on the MCU:

|MCU          |`TX`|`RX`|`CTS`|`RTS`|
|-------------|----|----|-----|-----|
|ATmega16/32U2|`D3`|`D2`|`D7` |`D6` |
|ATmega16/32U4|`D3`|`D2`|`D5` |`B7` |
|AT90USB64/128|`D3`|`D2`|*n/a*|*n/a*|
|ATmega32A    |`D1`|`D0`|*n/a*|*n/a*|
|ATmega328/P  |`D1`|`D0`|*n/a*|*n/a*|

## ChibiOS/ARM Configuration :id=arm-configuration

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

## API :id=api

### `void uart_init(uint32_t baud)` :id=api-uart-init

Initialize the UART driver. This function must be called only once, before any of the below functions can be called.

#### Arguments :id=api-uart-init-arguments

 - `uint32_t baud`  
   The baud rate to transmit and receive at. This may depend on the device you are communicating with. Common values are 1200, 2400, 4800, 9600, 19200, 38400, 57600, and 115200.

---

### `void uart_write(uint8_t data)` :id=api-uart-write

Transmit a single byte.

#### Arguments :id=api-uart-write-arguments

 - `uint8_t data`  
   The byte to write.

---

### `uint8_t uart_read(void)` :id=api-uart-read

Receive a single byte.

#### Return Value :id=api-uart-read-return

The byte read from the receive buffer. This function will block if the buffer is empty (ie. no data to read).

---

### `void uart_transmit(const uint8_t *data, uint16_t length)` :id=api-uart-transmit

Transmit multiple bytes.

#### Arguments :id=api-uart-transmit-arguments

 - `const uint8_t *data`  
   A pointer to the data to write from.
 - `uint16_t length`  
   The number of bytes to write. Take care not to overrun the length of `data`.

---

### `void uart_receive(char *data, uint16_t length)` :id=api-uart-receive

Receive multiple bytes.

#### Arguments :id=api-uart-receive-arguments

 - `uint8_t *data`  
   A pointer to the buffer to read into.
 - `uint16_t length`  
   The number of bytes to read. Take care not to overrun the length of `data`.

---

### `bool uart_available(void)` :id=api-uart-available

Return whether the receive buffer contains data. Call this function to determine if `uart_read()` will return data immediately.

#### Return Value :id=api-uart-available-return

`true` if the receive buffer length is non-zero.
