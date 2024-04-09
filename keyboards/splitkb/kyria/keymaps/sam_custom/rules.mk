SRC += oled.c
SRC += capsword.c
SRC += tapdance.c
SRC += rgb_matrix_user.c

# Combo dictionary
VPATH += keyboards/gboards

# LEDs
OLED_ENABLE = yes
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes     # Disable keyboard RGB matrix, as it is enabled by default on rev3
RGB_MATRIX_CUSTOM_KB = yes     # Enable custom user animations

# Debug
CONSOLE_ENABLE = yes

# Disable some stuff we don't need
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no

# Hardware
ENCODER_ENABLE = yes       # Enables the use of one or more encoders

# Behaviors
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes

# Space saving
LTO_ENABLE = yes
