# MCU name
MCU = at90usb1286

# Bootloader selection
BOOTLOADER = halfkay

# Build Options
#   change to no to disable the options.
#
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
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
BACKLIGHT_ENABLE = yes
