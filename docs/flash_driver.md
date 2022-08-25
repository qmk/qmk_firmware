# FLASH Driver Configuration :id=flash-driver-configuration

The FLASH driver can be swapped out depending on the needs of the keyboard, or whether extra hardware is present.

Driver                             | Description
-----------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
`FLASH_DRIVER = spi`               | Supports writing to almost all NOR Flash chips. See the driver section below.


## SPI FLASH Driver Configuration :id=spi-flash-driver-configuration

Currently QMK supports almost all NOR Flash chips over SPI. As such, requires a working spi_master driver configuration. You can override the driver configuration via your config.h:

`config.h` override                            | Description                                                                          | Default Value
-----------------------------------------------|--------------------------------------------------------------------------------------|-----------------
`#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN`  | SPI Slave select pin in order to inform that the FLASH is currently being addressed  | _none_
`#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR`     | Clock divisor used to divide the peripheral clock to derive the SPI frequency        | `8`
`#define EXTERNAL_FLASH_PAGE_SIZE`             | The Page size of the FLASH in bytes, as specified in the datasheet                   | `256`
`#define EXTERNAL_FLASH_SECTOR_SIZE`           | The sector size of the FLASH in bytes, as specified in the datasheet                 | `(4 * 1024)`
`#define EXTERNAL_FLASH_BLOCK_SIZE`            | The block size of the FLASH in bytes, as specified in the datasheet                  | `(64 * 1024)`
`#define EXTERNAL_FLASH_SIZE`                  | The total size of the FLASH in bytes, as specified in the datasheet                  | `(512 * 1024)`
`#define EXTERNAL_FLASH_ADDRESS_SIZE`          | The Flash address size in bytes, as specified in datasheet                           | `3`

!> All the above default configurations are based on MX25L4006E NOR Flash.
