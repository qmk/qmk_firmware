LTO_ENABLE = yes

ifeq ($(strip $(REDUCE_RGB)), yes)
	OPT_DEFS += -DREDUCE_RGB
endif

ifeq ($(strip $(MACROS_ENABLED)), yes)
	OPT_DEFS += -DMACROS_ENABLED
endif

ifeq ($(strip $(REMOVE_DEBOUNCE)), yes)
	OPT_DEFS += -DREMOVE_DEBOUNCE
endif
