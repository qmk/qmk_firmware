SRC += ./lib/layer_status/layer_status.c
SRC += ./lib/logo.c

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

# Additional thing to reduce compiled size
LTO_ENABLE = yes
SPACE_CADET_ENABLE = no

# OLED enabled
OLED_ENABLE = yes
OLED_DRIVER = SSD1306

# RGB Matrix enabled
RGB_MATRIX_ENABLE = yes

# Encoder enabled
ENCODER_ENABLE = yes
