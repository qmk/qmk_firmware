BOOTLOADER = atmel-dfu  # Elite-C
NKRO_ENABLE = yes
TAP_DANCE_ENABLE = yes
EXTRAKEY_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c
