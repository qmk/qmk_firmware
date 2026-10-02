OPT_DEFS += -DVIA_ENABLE

ifeq ($(strip $(VIA_INSECURE)), yes)
	OPT_DEFS += -DVIA_INSECURE
endif
