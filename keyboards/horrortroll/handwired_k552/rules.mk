SRC += lib/logo.c

# MCU name
MCU = STM32F103

# Custom bootloader configuration
BOOTLOADER_TYPE = stm32duino
OPT_DEFS += -DBOOTLOADER_STM32DUINO
MCU_LDSCRIPT = STM32F103xC_stm32duino_bootloader
BOARD = STM32_F103XC_STM32DUINO
DFU_ARGS = -d 1EAF:0003 -a 2 -R
DFU_SUFFIX_ARGS = -v 1EAF -p 0003

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

# RGB Matrix enabled
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

# OLED enabled
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
WPM_ENABLE = yes

LAYOUTS = tkl_ansi
