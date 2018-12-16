SRC += action_pseudo_lut.c

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
		./lib/keylogger.c \
        ./lib/mod_state_reader.c \
        ./lib/host_led_state_reader.c
