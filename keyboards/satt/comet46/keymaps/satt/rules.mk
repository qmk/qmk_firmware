SRC += action_pseudo_lut.c

# If you want to change display settings of the OLED, you need to change the following lines
SRC +=  ./lib/keylogger.c \
        ./lib/modifier_state_reader.c \
        ./lib/host_led_state_reader.c

OLED_ENABLE = yes
