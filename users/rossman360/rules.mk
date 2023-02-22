SRC += rossman360.c

ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif