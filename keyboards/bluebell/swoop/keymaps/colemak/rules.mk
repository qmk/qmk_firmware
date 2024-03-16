# Enables Link Time Optimization (LTO) when compiling the keyboard. This makes the process take longer,
# but it can significantly reduce the compiled size (and since the firmware is small, the added time is not noticeable).
LTO_ENABLE = no

# ENCODER_ENABLE = no
# WPM_ENABLE = no

MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes