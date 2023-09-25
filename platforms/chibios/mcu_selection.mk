ifneq ($(findstring MKL26Z64, $(MCU)),)
  # Cortex version
  MCU = cortex-m0plus

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 6

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = KINETIS
  MCU_SERIES = KL2x

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= MKL26Z64

  # Startup code to use
  #  - it should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= kl2x

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= PJRC_TEENSY_LC
endif

ifneq ($(findstring MK20DX128, $(MCU)),)
  # Cortex version
  MCU = cortex-m4

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = KINETIS
  MCU_SERIES = K20x

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= MK20DX128

  # Startup code to use
  #  - it should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= k20x5

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= PJRC_TEENSY_3
endif

ifneq ($(findstring MK20DX256, $(MCU)),)
  # Cortex version
  MCU = cortex-m4

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = KINETIS
  MCU_SERIES = K20x

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= MK20DX256

  # Startup code to use
  #  - it should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= k20x7

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= PJRC_TEENSY_3_1
endif

ifneq ($(findstring MK64FX512, $(MCU)),)
  # Cortex version
  MCU = cortex-m4

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = KINETIS
  MCU_SERIES = K60x

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= MK64FX512

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= k60x

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= PJRC_TEENSY_3_5
endif

ifneq ($(findstring MK66FX1M0, $(MCU)),)
  # Cortex version
  MCU = cortex-m4

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = KINETIS
  MCU_SERIES = MK66F18

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= MK66FX1M0

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= MK66F18

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= PJRC_TEENSY_3_6
endif

ifneq ($(findstring RP2040, $(MCU)),)
  # Cortex version
  MCU = cortex-m0plus

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  CHIBIOS_PORT = ARMv6-M-RP2

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = RP
  MCU_SERIES = RP2040

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  STARTUPLD_CONTRIB = $(CHIBIOS_CONTRIB)/os/common/startup/ARMCMx/compilers/GCC/ld
  MCU_LDSCRIPT ?= RP2040_FLASH_TIMECRIT
  LDFLAGS += -L $(STARTUPLD_CONTRIB)

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= rp2040

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_PROMICRO_RP2040

  # Default UF2 Bootloader settings
  UF2_FAMILY ?= RP2040
  FIRMWARE_FORMAT ?= uf2
endif

ifneq ($(findstring STM32F042, $(MCU)),)
  # Cortex version
  MCU = cortex-m0

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 6

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32F0xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F042x6

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f0xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F042X6

  USE_FPU ?= no

  # UF2 settings
  UF2_FAMILY ?= STM32F0

  # Stack sizes: Since this chip has limited RAM capacity, the stack area needs to be reduced.
  # This ensures that the EEPROM page buffer fits into RAM
  USE_PROCESS_STACKSIZE = 0x600
  USE_EXCEPTIONS_STACKSIZE = 0x300

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFFC400
endif

ifneq ($(findstring STM32F072, $(MCU)),)
  # Cortex version
  MCU = cortex-m0

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 6

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32F0xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F072xB

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f0xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F072XB

  USE_FPU ?= no

  # UF2 settings
  UF2_FAMILY ?= STM32F0

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFFC800
endif

ifneq ($(findstring STM32F103, $(MCU)),)
  # Cortex version
  MCU = cortex-m3

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32F1xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F103x8

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f1xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F103

  USE_FPU ?= no

  # UF2 settings
  UF2_FAMILY ?= STM32F1
endif

ifneq ($(findstring STM32F303, $(MCU)),)
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
  MCU_SERIES = STM32F3xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F303xC

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f3xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F303XC

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32F3

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFFD800
endif

ifneq ($(findstring STM32F401, $(MCU)),)
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
  MCU_SERIES = STM32F4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F401xC

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F401XC

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32F4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
endif

ifneq ($(findstring STM32F405, $(MCU)),)
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
  MCU_SERIES = STM32F4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F405xG

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F405XG

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32F4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
endif

ifneq ($(findstring STM32F407, $(MCU)),)
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
  MCU_SERIES = STM32F4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F407xE

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F407XE

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32F4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
endif

ifneq ($(findstring STM32F411, $(MCU)),)
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
  MCU_SERIES = STM32F4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F411xE

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F411XE

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32F4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
endif

ifneq ($(findstring STM32F446, $(MCU)),)
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
  MCU_SERIES = STM32F4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F446xE

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F446XE

  USE_FPU ?= yes

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

  # Default as no chibios efl config
  EEPROM_DRIVER ?= transient
endif

ifneq ($(findstring STM32G431, $(MCU)),)
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
  MCU_SERIES = STM32G4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32G431xB

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32g4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_G431XB

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32G4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

  # Default to transient driver as ChibiOS EFL is currently broken for single-bank G4xx devices
  EEPROM_DRIVER ?= transient
endif

ifneq ($(findstring STM32G474, $(MCU)),)
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
  MCU_SERIES = STM32G4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32G474xE

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32g4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_G474XE

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32G4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
endif

ifneq (,$(filter $(MCU),STM32L432 STM32L442))
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
  MCU_SERIES = STM32L4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32L432xC

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32l4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_L432XC

  PLATFORM_NAME ?= platform_l432

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32L4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
endif

ifneq (,$(filter $(MCU),STM32L433 STM32L443))
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
  MCU_SERIES = STM32L4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32L432xC

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32l4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_L433XC

  PLATFORM_NAME ?= platform_l432

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32L4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
endif

ifneq (,$(filter $(MCU),STM32L412 STM32L422))
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
  MCU_SERIES = STM32L4xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32L412xB

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32l4xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_L412XB

  PLATFORM_NAME ?= platform_l412_l422

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32L4

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
endif

ifneq (,$(filter $(MCU),STM32H723 STM32H733))
  # Cortex version
  MCU = cortex-m7

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32H7xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32H723xG_ITCM64k

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32h7xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_H723XG

  PLATFORM_NAME ?= platform_type2

  USE_FPU ?= yes

  # UF2 settings
  UF2_FAMILY ?= STM32H7

  # Bootloader address for STM32 DFU
  STM32_BOOTLOADER_ADDRESS ?= 0x1FF09800
endif

ifneq ($(findstring WB32F3G71, $(MCU)),)
  # Cortex version
  MCU = cortex-m3

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = WB32
  MCU_SERIES = WB32F3G71xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= WB32F3G71x9

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= wb32f3g71xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_WB32_F3G71XX

  USE_FPU ?= no

  # Bootloader address for WB32 DFU
  WB32_BOOTLOADER_ADDRESS ?= 0x1FFFE000
endif

ifneq ($(findstring WB32FQ95, $(MCU)),)
  # Cortex version
  MCU = cortex-m3

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = WB32
  MCU_SERIES = WB32FQ95xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= WB32FQ95xB

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= wb32fq95xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_WB32_FQ95XX

  USE_FPU ?= no

  # Bootloader address for WB32 DFU
  WB32_BOOTLOADER_ADDRESS ?= 0x1FFFE000
endif

ifneq ($(findstring GD32VF103, $(MCU)),)
  # RISC-V
  MCU = risc-v

  # RISC-V extensions and abi configuration
  MCU_ARCH = rv32imac
  MCU_ABI = ilp32
  MCU_CMODEL = medlow

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_PORT_NAME = GD
  MCU_FAMILY = GD32V
  MCU_SERIES = GD32VF103

  # Linker script to use
  # - it should exist either in <chibios>/os/common/startup/RISCV-ECLIC/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= GD32VF103xB

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/RISCV-ECLIC/compilers/GCC/mk/
  MCU_STARTUP ?= gd32vf103

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= SIPEED_LONGAN_NANO

  USE_FPU ?= no
endif
