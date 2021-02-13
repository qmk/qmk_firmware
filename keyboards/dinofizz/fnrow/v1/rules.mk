# MCU name
MCU = STM32F042

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no				# Mouse keys
EXTRAKEY_ENABLE = yes				# Audio control and System control
CONSOLE_ENABLE = no					# Console for debug
COMMAND_ENABLE = no    				# Commands for debug and configuration
NKRO_ENABLE = no					# USB Nkey Rollover


# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
