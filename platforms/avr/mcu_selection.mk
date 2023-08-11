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
