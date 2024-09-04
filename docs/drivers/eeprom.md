# EEPROM Driver Configuration {#eeprom-driver-configuration}

The EEPROM driver can be swapped out depending on the needs of the keyboard, or whether extra hardware is present.

Selecting the EEPROM driver is done in your keyboard's `rules.mk`:

Driver                             | Description
-----------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
`EEPROM_DRIVER = vendor` (default) | Uses the on-chip driver provided by the chip manufacturer. For AVR, this is provided by avr-libc. This is supported on ARM for a subset of chips -- STM32F3xx, STM32F1xx, and STM32F072xB will be emulated by writing to flash. STM32L0xx and STM32L1xx will use the onboard dedicated true EEPROM. Other chips will generally act as "transient" below.
`EEPROM_DRIVER = i2c`              | Supports writing to I2C-based 24xx EEPROM chips. See the driver section below.
`EEPROM_DRIVER = spi`              | Supports writing to SPI-based 25xx EEPROM chips. See the driver section below.
`EEPROM_DRIVER = transient`        | Fake EEPROM driver -- supports reading/writing to RAM, and will be discarded when power is lost.
`EEPROM_DRIVER = wear_leveling`    | Frontend driver for the wear_leveling system, allowing for EEPROM emulation on top of flash -- both in-MCU and external SPI NOR flash.

## Vendor Driver Configuration {#vendor-eeprom-driver-configuration}

#### STM32 L0/L1 Configuration {#stm32l0l1-eeprom-driver-configuration}

::: warning
Resetting EEPROM using an STM32L0/L1 device takes up to 1 second for every 1kB of internal EEPROM used.
:::

`config.h` override                 | Description                                                                                                              | Default Value
------------------------------------|--------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------
`#define STM32_ONBOARD_EEPROM_SIZE` | The size of the EEPROM to use, in bytes. Erase times can be high, so it's configurable here, if not using the default value. | Minimum required to cover base _eeconfig_ data, or `1024` if VIA is enabled.

## I2C Driver Configuration {#i2c-eeprom-driver-configuration}

Currently QMK supports 24xx-series chips over I2C. As such, requires a working i2c_master driver configuration. You can override the driver configuration via your config.h:

`config.h` override                         | Description                                                                         | Default Value
------------------------------------------- | ----------------------------------------------------------------------------------- | ------------------------------------
`#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS`  | Base I2C address for the EEPROM -- shifted left by 1 as per i2c_master requirements | 0b10100000
`#define EXTERNAL_EEPROM_I2C_ADDRESS(addr)` | Calculated I2C address for the EEPROM                                               | `(EXTERNAL_EEPROM_I2C_BASE_ADDRESS)`
`#define EXTERNAL_EEPROM_BYTE_COUNT`        | Total size of the EEPROM in bytes                                                   | 8192
`#define EXTERNAL_EEPROM_PAGE_SIZE`         | Page size of the EEPROM in bytes, as specified in the datasheet                     | 32
`#define EXTERNAL_EEPROM_ADDRESS_SIZE`      | The number of bytes to transmit for the memory location within the EEPROM           | 2
`#define EXTERNAL_EEPROM_WRITE_TIME`        | Write cycle time of the EEPROM, as specified in the datasheet                       | 5
`#define EXTERNAL_EEPROM_WP_PIN`            | If defined the WP pin will be toggled appropriately when writing to the EEPROM.     | _none_

Some I2C EEPROM manufacturers explicitly recommend against hardcoding the WP pin to ground. This is in order to protect the eeprom memory content during power-up/power-down/brown-out conditions at low voltage where the eeprom is still operational, but the i2c master output might be unpredictable. If a WP pin is configured, then having an external pull-up on the WP pin is recommended.

Default values and extended descriptions can be found in `drivers/eeprom/eeprom_i2c.h`.

Alternatively, there are pre-defined hardware configurations for available chips/modules:

Module           | Equivalent `#define`            | Source
-----------------|---------------------------------|------------------------------------------
CAT24C512 EEPROM | `#define EEPROM_I2C_CAT24C512`  | <https://www.sparkfun.com/products/14764>
RM24C512C EEPROM | `#define EEPROM_I2C_RM24C512C`  | <https://www.sparkfun.com/products/14764>
24LC32A EEPROM   | `#define EEPROM_I2C_24LC32A`    | <https://www.microchip.com/en-us/product/24LC32A>
24LC64 EEPROM    | `#define EEPROM_I2C_24LC64`     | <https://www.microchip.com/en-us/product/24LC64>
24LC128 EEPROM   | `#define EEPROM_I2C_24LC128`    | <https://www.microchip.com/en-us/product/24LC128>
24LC256 EEPROM   | `#define EEPROM_I2C_24LC256`    | <https://www.sparkfun.com/products/525>
MB85RC256V FRAM  | `#define EEPROM_I2C_MB85RC256V` | <https://www.adafruit.com/product/1895>

::: tip
If you find that the EEPROM is not cooperating, ensure you've correctly shifted up your EEPROM address by 1. For example, the datasheet might state the address as `0b01010000` -- the correct value of `EXTERNAL_EEPROM_I2C_BASE_ADDRESS` needs to be `0b10100000`.
:::

## SPI Driver Configuration {#spi-eeprom-driver-configuration}

Currently QMK supports 25xx-series chips over SPI. As such, requires a working spi_master driver configuration. You can override the driver configuration via your config.h:

`config.h` override                            | Default Value | Description
-----------------------------------------------|---------------|-------------------------------------------------------------------------------------
`#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN` | _none_        | SPI Slave select pin in order to inform that the EEPROM is currently being addressed
`#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR`    | `64`          | Clock divisor used to divide the peripheral clock to derive the SPI frequency
`#define EXTERNAL_EEPROM_BYTE_COUNT`           | `8192`        | Total size of the EEPROM in bytes
`#define EXTERNAL_EEPROM_PAGE_SIZE`            | `32`          | Page size of the EEPROM in bytes, as specified in the datasheet
`#define EXTERNAL_EEPROM_ADDRESS_SIZE`         | `2`           | The number of bytes to transmit for the memory location within the EEPROM

Default values and extended descriptions can be found in `drivers/eeprom/eeprom_spi.h`.

Alternatively, there are pre-defined hardware configurations for available chips/modules:

Module           | Equivalent `#define`            | Source
-----------------|---------------------------------|------------------------------------------
MB85RS64V FRAM   | `define EEPROM_SPI_MB85RS64V`   | <https://www.adafruit.com/product/1897>

::: warning
There's no way to determine if there is an SPI EEPROM actually responding. Generally, this will result in reads of nothing but zero.
:::

## Transient Driver configuration {#transient-eeprom-driver-configuration}

The only configurable item for the transient EEPROM driver is its size:

`config.h` override             | Description                               | Default Value
------------------------------- | ----------------------------------------- | -------------
`#define TRANSIENT_EEPROM_SIZE` | Total size of the EEPROM storage in bytes | 64

Default values and extended descriptions can be found in `drivers/eeprom/eeprom_transient.h`.

## Wear-leveling Driver Configuration {#wear_leveling-eeprom-driver-configuration}

The wear-leveling driver uses an algorithm to minimise the number of erase cycles on the underlying MCU flash memory.

There is no specific configuration for this driver, but the wear-leveling system used by this driver may need configuration. See the [wear-leveling configuration](#wear_leveling-configuration) section for more information.

# Wear-leveling Configuration {#wear_leveling-configuration}

The wear-leveling driver has a few possible _backing stores_ that may be used by adding to your keyboard's `rules.mk` file:

Driver                                  | Description
----------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
`WEAR_LEVELING_DRIVER = embedded_flash` | This driver is used for emulating EEPROM by writing to embedded flash on the MCU.
`WEAR_LEVELING_DRIVER = spi_flash`      | This driver is used to address external SPI NOR Flash peripherals.
`WEAR_LEVELING_DRIVER = rp2040_flash`   | This driver is used to write to the same storage the RP2040 executes code from.
`WEAR_LEVELING_DRIVER = legacy`         | This driver is the "legacy" emulated EEPROM provided in historical revisions of QMK. Currently used for STM32F0xx and STM32F4x1, but slated for deprecation and removal once `embedded_flash` support for those MCU families is complete.

::: warning
All wear-leveling drivers require an amount of RAM equivalent to the selected logical EEPROM size. Increasing the size to 32kB of EEPROM requires 32kB of RAM, which a significant number of MCUs simply do not have.
:::

## Wear-leveling Embedded Flash Driver Configuration {#wear_leveling-efl-driver-configuration}

This driver performs writes to the embedded flash storage embedded in the MCU. In most circumstances, the last few of sectors of flash are used in order to minimise the likelihood of collision with program code.

Configurable options in your keyboard's `config.h`:

`config.h` override                                | Default            | Description
---------------------------------------------------|--------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
`#define WEAR_LEVELING_EFL_FIRST_SECTOR`           | _unset_            | The first sector on the MCU to use. By default this is not defined and calculated at runtime based on the MCU. However, different flash sizes on MCUs may require custom configuration.
`#define WEAR_LEVELING_EFL_FLASH_SIZE`             | _unset_            | Allows overriding the flash size available for use for wear-leveling. Under normal circumstances this is automatically calculated and should not need to be overridden. Specifying a size larger than the amount actually available in flash will usually prevent the MCU from booting.
`#define WEAR_LEVELING_EFL_OMIT_LAST_SECTOR_COUNT` | `0`                | Number of sectors to omit at the end of the flash. These sectors will not be allocated to the driver and the usable flash block will be offset, but keeping the set flash size. Useful on devices with bootloaders requiring a check flag at the end of flash to be present in order to confirm a valid, bootable firmware.
`#define WEAR_LEVELING_LOGICAL_SIZE`               | `(backing_size/2)` | Number of bytes "exposed" to the rest of QMK and denotes the size of the usable EEPROM.
`#define WEAR_LEVELING_BACKING_SIZE`               | `2048`             | Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size.
`#define BACKING_STORE_WRITE_SIZE`                 | _automatic_        | The byte width of the underlying write used on the MCU, and is usually automatically determined from the selected MCU family. If an error occurs in the auto-detection, you'll need to consult the MCU's datasheet and determine this value, specifying it directly.

::: warning
If your MCU does not boot after swapping to the EFL wear-leveling driver, it's likely that the flash size is incorrectly detected, usually as an MCU with larger flash and may require overriding.
:::

## Wear-leveling SPI Flash Driver Configuration {#wear_leveling-flash_spi-driver-configuration}

This driver performs writes to an external SPI NOR Flash peripheral. It also requires a working configuration for the SPI NOR Flash peripheral -- see the [flash driver](flash) documentation for more information.

Configurable options in your keyboard's `config.h`:

`config.h` override                                 | Default                        | Description
----------------------------------------------------|--------------------------------|--------------------------------------------------------------------------------------------------------------------------------
`#define WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_COUNT`  | `1`                            | Number of blocks in the external flash used by the wear-leveling algorithm.
`#define WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET` | `0`                            | The index first block in the external flash used by the wear-leveling algorithm.
`#define WEAR_LEVELING_LOGICAL_SIZE`                | `((block_count*block_size)/2)` | Number of bytes "exposed" to the rest of QMK and denotes the size of the usable EEPROM. Result must be <= 64kB.
`#define WEAR_LEVELING_BACKING_SIZE`                | `(block_count*block_size)`     | Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size.
`#define BACKING_STORE_WRITE_SIZE`                  | `8`                            | The write width used whenever a write is performed on the external flash peripheral.

::: warning
There is currently a limit of 64kB for the EEPROM subsystem within QMK, so using a larger flash is not going to be beneficial as the logical size cannot be increased beyond 65536. The backing size may be increased to a larger value, but erase timing may suffer as a result.
:::

## Wear-leveling RP2040 Driver Configuration {#wear_leveling-rp2040-driver-configuration}

This driver performs writes to the same underlying storage that the RP2040 executes its code.

Configurable options in your keyboard's `config.h`:

`config.h` override                       | Default                    | Description
------------------------------------------|----------------------------|--------------------------------------------------------------------------------------------------------------------------------
`#define WEAR_LEVELING_RP2040_FLASH_SIZE` | `PICO_FLASH_SIZE_BYTES`    | Number of bytes of flash on the board.
`#define WEAR_LEVELING_RP2040_FLASH_BASE` | `(flash_size-sector_size)` | The byte-wise location that the backing storage should be located.
`#define WEAR_LEVELING_LOGICAL_SIZE`      | `(backing_size/2)`         | Number of bytes "exposed" to the rest of QMK and denotes the size of the usable EEPROM.
`#define WEAR_LEVELING_BACKING_SIZE`      | `8192`                     | Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size as well as the sector size.
`#define BACKING_STORE_WRITE_SIZE`        | `2`                        | The write width used whenever a write is performed on the external flash peripheral.

## Wear-leveling Legacy EEPROM Emulation Driver Configuration {#wear_leveling-legacy-driver-configuration}

This driver performs writes to the embedded flash storage embedded in the MCU much like the normal Embedded Flash Driver, and is only for use with STM32F0xx and STM32F4x1 devices. This flash implementation is still currently provided as the EFL driver is currently non-functional for the previously mentioned families.

By default, `1024` bytes of emulated EEPROM is provided:

MCU       | EEPROM Provided | Flash Used
----------|-----------------|--------------
STM32F042 | `1024` bytes    | `2048` bytes
STM32F070 | `1024` bytes    | `2048` bytes
STM32F072 | `1024` bytes    | `2048` bytes
STM32F401 | `1024` bytes    | `16384` bytes
STM32F411 | `1024` bytes    | `16384` bytes

Under normal circumstances configuration of this driver requires intimate knowledge of the MCU's flash structure -- reconfiguration is at your own risk and will require referring to the code.
