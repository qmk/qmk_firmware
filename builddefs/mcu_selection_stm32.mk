MCU_ORIG := $(MCU)

# Use bash for this Makefile section.
SHELL_ORIG := $(SHELL)
SHELL := bash

ifneq ($(findstring STM32, $(MCU_ORIG)),)

  LEN := $(shell v="$(MCU_ORIG)"; expr length "$$v")

  ifneq (11, $(LEN))
    $(error The processor name should have a length of 11 characters (e.g. 'STM32F042x6'), but '$(MCU_ORIG)' has a length of $(LEN))
  endif

  # Common MCU family for all STM32
  MCU_FAMILY = STM32
  STM32_X = x

  # The series string, e.g. 'F0' for an STM32F042x6.
  MCU_SERIES_AFFIX := $(shell v="$(MCU_ORIG)"; echo "$${v:5:2}")

  # The sub-series string, e.g. '42' for an STM32F042x6.
  MCU_SUB_SERIES_AFFIX := $(shell v="$(MCU_ORIG)"; echo "$${v:7:2}")

  # The memory affix is the last character of the MCU variable, e.g.
  # 4 → 16 kB of flash
  # 6 → 32 kB of flash
  # 8 → 64 kB of flash
  # B → 128 kB of flash
  # C → 256 kB of flash
  # ...

  # Extract the affix, which is the last character. It will later determine the linker script to be used.
  MEMORY_AFFIX := $(shell v="$(MCU_ORIG)"; echo "$${v: -1}")

  ifneq (,$(filter $(MCU_SERIES_AFFIX),F0))
	# STM32F0 series processor
    MCU = cortex-m0
    ARMV = 6
    USE_FPU ?= no

  else ifneq (,$(filter $(MCU_SERIES_AFFIX),L0))
	# STM32L0 series processor
    MCU = cortex-m0plus
    ARMV = 6
    USE_FPU ?= no

  else ifneq (,$(filter $(MCU_SERIES_AFFIX),F1))
  	# STM32F1 series processor
    MCU = cortex-m3
    ARMV = 7
    USE_FPU ?= no

  else ifneq (,$(filter $(MCU_SERIES_AFFIX),F3))
	# STM32F3 series processor
    MCU = cortex-m4
    ARMV = 7
    USE_FPU ?= yes

  else ifneq (,$(filter $(MCU_SERIES_AFFIX),F4 G4 L4))
	# STM32F4 series processor
    MCU = cortex-m4
    ARMV = 7
    USE_FPU ?= yes

  endif

  # UF2 settings, e.g. 'STM32F0' for an STM32F042x6.
  #    Example: [   STM32   ][        F0       ]
  UF2_FAMILY ?= $(MCU_FAMILY)$(MCU_SERIES_AFFIX)

  # Assemble MCU_SERIES variable, e.g. 'STM32F0xx' for an STM32F042x6.
  #   Example: [   STM32   ][        F0       ][    x   ][    x   ]
  MCU_SERIES = $(MCU_FAMILY)$(MCU_SERIES_AFFIX)$(STM32_X)$(STM32_X)

  # Derive startup script name from MCU_SERIES variable (convert to lower case), e.g. 'stm32f0xx' for an STM32F042x6.
  MCU_STARTUP ?= $(shell echo $(MCU_SERIES) | tr A-Z a-z)

  # The following section defines more specific per-MCU settings.
  # BOARD: A board definition, which should exist either in <chibios>/os/hal/boards/,  <keyboard_dir>/boards/, or drivers/boards/.
  # STM32_BOOTLOADER_ADDRESS: The bootloader address for STM32 DFU.

  ifneq ($(findstring STM32F042, $(MCU_ORIG)),)

    BOARD ?= GENERIC_STM32_F042X6
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFFC400

    # Stack sizes: Since this chip has limited RAM capacity, the stack area needs to be reduced.
    # This ensures that the EEPROM page buffer fits into RAM.
    USE_PROCESS_STACKSIZE = 0x600
    USE_EXCEPTIONS_STACKSIZE = 0x300

  else ifneq ($(findstring STM32F072, $(MCU_ORIG)),)

    BOARD ?= GENERIC_STM32_F072XB
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFFC800

  else ifneq ($(findstring STM32F103, $(MCU_ORIG)),)

    BOARD ?= GENERIC_STM32_F103
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFFF00

  else ifneq ($(findstring STM32F303, $(MCU_ORIG)),)
    
    BOARD ?= GENERIC_STM32_F303XC
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFFD800

  else ifneq ($(findstring STM32F401, $(MCU_ORIG)),)

    BOARD ?= BLACKPILL_STM32_F401
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

  else ifneq ($(findstring STM32F405, $(MCU_ORIG)),)
  
    BOARD ?= GENERIC_STM32_F405XG
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

  else ifneq ($(findstring STM32F407, $(MCU_ORIG)),)
  
    BOARD ?= GENERIC_STM32_F407XE
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
  
  else ifneq ($(findstring STM32F411, $(MCU_ORIG)),)

    BOARD ?= BLACKPILL_STM32_F411
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

  else ifneq ($(findstring STM32F446, $(MCU_ORIG)),)

    BOARD ?= GENERIC_STM32_F446XE
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

  else ifneq ($(findstring STM32G431, $(MCU_ORIG)),)
   
    BOARD ?= GENERIC_STM32_G431XB
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

  else ifneq ($(findstring STM32G474, $(MCU_ORIG)),)
    
    BOARD ?= GENERIC_STM32_G474XE
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

  else ifneq ($(findstring STM32L072, $(MCU_ORIG)),) 
    
    BOARD ?= GENERIC_STM32_L073XZ
    STM32_BOOTLOADER_ADDRESS ?= 0x1FF00000

    # Linker file sub-series affix does not match the affix from the MCU's name.
    MCU_SUB_SERIES_AFFIX_LD = 73

  else ifneq ($(findstring STM32L432, $(MCU_ORIG)),)
   
    BOARD ?= GENERIC_STM32_L432XC
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
    PLATFORM_NAME ?= platform_l432
    
  else ifneq ($(findstring STM32L442, $(MCU_ORIG)),)
   
    BOARD ?= GENERIC_STM32_L432XC
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
    PLATFORM_NAME ?= platform_l432

    # Linker file sub-series affix does not match the affix from the MCU's name.
    MCU_SUB_SERIES_AFFIX_LD = 32

  else ifneq ($(findstring STM32L433, $(MCU_ORIG)),)
   
    BOARD ?= GENERIC_STM32_L433XC
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
    PLATFORM_NAME ?= platform_l432
      
    # Linker file sub-series affix does not match the affix from the MCU's name.
    MCU_SUB_SERIES_AFFIX_LD = 32

  else ifneq ($(findstring STM32L443, $(MCU_ORIG)),)
   
    BOARD ?= GENERIC_STM32_L433XC
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
    PLATFORM_NAME ?= platform_l432

    # Linker file sub-series affix does not match the affix from the MCU's name.
    MCU_SUB_SERIES_AFFIX_LD = 32

  else ifneq ($(findstring STM32L412, $(MCU_ORIG)),)
  
    BOARD ?= GENERIC_STM32_L412XB
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
    PLATFORM_NAME ?= platform_l432

    # Linker file sub-series affix does not match the affix from the MCU's name.
    MCU_SUB_SERIES_AFFIX_LD = 32

  else ifneq ($(findstring STM32L422, $(MCU_ORIG)),)
  
    BOARD ?= GENERIC_STM32_L412XB
    STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000
    PLATFORM_NAME ?= platform_l432

    # Linker file sub-series affix does not match the affix from the MCU's name.
    MCU_SUB_SERIES_AFFIX_LD = 32

  else

    $(error Unsupported STM32 processor $(MCU_ORIG))

  endif

  # The affix for selecting the correct linker file is usually the sub-series string, e.g. '42' for an STM32F042x6,
  # but may have been overwritten, if a linker file for a different, but similar chip is used. Some chipsets share
  # the same memory configuration, so that they also share linker files (e.g. STM32L072xx and STM32L073xx).
  MCU_SUB_SERIES_AFFIX_LD ?= $(MCU_SUB_SERIES_AFFIX)

  # Select the linker script to use. It should exist either in 
  # <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/, or <keyboard_dir>/ld/.
  #      Example: [   STM32   ][        F0       ][           42           ][    x   ][      6      ]
  MCU_LDSCRIPT ?= $(MCU_FAMILY)$(MCU_SERIES_AFFIX)$(MCU_SUB_SERIES_AFFIX_LD)$(STM32_X)$(MEMORY_AFFIX)

  ifeq ($(strip $(BOOTLOADER)), tinyuf2)
  	# Use a special linker file for tinuf2 (TinyUSB) bootloaders.
	# See https://github.com/adafruit/tinyuf2 for details.
    MCU_LDSCRIPT := $(MCU_LDSCRIPT)_tinyuf2
    FIRMWARE_FORMAT ?= uf2
  endif

endif

# Return to the previously used shell.
SHELL := $(SHELL_ORIG)
