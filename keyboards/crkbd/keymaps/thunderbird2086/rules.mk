MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
LTO_ENABLE = yes

TAP_DANCE_ENABLE = yes

SRC += oled.c
SRC += process_records.c
SRC += rgb.c
SRC += tap_dances.c

ifneq ("$(wildcard keyboards/crkbd/keymaps/thunderbird2086/secrets.c)","")
	SRC += secrets.c
endif
