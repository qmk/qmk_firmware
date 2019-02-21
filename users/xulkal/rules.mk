SRC += xulkal.c \
       process_records.c

# Link time optimization, should save on firmware size
EXTRAFLAGS += -flto

# Some usual defaults
MOUSEKEY_ENABLE         = no    # Mouse keys(+4700)
EXTRAKEY_ENABLE         = yes   # Audio control and System control(+450)
CONSOLE_ENABLE          = no    # Console for debug(+400)
COMMAND_ENABLE          = no    # Commands for debug and configuration
TAP_DANCE_ENABLE        = yes   # Enable the tap dance feature.
