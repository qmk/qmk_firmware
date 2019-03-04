SRC += talljoe.c macros.c $(wildcard users/talljoe/tapdance/*.c)
ifeq ($(strip $(VISUALIZER_ENABLE)), yes)
  SRC += visualizer.c
endif

EXTRAFLAGS+=-flto

TAP_DANCE_ENABLE=yes
CONSOLE_ENABLE=no
COMMAND_ENABLE=no
DYNAMIC_KEYMAP_ENABLE=no
BOOTMAGIC_ENABLE=full
