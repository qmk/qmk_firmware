#----------------------------------------------------------------------------
# On command line:
#
# make = Make software.
#
# make clean = Clean out built project files.
#
# That's pretty much all you need. To compile, always go make clean, 
# followed by make.
#
# For advanced users only:
# make teensy = Download the hex file to the device, using teensy_loader_cli.
#               (must have teensy_loader_cli installed).
#
#----------------------------------------------------------------------------

# # project specific files
SRC = \
    twimaster.c \
	  matrix.c    \
    expander.c  \

# MCU name
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
F_CPU = 16000000

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


# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=4096

# Build Options
#   comment out to disable the options.
#
CUSTOM_MATRIX           = yes # Custom matrix file for the ErgoDone
UNICODE_ENABLE          = yes # Unicode
BOOTMAGIC_ENABLE        = yes	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE         = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE         = yes	# Audio control and System control(+450)
CONSOLE_ENABLE          = no	# Console for debug(+400)
COMMAND_ENABLE          = no  # Commands for debug and configuration
SLEEP_LED_ENABLE        = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE             = yes	# USB Nkey Rollover - not yet supported in LUFA
USB_6KRO_ENABLE         = no  # USB 6key Rollover
BACKLIGHT_ENABLE        = no	# Enable keyboard backlight functionality
KEYMAP_IN_EEPROM_ENABLE = no 	# External keymap in eeprom
KEYMAP_SECTION_ENABLE   = no	# Fixed address keymap for keymap editor
SOFTPWM_LED_ENABLE      = no  # Enable SoftPWM to drive backlight
FADING_LED_ENABLE       = no  # Enable fading backlight
BREATHING_LED_ENABLE    = no  # Enable breathing backlight
LEDMAP_ENABLE           = no	# Enable LED mapping
LEDMAP_IN_EEPROM_ENABLE = no  # Read LED mapping from eeprom
ONEHAND_ENABLE          = no  # Disable Onehand
RGBLIGHT_ENABLE         = no
MIDI_ENABLE             = no

LAYOUTS = ergodox
