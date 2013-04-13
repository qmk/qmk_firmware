LUFA_DIR = protocol/lufa

# Path to the LUFA library
LUFA_PATH ?= protocol/lufa/LUFA-120730

# Create the LUFA source path variables by including the LUFA makefile
ifneq (, $(wildcard $(TOP_DIR)/$(LUFA_PATH)/LUFA/Build/lufa_sources.mk))
    # New build system from 20120730
    LUFA_ROOT_PATH = $(LUFA_PATH)/LUFA
    include $(TOP_DIR)/$(LUFA_PATH)/LUFA/Build/lufa_sources.mk 
else
    include $(TOP_DIR)/$(LUFA_PATH)/LUFA/makefile
endif

LUFA_SRC = $(LUFA_DIR)/lufa.c \
	   $(LUFA_DIR)/descriptor.c \
	   $(LUFA_SRC_USB)

SRC += $(LUFA_SRC)

# Search Path
VPATH += $(TOP_DIR)/$(LUFA_DIR)
VPATH += $(TOP_DIR)/$(LUFA_PATH)

# Option modules
#ifdef $(or MOUSEKEY_ENABLE, PS2_MOUSE_ENABLE)
#endif

#ifdef EXTRAKEY_ENABLE
#endif

# LUFA library compile-time options and predefined tokens
LUFA_OPTS  = -D USB_DEVICE_ONLY
LUFA_OPTS += -D USE_FLASH_DESCRIPTORS
LUFA_OPTS += -D USE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"

OPT_DEFS += -DF_USB=$(F_USB)UL
OPT_DEFS += -DARCH=ARCH_$(ARCH)
OPT_DEFS += $(LUFA_OPTS)

# This indicates using LUFA stack
OPT_DEFS += -DPROTOCOL_LUFA
