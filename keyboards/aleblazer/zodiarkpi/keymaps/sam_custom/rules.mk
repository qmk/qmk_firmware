SRC += capsword.c
SRC += tapdance.c
SRC += rgb_matrix_user.c

# Combo dictionary
VPATH += keyboards/gboards

# LEDs
OLED_ENABLE = no
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes     # Disable keyboard RGB matrix, as it is enabled by default on rev3
RGB_MATRIX_DRIVER = ws2812
RGB_MATRIX_CUSTOM_USER = yes     # Enable custom user animations

# Screens
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
POINTING_DEVICE_ENABLE = no

# Debug
CONSOLE_ENABLE = yes

# Disable some stuff we don't need
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no

# Hardware
SPLIT_KEYBOARD = yes
ENCODER_ENABLE = yes       # Enables the use of one or more encoders

# Behaviors
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
TRI_LAYER_ENABLE = yes

# Space saving
LTO_ENABLE = yes
