# System76 EC
#   remove the RESET HID command
VALID_SYSTEM76_EC_TYPES := yes
SYSTEM76_EC_ENABLE ?= no
ifneq ($(strip $(SYSTEM76_EC_ENABLE)),no)
    ifeq ($(filter $(SYSTEM76_EC_ENABLE),$(VALID_SYSTEM76_EC_TYPES)),)
        $(error SYSTEM76_EC_EN="$(strip $(SYSTEM76_EC_ENABLE))" is not a valid type for the System76 EC option)
    endif
    ifneq ($(strip $(SYSTEM76_EC_ENABLE)),no)
        OPT_DEFS += -DSYSTEM76_EC
    endif
endif
