# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight. - We have custom RGB underglow

RGB_MATRIX_ENABLE = yes     # Enable RGB matrix effects.
RGB_MATRIX_DRIVER = custom  # Enable RGB matrix effects.

COMMON_VPATH += $(DRIVER_PATH)/issi

# project specific files
SRC +=  drivers/led/issi/is31fl3731.c \
        ws2812.c

QUANTUM_LIB_SRC += i2c_master.c 

LTO_ENABLE = yes
