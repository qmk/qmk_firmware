LTO_ENABLE = yes
SRC += chrisgve.c

ifeq ($(strip $(REDUCE_RGB)), yes)
	OPT_DEFS += -DREDUCE_RGB
endif

ifeq ($(strip $(MACROS_ENABLE)), yes)
	OPT_DEFS += -DMACROS_ENABLE
endif

ifeq ($(strip $(REMOVE_DEBOUNCE)), yes)
	OPT_DEFS += -DREMOVE_DEBOUNCE
endif

ifeq ($(strip $(SHIFT_ENABLE)), yes)
	OPT_DEFS += -DSHIFT_ENABLE
endif
