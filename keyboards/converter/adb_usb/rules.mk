# MCU name
# atmega32u4 	Teensy2.0
# atemga32u4	TMK Converter rev.1
# atemga32u2	TMK Converter rev.2
MCU = atmega32u4

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
#
F_CPU = 16000000
# F_CPU = 8000000

#
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
F_USB = $(F_CPU)

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Bootloader
#     This definition is optional, and if your keyboard supports multiple bootloaders of
#     different sizes, comment this out, and the correct address will be loaded
#     automatically (+60). See bootloader.mk for all options.
BOOTLOADER = caterina

# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096	for TMK Converter rev.1/rev.2
#   LUFA bootloader  4096
#   USBaspLoader     2048

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE	= no			# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE		= no			# Mouse keys(+4700)
CONSOLE_ENABLE		= no			# Console for debug(+400)
COMMAND_ENABLE		= no  		# Commands for debug and configuration
SLEEP_LED_ENABLE 	= no  		# Breathing sleep LED during USB suspend
NKRO_ENABLE 		  = no			# USB Nkey Rollover - not yet supported in LUFA
EXTRAKEY_ENABLE		= yes
USB_HID_ENABLE 		= yes
BACKLIGHT_ENABLE 	= no
#BLUETOOTH 			= AdafruitBLE   # For Adafruit Feather 32U4 BLE support, uncomment this line

CUSTOM_MATRIX = yes
SRC = matrix.c \
      adb.c
