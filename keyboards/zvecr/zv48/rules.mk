# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
KEYBOARD_SHARED_EP = yes    # Free up some extra endpoints - needed if console+mouse+extra
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
ENCODER_ENABLE = yes        # Enable rotary encoder support
AUDIO_ENABLE = no           # Audio output

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart
WS2812_DRIVER = pwm

DEFAULT_FOLDER = zvecr/zv48/f401

LAYOUTS = ortho_4x12
