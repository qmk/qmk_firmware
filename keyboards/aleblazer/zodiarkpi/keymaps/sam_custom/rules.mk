SRC += capsword.c
SRC += tapdance.c
SRC += display.c
SRC += lvgl_helpers.c
SRC += rgb_matrix_user.c
SRC += ui/ui.c \
	   ui/ui_comp_hook.c \
	   ui/ui_helpers.c \
	   ui/ui_Screen1.c \
	   ui/ui_Screen2.c

# Combo dictionary
VPATH += keyboards/gboards

# LEDs
OLED_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
RGB_MATRIX_CUSTOM_USER = yes

# Screens
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
POINTING_DEVICE_ENABLE = no

# Debug
CONSOLE_ENABLE = yes

# Disable some stuff we don't need
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no

# Hardware
SPLIT_KEYBOARD = yes
ENCODER_ENABLE = yes
MOUSEKEY_ENABLE = yes

# Behaviors
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
TRI_LAYER_ENABLE = yes

# Space saving
LTO_ENABLE = yes
