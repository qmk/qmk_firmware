#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

MCU          = at90usb1287
ARCH         = AVR8
F_CPU        = 1000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = HID_EEPROM_Loader
SRC          = $(TARGET).c
LUFA_PATH    = ../../../LUFA
CC_FLAGS     =
LD_FLAGS     =
OBJECT_FILES = InputEEData.o

# Default target
all:

# Determine the AVR sub-architecture of the build main application object file
FIND_AVR_SUBARCH = avr$(shell avr-objdump -f $(TARGET).o | grep architecture | cut -d':' -f3 | cut -d',' -f1)

# Create a linkable object file with the input binary EEPROM data stored in the FLASH section
InputEEData.o: InputEEData.bin $(TARGET).o $(MAKEFILE_LIST)
	@echo $(MSG_OBJCPY_CMD) Converting \"$<\" to a object file \"$@\"
	avr-objcopy -I binary -O elf32-avr -B $(call FIND_AVR_SUBARCH) --rename-section .data=.progmem.data,contents,alloc,readonly,data $< $@

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
