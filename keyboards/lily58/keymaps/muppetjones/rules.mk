OLED_ENABLE= yes     # OLED display
WPM_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes

# If you want to change the display of OLED, you need to change here
# SRC +=  ./lib/rgb_state_reader.c
SRC +=  ./lib/layer_state_reader.c
SRC +=  ./lib/logo_reader.c
SRC +=  ./lib/keylogger.c
SRC +=  ./features/bongo_cat.c

# Reduce firmware size
# 	https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
# also requires in config.h
LTO_ENABLE = yes
