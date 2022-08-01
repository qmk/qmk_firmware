# STEMCELL MCU settings for converting AVR projects
MCU := STM32F411
BOARD := STEMCELL
BOOTLOADER := tinyuf2
MCU_LDSCRIPT := STEMCELL_tinyuf2

FIRMWARE_FORMAT := uf2

SERIAL_DRIVER := usart

# These are defaults based on what has been implemented for ARM boards
AUDIO_ENABLE ?= no
WS2812_DRIVER ?= bitbang

ifeq ($(strip $(STMC_US)), yes)
  CONVERT_TO_STEMCELL_UART_SWAP=yes
  OPT_DEFS += -DCONVERT_TO_STEMCELL_UART_SWAP
endif

ifeq ($(strip $(STMC_IS)), yes)
  CONVERT_TO_STEMCELL_I2C_SWAP=yes
  OPT_DEFS += -DCONVERT_TO_STEMCELL_I2C_SWAP
endif
