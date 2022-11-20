# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
EXTRAKEY_ENABLE = yes       # Audio control and System control
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key rollover
AUDIO_ENABLE = no           # Audio output
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality

SPLIT_KEYBOARD = yes

# Enables the use of OLED displays
OLED_ENABLE = yes
OLED_DRIVER = SSD1306

# Enable LEDs
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no      # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
RGB_MATRIX_SUPPORTED = no

# Enables the use of one or more encoders
ENCODER_ENABLE = yes

# Enable Link Time Optimization
LTO_ENABLE = yes			# Enable help with smaller firmware size

DEFAULT_FOLDER = clickety_split/leeloo/rev2
