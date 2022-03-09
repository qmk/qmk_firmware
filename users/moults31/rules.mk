SRC += moults31.c

# Custom macro sources
SRC += vscode.c
SRC += obs.c
SRC += gdb.c

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE = yes               # Enable link time optimization
endif
