# MCU name
MCU = STM32F103

# GENERIC STM32F103C8T6 board - stm32duino bootloader
# OPT_DEFS = -DCORTEX_VTOR_INIT=0x2000
# MCU_LDSCRIPT = STM32F103x8_stm32duino_bootloader
# BOARD = STM32_F103_STM32DUINO
BOOTLOADER = stm32duino

# DFU_ARGS = -d 1eaf:0003 -a2 -R
# DFU_SUFFIX_ARGS = -v 1eaf -p 0003

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no	# Console for debug(+400)
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
