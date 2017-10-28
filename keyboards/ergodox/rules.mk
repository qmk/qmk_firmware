#----------------------------------------------------------------------------
# On command line:
#
# make = Make software.
#
# make clean = Clean out built project files.
#
# That's pretty much all you need. To compile, always go make clean, 
# followed by make.
#
# For advanced users only:
# make teensy = Download the hex file to the device, using teensy_loader_cli.
#               (must have teensy_loader_cli installed).
#
#----------------------------------------------------------------------------
# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = yes # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes # Audio control and System control(+450)
CONSOLE_ENABLE   = no  # Console for debug(+400)
COMMAND_ENABLE   = yes # Commands for debug and configuration
CUSTOM_MATRIX    = yes # Custom matrix file for the ErgoDox EZ
SLEEP_LED_ENABLE = yes # Breathing sleep LED during USB suspend
NKRO_ENABLE      = yes # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
UNICODE_ENABLE   = yes # Unicode
ONEHAND_ENABLE   = yes # Allow swapping hands of keyboard
