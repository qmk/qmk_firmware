# MCU name
MCU = STM32F401
BOARD = BLACKPILL_STM32_F401

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
DIP_SWITCH_ENABLE = yes     # Dip Switch Enabled

# Necessary for stenography functionality
STENO_ENABLE = yes          # Enable stenography endpoint
NKRO_ENABLE = yes           # Enable N-Key Rollover
KEYBOARD_SHARED_EP = yes    # Needed to free up an endpoint in blackpill