# STM32 MCU settings for converting AVR projects
MCU := STM32F411
BOARD := STEMCELL
BOOTLOADER := tinyuf2
FIRMWARE_FORMAT := uf2

SERIAL_DRIVER ?= usart
WS2812_DRIVER ?= bitbang

EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = legacy

ifeq ($(strip $(STMC_US)), yes)
  STEMCELL_UART_SWAP=yes
  OPT_DEFS += -DSTEMCELL_UART_SWAP
  OPT_DEFS += -DSERIAL_USART_DRIVER=SD2
endif

ifeq ($(strip $(STMC_IS)), yes)
  STEMCELL_I2C_SWAP=yes
  OPT_DEFS += -DSTEMCELL_I2C_SWAP
endif
