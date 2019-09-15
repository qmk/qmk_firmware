# Target file name (without extension).

# project specific files

# MCU name
MCU = at90usb1286

# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
BOOTLOADER = halfKay

# Build Options
#   change to no to disable the options.
#
BOOTMAGIC_ENABLE = yes # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = yes # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes # Audio control and System control(+450)
CONSOLE_ENABLE   = yes # Console for debug(+400)
COMMAND_ENABLE   = yes # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE      = no  # USB Nkey Rollover - not yet supported in LUFA
UNICODE_ENABLE   = yes # Enable support for arrow keys icon on the second layer.
COMBO_ENABLE     = yes # Enable combo for special function when using multiple keys at once.
TAP_DANCE_ENABLE = no  # Enable use multiple tap
NKRO_ENABLE      = yes
