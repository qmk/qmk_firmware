# VIA support uses raw HID, don't need to enable it extra.
# Only when disabling VIA but still wanting to use RAW, need to enable it here.
VIA_ENABLE = yes
RAW_ENABLE = no

# Enabled in info.json
# EXTRAKEY_ENABLE = yes          # Audio control and System control

# Enable for all. ANSI keyboard supports RGB and white, macropad only RGB, all others only white.
# No harm in enabling it for all.
# Also RP pico has the built-in LED wired to the same GPIO. Good for prototyping
BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm

# Custom matrix scanning code via ADC
CUSTOM_MATRIX = lite
SRC += matrix.c analog.c

DEFAULT_FOLDER = framework/ansi

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
