MCU = STM32F401
BOARD = GENERIC_STM32_F401XC

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes          # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes     # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = pwm
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
AUDIO_ENABLE = no          # Audio output
LTO_ENABLE = yes
ENCODER_ENABLE = no

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
