# I2C Master Driver

The I2C Master drivers used in QMK have a set of common functions to allow portability between MCUs.

## Available functions

|Function                                                                                                          |Description                                                                                                                                                                  |
|------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`void i2c_init(void);`                                                                                            |Initializes the I2C driver. This function should be called once before any transaction is initiated.                                                                         |
|`uint8_t i2c_start(uint8_t address);`                                                                             |Starts an I2C transaction. Address is the 7-bit slave address without the direction bit.                                                                                     |
|`uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);`                        |Transmit data over I2C. Address is the 7-bit slave address without the direction. Returns status of transaction.                                                             |
|`uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);`                         |Receive data over I2C. Address is the 7-bit slave address without the direction. Saves number of bytes specified by `length` in `data` array. Returns status of transaction. |
|`uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);`       |Same as the `i2c_transmit` function but `regaddr` sets where in the slave the data will be written.                                                                          |
|`uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);`        |Same as the `i2c_receive` function but `regaddr` sets from where in the slave the data will be read.                                                                         |
|`uint8_t i2c_stop(uint16_t timeout);`                                                                             |Stops the I2C driver.                                                                                                                                                        |

### Function Return

All the above functions, except `void i2c_init(void);` return the following truth table:

|Return Value   |Description                                        |
|---------------|---------------------------------------------------|
|0              |Operation executed successfully.                   |
|-1             |Operation failed.                                  |
|-2             |Operation timed out.                               |


## AVR

### Configuration

The following defines can be used to configure the I2C master driver.

|Variable          |Description                                        |Default|
|------------------|---------------------------------------------------|-------|
|`#F_SCL`          |Clock frequency in Hz                              |400KHz |
|`#Prescaler`      |Divides master clock to aid in I2C clock selection |1      |

AVRs usually have set GPIO which turn into I2C pins, therefore no further configuration is required.

## ARM

For ARM the Chibios I2C HAL driver is under the hood.
This section assumes an STM32 MCU.

### Configuration

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

STM32 MCUs allows a variety of pins to be configured as I2C pins depending on the hardware driver used. By default B6 and B7 are set to I2C.

This can be changed by declaring the `i2c_init` function which intentionally has a weak attribute. Please consult the datasheet of your MCU for the available GPIO configurations. The following is an example initialization function:

```C
void i2c_init(void)
{
  setPinInput(B6); // Try releasing special pins for a short time
  setPinInput(B7);
  chThdSleepMilliseconds(10); // Wait for the release to happen

  palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B6 to I2C function
  palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP); // Set B7 to I2C function
}
```


