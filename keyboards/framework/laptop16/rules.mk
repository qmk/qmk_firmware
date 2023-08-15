BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm

# Custom matrix scanning code via ADC
CUSTOM_MATRIX = lite
SRC += matrix.c analog.c

DEFAULT_FOLDER = framework/laptop16/ansi

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
