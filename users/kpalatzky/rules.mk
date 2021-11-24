# 60% is default
SRC += 60/kpalatzky.c

# Flags
CONSOLE_ENABLE = no
TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = no

# Link time optimization, should save on firmware size
EXTRAFLAGS += -flto

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE        = yes
endif
