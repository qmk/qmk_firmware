# MCU name : Use STM32F072 instead of STM32F070 as there are no entry in mcu_selection.mk. STM32F072 & STM32F070 are both ARMV = 6

MCU = STM32F072


BOARD = ST_NUCLEO64_F070RB

# Do not put the microcontroller into power saving mode
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

# Build Options
#   comment out to disable the options.
#
EXTRAKEY_ENABLE   = yes         # Audio control and System control
NKRO_ENABLE       = yes         # USB Nkey Rollover
BOOTMAGIC_ENABLE  = lite        # BOOTMAGIC lite configuration
UNICODEMAP_ENABLE = yes         # Enable Unicode Map
BACKLIGHT_ENABLE  = no          # No keyboard backlight functionality
MOUSEKEY_ENABLE   = no          # No Mouse keys
CONSOLE_ENABLE    = no          # No Console for debug
COMMAND_ENABLE    = no          # No Commands for debug and configuration
AUDIO_ENABLE      = no          # No Audio output
NO_USB_STARTUP_CHECK = no       # Disable initialization only when usb is plugged in
