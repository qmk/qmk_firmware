# MCU name
MCU = STM32F411

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
MCU_LDSCRIPT = noah_boot

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = noah_bd

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes	    # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # USB Nkey Rollover
NO_USB_STARTUP_CHECK = yes	# Disable initialization only when usb is plugged in

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3731

RGBLIGHT_ENABLE = yes
RGBLIGHT_CUSTOM_DRIVER = yes

CUSTOM_MATRIX = yes
# project specific files
SRC += ws2812.c matrix.c

LAYOUTS = 65_iso_blocker
