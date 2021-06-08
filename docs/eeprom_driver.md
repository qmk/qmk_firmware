# EEPROM Driver Configuration :id=eeprom-driver-configuration

The EEPROM driver can be swapped out depending on the needs of the keyboard, or whether extra hardware is present.

Driver                             | Description
-----------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
`EEPROM_DRIVER = vendor` (default) | Uses the on-chip driver provided by the chip manufacturer. For AVR, this is provided by avr-libc. This is supported on ARM for a subset of chips -- STM32F3xx, STM32F1xx, and STM32F072xB will be emulated by writing to flash. STM32L0xx and STM32L1xx will use the onboard dedicated true EEPROM. Other chips will generally act as "transient" below.
`EEPROM_DRIVER = i2c`              | Supports writing to I2C-based 24xx EEPROM chips. See the driver section below.
`EEPROM_DRIVER = spi`              | Supports writing to SPI-based 25xx EEPROM chips. See the driver section below.
`EEPROM_DRIVER = transient`        | Fake EEPROM driver -- supports reading/writing to RAM, and will be discarded when power is lost.

## Vendor Driver Configuration :id=vendor-eeprom-driver-configuration

#### STM32 L0/L1 Configuration :id=stm32l0l1-eeprom-driver-configuration

!> Resetting EEPROM using an STM32L0/L1 device takes up to 1 second for every 1kB of internal EEPROM used.

`config.h` override                 | Description                                                                                                              | Default Value
------------------------------------|--------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------
`#define STM32_ONBOARD_EEPROM_SIZE` | The size of the EEPROM to use, in bytes. Erase times can be high, so it's configurable here, if not using the default value. | Minimum required to cover base _eeconfig_ data, or `1024` if VIA is enabled.

## I2C Driver Configuration :id=i2c-eeprom-driver-configuration

Currently QMK supports 24xx-series chips over I2C. As such, requires a working i2c_master driver configuration. You can override the driver configuration via your config.h:

`config.h` override                         | Description                                                                         | Default Value
------------------------------------------- | ----------------------------------------------------------------------------------- | ------------------------------------
`#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS`  | Base I2C address for the EEPROM -- shifted left by 1 as per i2c_master requirements | 0b10100000
`#define EXTERNAL_EEPROM_I2C_ADDRESS(addr)` | Calculated I2C address for the EEPROM                                               | `(EXTERNAL_EEPROM_I2C_BASE_ADDRESS)`
`#define EXTERNAL_EEPROM_BYTE_COUNT`        | Total size of the EEPROM in bytes                                                   | 8192
`#define EXTERNAL_EEPROM_PAGE_SIZE`         | Page size of the EEPROM in bytes, as specified in the datasheet                     | 32
`#define EXTERNAL_EEPROM_ADDRESS_SIZE`      | The number of bytes to transmit for the memory location within the EEPROM           | 2
`#define EXTERNAL_EEPROM_WRITE_TIME`        | Write cycle time of the EEPROM, as specified in the datasheet                       | 5

Default values and extended descriptions can be found in `drivers/eeprom/eeprom_i2c.h`.

Alternatively, there are pre-defined hardware configurations for available chips/modules:

Module           | Equivalent `#define`            | Source
-----------------|---------------------------------|------------------------------------------
CAT24C512 EEPROM | `#define EEPROM_I2C_CAT24C512`  | <https://www.sparkfun.com/products/14764>
RM24C512C EEPROM | `#define EEPROM_I2C_RM24C512C`  | <https://www.sparkfun.com/products/14764>
24LC64 EEPROM    | `#define EEPROM_I2C_24LC64`     | <https://www.microchip.com/wwwproducts/en/24LC64>
24LC128 EEPROM   | `#define EEPROM_I2C_24LC128`    | <https://www.microchip.com/wwwproducts/en/24LC128>
24LC256 EEPROM   | `#define EEPROM_I2C_24LC256`    | <https://www.sparkfun.com/products/525>
MB85RC256V FRAM  | `#define EEPROM_I2C_MB85RC256V` | <https://www.adafruit.com/product/1895>

?> If you find that the EEPROM is not cooperating, ensure you've correctly shifted up your EEPROM address by 1. For example, the datasheet might state the address as `0b01010000` -- the correct value of `EXTERNAL_EEPROM_I2C_BASE_ADDRESS` needs to be `0b10100000`.

## SPI Driver Configuration :id=spi-eeprom-driver-configuration

Currently QMK supports 25xx-series chips over SPI. As such, requires a working spi_master driver configuration. You can override the driver configuration via your config.h:

`config.h` override                            | Description                                                                          | Default Value
-----------------------------------------------|--------------------------------------------------------------------------------------|--------------
`#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN` | SPI Slave select pin in order to inform that the EEPROM is currently being addressed | _none_
`#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR`    | Clock divisor used to divide the peripheral clock to derive the SPI frequency        | `64`
`#define EXTERNAL_EEPROM_BYTE_COUNT`           | Total size of the EEPROM in bytes                                                    | 8192
`#define EXTERNAL_EEPROM_PAGE_SIZE`            | Page size of the EEPROM in bytes, as specified in the datasheet                      | 32
`#define EXTERNAL_EEPROM_ADDRESS_SIZE`         | The number of bytes to transmit for the memory location within the EEPROM            | 2

!> There's no way to determine if there is an SPI EEPROM actually responding. Generally, this will result in reads of nothing but zero.

## Transient Driver configuration :id=transient-eeprom-driver-configuration

The only configurable item for the transient EEPROM driver is its size:

`config.h` override             | Description                               | Default Value
------------------------------- | ----------------------------------------- | -------------
`#define TRANSIENT_EEPROM_SIZE` | Total size of the EEPROM storage in bytes | 64

Default values and extended descriptions can be found in `drivers/eeprom/eeprom_transient.h`.
