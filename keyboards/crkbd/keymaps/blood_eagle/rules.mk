MCU = atmega32u4

BOOTLOADER = qmk-dfu

BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes      # Audio control and System control(+450)
CONSOLE_ENABLE = no        # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes          # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
UNICODE_ENABLE = no        # Unicode
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes      # Enable WS2812 RGB underlight.
# RGB_MATRIX_ENABLE  = WS2812
OLED_DRIVER_ENABLE = yes

# if firmware size over limit, try this option
CFLAGS += -flto

DEFAULT_FOLDER = crkbd/rev1
