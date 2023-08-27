# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = adns5050
MOUSEKEY_ENABLE = yes        # Mouse keys

ENCODER_ENABLE := no
OPTS_DEF += -DENCODER_ENABLE

QUANTUM_LIB_SRC += analog.c
SRC += opt_encoder.c

DEFAULT_FOLDER = ploopyco/trackball_mini/rev1_001
