# If you are using a custom AVR Pro Micro-compatible dev board (Elite-C, Sea-Micro, etc)
# you may need to uncomment and modify this BOOTLOADER setting to use the correct
# bootloader. (e.g. Elite-Cs use "atmel-dfu", not "caterina".)
#
# See the QMK docs for more information:
# https://docs.qmk.fm/#/flashing
# https://docs.qmk.fm/#/driver_installation_zadig?id=list-of-known-bootloaders

# BOOTLOADER = caterina

# Conversion to some non-AVR Pro Micro-compatible dev boards can be performed automatically.
# Uncomment and modify this CONVERT_TO setting for your dev board.
#
# See the QMK docs for more information:
# https://docs.qmk.fm/#/feature_converters

# CONVERT_TO=promicro_rp2040

# If you are not using an encoder, set these options to no.
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# If you did not add RGB LEDs, set this option to no.
RGBLIGHT_ENABLE = yes
