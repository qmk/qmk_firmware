# MCU name
MCU = STM32F303
#OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
AUDIO_ENABLE = yes
USE_I2C = no
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
OLED_DRIVER_ENABLE = yes
UNICODE_ENABLE = yes
# UCIS_ENABLE = no
#CTPC = yes
#SLEEP_LED_ENABLE = yes    # Breathing sleep LED during USB suspend
