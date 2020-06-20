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
	   outputselect.c \
	   $(LUFA_SRC_USB)

ifeq ($(strip $(MIDI_ENABLE)), yes)
	include $(TMK_PATH)/protocol/midi.mk
endif

ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
	LUFA_SRC += $(LUFA_DIR)/bluetooth.c \
	$(TMK_DIR)/protocol/serial_uart.c
endif

ifeq ($(strip $(BLUETOOTH)), AdafruitBLE)
		LUFA_SRC += spi_master.c
		LUFA_SRC += analog.c
		LUFA_SRC += $(LUFA_DIR)/adafruit_ble.cpp
endif

ifeq ($(strip $(BLUETOOTH)), AdafruitEZKey)
	LUFA_SRC += $(LUFA_DIR)/bluetooth.c \
	$(TMK_DIR)/protocol/serial_uart.c
endif

ifeq ($(strip $(BLUETOOTH)), RN42)
	LUFA_SRC += $(LUFA_DIR)/bluetooth.c \
	$(TMK_DIR)/protocol/serial_uart.c
endif

ifeq ($(strip $(VIRTSER_ENABLE)), yes)
	LUFA_SRC += $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/CDCClassDevice.c
endif

SRC += $(LUFA_SRC)

# Search Path
VPATH += $(TMK_PATH)/$(LUFA_DIR)
VPATH += $(LUFA_PATH)
VPATH += $(DRIVER_PATH)/avr

# Option modules
#ifdef $(or MOUSEKEY_ENABLE, PS2_MOUSE_ENABLE)
#endif

#ifdef EXTRAKEY_ENABLE
#endif

# LUFA library compile-time options and predefined tokens
LUFA_OPTS  = -DUSB_DEVICE_ONLY
LUFA_OPTS += -DUSE_FLASH_DESCRIPTORS
LUFA_OPTS += -DUSE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"
#LUFA_OPTS += -DINTERRUPT_CONTROL_ENDPOINT
LUFA_OPTS += -DFIXED_CONTROL_ENDPOINT_SIZE=8
LUFA_OPTS += -DFIXED_CONTROL_ENDPOINT_SIZE=8
LUFA_OPTS += -DFIXED_NUM_CONFIGURATIONS=1

# Remote wakeup fix for ATmega32U2        https://github.com/tmk/tmk_keyboard/issues/361
ifeq ($(MCU),atmega32u2)
	LUFA_OPTS += -DNO_LIMITED_CONTROLLER_CONNECT
endif

OPT_DEFS += -DF_USB=$(F_USB)UL
OPT_DEFS += -DARCH=ARCH_$(ARCH)
OPT_DEFS += $(LUFA_OPTS)

# This indicates using LUFA stack
OPT_DEFS += -DPROTOCOL_LUFA
