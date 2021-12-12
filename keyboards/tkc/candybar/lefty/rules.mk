# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   comment out to disable the options.
#
# LTO_ENABLE = yes
LTO_ENABLE = yes
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no


# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
