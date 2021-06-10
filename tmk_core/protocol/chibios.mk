PROTOCOL_DIR = protocol
CHIBIOS_DIR = $(PROTOCOL_DIR)/chibios


SRC += $(CHIBIOS_DIR)/usb_main.c
SRC += $(CHIBIOS_DIR)/main.c
SRC += usb_descriptor.c
SRC += $(CHIBIOS_DIR)/usb_driver.c
SRC += $(CHIBIOS_DIR)/usb_util.c
SRC += $(LIBSRC)

VPATH += $(TMK_PATH)/$(PROTOCOL_DIR)
VPATH += $(TMK_PATH)/$(CHIBIOS_DIR)
VPATH += $(TMK_PATH)/$(CHIBIOS_DIR)/lufa_utils

OPT_DEFS += -DFIXED_CONTROL_ENDPOINT_SIZE=64
OPT_DEFS += -DFIXED_NUM_CONFIGURATIONS=1

ifeq ($(strip $(MIDI_ENABLE)), yes)
  include $(TMK_PATH)/protocol/midi.mk
endif
