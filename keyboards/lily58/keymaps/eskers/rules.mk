NKRO_ENABLE = yes
EXTRAKEY_ENABLE = yes
LTO_ENABLE = yes
DEBOUNCE_TYPE = asym_eager_defer_pk
CAPS_WORD_ENABLE = yes
#CONSOLE_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/logo_reader.c \
		./lib/eskers_reader.c \
		#./lib/layer_state_reader_eskers.c \
		#./lib/rgb_state_reader.c \
        #./lib/keylogger.c \
        #./lib/host_led_state_reader.c \
        #./lib/timelogger.c \
		#./lib/mode_icon_reader.c \
