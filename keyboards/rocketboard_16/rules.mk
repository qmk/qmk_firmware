# MCU name
MCU = STM32F103

# Bootloader selection
# BOOTLOADER = stm32duino

# Custom loader configuration
MCU_LDSCRIPT = STM32F103xB_stm32duino_bootloader
OPT_DEFS += -DBOOTLOADER_STM32DUINO
BOARD = STM32_F103_STM32DUINO
STM32_BOOTLOADER_ADDRESS = 0x80000000
DFU_ARGS = -d 1EAF:0003 -a 2 -R
DFU_SUFFIX_ARGS = -v 1EAF -p 0003

# Extra include
SRC += keycode_lookup.c

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB backlit keys
AUDIO_ENABLE = no           # Audio output
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
ENCODER_ENABLE = yes

RAW_ENABLE = yes            # Enables HID RAW communication between the board and the PC

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

LTO_ENABLE = yes
