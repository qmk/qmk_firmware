# MCU name
MCU = STM32F303

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = yes    # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
AUDIO_ENABLE = yes
USE_I2C = no
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
OLED_DRIVER_ENABLE = yes
UNICODE_ENABLE = yes

SRC += ds1307.c taphold.c
