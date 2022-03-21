MCU_ORIG := $(MCU)

include $(BUILDDEFS_PATH)/mcu_selection_stm32.mk

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
  STM32_BOOTLOADER_ADDRESS ?= 0x1FFFE000
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

ifneq (,$(filter $(MCU),at90usb162 atmega16u2 atmega32u2 atmega16u4 atmega32u4 at90usb646 at90usb647 at90usb1286 at90usb1287))
  PROTOCOL = LUFA

  # Processor frequency.
  #     This will define a symbol, F_CPU, in all source code files equal to the
  #     processor frequency in Hz. You can then use this symbol in your source code to
  #     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
  #     automatically to create a 32-bit value in your source code.
  #
  #     This will be an integer division of F_USB below, as it is sourced by
  #     F_USB after it has run through any CPU prescalers. Note that this value
  #     does not *change* the processor frequency - it should merely be updated to
  #     reflect the processor speed set externally so that the code can use accurate
  #     software delays.
  F_CPU ?= 16000000

  # LUFA specific
  #
  # Target architecture (see library "Board Types" documentation).
  ARCH = AVR8

  # Input clock frequency.
  #     This will define a symbol, F_USB, in all source code files equal to the
  #     input clock frequency (before any prescaling is performed) in Hz. This value may
  #     differ from F_CPU if prescaling is used on the latter, and is required as the
  #     raw input clock is fed directly to the PLL sections of the AVR for high speed
  #     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
  #     at the end, this will be done automatically to create a 32-bit value in your
  #     source code.
  #
  #     If no clock division is performed on the input clock inside the AVR (via the
  #     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
  F_USB ?= $(F_CPU)

  # Interrupt driven control endpoint task
  ifeq (,$(filter $(NO_INTERRUPT_CONTROL_ENDPOINT),yes))
    OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT
  endif
  ifneq (,$(filter $(MCU),at90usb162 atmega16u2 atmega32u2))
    NO_I2C = yes
  endif
endif

ifneq (,$(filter $(MCU),atmega32a))
  # MCU name for avrdude
  AVRDUDE_MCU = m32

  PROTOCOL = VUSB

  # Processor frequency.
  #     This will define a symbol, F_CPU, in all source code files equal to the
  #     processor frequency in Hz. You can then use this symbol in your source code to
  #     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
  #     automatically to create a 32-bit value in your source code.
  F_CPU ?= 12000000
endif

ifneq (,$(filter $(MCU),atmega328p))
  # MCU name for avrdude
  AVRDUDE_MCU = m328p

  PROTOCOL = VUSB

  # Processor frequency.
  #     This will define a symbol, F_CPU, in all source code files equal to the
  #     processor frequency in Hz. You can then use this symbol in your source code to
  #     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
  #     automatically to create a 32-bit value in your source code.
  F_CPU ?= 16000000
endif

ifneq (,$(filter $(MCU),atmega328))
  # MCU name for avrdude
  AVRDUDE_MCU = m328

  PROTOCOL = VUSB

  # Processor frequency.
  #     This will define a symbol, F_CPU, in all source code files equal to the
  #     processor frequency in Hz. You can then use this symbol in your source code to
  #     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
  #     automatically to create a 32-bit value in your source code.
  F_CPU ?= 16000000
endif

ifneq (,$(filter $(MCU),attiny85))
  PROTOCOL = VUSB

  # Processor frequency.
  #     This will define a symbol, F_CPU, in all source code files equal to the
  #     processor frequency in Hz. You can then use this symbol in your source code to
  #     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
  #     automatically to create a 32-bit value in your source code.
  F_CPU ?= 16500000
endif
