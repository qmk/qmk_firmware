# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Project, sources and paths
#

RIOTBASE = $(TOP_DIR)/lib/riot

RM=/usr/bin/rm -f
ARFLAGS = rcTs
export RM
export ARFLAGS
LINKFLAGPREFIX ?= -Wl,

LDFLAGS += -Wl,--unresolved-symbols=ignore-in-object-files

MCUFLAGS = -mno-thumb-interwork -mlittle-endian -mthumb -mcpu=$(MCU)

ARMV ?= 7
ifeq ($(strip $(ARMV)),6)
	MCUFLAGS += -march=armv6s-m
endif

USE_FPU ?= no
ifneq ($(USE_FPU),no)
	MCUFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
else
	MCUFLAGS += -mfloat-abi=soft
endif

PLATFORM_SRC = \
        $(PLATFORM_COMMON_DIR)/wait.c \

##############################################################################
# Compiler settings
#
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
AR = arm-none-eabi-ar
NM = arm-none-eabi-nm
HEX = $(OBJCOPY) -O $(FORMAT)
EEP =
BIN = $(OBJCOPY) -O binary

OPT_DEFS += -DPROTOCOL_RIOT

# TODO: Print lib seems to complain but not on chibi/arm_atsam?
CFLAGS += -Wformat=0
CFLAGS += -Wno-format-extra-args

##############################################################################
# RIOT-OS Bodges
#
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/boards/$(BOARD)/Makefile)","")
    KEYBOARD_BOARD_DIR = $(KEYBOARD_PATH_5)/boards/
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/boards/$(BOARD)/Makefile)","")
    KEYBOARD_BOARD_DIR = $(KEYBOARD_PATH_4)/boards/
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/boards/$(BOARD)/Makefile)","")
    KEYBOARD_BOARD_DIR = $(KEYBOARD_PATH_3)/boards/
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/boards/$(BOARD)/Makefile)","")
    KEYBOARD_BOARD_DIR = $(KEYBOARD_PATH_2)/boards/
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/boards/$(BOARD)/Makefile)","")
    KEYBOARD_BOARD_DIR = $(KEYBOARD_PATH_1)/boards/
endif

RIOT_INCS := $(shell $(MAKE) -C platforms/riot/stub BOARD=$(BOARD) KEYMAP_OUTPUT=$(abspath $(KEYMAP_OUTPUT)) KEYBOARD_OUTPUT=$(abspath $(KEYBOARD_OUTPUT))  KEYBOARD_BOARD_DIR=$(KEYBOARD_BOARD_DIR) dump_includes)
RIOT_BODGE_CFLAGS += $(RIOT_INCS) $(CFLAGS) -include $(KEYMAP_OUTPUT)/$(BOARD)/riotbuild/riotbuild.h -include $(KEYBOARD_OUTPUT)/src/riot_usb.h

sizeafter: $(BUILD_DIR)/$(TARGET).bin

$(KEYBOARD_OUTPUT)/src/riot_usb.h:
	$(shell $(QMK_BIN) generate-riot-header --quiet --keyboard $(KEYBOARD) --output $(KEYBOARD_OUTPUT)/src/riot_usb.h)

generated-files: $(KEYBOARD_OUTPUT)/src/riot_usb.h

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(MAKE) -C platforms/riot/stub BOARD=$(BOARD) KEYMAP_OUTPUT=$(abspath $(KEYMAP_OUTPUT)) KEYBOARD_OUTPUT=$(abspath $(KEYBOARD_OUTPUT)) KEYBOARD_BOARD_DIR=$(KEYBOARD_BOARD_DIR) QWER="$(CONFIG_H)" ASDF=$(abspath $(KEYMAP_OUTPUT)/obj.txt) | sed 's/"make" -C/$(MSG_COMPILING)/'
	$(COPY) $(KEYMAP_OUTPUT)/$(BOARD)/qmk_firmware.bin $(BUILD_DIR)/$(TARGET).bin

bin: $(BUILD_DIR)/$(TARGET).bin sizeafter
	$(COPY) $(BUILD_DIR)/$(TARGET).bin $(TARGET).bin;
