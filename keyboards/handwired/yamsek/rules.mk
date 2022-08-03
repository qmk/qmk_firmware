#
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
#CONSOLE_ENABLE = no         # Console for debug(+400)
#COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE = no            # MIDI controls
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6

SPLIT_KEYBOARD = no # port-expander doesn't count as "two controller split"
# OLED_ENABLE = no


CC_FLAGS += -Werror


# override quantums matrix.c with custom matrix file
#   which uses a row-oriented internal data-structure, we use a column oriented
#   that was inherited from the I2C/MCP23018 code of the ergodox/ez
CUSTOM_MATRIX = yes
SRC += matrix.c

RGBLIGHT_ENABLE = no
RGBLIGHT_DRIVER = WS2812

VPATH += drivers/gpio
SRC += mcp23018.c i2c_master.c
