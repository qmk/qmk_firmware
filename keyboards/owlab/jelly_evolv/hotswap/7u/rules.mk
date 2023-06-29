MCU_LDSCRIPT = STM32F103x8_0x08006000_bootloader
DFU_ARGS = -d 1688:2220 -a 0 -s 0x08006000 
DFU_SUFFIX_ARGS = -v 1688 -p 2220
BOOTLOADER_TYPE = stm32duino
OPT_DEFS += -DBOOTLOADER_STM32DUINO
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output