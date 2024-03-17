# general rules.mk settings for all pogues keymaps

# required settings for these
COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes

# some general settings
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
EXTRAKEY_ENABLE = no
NKRO_ENABLE = no
AUDIO_ENABLE = no

# the source files to include
SRC += pogues.c
SRC += features/achordion.c
SRC += features/compose.c
