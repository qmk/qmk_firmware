# MCU name
MCU = STM32F072

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes   # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = yes    # Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes       # USB Nkey Rollover
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = yes
WS2812_DRIVER = spi

LAYOUTS = 60_ansi 60_tsangan_hhkb 60_iso

# Wildcard to allow APM32 MCU 
DFU_SUFFIX_ARGS = -p FFFF -v FFFF

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
