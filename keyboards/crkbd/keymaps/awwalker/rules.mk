EXTRAKEY_ENABLE = yes        # Audio control and System control(+450)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
SLEEP_LED_ENABLE = yes    # Breathing sleep LED during USB suspend.
OLED_DRIVER_ENABLE = yes
WPM_ENABLE = yes
TAP_DANCE_ENABLE = yes
CONSOLE_ENABLE = no

EXTRAFLAGS += -flto

SRC += ./lib/rgb_state_reader.c \
	   ./lib/layer_state_reader.c \
	   ./lib/logo_reader.c \
	   ./oled.c \
