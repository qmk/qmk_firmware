# Build Options
#   change yes to no to disable
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes				# Mouse keys
EXTRAKEY_ENABLE = yes				# Audio control and System control
CONSOLE_ENABLE = no					# Console for debug
COMMAND_ENABLE = no    				# Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
NO_USB_STARTUP_CHECK = no         	# Disable initialization only when usb is plugged in


# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
