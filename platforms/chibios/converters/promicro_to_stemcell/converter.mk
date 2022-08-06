# STM32 MCU settings for converting AVR projects
MCU := STM32F411
BOARD := STEMCELL
BOOTLOADER := tinyuf2
FIRMWARE_FORMAT := uf2

SERIAL_DRIVER ?= usart
WS2812_DRIVER ?= bitbang

EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = legacy


OPT_DEFS += -DSERIAL_USART_DRIVER=SD2

ifeq ($(strip $(STMC_US)), yes)
  OPT_DEFS += -DSTEMCELL_UART_SWAP
endif

ifeq ($(strip $(STMC_IS)), yes)
  OPT_DEFS += -DSTEMCELL_I2C_SWAP
endif

# Board Versions:
# https://megamind4089.github.io/STeMCell/pinout/
# 1.0.0 - STEMCELL_VERSION=1
# 1.0.1 - STEMCELL_VERSION=2 (Default)
ifeq ($(strip $(STMC_VERSION)), 1)
  OPT_DEFS += -DSTEMCELL_VERSION=1
else
  OPT_DEFS += -DSTEMCELL_VERSION=2
endif
