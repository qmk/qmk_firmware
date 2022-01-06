OLED_ENABLE = yes
OLED_DRIVER = SSD1306

# VIA only support 4 layers by default
# Use "#define DYNAMIC_KEYMAP_LAYER_COUNT" in config.h to change the limit
VIA_ENABLE = no

TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes

UNICODEMAP_ENABLE = yes

RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes

# https://github.com/qmk/qmk_firmware/blob/develop/docs/squeezing_avr.md
CONSOLE_ENABLE = no
COMMAND_ENABLE = no # Needed for Space Cadet Shift
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no # Implemented with tap dance
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no
