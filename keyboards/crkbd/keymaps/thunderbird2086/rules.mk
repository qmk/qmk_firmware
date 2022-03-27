MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
LTO_ENABLE = yes

TAP_DANCE_ENABLE = yes      # Enable Tap Dance.
# COMBO_ENABLE = yes          # Enable Combos

SRC += oled.c
SRC += process_records.c
SRC += tap_dances.c

ifneq ("$(wildcard keyboards/crkbd/keymaps/thunderbird2086/secrets.c)","")
	SRC += secrets.c
endif
