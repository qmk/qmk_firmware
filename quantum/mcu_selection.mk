ifneq ($(findstring STM32F303, $(MCU)),)
  # Cortex version
  MCU = cortex-m4

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32F3xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F303xC

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f3xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F303XC

  USE_FPU ?= yes

  # Options to pass to dfu-util when flashing
  DFU_ARGS ?= -d 0483:df11 -a 0 -s 0x08000000:leave
  DFU_SUFFIX_ARGS ?= -v 0483 -p df11
endif

ifneq ($(findstring STM32F072, $(MCU)),)
  # Cortex version
  MCU = cortex-m0

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 6

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32F0xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F072xB

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f0xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F072XB

  USE_FPU ?= no

  # Options to pass to dfu-util when flashing
  DFU_ARGS ?= -d 0483:df11 -a 0 -s 0x08000000:leave
  DFU_SUFFIX_ARGS ?= -v 0483 -p df11
endif

ifneq ($(findstring STM32F042, $(MCU)),)
  # Cortex version
  MCU = cortex-m0

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 6

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32F0xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F042x6

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f0xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F042X6

  USE_FPU ?= no

  # Options to pass to dfu-util when flashing
  DFU_ARGS ?= -d 0483:df11 -a 0 -s 0x08000000:leave
  DFU_SUFFIX_ARGS ?= -v 0483 -p df11
endif

ifneq ($(findstring STM32F103, $(MCU)),)
  # Cortex version
  MCU = cortex-m3

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32F1xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT ?= STM32F103x8

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP ?= stm32f1xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= GENERIC_STM32_F103

  USE_FPU ?= no
  
  # Vector table for application
  # 0x00000000-0x00001000 area is occupied by bootloader.*/
  # The CORTEX_VTOR... is needed only for MCHCK/Infinity KB
  # OPT_DEFS = -DCORTEX_VTOR_INIT=0x08005000


  # Options to pass to dfu-util when flashing
  DFU_ARGS ?= -d 0483:df11 -a 0 -s 0x08000000:leave
  DFU_SUFFIX_ARGS ?= -v 0483 -p df11
endif

ifneq (,$(filter $(MCU),atmega16u2 atmega32u2 atmega16u4 atmega32u4 at90usb646 at90usb1286))
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
endif

ifneq (,$(filter $(MCU),atmega32a))
  PROTOCOL = VUSB

  # Processor frequency.
  #     This will define a symbol, F_CPU, in all source code files equal to the
  #     processor frequency in Hz. You can then use this symbol in your source code to
  #     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
  #     automatically to create a 32-bit value in your source code.
  F_CPU ?= 12000000

  # unsupported features for now
  NO_UART ?= yes
  NO_SUSPEND_POWER_DOWN ?= yes

  # Programming options
  PROGRAM_CMD ?= ./util/atmega32a_program.py $(TARGET).hex
endif

ifneq (,$(filter $(MCU),atmega328p))
  PROTOCOL = VUSB

  # Processor frequency.
  #     This will define a symbol, F_CPU, in all source code files equal to the
  #     processor frequency in Hz. You can then use this symbol in your source code to
  #     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
  #     automatically to create a 32-bit value in your source code.
  F_CPU ?= 16000000

  # unsupported features for now
  NO_UART ?= yes
  NO_SUSPEND_POWER_DOWN ?= yes
endif
