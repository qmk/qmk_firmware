# If you have Left LEDs (see
# https://geekhack.org/index.php?topic=22780.msg873819#msg873819 for
# details), include the following define:
OPT_DEFS += -DLEFT_LEDS

CUSTOM_MATRIX = lite        # Custom matrix file for the BAJJAK

# Disable unsupported hardware
BACKLIGHT_SUPPORTED = no
AUDIO_SUPPORTED = no

# project specific files
SRC += matrix.c 
I2C_DRIVER_REQUIRED = yes
