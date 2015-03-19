PROJECT = infinity

TMK_DIR = ../..
MBED_DIR = $(TMK_DIR)/mbed-sdk

#VPATH += $(MBED_DIR):$(TMK_DIR)
vpath %.s .:$(MBED_DIR):$(TMK_DIR)
vpath %.c .:$(MBED_DIR):$(TMK_DIR)
vpath %.cpp .:$(MBED_DIR):$(TMK_DIR)

OBJDIR = ./build

OBJECTS = \
	$(OBJDIR)/matrix.o \
	$(OBJDIR)/keymap_common.o \
	$(OBJDIR)/led.o \
	$(OBJDIR)/main.o

ifdef KEYMAP
    OBJECTS := $(OBJDIR)/keymap_$(KEYMAP).o $(OBJECTS)
else
    OBJECTS := $(OBJDIR)/keymap.o $(OBJECTS)
endif

CONFIG_H = config.h

INCLUDE_PATHS = -I.


# Build Options
#   Comment out to disable
#BOOTMAGIC_ENABLE = yes
#MOUSEKEY_ENABLE = yes


include mbed-infinity.mk
include $(TMK_DIR)/tool/mbed/mbed.mk
include $(TMK_DIR)/tool/mbed/common.mk
include $(TMK_DIR)/tool/mbed/gcc.mk

program: $(OBJDIR)/$(PROJECT).bin
	dfu-util -D $(OBJDIR)/$(PROJECT).bin
