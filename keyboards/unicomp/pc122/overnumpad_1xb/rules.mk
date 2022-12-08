# MCU name
MCU = STM32F446 # STM32F446RET6

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
ENCODER_ENABLE = no         # Enable rotary encoder support
AUDIO_ENABLE = no           # Audio output
KEYBOARD_SHARED_EP = yes    # Free up some extra endpoints - needed if console+mouse+extra

HAPTIC_ENABLE = yes
HAPTIC_DRIVER = SOLENOID
