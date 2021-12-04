
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
BOOTLOADER = atmel-dfu
TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
UNICODEMAP_ENABLE = yes
STENO_ENABLE = yes
NKRO_ENABLE = yes
EXTRAFLAGS += -flto
