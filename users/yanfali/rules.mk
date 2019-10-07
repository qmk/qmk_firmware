BOOTMAGIC = lite
DYNAMIC_KEYMAP_ENABLE = no
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
LINK_TIME_OPTIMIZATION_ENABLE = yes

ifneq (, $(findstring tokyo60, $(KEYBOARD)))
    AUDIO_ENABLE = no
else
    AUDIO_ENABLE = yes
endif

