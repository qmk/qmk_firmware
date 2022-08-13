# a "*" in the feature comments signals that it isn't actually implented in the
# keymap and is listed here to make sure it's disabled

LTO_ENABLE = yes             # very aggressive space saving
NKRO_ENABLE = yes            # USB Nkey Rollover
DYNAMIC_MACRO_ENABLE = yes	 # Dynamic macro recording and play
BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite

UNICODE_ENABLE  = no         # enable unicode support *
EXTRAKEY_ENABLE = yes        # Audio control and System control
MOUSEKEY_ENABLE = no         # Use keyboard as mouse *
JOYSTICK_ENABLE = no         # Use keyboard as controller *

# RGB stuff
RGB_MATRIX_ENABLE = yes      # enable RGB
RGB_MATRIX_DRIVER = WS2812   # What RGBMatrix driver
RGBLIGHT_ENABLE = no         # enable RGBLight?
RGBLIGHT_DRIVER = WS2812     # What RGBLight driver

VIA_ENABLE = no              # Enable VIA