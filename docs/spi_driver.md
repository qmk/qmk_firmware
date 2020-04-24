# SPI Master Driver

The SPI Master drivers used in QMK have a set of common functions to allow portability between MCUs.

## AVR Configuration

No special setup is required - just connect the `SS`, `SCK`, `MOSI` and `MISO` pins of your SPI devices to the matching pins on the MCU:

|MCU            |`SS`|`SCK`|`MOSI`|`MISO`|
|---------------|----|-----|------|------|
|ATMega16/32U2/4|`B0`|`B1` |`B2`  |`B3`  |
|AT90USB64/128  |`B0`|`B1` |`B2`  |`B3`  |
|ATmega32A      |`B4`|`B7` |`B5`  |`B6`  |
|ATmega328P     |`B2`|`B5` |`B3`  |`B4`  |

You may use more than one slave select pin, not just the `SS` pin. This is useful when you have multiple devices connected and need to communicate with them individually.
`SPI_SS_PIN` can be passed to `spi_start()` to refer to `SS`.

## ChibiOS/ARM Configuration

ARM support for this driver is not ready yet. Check back later!

## Functions

### `void spi_init(void)`

Initialize the SPI driver. This function must be called only once, before any of the below functions can be called.

---

### `bool spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor)`

Start an SPI transaction.

#### Arguments

 - `pin_t slavePin`  
   The QMK pin to assert as the slave select pin, eg. `B4`.
 - `bool lsbFirst`  
   Determines the endianness of the transmission. If `true`, the least significant bit of each byte is sent first.
 - `uint8_t mode`  
   The SPI mode to use:

   |Mode|Clock Polarity      |Clock Phase            |
   |----|--------------------|-----------------------|
   |`0` |Leading edge rising |Sample on leading edge |
   |`1` |Leading edge rising |Sample on trailing edge|
   |`2` |Leading edge falling|Sample on leading edge |
   |`3` |Leading edge falling|Sample on trailing edge|

 - `uint16_t divisor`  
   The SPI clock divisor, will be rounded up to the nearest power of two. This number can be calculated by dividing the MCU's clock speed by the desired SPI clock speed. For example, an MCU running at 8 MHz wanting to talk to an SPI device at 4 MHz would set the divisor to `2`.

#### Return Value

`false` if the supplied parameters are invalid or the SPI peripheral is already in use, or `true`.

---

### `spi_status_t spi_write(uint8_t data)`

Write a byte to the selected SPI device.

#### Arguments

 - `uint8_t data`  
   The byte to write.

#### Return Value

`SPI_STATUS_TIMEOUT` if the timeout period elapses, or `SPI_STATUS_SUCCESS`.

---

### `spi_status_t spi_read(void)`

Read a byte from the selected SPI device.

#### Return Value

`SPI_STATUS_TIMEOUT` if the timeout period elapses, or the byte read from the device.

---

### `spi_status_t spi_transmit(const uint8_t *data, uint16_t length)`

Send multiple bytes to the selected SPI device.

#### Arguments

 - `const uint8_t *data`  
   A pointer to the data to write from.
 - `uint16_t length`  
   The number of bytes to write. Take care not to overrun the length of `data`.

#### Return Value

`SPI_STATUS_TIMEOUT` if the timeout period elapses, `SPI_STATUS_SUCCESS` on success, or `SPI_STATUS_ERROR` otherwise.

---

### `spi_status_t spi_receive(uint8_t *data, uint16_t length)`

Receive multiple bytes from the selected SPI device.

#### Arguments

 - `uint8_t *data`  
   A pointer to the buffer to read into.
 - `uint16_t length`  
   The number of bytes to read. Take care not to overrun the length of `data`.

#### Return Value

`SPI_STATUS_TIMEOUT` if the internal transmission timeout period elapses, `SPI_STATUS_SUCCESS` on success, or `SPI_STATUS_ERROR` otherwise.

---

### `void spi_stop(void)`

End the current SPI transaction. This will deassert the slave select pin and reset the endianness, mode and divisor configured by `spi_start()`.
