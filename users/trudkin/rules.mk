ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif

ifeq ($(strip $(USE_1X2_LAYOUT)), yes)
    OPT_DEFS += -DUSE_1X2_LAYOUT
endif
