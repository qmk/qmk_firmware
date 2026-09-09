RGB_MATRIX_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes
# Use the RK custom rgblight implementation and avoid QMK's built-in rgblight objects.
RGBLIGHT_ENABLE = no
RGBLIGHT_DRIVER = custom
SRC += keyboards/royal_kludge/r87pro_us_usb/rgb_record/rgb_rgblight.c
SRC += keyboards/royal_kludge/r87pro_us_usb/rgb_record/rgb_effect.c
include keyboards/royal_kludge/r87pro_us_usb/rgb_record/rgb_record.mk
include keyboards/royal_kludge/r87pro_us_usb/wls/wls.mk
include keyboards/royal_kludge/linker/wireless/wireless.mk
