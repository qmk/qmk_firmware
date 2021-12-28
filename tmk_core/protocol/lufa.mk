LUFA_DIR = protocol/lufa

# Path to the LUFA library
LUFA_PATH = $(LIB_PATH)/lufa

# Create the LUFA source path variables by including the LUFA makefile
ifneq (, $(wildcard $(LUFA_PATH)/LUFA/Build/lufa_sources.mk))
    # New build system from 20120730
    LUFA_ROOT_PATH = $(LUFA_PATH)/LUFA
    DMBS_LUFA_PATH = $(LUFA_PATH)/LUFA/Build/LUFA
    include $(LUFA_PATH)/LUFA/Build/lufa_sources.mk
else
    include $(LUFA_PATH)/LUFA/makefile
endif

LUFA_SRC = lufa.c \
	usb_descriptor.c \
	$(LUFA_SRC_USB)

ifeq ($(strip $(MIDI_ENABLE)), yes)
	include $(TMK_PATH)/protocol/midi.mk
endif

ifeq ($(strip $(VIRTSER_ENABLE)), yes)
	LUFA_SRC += $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/CDCClassDevice.c
endif

SRC += $(LUFA_SRC)
SRC += $(LUFA_DIR)/usb_util.c

# Search Path
VPATH += $(TMK_PATH)/$(LUFA_DIR)
VPATH += $(LUFA_PATH)

# LUFA library compile-time options and predefined tokens
LUFA_OPTS  = -DUSB_DEVICE_ONLY
LUFA_OPTS += -DUSE_FLASH_DESCRIPTORS
LUFA_OPTS += -DUSE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"
LUFA_OPTS += -DFIXED_CONTROL_ENDPOINT_SIZE=8
LUFA_OPTS += -DFIXED_NUM_CONFIGURATIONS=1

# Remote wakeup fix for ATmega16/32U2        https://github.com/tmk/tmk_keyboard/issues/361
ifneq (,$(filter $(MCU), at90usb162 atmega16u2 atmega32u2))
	LUFA_OPTS += -DNO_LIMITED_CONTROLLER_CONNECT
endif

OPT_DEFS += -DF_USB=$(F_USB)UL
OPT_DEFS += -DARCH=ARCH_$(ARCH)
OPT_DEFS += $(LUFA_OPTS)

# This indicates using LUFA stack
OPT_DEFS += -DPROTOCOL_LUFA
