# MCU name
MCU = STM32L433

# MCU = STM32L432
# MCU = cortex-m4
# ARMV = 7
# MCU_FAMILY = STM32
# MCU_SERIES = STM32L4xx
# MCU_LDSCRIPT = STM32L432xB
# MCU_STARTUP = stm32l4xx
# BOARD = GENERIC_STM32_L433XC
# PLATFORM_NAME = platform_l432
# USE_FPU = yes
# UF2_FAMILY = STM32L4

# Build Options
#   change yes to no to disable.
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # USB N-key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = no         # Enable Encoder
DIP_SWITCH_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = CKLED2001

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# EEPROM_DRIVER = i2c