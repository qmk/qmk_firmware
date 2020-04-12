# MCU name
MCU = atmega32u4

BOOTLOADER = caterina

# Build Options
# change yes to no to disable
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
AUDIO_ENABLE = no
#RGBLIGHT_ENABLE = yes
OLED_DRIVER_ENABLE = yes
ENCODER_ENABLE = yes
LAYOUTS = hasu_5x4
RGB_MATRIX_ENABLE = WS2812
#BACKLIGHT_ENABLE = yes	# Enable keyboard backlight functionality
