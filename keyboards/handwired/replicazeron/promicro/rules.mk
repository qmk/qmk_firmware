# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
TAP_DANCE_ENABLE = no      # Tap Dance

JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
LTO_ENABLE = yes

##########

QMK_SETTINGS = yes

LEDS_ENABLE = yes
THUMBSTICK_ENABLE = yes

SRC += ../common/state.c
