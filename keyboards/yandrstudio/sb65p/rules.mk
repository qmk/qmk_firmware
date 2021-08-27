# MCU name
MCU = atmega32u2
BOOTLOADER = caterina


# Build Options
#   comment out to disable the options.
#
# BOOTMAGIC_ENABLE ?= yes	# Virtual DIP switch configuration(+1000)
BOOTMAGIC_ENABLE = lite	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Remote matrix from the wireless bridge
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - not yet supported in LUFA
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
# MIDI_ENABLE = YES 		# MIDI controls


VIA_ENABLE = yes
LTO_ENABLE = yes

# # project specific file
SRC += matrix.c
