# I2C Master Driver {#i2c-master-driver}

The I2C Master drivers used in QMK have a set of common functions to allow portability between MCUs.

## Usage {#usage}

In most cases, the I2C Master driver code is automatically included if you are using a feature or driver which requires it, such as [OLED](../features/oled_driver).

However, if you need to use the driver standalone, add the following to your `rules.mk`:

```make
I2C_DRIVER_REQUIRED = yes
```

You can then call the I2C API by including `i2c_master.h` in your code.

## I2C Addressing {#note-on-i2c-addresses}

I2C addresses listed on datasheets and the internet are usually represented as a 7-bit value. The eighth bit (the least significant bit) controls whether the operation is a read or a write.

All of the address parameters expected by the driver API should therefore be pushed to the upper 7 bits of the address byte; the driver will take care of setting the read/write bit as appropriate.

This is easy to do via the bitwise left shift operator. For example, if your device has an address of `0x18` you might create a define for convenience:

```c
#define MY_I2C_ADDRESS (0x18 << 1)
```

Or, you can shift the address ahead of time:

```c
#define MY_I2C_ADDRESS 0x30
```

See https://www.robot-electronics.co.uk/i2c-tutorial for more information about I2C addressing and other technical details.

## AVR Configuration {#avr-configuration}

The following defines can be used to configure the I2C master driver:

|`config.h` Override|Description          |Default |
|-------------------|---------------------|--------|
|`F_SCL`            |Clock frequency in Hz|`400000`|

No further setup is required - just connect the `SDA` and `SCL` pins of your I2C devices to the matching pins on the MCU:

|MCU          |`SCL`|`SDA`|
|-------------|-----|-----|
|ATmega16/32U4|`D0` |`D1` |
|AT90USB64/128|`D0` |`D1` |
|ATmega32A    |`C0` |`C1` |
|ATmega328/P  |`C5` |`C4` |

::: tip
The ATmega16/32U2 does not possess I2C functionality, and so cannot use this driver.
:::

## ChibiOS/ARM Configuration {#arm-configuration}

You'll need to determine which pins can be used for I2C -- as an example, STM32 parts generally have multiple I2C peripherals, labeled I2C1, I2C2, I2C3 etc.

To enable I2C, modify your board's `halconf.h` to enable I2C, then modify your board's `mcuconf.h` to enable the peripheral you've chosen:

::: code-group
```c [halconf.h]
#pragma once

#define HAL_USE_I2C TRUE // [!code focus]

#include_next <halconf.h>
```
```c [mcuconf.h]
#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C2 // [!code focus]
#define STM32_I2C_USE_I2C2 TRUE // [!code focus]
```
:::

|`mcuconf.h` Setting         |Description                                                                       |Default|
|----------------------------|----------------------------------------------------------------------------------|-------|
|`STM32_I2C_BUSY_TIMEOUT`    |Time in milliseconds until the I2C command is aborted if no response is received  |`50`   |
|`STM32_I2C_XXX_IRQ_PRIORITY`|Interrupt priority for hardware driver XXX (THIS IS AN EXPERT SETTING)            |`10`   |
|`STM32_I2C_USE_DMA`         |Enable/Disable the ability of the MCU to offload the data transfer to the DMA unit|`TRUE` |
|`STM32_I2C_XXX_DMA_PRIORITY`|Priority of DMA unit for hardware driver XXX (THIS IS AN EXPERT SETTING)          |`1`    |

Configuration-wise, you'll need to set up the peripheral as per your MCU's datasheet -- the defaults match the pins for a Proton-C, i.e. STM32F303.

|`config.h` Override|Description                                                  |Default|
|-------------------|-------------------------------------------------------------|-------|
|`I2C_DRIVER`       |I2C peripheral to use - I2C1 -> `I2CD1`, I2C2 -> `I2CD2` etc.|`I2CD1`|
|`I2C1_SCL_PIN`     |The pin to use for SCL                                       |`B6`   |
|`I2C1_SCL_PAL_MODE`|The alternate function mode for SCL                          |`4`    |
|`I2C1_SDA_PIN`     |The pin to use for SDA                                       |`B7`   |
|`I2C1_SDA_PAL_MODE`|The alternate function mode for SDA                          |`4`    |

::: tip
Currently only a single I2C peripheral is supported, therefore the `I2C1_*` defines are used for configuration regardless of the selected peripheral.
:::

The following configuration values are dependent on the ChibiOS I2C LLD, which is dictated by the microcontroller.

### I2Cv1 {#arm-configuration-i2cv1}

* STM32F1xx
* STM32F2xx
* STM32F4xx
* STM32L0xx
* STM32L1xx

See [this page](https://www.playembedded.org/blog/stm32-i2c-chibios/#7_I2Cv1_configuration_structure) for the I2Cv1 configuration structure.

|`config.h` Override|Default         |
|-------------------|----------------|
|`I2C1_OPMODE`      |`OPMODE_I2C`    |
|`I2C1_CLOCK_SPEED` |`100000`        |
|`I2C1_DUTY_CYCLE`  |`STD_DUTY_CYCLE`|

### I2Cv2 {#arm-configuration-i2cv2}

* STM32F0xx
* STM32F3xx
* STM32F7xx
* STM32L4xx

See [this page](https://www.playembedded.org/blog/stm32-i2c-chibios/#8_I2Cv2_I2Cv3_configuration_structure) for the I2Cv2 configuration structure.

|`config.h` Override  |Default|
|---------------------|-------|
|`I2C1_TIMINGR_PRESC` |`0U`   |
|`I2C1_TIMINGR_SCLDEL`|`7U`   |
|`I2C1_TIMINGR_SDADEL`|`0U`   |
|`I2C1_TIMINGR_SCLH`  |`38U`  |
|`I2C1_TIMINGR_SCLL`  |`129U` |

## API {#api}

### `void i2c_init(void)` {#api-i2c-init}

Initialize the I2C driver. This function must be called only once, before any of the below functions can be called.

This function is weakly defined, meaning it can be overridden if necessary for your particular use case:

```c
void i2c_init(void) {
    gpio_set_pin_input(B6); // Try releasing special pins for a short time
    gpio_set_pin_input(B7);
    wait_ms(10); // Wait for the release to happen

    palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B6 to I2C function
    palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B7 to I2C function
}
```

---

### `i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout)` {#api-i2c-transmit}

Send multiple bytes to the selected I2C device.

#### Arguments {#api-i2c-transmit-arguments}

 - `uint8_t address`  
   The 7-bit I2C address of the device.
 - `const uint8_t* data`  
   A pointer to the data to transmit.
 - `uint16_t length`  
   The number of bytes to write. Take care not to overrun the length of `data`.
 - `uint16_t timeout`  
   The time in milliseconds to wait for a response from the target device.

#### Return Value {#api-i2c-transmit-return}

`I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.

---

### `i2c_status_t i2c_transmit_P(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout)` {#api-i2c-transmit-p}

Send multiple bytes from PROGMEM to the selected I2C device.

On ARM devices, this function is simply an alias for `i2c_transmit(address, data, length, timeout)`.

#### Arguments {#api-i2c-transmit-p-arguments}

 - `uint8_t address`  
   The 7-bit I2C address of the device.
 - `const uint8_t* data`  
   A pointer to the data to transmit.
 - `uint16_t length`  
   The number of bytes to write. Take care not to overrun the length of `data`.
 - `uint16_t timeout`  
   The time in milliseconds to wait for a response from the target device.

#### Return Value {#api-i2c-transmit-p-return}

`I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.

---

### `i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)` {#api-i2c-receive}

Receive multiple bytes from the selected I2C device.

#### Arguments {#api-i2c-receive-arguments}

 - `uint8_t address`  
   The 7-bit I2C address of the device.
 - `uint8_t* data`  
   A pointer to a buffer to read into.
 - `uint16_t length`  
   The number of bytes to read. Take care not to overrun the length of `data`.
 - `uint16_t timeout`  
   The time in milliseconds to wait for a response from the target device.

#### Return Value {#api-i2c-receive-return}

`I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.

---

### `i2c_status_t i2c_write_register(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout)` {#api-i2c-write-register}

Write to a register with an 8-bit address on the I2C device.

#### Arguments {#api-i2c-write-register-arguments}

 - `uint8_t devaddr`  
   The 7-bit I2C address of the device.
 - `uint8_t regaddr`  
   The register address to write to.
 - `const uint8_t* data`  
   A pointer to the data to transmit.
 - `uint16_t length`  
   The number of bytes to write. Take care not to overrun the length of `data`.
 - `uint16_t timeout`  
   The time in milliseconds to wait for a response from the target device.

#### Return Value {#api-i2c-write-register-return}

`I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.

---

### `i2c_status_t i2c_write_register16(uint8_t devaddr, uint16_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout)` {#api-i2c-write-register16}

Write to a register with a 16-bit address (big endian) on the I2C device.

#### Arguments {#api-i2c-write-register16-arguments}

 - `uint8_t devaddr`  
   The 7-bit I2C address of the device.
 - `uint16_t regaddr`  
   The register address to write to.
 - `const uint8_t* data`  
   A pointer to the data to transmit.
 - `uint16_t length`  
   The number of bytes to write. Take care not to overrun the length of `data`.
 - `uint16_t timeout`  
   The time in milliseconds to wait for a response from the target device.

#### Return Value {#api-i2c-write-register16-return}

`I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.

---

### `i2c_status_t i2c_read_register(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout)` {#api-i2c-read-register}

Read from a register with an 8-bit address on the I2C device.

#### Arguments {#api-i2c-read-register-arguments}

 - `uint8_t devaddr`  
   The 7-bit I2C address of the device.
 - `uint8_t regaddr`  
   The register address to read from.
 - `uint8_t data`  
   A pointer to a buffer to read into.
 - `uint16_t length`  
   The number of bytes to read. Take care not to overrun the length of `data`.
 - `uint16_t timeout`  
   The time in milliseconds to wait for a response from the target device.

#### Return Value {#api-i2c-read-register-return}

`I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.

---

### `i2c_status_t i2c_read_register16(uint8_t devaddr, uint16_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout)` {#api-i2c-read-register16}

Read from a register with a 16-bit address (big endian) on the I2C device.

#### Arguments {#api-i2c-read-register16-arguments}

 - `uint8_t devaddr`  
   The 7-bit I2C address of the device.
 - `uint16_t regaddr`  
   The register address to read from.
 - `uint8_t* data`  
   A pointer to a buffer to read into.
 - `uint16_t length`  
   The number of bytes to read. Take care not to overrun the length of `data`.
 - `uint16_t timeout`  
   The time in milliseconds to wait for a response from the target device.

#### Return Value {#api-i2c-read-register16-return}

`I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.

---

### `i2c_status_t i2c_ping_address(uint8_t address, uint16_t timeout)` {#api-i2c-ping-address}

Ping the I2C bus for a specific address.

On ChibiOS a "best effort" attempt is made by reading a single byte from register 0 at the given address. This should generally work except for I2C devices that do not not respond to a register 0 read request, which will result in a false negative result (unsuccessful response to ping attempt).

This function is weakly defined, meaning it can be overridden if necessary for your particular use case.

#### Arguments {#api-i2c-ping-address-arguments}

 - `uint8_t address`  
   The 7-bit I2C address of the device.
 - `uint16_t timeout`  
   The time in milliseconds to wait for a response from the target device.

#### Return Value {#api-i2c-ping-address-return}

`I2C_STATUS_TIMEOUT` if the timeout period elapses, `I2C_STATUS_ERROR` if some other error occurs, otherwise `I2C_STATUS_SUCCESS`.
