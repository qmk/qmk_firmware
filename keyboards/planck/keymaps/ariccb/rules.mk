BOOTMAGIC_ENABLE = no
CONSOLE_ENABLE = no
BACKLIGHT_ENABLE = yes
MIDI_ENABLE = no
TAP_DANCE_ENABLE = no
DIP_SWITCH_ENABLE = no
COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes

SRC += features/select_word.c
SRC += features/autocorrection.c
SRC += features/layer_lock.c