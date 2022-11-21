# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

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
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = yes          # Audio output
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
RGB_MATRIX_DRIVER = WS2812
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = DRV2605L
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
