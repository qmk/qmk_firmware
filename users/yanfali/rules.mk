BOOTMAGIC = lite
DYNAMIC_KEYMAP_ENABLE = no
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
LINK_TIME_OPTIMIZATION_ENABLE = yes

# only enable audio on specific boards
ifeq ($(strip $(KEYBOARD)), maartenwut/plain60)
    AUDIO_ENABLE = yes
else
    AUDIO_ENABLE = no
endif

ifeq ($(strip $(KEYBOARD)), fruity60)
    COMMAND_ENABLE = no
endif
