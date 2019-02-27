SRC += talljoe.c combos.c macros.c $(wildcard users/talljoe/tapdance/*.c)

EXTRAFLAGS+=-flto

TAP_DANCE_ENABLE=yes
COMBO_ENABLE = yes
CONSOLE_ENABLE=no
COMMAND_ENABLE=no
DYNAMIC_KEYMAP_ENABLE=no
BOOTMAGIC_ENABLE=full
