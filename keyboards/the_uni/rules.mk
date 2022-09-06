# MCU name
MCU = atmega32u4

# Bootloader
BOOTLOADER = atmel-dfu


# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite	# Virtual DIP switch configuration
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no
FORCE_NKRO = yes
EXTRAKEY_ENABLE = no
MOUSEKEY_ENABLE = no        # Mouse keys
STENO_ENABLE = yes      
