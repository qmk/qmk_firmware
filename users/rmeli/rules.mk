# https://github.com/qmk/qmk_firmware/blob/develop/docs/squeezing_avr.md
CONSOLE_ENABLE = no
COMMAND_ENABLE = no # Turned off for Space Cadet Shift and Caps Word
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no # Implemented with tap dance
GRAVE_ESC_ENABLE = no
MUSIC_ENABLE = no
CAPS_WORD_ENABLE = yes
HOME_ROW_MODS_ENABLE = yes

# VIA only support 4 layers by default
# Use "#define DYNAMIC_KEYMAP_LAYER_COUNT" in config.h to change the limit
VIA_ENABLE = no

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += $(USER_PATH)/oled/oled.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += $(USER_PATH)/keyrecords/tap_dances.c
endif

ifeq ($(strip $(HOME_ROW_MODS_ENABLE)), yes)
    # Define custom variable
    OPT_DEFS += -DHOME_ROW_MODS_ENABLED
endif