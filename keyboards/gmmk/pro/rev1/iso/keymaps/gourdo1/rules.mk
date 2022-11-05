LTO_ENABLE = yes               # link time optimization -- achieves a smaller compiled size
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = yes

VIA_ENABLE = yes
TAP_DANCE_ENABLE = yes
BOOTMAGIC_ENABLE = yes         # Enable Bootmagic Lite
CAPS_WORD_ENABLE = yes         # Enable built-in Caps Word functionality

TD_LSFT_CAPSLOCK_ENABLE = yes
IDLE_TIMEOUT_ENABLE = yes
STARTUP_NUMLOCK_ON = yes
ENCODER_DEFAULTACTIONS_ENABLE = no

COLEMAK_LAYER_ENABLE = yes     # Enable Colemak layer / set to no to disable
INVERT_NUMLOCK_INDICATOR = yes

GAME_ENABLE ?= yes             # Enable Paddle Game / set to no to disable
ifeq ($(strip $(GAME_ENABLE)), yes)
    OPT_DEFS += -DGAME_ENABLE
endif
