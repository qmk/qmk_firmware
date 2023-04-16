# general rules.mk settings for all pogues keymaps

# required settings for these
COMBO_ENABLE = yes

# some general settings
EXTRAKEY_ENABLE = no
NKRO_ENABLE = no
AUDIO_ENABLE = no

# the source files to include
SRC += pogues.c
SRC += features/casemodes.c
SRC += features/compose.c
