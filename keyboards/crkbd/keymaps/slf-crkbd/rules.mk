# Bootloader selection
BOOTLOADER = qmk-dfu  # Elite C
# BOOTLOADER = caterina



RGBLIGHT_ENABLE    = no
RGB_MATRIX_ENABLE  = WS2812
MOUSEKEY_ENABLE    = no
EXTRAKEY_ENABLE    = yes
NKRO_ENABLE        = yes
OLED_DRIVER_ENABLE = yes
AUTO_SHIFT_ENABLE  = yes
TAP_DANCE_ENABLE   = yes      # FrAT # tap dance. One tap one code, two taps another code, three taps, and so on.

# added for filesize optimization
EXTRAFLAGS += -flto
 