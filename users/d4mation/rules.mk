SRC += d4mation.c \
  tap-hold.c \
  macros.c

BOOTMAGIC_ENABLE = no
LTO_ENABLE = yes
MOUSEKEY_ENABLE = no

ifeq ($(strip $(UNICODE_ENABLE)), yes)
  SRC += zalgo.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap-dance.c
endif