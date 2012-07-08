#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

MCU          = at90usb1287
ARCH         = AVR8
F_CPU        = 1000000
F_USB        = $(F_CPU)
OPTIMIZATION = 0
TARGET       = HID_EEPROM_Loader
SRC          = $(TARGET).c
LUFA_PATH    = ../../../LUFA/
CC_FLAGS     = 
LD_FLAGS     =
OBJECT_FILES = InputEEData.o

# Default target
all: InputEEData.o hex

.PHONY: InputEEData.o
InputEEData.o: InputEEData.bin $(TARGET).o $(MAKEFILE_LIST)
	@echo $(MSG_OBJCPY_CMD) Converting \"$<\" to a object file \"$@\"
	avr-objcopy -I binary -O elf32-avr -B avr$(shell avr-objdump -f $(TARGET).o | grep architecture | cut -d':' -f3 | cut -d',' -f1) \
	  --rename-section .data=.progmem.data,contents,alloc,readonly,data \
	  --redefine-sym _binary_$(basename $@)_bin_start=$(basename $@) \
	  --redefine-sym _binary_$(basename $@)_bin_size=$(basename $@)_size_sym \
	  $< $@

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa.core.in
include $(LUFA_PATH)/Build/lufa.sources.in
include $(LUFA_PATH)/Build/lufa.build.in
include $(LUFA_PATH)/Build/lufa.cppcheck.in
include $(LUFA_PATH)/Build/lufa.doxygen.in
include $(LUFA_PATH)/Build/lufa.dfu.in
include $(LUFA_PATH)/Build/lufa.hid.in
include $(LUFA_PATH)/Build/lufa.avrdude.in
include $(LUFA_PATH)/Build/lufa.atprogram.in
