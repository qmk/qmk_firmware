LTO_ENABLE=no
AUDIO_ENABLE=no
ENCODER_ENABLE=no

# Broken with gcc >6, see https://github.com/qmk/qmk_firmware/issues/6753
# (yes, different option, but I suspect the code has moved around)
# This produces working firmware on Arch Linux with GCC 11, but is still broken
# on Debian with 8.3.1
RGBLIGHT_ENABLE=no
RGB_MATRIX_ENABLE=no

# not required, but helps on debian where there is a soft/hard float confusion.
# but see above, gcc 8.3.1 still fucks up the firmware.
USE_FPU=no
