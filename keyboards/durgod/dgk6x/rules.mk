# MCU name
# Actually F070, but close enough
MCU = STM32F072
BOARD = DURGOD_STM32_F070

# Bootloader selection
BOOTLOADER = stm32-dfu

# Do not put the microcontroller into power saving mode
NO_SUSPEND_POWER_DOWN = yes

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
LTO_ENABLE = yes

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3733

DEFAULT_FOLDER=durgod/dgk6x/hades
