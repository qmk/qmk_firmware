# MCU name
MCU = atmega32u4
BOOTLOADER = atmel-dfu
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
# MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

OLED_ENABLE = yes    # Enable Support for SSD1306 or SH1106 OLED Displays; Communicating over I2C
OLED_DRIVER = SSD1306

LTO_ENABLE = yes

# NO_USB_STARTUP_CHECK = yes

RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = WS2812
# RGB_MATRIX_ENABLE = yes
# RGB_MATRIX_DRIVER = WS2812
SPLIT_KEYBOARD = yes
