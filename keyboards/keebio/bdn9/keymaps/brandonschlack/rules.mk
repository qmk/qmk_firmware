# Use macropad-specific defines, layers, functions. Flash bootloader with QM_MAKE
IS_MACROPAD = yes

# Use dfu bootloader for Elite-C
BOOTLOADER = atmel-dfu

# Build Options
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
COMMAND_ENABLE = no         # Disable Command, breaks with Mouse Keys set to constant.
BACKLIGHT_ENABLE = no       # No backlights installed
TAP_DANCE_ENABLE = yes      # Use tap dance
