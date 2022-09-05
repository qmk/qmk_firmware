# MCU name
MCU = STM32F042
BOARD = ST_NUCLEO32_F042K6

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no				# Mouse keys
EXTRAKEY_ENABLE = no				# Audio control and System control
CONSOLE_ENABLE = no					# Console for debug
COMMAND_ENABLE = no    			# Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
NO_USB_STARTUP_CHECK = no   # Disable initialization only when usb is plugged in

LAYOUTS = 60_ansi 60_iso

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
