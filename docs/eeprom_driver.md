# EEPROM Driver Configuration

The EEPROM driver can be swapped out depending on the needs of the keyboard, or whether extra hardware is present.

Driver                      | Description
--------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
`EEPROM_DRIVER = vendor`    | Uses the on-chip driver provided by the chip manufacturer. For AVR, this is provided by avr-libc. This is supported on ARM for a subset of chips -- STM32F3xx, STM32F1xx, and STM32F072xB will be emulated by writing to flash. Other chips will generally act as "transient" below.
`EEPROM_DRIVER = i2c`       | Supports writing to I2C-based 24xx EEPROM chips. See the driver section below.
`EEPROM_DRIVER = transient` | Fake EEPROM driver -- supports reading/writing to RAM, and will be discarded when power is lost.

## Vendor Driver Configuration

No configurable options are available.

## I2C Driver Configuration

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
24LC128 EEPROM   | `#define EEPROM_I2C_24LC128`    | <https://www.microchip.com/wwwproducts/en/24LC128>
24LC256 EEPROM   | `#define EEPROM_I2C_24LC256`    | <https://www.sparkfun.com/products/525>
MB85RC256V FRAM  | `#define EEPROM_I2C_MB85RC256V` | <https://www.adafruit.com/product/1895>

?> If you find that the EEPROM is not cooperating, ensure you've correctly shifted up your EEPROM address by 1. For example, the datasheet might state the address as `0b01010000` -- the correct value of `EXTERNAL_EEPROM_I2C_BASE_ADDRESS` needs to be `0b10100000`.

## Transient Driver configuration

The only configurable item for the transient EEPROM driver is its size:

`config.h` override             | Description                               | Default Value
------------------------------- | ----------------------------------------- | -------------
`#define TRANSIENT_EEPROM_SIZE` | Total size of the EEPROM storage in bytes | 64

Default values and extended descriptions can be found in `drivers/eeprom/eeprom_transient.h`.
