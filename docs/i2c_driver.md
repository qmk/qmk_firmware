# I2C Master Driver :id=i2c-master-driver

The I2C Master drivers used in QMK have a set of common functions to allow portability between MCUs.

## An important note on I2C Addresses :id=note-on-i2c-addresses

All of the addresses expected by this driver should be pushed to the upper 7 bits of the address byte.  Setting
the lower bit (indicating read/write) will be done by the respective functions.  Almost all I2C addresses listed 
on datasheets and the internet will be represented as 7 bits occupying the lower 7 bits and will need to be
shifted to the left (more significant) by one bit.  This is easy to do via the bitwise shift operator `<< 1`.

You can either do this on each call to the functions below, or once in your definition of the address.  For example if your device has an address of `0x18`:

`#define MY_I2C_ADDRESS (0x18 << 1)`

See https://www.robot-electronics.co.uk/i2c-tutorial for more information about I2C addressing and other technical details.

## Available functions :id=available-functions

|Function                                                                                                          |Description                                                                                                                                                                  |
|------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`void i2c_init(void);`                                                                                            |Initializes the I2C driver. This function should be called once before any transaction is initiated.                                                                         |
|`i2c_status_t i2c_start(uint8_t address, uint16_t timeout);`                                                                             |Starts an I2C transaction. Address is the 7-bit slave address without the direction bit.                                                                                     |
|`i2c_status_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);`                        |Transmit data over I2C. Address is the 7-bit slave address without the direction. Returns status of transaction.                                                             |
|`i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);`                         |Receive data over I2C. Address is the 7-bit slave address without the direction. Saves number of bytes specified by `length` in `data` array. Returns status of transaction. |
|`i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);`       |Same as the `i2c_transmit` function but `regaddr` sets where in the slave the data will be written.                                                                          |
|`i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);`        |Same as the `i2c_receive` function but `regaddr` sets from where in the slave the data will be read.                                                                         |
|`i2c_status_t i2c_stop(void);`                                                                                         |Ends an I2C transaction.                                                                                                                                                     |

### Function Return :id=function-return

All the above functions, except `void i2c_init(void);` return the following truth table:

|Return Constant     |Value|Description                     |
|--------------------|-----|--------------------------------|
|`I2C_STATUS_SUCCESS`|0    |Operation executed successfully.|
|`I2C_STATUS_ERROR`  |-1   |Operation failed.               |
|`I2C_STATUS_TIMEOUT`|-2   |Operation timed out.            |


## AVR :id=avr

### Configuration :id=avr-configuration

The following defines can be used to configure the I2C master driver.

|Variable          |Description                                        |Default|
|------------------|---------------------------------------------------|-------|
|`F_SCL`           |Clock frequency in Hz                              |400KHz |

AVRs usually have set GPIO which turn into I2C pins, therefore no further configuration is required.

## ARM :id=arm

For ARM the Chibios I2C HAL driver is under the hood.
This section assumes an STM32 MCU.

### Configuration :id=arm-configuration

The configuration for ARM MCUs can be quite complex as often there are multiple I2C drivers which can be assigned to a variety of ports.

Firstly the `mcuconf.h` file must be setup to enable the necessary hardware drivers.

|Variable                      |Description                                                                        |Default|
|------------------------------|------------------------------------------------------------------------------------|-------|
|`#STM32_I2C_USE_XXX`          |Enable/Disable the hardware driver XXX (each driver should be explicitly listed)    |FALSE  |
|`#STM32_I2C_BUSY_TIMEOUT`     |Time in ms until the I2C command is aborted if no response is received              |50     |
|`#STM32_I2C_XXX_IRQ_PRIORITY` |Interrupt priority for hardware driver XXX (THIS IS AN EXPERT SETTING)              |10     |
|`#STM32_I2C_USE_DMA`          |Enable/Disable the ability of the MCU to offload the data transfer to the DMA unit  |TRUE   |
|`#STM32_I2C_XXX_DMA_PRIORITY` |Priority of DMA unit for hardware driver XXX (THIS IS AN EXPERT SETTING)            |1      |

Secondly, in the `halconf.h` file, `#define HAL_USE_I2C` must be set to `TRUE`. This allows ChibiOS to load its I2C driver.

Lastly, we need to assign the correct GPIO pins depending on the I2C hardware driver we want to use.

By default the I2C1 hardware driver is assumed to be used. If another hardware driver is used,  `#define I2C_DRIVER I2CDX` should be added to the `config.h` file with X being the number of hardware driver used. For example is I2C3 is enabled, the `config.h` file should contain `#define I2C_DRIVER I2CD3`. This aligns the QMK I2C driver with the Chibios I2C driver.

STM32 MCUs allows a variety of pins to be configured as I2C pins depending on the hardware driver used. By default B6 and B7 are set to I2C. You can use these defines to set your i2c pins:

| Variable                 | Description                                                                                  | Default |
|--------------------------|----------------------------------------------------------------------------------------------|---------|
| `I2C1_SCL_BANK`          | The bank of pins (`GPIOA`, `GPIOB`, `GPIOC`) to use for SCL                                  | `GPIOB` |
| `I2C1_SDA_BANK`          | The bank of pins (`GPIOA`, `GPIOB`, `GPIOC`) to use for SDA                                  | `GPIOB` |
| `I2C1_SCL`               | The pin number for the SCL pin (0-9)                                                         | `6`     |
| `I2C1_SDA`               | The pin number for the SDA pin (0-9)                                                         | `7`     |
| `I2C1_BANK` (deprecated) | The bank of pins (`GPIOA`, `GPIOB`, `GPIOC`), superceded by `I2C1_SCL_BANK`, `I2C1_SDA_BANK` | `GPIOB` |

The ChibiOS I2C driver configuration depends on STM32 MCU:

    STM32F1xx, STM32F2xx, STM32F4xx, STM32L0xx and STM32L1xx use I2Cv1;
    STM32F0xx, STM32F3xx, STM32F7xx and STM32L4xx use I2Cv2;

#### I2Cv1 :id=i2cv1
STM32 MCUs allow for different clock and duty parameters when configuring I2Cv1. These can be modified using the following parameters, using <https://www.playembedded.org/blog/stm32-i2c-chibios/#I2Cv1_configuration_structure> as a reference:

| Variable           | Default          |
|--------------------|------------------|
| `I2C1_OPMODE`      | `OPMODE_I2C`     |
| `I2C1_CLOCK_SPEED` | `100000`         |
| `I2C1_DUTY_CYCLE`  | `STD_DUTY_CYCLE` |

#### I2Cv2 :id=i2cv2
STM32 MCUs allow for different timing parameters when configuring I2Cv2. These can be modified using the following parameters, using <https://www.st.com/en/embedded-software/stsw-stm32126.html> as a reference:

| Variable              | Default |
|-----------------------|---------|
| `I2C1_TIMINGR_PRESC`  | `15U`   |
| `I2C1_TIMINGR_SCLDEL` | `4U`    |
| `I2C1_TIMINGR_SDADEL` | `2U`    |
| `I2C1_TIMINGR_SCLH`   | `15U`   |
| `I2C1_TIMINGR_SCLL`   | `21U`   |

STM32 MCUs allow for different "alternate function" modes when configuring GPIO pins. These are required to switch the pins used to I2Cv2 mode. See the respective datasheet for the appropriate values for your MCU.

| Variable            | Default |
|---------------------|---------|
| `I2C1_SCL_PAL_MODE` | `4`     |
| `I2C1_SDA_PAL_MODE` | `4`     |

#### Other :id=other
You can also overload the `void i2c_init(void)` function, which has a weak attribute. If you do this the configuration variables above will not be used. Please consult the datasheet of your MCU for the available GPIO configurations. The following is an example initialization function:

```C
void i2c_init(void)
{
  setPinInput(B6); // Try releasing special pins for a short time
  setPinInput(B7);
  wait_ms(10); // Wait for the release to happen

  palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B6 to I2C function
  palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B7 to I2C function
}
```
