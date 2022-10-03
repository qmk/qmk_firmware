# MCU name
MCU = atmega32u4

BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
LTO_ENABLE = yes
RGBLIGHT_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

# disable
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
AUDIO_ENABLE = no
NKRO_ENABLE = no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
VIA_ENABLE = no 
MOUSEKEY_ENABLE = no	# Mouse keys(+4700)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
EXTRAKEY_ENABLE = no	# Audio control and System control(+450)
