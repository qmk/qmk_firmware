# Use macropad-specific defines, layers, functions. Flash bootloader with KC_MAKE
IS_MACROPAD = yes

# Use dfu bootloader for Elite-C
BOOTLOADER = atmel-dfu

# Build Options
RGBLIGHT_ENABLE = yes        # Enable WS2812 RGB underlight.
CONSOLE_ENABLE = yes         # Console for debug(+400)
MOUSEKEY_ENABLE = yes        # Use mouse keys for scrolling.
COMMAND_ENABLE = no          # Disable Command, breaks with Mouse Keys set to constant.
TAP_DANCE_ENABLE = yes       # Use tap dance

# Userspace Options
RGB_THEME = granite	         # Set RGB colors to Granite Theme
