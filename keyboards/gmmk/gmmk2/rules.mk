EEPROM_DRIVER = custom       # Enable SPI flash memory
SRC +=  external_flash/flash_spi.c \
        external_flash/eeprom_flash.c \
        external_flash/wb32_spi_master.c
