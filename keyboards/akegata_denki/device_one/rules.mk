# MCU name
MCU = STM32F042

BOARD = ST_NUCLEO32_F042K6

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no				# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no				# Mouse keys
EXTRAKEY_ENABLE = no				# Audio control and System control
CONSOLE_ENABLE = no					# Console for debug
COMMAND_ENABLE = no    			# Commands for debug and configuration
NKRO_ENABLE = yes					  # USB Nkey Rollover
NO_USB_STARTUP_CHECK = no   # Disable initialization only when usb is plugged in

LAYOUTS = 60_ansi 60_iso

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
