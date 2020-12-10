BOOTMAGIC = lite
DYNAMIC_KEYMAP_ENABLE = no
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
LTO_ENABLE = yes
AUDIO_ENABLE = no

# only enable audio on specific boards
ifeq ($(strip $(KEYBOARD)), evyd13/plain60)
    AUDIO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), clueboard/60)
    AUDIO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), hadron/ver3)
    AUDIO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), fruity60)
    COMMAND_ENABLE = no
endif

ifeq ($(strip $(KEYBOARD)), kbdfans/kbd75/rev1)
    COMMAND_ENABLE = no
endif

ifeq ($(strip $(KEYBOARD)), ai03/polaris)
    RGBLIGHT_ENABLE = no
endif
