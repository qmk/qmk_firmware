CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output (needs a pin configured in config.h, see docs/feature_audio.md)
MOUSEKEY_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = WS2812
OLED_DRIVER_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  logo_reader.c \
				layer.c
