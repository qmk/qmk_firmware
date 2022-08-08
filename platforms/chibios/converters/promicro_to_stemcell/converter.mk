# STM32 MCU settings for converting AVR projects
MCU := STM32F411
BOARD := STEMCELL
BOOTLOADER := tinyuf2

SERIAL_DRIVER ?= usart
WS2812_DRIVER ?= bitbang

EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = legacy


ifeq ($(strip $(STMC_US)), yes)
  OPT_DEFS += -DSTEMCELL_UART_SWAP
endif

ifeq ($(strip $(STMC_IS)), yes)
  OPT_DEFS += -DSTEMCELL_I2C_SWAP
endif

