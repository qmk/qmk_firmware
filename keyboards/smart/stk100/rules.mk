
# Cortex version
  MCU = cortex-m4

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32WBxx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32WB55xG

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32wbxx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= ST_NUCLEO68_WB55RG

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32WB

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
#OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_WEAR_LEVELING
#SRC += eeprom_driver.c eeprom_wear_leveling.c
#WEAR_LEVELING_DRIVER = embedded_flash

#OPT_DEFS += -DEEPROM_DRIVER -DEEPROM_TRANSIENT
#SRC += eeprom_driver.c eeprom_transient.c

#EEPROM_DRIVER = transient

DIP_SWITCH_ENABLE = yes
ENCODER_MAP_ENABLE = yes
ENCODER_ENABLE = yes
#KEYBOARD_SHARED_EP = yes
#SRC += analog.c \
#     rgblight_custom.c

