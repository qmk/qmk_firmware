LTO_ENABLE = yes

ifeq ($(strip $(MACROS_ENABLED)), yes)
	OPT_DEFS += -DMACROS_ENABLED
endif
