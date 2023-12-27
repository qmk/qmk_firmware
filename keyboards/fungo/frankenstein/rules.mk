# Build Options
#   change yes to no to disable
#
MCU = atmega32u4
BOOTLOADER = atmel-dfu   # controller Elite-C


BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no       # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
KEY_LOCK_ENABLE = yes       # kc_lock use


OLED_ENABLE = no
ENCODER_ENABLE = yes        # encoder
ENCODER_MAP_ENABLE = yes    # ENCODER MAP

# caps word, auto return prev capslock,  
# check option {COMMAND_ENABLE = no}
CAPS_WORD_ENABLE = yes

POINTING_DEVICE_ENABLE = yes
# POINTING_DEVICE_DRIVER = analog_joystick
POINTING_DEVICE_DRIVER = pimoroni_trackball