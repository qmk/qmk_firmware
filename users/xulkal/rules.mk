SRC += xulkal.c \
       process_records.c

# Some usual defaults
MOUSEKEY_ENABLE         = no    # Mouse keys (+4700)
EXTRAKEY_ENABLE         = yes   # Audio control and System control (+450)
TAP_DANCE_ENABLE        = yes   # Enable the tap dance feature. (+1100)

ifneq ($(strip $(DISABLE_LTO)), yes)
  EXTRAFLAGS += -flto
  OPT_DEFS += -DNO_ACTION_MACRO
  OPT_DEFS += -DNO_ACTION_FUNCTION
endif
