PROJECT = mbed_onekey

TMK_DIR = ../..
MBED_DIR = $(TMK_DIR)/mbed-sdk

#VPATH += $(MBED_DIR):$(TMK_DIR)
vpath %.s .:$(MBED_DIR):$(TMK_DIR)
vpath %.c .:$(MBED_DIR):$(TMK_DIR)
vpath %.cpp .:$(MBED_DIR):$(TMK_DIR)

OBJDIR = ./build

OBJECTS = \
	$(OBJDIR)/./main.o

CONFIG_H = config.h

SYS_OBJECTS = 

INCLUDE_PATHS = -I.

LIBRARY_PATHS = 
LIBRARIES = 

# Build Options
#   Comment out to disable
#BOOTMAGIC_ENABLE = yes
#MOUSEKEY_ENABLE = yes


include $(TMK_DIR)/tool/mbed/mbed.mk
include $(TMK_DIR)/tool/mbed/common.mk
include $(TMK_DIR)/tool/mbed/gcc.mk
