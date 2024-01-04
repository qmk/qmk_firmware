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
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight. - We have custom RGB underglow

RGB_MATRIX_ENABLE = yes     # Enable RGB matrix effects.
WS2812_DRIVER_REQUIRED = yes

COMMON_VPATH += $(DRIVER_PATH)/issi

# project specific files
SRC +=  drivers/led/issi/is31fl3731.c

I2C_DRIVER_REQUIRED = yes

LTO_ENABLE = yes
