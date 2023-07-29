ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
UNICODEMAP_ENABLE = yes # I maybe need this for send_unicode_string

# Firmware size optimizations:
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
