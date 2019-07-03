SRC += muse.c
# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LINK_TIME_OPTIMIZATION_ENABLE = yes
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
COMBO_ENABLE = no
TAP_DANCE_ENABLE = no
NKRO_ENABLE = yes
COMMAND_ENABLE = no       # Commands for debug and configuration
MOUSEKEY_ENABLE = no      # Mouse keys(+4700)
CONSOLE_ENABLE = no         # Console for debug(+400)
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration(+1000)
NO_USB_STARTUP_CHECK = yes   # Disable usb suspend check after keyboard startup
