# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = no	# Mouse keys
EXTRAKEY_ENABLE  = no	# Audio control and System control
CONSOLE_ENABLE  = yes	# Console for debug
COMMAND_ENABLE  = yes    # Commands for debug and configuration
NKRO_ENABLE  = no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE  = no  # Custom backlighting code is used, so this should not be enabled
AUDIO_ENABLE  = no # This can be enabled if a speaker is connected to the expansion port. Not compatible with RGBLIGHT below
RGBLIGHT_ENABLE  = yes # This can be enabled if a ws2812 strip is connected to the expansion port.

