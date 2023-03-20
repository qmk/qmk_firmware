# MCU name
MCU = atmega32u4


BOOTLOADER = atmel-dfu


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
F_CPU = 8000000

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

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug test
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover

BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality test
# BACKLIGHT_DRIVER = pwm # test
# BACKLIGHT_DRIVER = software

RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
# BLUETOOTH = AdafruitBLE       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output
DEBOUNCE_TYPE = sym_defer_pk
CUSTOM_MATRIX = lite

# SRC += analog.c

SRC += matrix.c

	   
QUANTUM_LIB_SRC += i2c_master.c

VIA_ENABLE = no


# BOOTLOADER = halfkay


# # Build Options
# #   comment out to disable the options.
# #
# BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
# MOUSEKEY_ENABLE  = yes # Mouse keys
# EXTRAKEY_ENABLE  = yes # Audio control and System control
# CONSOLE_ENABLE   = no  # Console for debug
# COMMAND_ENABLE   = yes # Commands for debug and configuration
# CUSTOM_MATRIX    = yes # Custom matrix file for the ErgoDox EZ
# NKRO_ENABLE      = yes # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# UNICODE_ENABLE   = yes # Unicode
# SWAP_HANDS_ENABLE= yes # Allow swapping hands of keyboard
# SLEEP_LED_ENABLE = no
# API_SYSEX_ENABLE = no
# RGBLIGHT_ENABLE = no
# RGBLIGHT_CUSTOM_DRIVER = no

# RGB_MATRIX_ENABLE = no # enable later
# DEBOUNCE_TYPE = eager_pr

# # project specific files
# SRC += matrix.c \
# 	   analog.c
# QUANTUM_LIB_SRC += i2c_master.c

# LAYOUTS = default
