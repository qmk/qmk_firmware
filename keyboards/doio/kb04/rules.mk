# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = stm32duino

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

# Additional thing to reduce compiled size
LTO_ENABLE = yes

# RGB Matrix enabled
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

# Encoder enabled
ENCODER_ENABLE = yes

# Wear-levelling driver
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE