# System76 EC
#   Add System76 EC raw HID command interface
VALID_SYSTEM76_EC_SETTINGS := yes no
SYSTEM76_EC_ENABLE ?= yes
ifneq ($(strip $(SYSTEM76_EC_ENABLE)),yes)
    ifeq ($(filter $(SYSTEM76_EC_ENABLE),$(VALID_SYSTEM76_EC_SETTINGS)),)
        $(error SYSTEM76_EC_ENABLE="$(strip $(SYSTEM76_EC_ENABLE))" is not a valid setting for the System76 EC option)
    endif
    ifeq ($(strip $(SYSTEM76_EC_ENABLE)),no)
        RAW_ENABLE = no
    endif
else
    OPT_DEFS += -DSYSTEM76_EC
endif
SRC += system76_ec.c

# USB multiplexer
#   Allow variable-length arrays in USB multiplexer's I2C functions
VALID_USB_VLA_SETTINGS := yes no
USB_VLA_ENABLE ?= no
ifeq ($(strip $(USB_VLA_ENABLE)),yes)
    OPT_DEFS += -DUSB_VLA
endif
