# MCU name
MCU = STM32F303

# Use custom matrix to specify how to scan the matrix on the MCP23017.
SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
CUSTOM_MATRIX = lite

CONSOLE_ENABLE = yes
COMMAND_ENABLE = no         # Commands for debug and configuration

# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover

BACKLIGHT_ENABLE = yes      # Used for setting on-board LED brightness
BACKLIGHT_DRIVER = pwm

RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow

UNICODE_ENABLE = no         # Unicode
UNICODEMAP_ENABLE = no      # ^^
UCIS_ENABLE = no            # ^^
